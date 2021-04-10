/* FILE NAME: RND.C
 * PROGRAMMER: AG6
 * DATE: 08.01.2019
 * PURPORSE: .
 */


#include "unit.h"
#include "rnd.h"
#include "rndres.h"


typedef struct tagag6UNIT_TEST ag6UNIT_TEST;
struct tagag6UNIT_TEST
{
  UNIT_BASE_FIELDS;
  ag6PRIM Test;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_TEST *Uni, ag6ANIM *Ani )
{
  ag6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{200, 0, 0}, {4, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 100, 0}, {0, 2}, {0, 0, 1}, {1, 1, 1, 1}},
    {{200, 100, 0}, {4, 2}, {0, 0, 1}, {1, 1, 1, 1}},
  };
  int I[] =
  {
    0, 1, 2,
    2, 1, 3
  };
  ag6MATERIAL mtl =
  {
    "Sample material",
    {0.1, 0.1, 0.1}, {1, 1, 1}, {0, 0, 0}, 1,
    1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    -1
  };

  AG6_RndPrimCreate(&Uni->Test, AG6_PRIM_TRIMESH, V, 4, I, 6);
  mtl.Tex[0] = AG6_RndTextureAddFromFileg24("pyatack.g24");
  Uni->Test.MtNo = AG6_RndMaterialAdd(&mtl);
  Uni->Test.Type = AG6_PRIM_TRIMESH;

} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_TEST *Uni, ag6ANIM *Ani )
{
 
} /* End of 'AG6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitResponse( ag6UNIT_TEST *Uni, ag6ANIM *Ani )
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
static VOID AG6_UnitRender( ag6UNIT_TEST *Uni, ag6ANIM *Ani )
{
  SelectObject(AG6_hRndDC, GetStockObject(NULL_BRUSH));
  AG6_RndPrimDraw(&Uni->Test, MatrMulMatr(MatrTranslate(VecSet(-1, -80, 4)), MatrRotateX(180)));
} /* End of 'AG6_UnitRender' function */

ag6UNIT * AG6_UnitCreateTest( VOID )
{
  ag6UNIT_TEST *Uni;

  /* Memory allocation */
  if ((Uni = (ag6UNIT_TEST *)AG6_AnimUnitCreate(sizeof(ag6UNIT_TEST))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Close = (VOID *)AG6_UnitClose;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Render = (VOID *)AG6_UnitRender;
  return (ag6UNIT *)Uni;
} /* End of 'AG6_AnimUnitCreate' function */

/* END OF 'U_TEST.C' FILE*/