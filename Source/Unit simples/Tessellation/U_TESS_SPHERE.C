/* FILE NAME: U_TESS.C
 * PROGRAMMER: AG6
 * DATE: 15.02.2019
 * PURPOSE: ANIMATIOM SYSTEM
 */

#include "rndres.h"
#include "anim.h"

#define NUM_OF_VERTEX 8

typedef struct tagag6UNIT_TESS ag6UNIT_TESS;
typedef struct tagag6UNIT_TESS
{
  UNIT_BASE_FIELDS;
  ag6PRIM Pr;
  ag6OBJ Line;
  ag6VERTEX *V;
};


/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_TESS *Uni, ag6ANIM *Ani )
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
static VOID AG6_UnitRender( ag6UNIT_TESS *Uni, ag6ANIM *Ani )
{
  int i;

  glLineWidth(3);
  for (i = 0; i < NUM_OF_VERTEX; i++)
    AG6_RndPrimDraw(&Uni->Pr, MatrMulMatr(UnitMatrix, MatrTranslate(Uni->V[i].P)));
} /* End of 'AG6_UnitRender' function */

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_TESS *Uni, ag6ANIM *Ani )
{
  ag6MATERIAL mtl = {"SPHERE Material"};
  
  if ((Uni->V = malloc(sizeof(ag6VERTEX) * NUM_OF_VERTEX)) == NULL)
	return;
  memset(Uni->V, 0, sizeof(ag6VERTEX) * NUM_OF_VERTEX);

  Uni->V[0].P = VecSet(0, 11, 0);
  Uni->V[1].P = VecSet(11, 11, 0);
  Uni->V[2].P = VecSet(11, 0, 0);
  Uni->V[3].P = VecSet(22, 11, 0);
  Uni->V[4].P = VecSet(4, 20, 0);
  Uni->V[5].P = VecSet(2, 10, 0);
  Uni->V[6].P = VecSet(10, 15, 5);
  Uni->V[7].P = VecSet(20, -20, 0);

  mtl.ShdNo = AG6_RndShaderAdd("SPHERE");
  AG6_RndPrimCreate(&Uni->Pr, AG6_PRIM_PATCH1, Uni->V, 1, NULL, 0);
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
static VOID AG6_UnitResponse( ag6UNIT_TESS *Uni, ag6ANIM *Ani )
{
} /* End of 'AG6_UnitResponse' function */

/* Unit axe creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_UnitCreateSphere( VOID )
{
  ag6UNIT_TESS *Uni;


  if ((Uni = (ag6UNIT_TESS *)AG6_AnimUnitCreate(sizeof(ag6UNIT_TESS))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Close = (VOID *)AG6_UnitClose;

  return (ag6UNIT *)Uni;
} /* End of 'AG6_UnitCreateTess' function */

/* END OF 'U_TESS.C' FILE */
