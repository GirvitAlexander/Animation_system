/* FILE NAME: U_GEOM.C
 * PROGRAMMER: AG6
 * DATE: 15.02.2019
 * PURPOSE: ANIMATIOM SYSTEM
 */

#include "rndres.h"
#include "anim.h"

typedef struct tagag6UNIT_GEOM ag6UNIT_GEOM;
typedef struct tagag6UNIT_GEOM
{
  UNIT_BASE_FIELDS;
  ag6PRIM Pr;
  float Step;
};

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_GEOM *Uni, ag6ANIM *Ani )
{
  AG6_RndPrimFree(&Uni->Pr);
} /* End of 'AG6_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitRender( ag6UNIT_GEOM *Uni, ag6ANIM *Ani )
{
  glDepthMask(FALSE);
  Uni->Step += Ani->DeltaTime * 10;
  AG6_RndPrimDraw(&Uni->Pr, MatrTranslate(VecSet(sin(Uni->Step) * 30, sin(Uni->Step) * 50, sin(Uni->Step) * 10)));
  glDepthMask(TRUE);
} /* End of 'AG6_UnitRender' function */

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_GEOM *Uni, ag6ANIM *Ani )
{
  ag6MATERIAL mtl;

  //mtl.Tex[0] = AG6_RndTextureAddFromFile("DUST_1.tga");
  mtl.Tex[1] = AG6_TabTex;
  mtl.Tex[2] = AG6_PermTex;
  
  mtl.ShdNo = AG6_RndShaderAdd("GEOM");
  AG6_RndPrimCreate(&Uni->Pr, AG6_PRIM_TRIMESH, NULL, 4, NULL, 6);
  Uni->Pr.MtNo = AG6_RndMaterialAdd(&mtl);
} /* End of 'AG6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitResponse( ag6UNIT_GEOM *Uni, ag6ANIM *Ani )
{
} /* End of 'AG6_UnitResponse' function */

/* Unit axe creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_UnitCreateGeom( VOID )
{
  ag6UNIT_GEOM *Uni;


  if ((Uni = (ag6UNIT_GEOM *)AG6_AnimUnitCreate(sizeof(ag6UNIT_GEOM))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Close = (VOID *)AG6_UnitClose;

  return (ag6UNIT *)Uni;
} /* End of 'AG6_UnitCreateBall' function */

/* END OF 'U_GEOM.C' FILE */