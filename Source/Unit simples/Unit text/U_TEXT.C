/* FILE NAME: U_SPHERE.C
 * PROGRAMMER: AG6
 * DATE: 30.01.2019
 * PURPOSE:. 
 */

#include "anim.h"
#include "rndfont.h"

typedef struct tagag6UNIT_TXT ag6UNIT_TXT;
struct tagag6UNIT_TXT
{
  UNIT_BASE_FIELDS;
  ag6FONT Fnt;
  ag6PRIM Pr;
  char Buf[100];
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT_TXT *Uni, ag6ANIM *Ani )
{
  AG6_RndFntLoad(&Uni->Fnt, "BOOK.FNT");
} /* End of 'AG6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT_TXT *Uni, ag6ANIM *Ani )
{
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
static VOID AG6_UnitResponse( ag6UNIT_TXT *Uni, ag6ANIM *Ani )
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
static VOID AG6_UnitRender( ag6UNIT_TXT *Uni, ag6ANIM *Ani )
{
  memset(&Uni->Buf, 0, sizeof(Uni->Buf));
  sprintf(Uni->Buf, "FPS %f\nCGSG FOREVER!!!\n", AG6_Anim.FPS * 3.6 + 0.3);
  AG6_RndPrimFromFont(&Uni->Pr, Uni->Buf, &Uni->Fnt, 32, Vec4Set(0.5, 0.5, 0, 1));
  Uni->Pr.MtNo = Uni->Fnt.MtlNo;
  glDepthMask(FALSE);
  AG6_RndPrimDraw(&Uni->Pr, UnitMatrix);
  glDepthMask(TRUE);
} /* End of 'AG6_UnitRender' function */

/* Cow creation function.
 * ARGUMENTS: none;
 * RETURNS:
 *   (ag6UNIT *) pointer to created unit.
 */
ag6UNIT * AG6_AnimUnitCreateText( VOID )
{
  ag6UNIT_TXT *Uni;

  /* Memory allocation */
  if ((Uni = (ag6UNIT_TXT *)AG6_AnimUnitCreate(sizeof(ag6UNIT_TXT))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AG6_UnitInit;
  Uni->Render = (VOID *)AG6_UnitRender;
  Uni->Response = (VOID *)AG6_UnitResponse;
  Uni->Close = (VOID *)AG6_UnitClose;
  return (ag6UNIT *)Uni;
} /* End of 'AG6_AnimUnitCreateCow' function */

/* END OF 'U_TEXT.C' FILE */