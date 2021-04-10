/* FILE NAME: U_COW.C
 * PROGRAMMER: AG6
 * DATE: 07.01.2019
 * PURPOSE: 
 */

#include <time.h>
#include "anim.h"

typedef struct tagag6UNIT_COW ag6UNIT_CAR;
struct tagag6UNIT_CAR
{
  UNIT_BASE_FIELDS;
  ag6PRIM Car;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_CAR *Uni, ag6ANIM *Ani )
{
  AG6_RndPrimLoad(&Uni->Car, "x6.object");
} /* End of 'AG6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_CAR *Uni, ag6ANIM *Ani )
{
  AG6_RndPrimFree(&Uni->Car);
} /* End of 'AG6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitResponse( ag6UNIT_CAR *Uni, ag6ANIM *Ani )
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
static VOID AG6_UnitRender( ag6UNIT_CAR *Uni, ag6ANIM *Ani )
{
  SelectObject(AG6_hRndDC, GetStockObject(NULL_BRUSH));
  AG6_RndPrimDraw(&Uni->Cow, MatrMulMatr(MatrRotateX(-90),UnitMatrix));
} /* End of 'AG6_UnitRender' function */

/* Car creation function.
 * ARGUMENTS: none;
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_AnimUnitCreateCar( VOID )
{
  ag6UNIT_CAR *Uni;

  /* Memory allocation */
  if ((Uni = (ag6UNIT_CAR *)AG6_AnimUnitCreate(sizeof(ag6UNIT_CAR))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Close = (VOID *)AG6_UnitClose;
  return (ag6UNIT *)Uni;
} /* End of 'AG6_AnimUnitCreateCar' function */

/* END OF 'U_CAR.C' FILE */