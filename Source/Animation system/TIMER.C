/* FILE NAME: TIMER.C
 * PROGRAMMER: AG6
 * DATE: 08.01.2019
 * PURPOSE: TIMER
 */

#include "timer.h"
#include "anim.h"

static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */

/* Start measure function
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID AG6_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  AG6_Anim.IsPause = FALSE;
  AG6_Anim.FPS = 30.0;
  PauseTime = 0;
} /* End of 'AG6_TimerInit' function */

/* Response measure function
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID AG6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  AG6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  AG6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (AG6_Anim.IsPause)
  {
    AG6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    AG6_Anim.DeltaTime = AG6_Anim.GlobalDeltaTime;
    AG6_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    AG6_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'AG6_TimerResponse' function */

/* END OF 'TIMER.C' FILE */