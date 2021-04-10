/* FILE NAME: U_AXE.C
 * PROGRAMMER: ag6
 * DATE: 29.01.2019
 * PURPOSE: ANIMATIOM SYSTEM.
 */

#include "anim.h"
#include "rndres.h"

typedef struct tagag6UNIT_AXE ag6UNIT_AXE;
typedef struct tagag6UNIT_AXE
{
  UNIT_BASE_FIELDS;
  ag6PRIM Axe;
};


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_AXE *Uni, ag6ANIM *Ani )
{
  int i;

  ag6VERTEX av[] =
  {
    {{0, 0, 0}, {0}, {0}, {1, 0, 0, 1}}, {{30000, 0, 0}, {0}, {0}, {1, 0, 0, 1}},
    {{0, 0, 0}, {0}, {0}, {0, 1, 0, 1}}, {{0, 30000, 0}, {0}, {0}, {0, 1, 0, 1}},
    {{0, 0, 0}, {0}, {0}, {0, 0, 1, 1}}, {{0, 0, 30000}, {0}, {0}, {0, 0, 1, 1}},
  };
  ag6MATERIAL mtl = {"Axe draw"};

  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;

  mtl.ShdNo = AG6_RndShaderAdd("AXE");
  AG6_RndPrimCreate(&Uni->Axe, AG6_PRIM_LINES, av, 6, NULL, 0);
  Uni->Axe.MtNo = AG6_RndMaterialAdd(&mtl);
} /* End of 'AG6_UnitInit' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitRender( ag6UNIT_AXE *Uni, ag6ANIM *Ani )
{
  AG6_RndPrimDraw(&Uni->Axe, MatrIdentity());
} /* End of 'AG6_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_UnitCreateAxe( VOID )
{
  ag6UNIT_AXE *Uni;


  if ((Uni = (ag6UNIT_AXE *)AG6_AnimUnitCreate(sizeof(ag6UNIT_AXE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;

  return (ag6UNIT *)Uni;
} /* End of 'AG6_UnitCreateBall' function */

/* END OF 'U_AXE.C' FILE */
