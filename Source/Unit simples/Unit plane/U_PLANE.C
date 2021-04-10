/* FILE NAME: U_PLANE.C
 * PROGRAMMER: AG6
 * DATE: 15.02.2019
 * PURPOSE: ANIMATIOM SYSTEM
 */

#include "rndres.h"
#include "anim.h"

#define NUM_OF_VERTEX 16

typedef struct tagag6UNIT_PLANE ag6UNIT_PLANE;
typedef struct tagag6UNIT_PLANE
{
  UNIT_BASE_FIELDS;
  ag6PRIM *Pr;
  ag6OBJ Line;
  ag6GRID Gr;
  ag6VERTEX *V;
};

int NumOfPlane;

int AG6_RndLoadTess( ag6UNIT_PLANE *Uni, char *FileName )
{
  int size, i, k = 0;
  FILE *F;
  char Buf[1000];
  float a, b, c;



  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fgets(Buf, sizeof(Buf) - 1, F);
  sscanf(Buf, "%i", &size);
  NumOfPlane = size;
  if ((Uni->V = malloc(sizeof(ag6VERTEX) * NUM_OF_VERTEX)) == NULL)
	return FALSE;
  memset(Uni->V, 0, sizeof(ag6VERTEX) * NUM_OF_VERTEX);

  if ((Uni->Pr = malloc(sizeof(ag6PRIM) * size)) == NULL)
    return FALSE;

  for (i = 0; i < size; i++)
  {
    while (k < 16)
    {
      fscanf(F, "%f %f %f", &a, &b, &c);
      Uni->V[k++].P = VecSet(a, b, c);
    }
    k = 0;
    AG6_RndPrimCreate(&Uni->Pr[i], AG6_PRIM_PATCHLINE, Uni->V, NUM_OF_VERTEX, NULL, 0);
  }

  fclose(F);
  return TRUE;
}

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_PLANE *Uni, ag6ANIM *Ani )
{
  int i;

  for (i = 0; i < NumOfPlane; i++)
    AG6_RndPrimFree(&Uni->Pr[i]);
} /* End of 'AG6_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitRender( ag6UNIT_PLANE *Uni, ag6ANIM *Ani )
{
  int i;

  for (i = 0; i < NumOfPlane; i++)
    AG6_RndPrimDraw(&Uni->Pr[i], UnitMatrix);
} /* End of 'AG6_UnitRender' function */

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_PLANE *Uni, ag6ANIM *Ani )
{
  int i;
  ag6MATERIAL mtl = {"Tess Material"};

  AG6_RndLoadTess(Uni, "SPOON.TXT");

  mtl.ShdNo = AG6_RndShaderAdd("PLANE");
  for (i = 0; i < NumOfPlane; i++)
    Uni->Pr[i].MtNo = AG6_RndMaterialAdd(&mtl);
} /* End of 'AG6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitResponse( ag6UNIT_PLANE *Uni, ag6ANIM *Ani )
{
} /* End of 'AG6_UnitResponse' function */

/* Unit axe creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_UnitCreatePlane( VOID )
{
  ag6UNIT_PLANE *Uni;


  if ((Uni = (ag6UNIT_PLANE *)AG6_AnimUnitCreate(sizeof(ag6UNIT_PLANE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Close = (VOID *)AG6_UnitClose;

  return (ag6UNIT *)Uni;
} /* End of 'AG6_UnitCreateTess' function */

/* END OF 'U_PLANE.C' FILE */