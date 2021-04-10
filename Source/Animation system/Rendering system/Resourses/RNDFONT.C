/* FILE NAME: RNDFONT.C
 * PROGRAMMER: AG6
 * DATE: 01.02.2019
 * PURPOSE: 
 */
#include <stdio.h>
#include "rndfont.h"

/* Font load function.
 * ARGUMENTS:
 *   - font structure pointer:
 *       ag6FONT *Fnt;
 *   - font file name:
 *       char *FileName;
 * RETURNS:
 *   (int) TRUE if success, FALSE otherwise.
 */
int AG6_RndFntLoad( ag6FONT *Fnt, char *FileName )
{
  unsigned long int Sign;
  FILE *F;
  ag6MATERIAL mtl = {{0}};
  char
    Path[_MAX_PATH],
    Drive[_MAX_DRIVE],
    Dir[_MAX_DIR],
    FName[_MAX_FNAME],
    FExt[_MAX_EXT],
    Drive1[_MAX_DRIVE],
    Dir1[_MAX_DIR],
    FName1[_MAX_FNAME],
    FExt1[_MAX_EXT];

  memset(Fnt, 0, sizeof(ag6FONT));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  fread(&Sign, 4, 1, F);
  if (Sign != *(unsigned long int *)"BMF\x03")
  {
    fclose(F);
    return FALSE;
  }
  while (TRUE)
  {
    int i, ch;
    unsigned char BlkId;
    unsigned long int BlkLen, pos;

    if (fread(&BlkId, 1, 1, F) != 1 ||
        fread(&BlkLen, 4, 1, F) != 1)
      break;
    pos = ftell(F);

    switch (BlkId)
    {
    case 1:
      fread(&Fnt->Info, sizeof(ag6FNTINFO), 1, F);
      i = 0;
      while ((ch = fgetc(F)) != EOF && ch != 0)
        if (i < AG6_MATERIAL_NAME_SIZE - 1)
          Fnt->FontName[i++] = ch;
      Fnt->FontName[i] = 0;
      break;
    case 2:
      fread(&Fnt->Common, sizeof(ag6FNTCOMMON), 1, F);
      break;
    case 3:
      i = 0;
      while ((ch = fgetc(F)) != EOF && ch != 0)
        if (i < AG6_MATERIAL_NAME_SIZE - 1)
          Fnt->TextureFileName[i++] = ch;
      Fnt->TextureFileName[i] = 0;
      _splitpath(FileName, Drive, Dir, FName, FExt);
      _splitpath(Fnt->TextureFileName, Drive1, Dir1, FName1, FExt1);
      _makepath(Path, Drive, Dir, FName1, ".TGA");
      //Fnt->TexNo = AG6_RndTextureAddFromFile(Path);
      break;
    case 4:
      for (i = 0; i < BlkLen / sizeof(ag6FNTCHARS); i++)
      {
        ag6FNTCHARS c;

        fread(&c, sizeof(ag6FNTCHARS), 1, F);
        if (c.Id < 256)
          Fnt->Chars[c.Id] = c;
      }
      break;
    }

    fseek(F, pos + BlkLen, SEEK_SET);
  }
  strncpy(mtl.Name, Fnt->FontName, AG6_MATERIAL_NAME_SIZE - 1);
  mtl.ShdNo = AG6_RndShaderAdd("FONT");
  memset(mtl.Tex, -1, sizeof(mtl.Tex));
  mtl.Tex[0] = Fnt->TexNo;

  Fnt->MtlNo = AG6_RndMaterialAdd(&mtl);

  fclose(F);
  return TRUE;
} /* End of 'AG6_RndFntLoad' function */

/* Loading primitive from font function.
 * ARGUMENTS:
 *   - PRIM struct:
 *       ag6PRIM *Pr;
 *   - FONT struct:
 *       ag6GFONT *Fnt;
 * RETURNS: None.
 */
