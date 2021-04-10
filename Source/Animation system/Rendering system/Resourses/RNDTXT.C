/* FILE NAME: RNDTXT.C
 * PROGRAMMER: AG6
 * DATE: 23.01.2019
 * PURPOSE:.
 */

#pragma pack(push, 1)
//#include <tgahead.h>
#pragma pack(pop)
#include "rndres.h"

/* Texture resource table and size */
ag6TEXTURE AG6_RndTextures[AG6_RESOURCE_TABLE_SIZE];
int AG6_RndTexturesSize;

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       char *FileName;
 * RETURNS:
 *   (int) texture table index or -1 if error is occured.
 */
int AG6_RndTextureAddFromFileg24( char *FileName )
{
  int tex = -1, w = 0, h = 0, x, y;
  unsigned long int *mem;
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return -1;
  fread(&w, 2, 1, F);
  fread(&h, 2, 1, F);
  if ((mem = malloc(w * h * 4)) != NULL)
  {
    unsigned long int d = 0;

    for (y = 0; y < h; y++)
      for (x = 0; x < w; x++)
      {
        fread(&d, 3, 1, F);
        d |= 0xFF000000;
        mem[(h - 1 - y) * w + x] = d;
      }
    tex = AG6_RndTextureAdd(FileName, w, h, mem);
    free(mem);
  }
  fclose(F);
  return tex;
} /* End of 'AG6_RndTextureAddFromFile' function */

/* Add texture image by image data function.
 * ARGUMENTS:
 *   - texture name:
 *       char *Name;
 *   - texture image size:
 *       int W, H;
 *   - texture image pixel color data (unsigned long int colors):
 *       VOID *ImageData;
 * RETURNS:
 *   (int) texture table index or -1 if error is occured.
 */
int AG6_RndTextureAdd( char *Name, int W, int H, VOID *ImageData )
{
  if (AG6_RndTexturesSize >= AG6_RESOURCE_TABLE_SIZE)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &AG6_RndTextures[AG6_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, AG6_RndTextures[AG6_RndTexturesSize].TexId);

  /* Upload texture */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, ImageData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  strncpy(AG6_RndTextures[AG6_RndTexturesSize].Name, Name, AG6_MATERIAL_NAME_SIZE - 1);
  AG6_RndTextures[AG6_RndTexturesSize].W = W;
  AG6_RndTextures[AG6_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return AG6_RndTexturesSize++;
} /* End of 'AG6_RndTextureAdd' function */

/* Remove texture from resource table function.
 * ARGUMENTS:
 *   - texture table index:
 *       int TexNo;
 * RETURNS: None.
 */
VOID AG6_RndTextureDelete( int TexNo )
{
  if (TexNo < 0 || TexNo >= AG6_RndTexturesSize)
    return;
  glDeleteTextures(1, &AG6_RndTextures[TexNo].TexId);
  memset(&AG6_RndTextures[TexNo], 0, sizeof(ag6TEXTURE));
} /* End of 'AG6_RndTextureDelete' function */


/* END OF 'RNDTXT.C' FILE */