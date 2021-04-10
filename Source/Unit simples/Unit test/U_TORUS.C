/* FILE NAME: U_TORUS.C
 * PROGRAMMER: AG6
 * DATE: 30.01.2019
 * PURPOSE:. 
 */

#include "anim.h"
#include "rndres.h"

typedef struct tagag6UNIT_TORUS ag6UNIT_TORUS;
struct tagag6UNIT_TORUS
{
  UNIT_BASE_FIELDS;
  ag6GRID Torus;
  ag6PRIM Pr;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_TORUS *Uni, ag6ANIM *Ani )
{
  AG6_RndGridCreate(&Uni->Torus, 100, 100);
  AG6_RndGridCreateSphere(&Uni->Torus, Uni->Torus.H, Uni->Torus.W, VecSet(1, 0, 1), 100.0, 50.0);
  AG6_RndPrimFromGrid(&Uni->Pr, &Uni->Torus);
} /* End of 'AG6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_TORUS *Uni, ag6ANIM *Ani )
{
  AG6_RndGridFree(&Uni->Torus);
  AG6_RndPrimFree(&Uni->Pr);
} /* End of 'AG6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitResponse( ag6UNIT_TORUS *Uni, ag6ANIM *Ani )
{
} /* End of 'AG6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitRender( ag6UNIT_TORUS *Uni, ag6ANIM *Ani )
{
  AG6_RndPrimDraw(&Uni->Pr, MatrIdentity());
} /* End of 'AG6_UnitRender' function */

/* Torus creation function.
 * ARGUMENTS: none;
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_AnimUnitCreateTorus( VOID )
{
  ag6UNIT_TORUS *Uni;

  /* Memory allocation */
  if ((Uni = (ag6UNIT_TORUS *)AG6_AnimUnitCreate(sizeof(ag6UNIT_TORUS))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Close = (VOID *)AG6_UnitClose;
  return (ag6UNIT *)Uni;
} /* End of 'AG6_AnimUnitCreateSphere' function */

/* END OF 'U_TORUS.C' FILE */