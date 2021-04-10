/* FILE NAME: RNDMTL.C
 * PROGRAMMER: AG6
 * DATE: 23.01.2019
 * PURPOSE:.
 */

#include "rndres.h"

/* Material resource table and size */
ag6MATERIAL AG6_RndMaterials[AG6_RESOURCE_TABLE_SIZE];
int AG6_RndMaterialsSize;

/* Add material function.
 * ARGUMENTS:
 *   - material data structure pointer:
 *       ag6MATERIAL *Mtl;
 * RETURNS:
 *   (int) material table index or -1 if error is occured.
 */
int AG6_RndMaterialAdd( ag6MATERIAL *Mtl )
{
  int i;

  /* Look for exists material */
  for (i = 0; i < AG6_RndMaterialsSize; i++)
    if (strcmp(AG6_RndMaterials[i].Name, Mtl->Name) == 0)
      break;

  if (i >= AG6_RESOURCE_TABLE_SIZE)
    return -1;

  AG6_RndMaterials[AG6_RndMaterialsSize] = *Mtl;
  return AG6_RndMaterialsSize++;
} /* End of 'AG6_RndMaterialAdd' function */

/* Material apply function.
 * ARGUMENTS:
 *   - material table index:
 *       int MtlNo;
 * RETURNS:
 *   (UINT) apply result shader program identifier.
 */
UINT AG6_RndMaterialApply( int MtlNo )
{
  int loc, i;
  ag6MATERIAL *mtl;
  UINT ProgId;

  /* Correct material number */
  if (MtlNo < 0 || MtlNo >= AG6_RndMaterialsSize)
    MtlNo = 0;
  mtl = &AG6_RndMaterials[MtlNo];

  /* Correct shader number */
  if (mtl->ShdNo < 0 || mtl->ShdNo >= AG6_RndShadersSize)
    ProgId = AG6_RndShaders[0].PrgNo;
  else
    ProgId = AG6_RndShaders[mtl->ShdNo].PrgNo;

  glUseProgram(ProgId);

  /* Setup illumination coefficients */
  if ((loc = glGetUniformLocation(ProgId, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(ProgId, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(ProgId, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(ProgId, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(ProgId, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Texture apply */
  for (i = 0; i < 8; i++)
  {
    int is = FALSE;
    static char TexName[] = "IsTexture0";

    TexName[sizeof(TexName) - 2] = '0' + i;
    glActiveTexture(GL_TEXTURE0 + i);
    if (mtl->Tex[i] >= 0 && mtl->Tex[i] < AG6_RndTexturesSize)
    {
      is = TRUE;
      glBindTexture(GL_TEXTURE_2D, AG6_RndTextures[mtl->Tex[i]].TexId);
    }
    else
      glBindTexture(GL_TEXTURE_2D, 0);
    if ((loc = glGetUniformLocation(ProgId, TexName)) != -1)
      glUniform1i(loc, is);
  }
  return ProgId;
} /* End of 'AG6_RndMaterialApply' function */




/* END OF 'RNDMTL.C' FILE */

