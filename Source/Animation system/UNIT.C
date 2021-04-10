/* FILE NAME: RND.C
 * PROGRAMMER: AG6
 * DATE: 08.01.2019
 * PURPORSE: .
 */


#include "unit.h"


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitInit( ag6UNIT *Uni, ag6ANIM *Ani )
{

} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ag6UNIT *Uni;
 *   - animation context:
 *       ag6ANIM *Ani;
 * RETURNS: None.
 */
static VOID AG6_UnitClose( ag6UNIT *Uni, ag6ANIM *Ani )
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
static VOID AG6_UnitResponse( ag6UNIT *Uni, ag6ANIM *Ani )
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
static VOID AG6_UnitRender( ag6UNIT *Uni, ag6ANIM *Ani )
{
 
} /* End of 'AG6_UnitRender' function */

ag6UNIT * AG6_AnimUnitCreate( int Size )
{
  ag6UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(ag6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = AG6_UnitInit;
  Uni->Close = AG6_UnitClose;
  Uni->Response = AG6_UnitResponse;
  Uni->Render = AG6_UnitRender;
  return Uni;
} /* End of 'AG6_AnimUnitCreate' function */