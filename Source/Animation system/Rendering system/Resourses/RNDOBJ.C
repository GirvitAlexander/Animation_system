/* FILE NAME: RNDMTL.C
 * PROGRAMMER: AG6
 * DATE: 25.01.2019
 * PURPOSE:.
 */

#include "rnd.h"
#include "rndres.h"

/* Create object function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 *   - primitives count:
 *       int NumOfPrims;
 * RETUNRS:
 *   (int) TRUE if successful, FALSE otherwise.
 */
int AG6_RndObjCreate( ag6OBJ *Obj, int NumOfPrims )
{
  memset(Obj, 0, sizeof(ag6OBJ));
  if ((Obj->Prims = malloc(sizeof(ag6PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Obj->Prims, 0, sizeof(ag6PRIM) * NumOfPrims);
  Obj->NumOfPrims = NumOfPrims;
  Obj->Trans = MatrIdentity();
  return TRUE;
} /* End of 'AG6_RndObjCreate' function */

/* Free object function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 * RETUNRS: None.
 */
VOID AG6_RndObjFree( ag6OBJ *Obj )
{
  if (Obj->Prims != NULL)
  {
    int i;

    for (i = 0; i < Obj->NumOfPrims; i++)
      AG6_RndPrimFree(&Obj->Prims[i]);
    free(Obj->Prims);
  }
  memset(Obj, 0, sizeof(ag6OBJ));
} /* End of 'AG6_RndObjFree' function */

/* Load object from CGSG '.G3DM' file function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 *   - file name:
 *       char *FileName;
 * RETUNRS:
 *   (int) TRUE if successful, FALSE otherwise.
 */
int AG6_RndObjLoad( ag6OBJ *Obj, char *FileName )
{
  FILE *F;
  int p, m, t, mtl_start, txt_start;
  unsigned long int Sign;
  unsigned long int NumOfPrims;
  unsigned long int NumOfMaterials;
  unsigned long int NumOfTextures;

  memset(Obj, 0, sizeof(ag6OBJ));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  if (fread(&Sign, 4, 1, F) != 1 ||
      Sign != *(unsigned long int *)"G3DM" ||
      fread(&NumOfPrims, 4, 1, F) != 1 ||
      fread(&NumOfMaterials, 4, 1, F) != 1 ||
      fread(&NumOfTextures, 4, 1, F) != 1 ||
      !AG6_RndObjCreate(Obj, NumOfPrims))
  {
    fclose(F);
    return FALSE;
  }
  for (p = 0; p < NumOfPrims; p++)
  {
    unsigned long int NumOfVertexes;
    unsigned long int NumOfFacetIndexes;  /* num of facets * 3 */
    unsigned long int MtlNo;
    ag6VERTEX *V;
    int *I, size;

    fread(&NumOfVertexes, 4, 1, F);
    fread(&NumOfFacetIndexes, 4, 1, F);
    fread(&MtlNo, 4, 1, F);

    size = sizeof(ag6VERTEX) * NumOfVertexes + sizeof(int) * NumOfFacetIndexes;
    if ((V = malloc(size)) == NULL)
    {
      AG6_RndObjFree(Obj);
      fclose(F);
      return FALSE;
    }
    memset(V, 0, size);
    I = (int *)(V + NumOfVertexes);
    fread(V, 1, size, F);
    AG6_RndPrimCreate(&Obj->Prims[p], AG6_PRIM_TRIMESH, V, NumOfVertexes, I, NumOfFacetIndexes);
    Obj->Prims[p].MtNo = MtlNo;
    free(V);
  }

  /* Materials */
  mtl_start = AG6_RndMaterialsSize;
  for (m = 0; m < NumOfMaterials; m++)
  {
    ag6MATERIAL mtl = {0};
    char ShaderString[300]; /* Additional shader information */
    unsigned long int Shader;       /* Shader number (uses after load into memory) */

    fread(&mtl, sizeof(ag6MATERIAL) - sizeof(int), 1, F);
    fread(ShaderString, 1, 300, F);
    fread(&Shader, 4, 1, F);
    AG6_RndMaterialAdd(&mtl);
  }
  for (p = 0; p < NumOfPrims; p++)
  {
    Obj->Prims[p].MtNo += mtl_start;
  }

  /* Textures */
  txt_start = AG6_RndTexturesSize;
  for (t = 0; t < NumOfTextures; t++)
  {
    char Name[300]; /* Texture name */
    unsigned long int W, H;     /* Texture image size in pixels */
    unsigned long int C;        /* Texture image components (1-mono, 3-bgr or 4-bgra) */
    unsigned char *TextureImage;

    fread(Name, 1, 300, F);
    fread(&W, 4, 1, F);
    fread(&H, 4, 1, F);
    fread(&C, 4, 1, F);
    if ((TextureImage = malloc(W * H * C)) != NULL)
    {
      fread(TextureImage, C, W * H, F);
      AG6_RndTextureAdd(Name, W, H, TextureImage);
      free(TextureImage);
    }
  }
  for (m = 0; m < NumOfMaterials; m++)
    for (t = 0; t < 8; t++)
      if (AG6_RndMaterials[m].Tex[t] != -1)
        AG6_RndMaterials[m].Tex[t] += txt_start;

  fclose(F);
  return TRUE;
} /* End of 'AG6_RndObjLoad' function */

/* Draw object function.
 * ARGUMENTS:
 *   - object structure:
 *       ag6OBJ *Obj;
 *   - object all primitives transformation matrix:
 *       MATR World;
 * RETUNRS: None.
 */
VOID AG6_RndObjDraw( ag6OBJ *Obj, MATR World )
{
  int i, mtl_no;
  MATR M = MatrMulMatr(Obj->Trans, World);

  AG6_RndShdAddOn0 = Obj->NumOfPrims;
  /* Draw non transparent primitives */
  for (i = 0; i < Obj->NumOfPrims; i++)
  {
    AG6_RndShdAddOn1 = i;
    mtl_no = Obj->Prims[i].MtNo;
    if (mtl_no < 0 || mtl_no >= AG6_RndMaterialsSize)
      mtl_no = 0;
    if (AG6_RndMaterials[mtl_no].Trans == 1)
      AG6_RndPrimDraw(&Obj->Prims[i], M);
  }

  /* Draw transparent back faced primitives */
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  for (i = 0; i < Obj->NumOfPrims; i++)
  {
    AG6_RndShdAddOn1 = i;
    mtl_no = Obj->Prims[i].MtNo;
    if (mtl_no < 0 || mtl_no >= AG6_RndMaterialsSize)
      mtl_no = 0;
    if (AG6_RndMaterials[mtl_no].Trans != 1)
      AG6_RndPrimDraw(&Obj->Prims[i], M);
  }

  /* Draw transparent front faced primitives */
  glCullFace(GL_BACK);
  for (i = 0; i < Obj->NumOfPrims; i++)
  {
    AG6_RndShdAddOn1 = i;
    mtl_no = Obj->Prims[i].MtNo;
    if (mtl_no < 0 || mtl_no >= AG6_RndMaterialsSize)
      mtl_no = 0;
    if (AG6_RndMaterials[mtl_no].Trans != 1)
      AG6_RndPrimDraw(&Obj->Prims[i], M);
  }
  glDisable(GL_CULL_FACE);
} /* End of 'AG6_RndObjDraw' function */


/* END OF 'RNDOBJ.C' FILE */