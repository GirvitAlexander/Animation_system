/* FILE NAME: U_TESS.C
 * PROGRAMMER: AG6
 * DATE: 15.02.2019
 * PURPOSE: ANIMATIOM SYSTEM
 */

#include "rndres.h"
#include "anim.h"

#define NUM_OF_VERTEX 10

typedef struct tagag6UNIT_TESS ag6UNIT_TESS;
typedef struct tagag6UNIT_TESS
{
  UNIT_BASE_FIELDS;
  ag6PRIM Pr;
  ag6OBJ Line;
  ag6GRID Gr;
};


VOID Besie( VEC P0, VEC P1, VEC P2, VEC P3, ag6PRIM *Pr, int N)
{
  DBL t, step;
  ag6VERTEX *V;
  int i;

  memset(Pr, 0, sizeof(ag6PRIM));
  if ((V = malloc(sizeof(ag6VERTEX) * N)) == NULL)
    return;

  memset(V, 0, sizeof(ag6VERTEX) * N);
  for (t = 0, step = 1 / (N - 1.0), i = 0; i < N; i++, t += step)
    V[i].P = VecAddVec(VecAddVec(VecMulNum(P0, (1 - t) * (1 - t) * (1 - t)), VecMulNum(P1, 3 * (1 - t) * (1 - t) * t)), VecAddVec(VecMulNum(P2, 3 * (1 - t) * t * t), VecMulNum(P1, t *  t * t)));
  AG6_RndPrimCreate(Pr, AG6_PRIM_LINES_STRIP, V, N, NULL, 0);
  free(V);
}


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
  AG6_RndPrimDraw(&Uni->Pr, UnitMatrix);
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
  ag6VERTEX *V;
  ag6MATERIAL mtl = {"Tess Material"};
  
  if ((V = malloc(sizeof(ag6VERTEX) * NUM_OF_VERTEX)) == NULL)
	return;
  memset(V, 0, sizeof(ag6VERTEX) * NUM_OF_VERTEX);

  V[0].P = VecSet(0, 0, 0);
  V[1].P = VecSet(0, 11, 0);
  V[2].P = VecSet(11, 11, 0);
  V[3].P = VecSet(11, 0, 0);
  V[4].P = VecSet(22, 11, 0);
  V[5].P = VecSet(4, 20, 0);
  V[6].P = VecSet(2, 10, 0);
  V[5].P = VecSet(4, 20, 0);
  V[6].P = VecSet(2, 10, 0);
  V[7].P = VecSet(10, 15, 5);
  V[8].P = VecSet(20, -20, 0);
  V[9].P = VecSet(0, 0, 0);

  mtl.ShdNo = AG6_RndShaderAdd("LINE");
  AG6_RndPrimCreate(&Uni->Pr, AG6_PRIM_LINE_ADJ, V, NUM_OF_VERTEX, NULL, 0);
  Uni->Pr.MtNo = AG6_RndMaterialAdd(&mtl);
  free(V); 
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
 /*
  glBindBuffer(GL_ARRAY_BUFFER, Uni->Pr.VBuf);
  for (i = 0; i < 5; i++)
    glBufferData(GL_ARRAY_BUFFER, sizeof(ag6VERTEX) * i, sizeof(VEC), Uni->P)
  glBindBuffer(GL_ARRAY_BUFFER, 0);
 */
} /* End of 'AG6_UnitResponse' function */

/* Unit axe creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_UnitCreateTess( VOID )
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