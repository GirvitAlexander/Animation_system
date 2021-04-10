/* FILE NAME: ANIM.H
 * PROGRAMMER: AG6
 * DATE: 07.01.2019
 * PURPOSE:
 */
#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "rnd.h"

/* Operations with unit */
#define UNIT_BASE_FIELDS \
  VOID (*Init)( ag6UNIT *Uni, ag6ANIM *Ani );      \
  VOID (*Close)( ag6UNIT *Uni, ag6ANIM *Ani );     \
  VOID (*Response)( ag6UNIT *Uni, ag6ANIM *Ani );  \
  VOID (*Render)( ag6UNIT *Uni, ag6ANIM *Ani )

/* Max number of units */
#define AG6_MAX_UNITS 100

typedef struct tagag6UNIT ag6UNIT;

/* Struct of anim */
typedef struct tagag6ANIM
{
  HWND hWnd;                     /* Window */                   
  HDC hDC;                       /* Window context */
  int W, H;                      /* Size of window */

  int IsPause;                  /* Pause identificator */
  double FPS, DeltaTime,         /* Frame per second, DeltaTime */
         GlobalTime, Time,       /* Global tima, Time */
         GlobalDeltaTime;        /* Global delta time */

  unsigned char KeysClick[256];
  unsigned char KeysOld[256];
  unsigned char Keys[256];
  unsigned char IsWireFrame;

  ag6UNIT *Units[AG6_MAX_UNITS]; /* Massive with all added units */
  int NumOfUnits;                /* Number of units */

  int Mdx, Mdy, My, Mx, Mz, Mdz;

  unsigned char
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  int JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */

} ag6ANIM;

extern ag6ANIM AG6_Anim;

/* Struct of unit */ 
struct tagag6UNIT
{
  UNIT_BASE_FIELDS; /* Operations with unit */
};

#endif /* __ANIM_H_ */
/* END OF 'ANIM.H' FILE */
