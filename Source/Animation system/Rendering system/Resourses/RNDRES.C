/* FILE NAME: RNDRES.C
 * PROGRAMMER: AG6
 * DATE: 23.01.2019
 * PURPOSE:.
 */

#include "rndres.h"

/* Rendering resource initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AG6_RndResInit( VOID )
{
  ag6MATERIAL DefMtl =
  {
    "Default material",
    {0.02, 0.02, 0.02}, {0.01, 0.01, 0.01}, {0.4, 0.4, 0.4}, 15.0, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    -1
  };

  /* Set all resource tables to zero size */
  AG6_RndMaterialsSize = 0;
  AG6_RndShadersSize = 0;
  AG6_RndTexturesSize = 0;

  /* Load default shader */
  DefMtl.ShdNo = AG6_RndShaderAdd("DEFAULT");

  /* Create default material */
  AG6_RndMaterialAdd(&DefMtl);
} /* End of 'AG6_RndResInit' function */

/* Rendering resource deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AG6_RndResClose( VOID )
{
  int i;

  /* Remove all resources */
  for (i = 0; i < AG6_RndShadersSize; i++)
    AG6_RndShaderDelete(i);
  for (i = 0; i < AG6_RndTexturesSize; i++)
    AG6_RndTextureDelete(i);

  /* Set all resource tables to zero size */
  AG6_RndMaterialsSize = 0;
  AG6_RndShadersSize = 0;
  AG6_RndTexturesSize = 0;
} /* End of 'AG6_RndResClose' function */


/* END OF 'RNDRES.C' FILE */