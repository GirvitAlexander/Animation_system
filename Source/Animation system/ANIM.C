/* FILE NAME: ANIM.C
 * PROGRAMMER: AG6
 * DATE: 23.01.2019
 * PURPOSE:
 */
#include "anim.h"
#include <mmsystem.h>


ag6ANIM AG6_Anim;
ag6UNIT Units[AG6_MAX_UNITS];
#define AG6_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)


#pragma comment(lib, "winmm")

/* Initialization function
 * ARGUMENTS:
 *   - window
 *     HWND hWnd;
 * RETURNS:
 *  None.   
 */
VOID AG6_AnimInit( HWND hWnd )
{
  AG6_Anim.IsWireFrame = FALSE;
  AG6_Anim.hWnd = hWnd;
  AG6_RndInit(hWnd);
  AG6_TimerInit();
} /* End of 'AG6_AnimInit' function */

/* Rendering function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_AnimRender( HWND hWnd )
{
  int i;
  POINT pt;

  AG6_TimerResponse();

  GetKeyboardState(AG6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    AG6_Anim.Keys[i] >>= 7;
    AG6_Anim.KeysClick[i] = AG6_Anim.Keys[i] && !AG6_Anim.KeysOld[i];
  }
  memcpy(AG6_Anim.KeysOld, AG6_Anim.Keys, 256);

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  AG6_Anim.Mdx = pt.x - AG6_Anim.Mx;
  AG6_Anim.Mdy = pt.y - AG6_Anim.My;
  AG6_Anim.Mdz = AG6_MouseWheel;
  AG6_Anim.Mz += AG6_MouseWheel;
  AG6_MouseWheel = 0;

  AG6_Anim.Mx = pt.x;
  AG6_Anim.My = pt.y;

  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          AG6_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          AG6_Anim.JButClick[i] = AG6_Anim.JBut[i] && !AG6_Anim.JButOld[i];
          AG6_Anim.JButOld[i] = AG6_Anim.JBut[i];
        }

        /* Axes */
        AG6_Anim.JX = AG6_GET_JOYSTIC_AXIS(X);
        AG6_Anim.JY = AG6_GET_JOYSTIC_AXIS(Y);
        AG6_Anim.JZ = AG6_GET_JOYSTIC_AXIS(Z);
        AG6_Anim.JR = AG6_GET_JOYSTIC_AXIS(R);

        /* Point of view */
        AG6_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }


  for (i = 0; i < AG6_Anim.NumOfUnits; i++)
    AG6_Anim.Units[i]->Response(AG6_Anim.Units[i], &AG6_Anim);

  AG6_RndStart();
  for (i = 0; i < AG6_Anim.NumOfUnits; i++)
    AG6_Anim.Units[i]->Render(AG6_Anim.Units[i], &AG6_Anim);
  AG6_RndEnd();
} /* End of 'AG6_AnimRender' function */ 

/* Addind unit function
 * ARGUMENTS:
 *   - pointer to adding unit
 *     AG6UNIT *Uni;
 * RETURNS:
 *  None.   
 */
VOID AG6_AnimUnitAdd( ag6UNIT *Uni )
{
  if (AG6_Anim.NumOfUnits < AG6_MAX_UNITS)
    AG6_Anim.Units[AG6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &AG6_Anim);
} /* End of 'AG6_AnimUnitAdd' function */

/* Close function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_AnimClose( VOID )
{
  int i;

  for (i = 0; i < AG6_Anim.NumOfUnits; i++)
  {
    AG6_Anim.Units[i]->Close(AG6_Anim.Units[i], &AG6_Anim);
    free(AG6_Anim.Units[i]);
  }
  AG6_Anim.NumOfUnits = 0;
  AG6_RndClose();  
} /* End of 'AG6_AnimClose' function */

/* Resizing window function
 * ARGUMENTS: 
 * - size of window:
 *    int W, H; 
 * RETURNS:
 *  None.   
 */
VOID AG6_AnimResize( int W, int H )
{
  AG6_Anim.H = H;
  AG6_Anim.W = W;
  AG6_RndResize(W, H);
} /* End of 'AG6_AnimResize' function */

/* Coping frame function
 * ARGUMENTS:
 * - copying context:
 *    HDC hDC;
 * RETURNS:
 *  None.   
 */
AG6_AnimCopyFrame( HDC hDC )
{
  AG6_RndCopyFrame(hDC);
} /* End of 'AG6_AnimCopyFrame' function */

/* END OF 'ANIM.C' FILE */