VOID AG6_RndPrimFromFont( ag6PRIM *Pr, char *Str, ag6FONT *Fnt, FLT FontSize, VEC4 Color )
{
  int i, noofv = 0, *Ind, len = strlen(Str);
  ag6FNTCHARS *cd = &Fnt->Chars[(unsigned char)*Str];
  FLT
    h_size = (FLT)Fnt->Common.LineHeight / (FLT)Fnt->Common.ScaleH,  
    base = (FLT)Fnt->Common.Base / (FLT)Fnt->Common.ScaleH,          
    c_size = FontSize / base,
    posx = 0,
    posy = 0;
  ag6VERTEX *vptr, *V;

  memset(Pr, 0, sizeof(ag6PRIM));
  if ((V = malloc(sizeof(ag6VERTEX) * 4 * len + sizeof(int) * 5 * len)) == NULL)
    return;

  Ind = (int *)(V + len * 4);
  
  for (i = 0; i < len * 4; i++)
    V[i].C = Color, V[i].N = VecSet(0, 0, 1);

  vptr = V;
  while (*Str != 0)
  {
    if (*Str == '\n')
      posx = 0, posy -= base * c_size;
    else
      if ((cd = &Fnt->Chars[(unsigned char)*Str])->Id != 0)
      {
        FLT
          tx = (FLT)cd->X / (FLT)Fnt->Common.ScaleW,
          ty = (FLT)cd->Y / (FLT)Fnt->Common.ScaleH,
          tdx = (FLT)cd->Width / (FLT)Fnt->Common.ScaleW,
          tdy = (FLT)cd->Height / (FLT)Fnt->Common.ScaleH,
          xoff = (FLT)cd->XOffset / (FLT)Fnt->Common.ScaleW,
          yoff = (FLT)cd->YOffset / (FLT)Fnt->Common.ScaleH,
          xadv = (FLT)cd->XAdvance / (FLT)Fnt->Common.ScaleW;

        /* left-top */
        vptr->P = VecSet(posx + xoff * c_size, posy - yoff * c_size, 0);
        vptr++->T = Vec2Set(tx, 1 - ty);

        /* left-bottom */
        vptr->P = VecSet(posx + xoff * c_size, posy - (yoff + tdy) * c_size, 0);
        vptr++->T = Vec2Set(tx, 1 - (ty + tdy));

        /* right-top */
        vptr->P = VecSet(posx + (xoff + tdx) * c_size, posy - yoff * c_size, 0);
        vptr++->T = Vec2Set(tx + tdx, 1 - ty);

        /* right-bottom */
        vptr->P = VecSet(posx + (xoff + tdx) * c_size, posy - (yoff + tdy) * c_size, 0);
        vptr++->T = Vec2Set(tx + tdx, 1 - (ty + tdy));

        posx += xadv * c_size;
        noofv++;
      }
    Str++;
  }
  /* Fill index array */
  for (i = 0; i < noofv; i++)
  {
    Ind[i * 5 + 0] = i * 4 + 0;
    Ind[i * 5 + 1] = i * 4 + 1;
    Ind[i * 5 + 2] = i * 4 + 2;
    Ind[i * 5 + 3] = i * 4 + 3;
    Ind[i * 5 + 4] = -1;
  }
  AG6_RndPrimCreate(Pr, AG6_RND_PRIM_GRID, V, noofv * 4, Ind, noofv * 5 - 1);
  free(V);
} /* End of 'AG6_RndPrimFromFont' function */

/* Font program free function.
 * ARGUMENTS:
 *   - Font struct:
 *       ag6FONT *F;
 * RETURNS: None.
 */
VOID AG6_RndFontFree( ag6FONT *F )
{
  if (&F != NULL)
    free(&F);
  memset(F, 0, sizeof(ag6FONT));
} /* End of 'AG6_RndFontFree' function */

/* Create image function.
 * ARGUMENTS:
 *   - image structure:
 *       IMAGE *Img;
 *   - new image size in pixels:
 *       int W, H;
 * RETURNS:
 *   (int) TRUE if success, FALSE otherwise.
 */
int AG6_ImageCreate( ag6IMAGE *Img, int W, int H )
{
  int i;
  unsigned long int size;

  memset(Img, 0, sizeof(ag6IMAGE));

  /* Memory allocation */
  size = W * H * 4 + H * sizeof(unsigned long int *);
  if ((Img->Pixels = malloc(size)) == NULL)
    return FALSE;
  memset(Img->Pixels, 0, size);

  /* Fill structure */
  Img->W = W;
  Img->H = H;
  Img->Rows = (unsigned long int **)(Img->Pixels + W * H);
  Img->RowsARGB = (unsigned char (**)[4])Img->Rows;

  /* Setup all rows pointers */
  for (i = 0; i < H; i++)
    Img->Rows[i] = Img->Pixels + W * i;
  return TRUE;
} /* End of 'AG6_ImageCreate' function */

/* Free image function.
 * ARGUMENTS:
 *   - image structure:
 *       IMAGE *Img;
 * RETURNS: None.
 */
VOID AG6_ImageFree( ag6IMAGE *Img )
{
  if (Img->Pixels != NULL)
    free(Img->Pixels);
  memset(Img, 0, sizeof(ag6IMAGE));
} /* End of 'AG6_ImageFree' function */


/* END OF 'RNDFONT.C' FILE */