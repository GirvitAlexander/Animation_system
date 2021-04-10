/* FILE NAME: U_CTRL.C
 * PROGRAMMER: ag6
 * DATE: 29.01.2019
 * PURPOSE: ANIMATIOM SYSTEM.
 */

#include "anim.h"

typedef struct tagag6UNIT_CTRL ag6UNIT_CTRL;
typedef struct tagag6UNIT_CTRL
{
  UNIT_BASE_FIELDS;
  VEC CamDir, CamLoc, CamRight, CamUp, CamAt;
  DBL RotX, RotY;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_CTRL *Uni, ag6ANIM *Ani )
{
  Uni->CamDir = VecSet(1, 0, 0);
  Uni->CamRight = VecSet(0, 0, 1);
  Uni->CamUp = VecSet(0, 1, 0);
  Uni->CamLoc = VecSet(18, 18, 18);
  Uni->CamAt = VecSet(0, 0, 0);
} /* End of 'AG6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitResponse( ag6UNIT_CTRL *Uni, ag6ANIM *Ani )
{
  if (Ani->KeysClick['W'] && Ani->Keys[VK_SHIFT])
  {
    if (Ani->IsWireFrame)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Ani->IsWireFrame = !Ani->IsWireFrame;
  }
  if (Ani->Keys[VK_ESCAPE])
    exit(0);

  if (Ani->Keys[VK_LBUTTON])
    Uni->CamLoc =
      PointTransform(Uni->CamLoc, MatrRotateY(Ani->DeltaTime * 100 * Ani->Mdx)),
    Uni->CamLoc =
      PointTransform(Uni->CamLoc, MatrRotateX(Ani->DeltaTime * 100 * Ani->Mdy));

  Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->CamLoc, -Ani->DeltaTime * Ani->Mdz * 0.090));

  Uni->CamLoc =
    PointTransform(Uni->CamLoc, MatrRotateY(Ani->DeltaTime * 100 * Ani->JX)),
  Uni->CamLoc =
    PointTransform(Uni->CamLoc, MatrRotateX(Ani->DeltaTime * 100 * Ani->JY));

  Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->CamLoc, Ani->DeltaTime * (Ani->Keys[VK_DOWN] - Ani->Keys[VK_UP])));
  Uni->CamLoc = PointTransform(Uni->CamLoc, MatrRotateY(Ani->DeltaTime * 40 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT])));
 
  AG6_RndCamSet(Uni->CamLoc, Uni->CamAt, Uni->CamUp);
} /* End of 'AG6_UnitResponse' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_UnitCreateCtrl( VOID )
{
  ag6UNIT_CTRL *Uni;


  if ((Uni = (ag6UNIT_CTRL *)AG6_AnimUnitCreate(sizeof(ag6UNIT_CTRL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Response = (VOID *)AG6_UnitResponse;

  return (ag6UNIT *)Uni;
} /* End of 'AG6_UnitCreateCtrl' function */

/* END OF 'U_CTRL.C' FILE */
