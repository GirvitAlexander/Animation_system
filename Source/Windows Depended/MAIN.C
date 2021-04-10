/* FILE NAME: MAIN.C
 * PROGRAMMER: AG6
 * DATE: 30.01.2019
 * PURPOSE: 
 */
#include <stdio.h>
#include <conio.h>

#include "def.h"
#include "rnd.h"
#include "timer.h"
#include "anim.h"

/* Name of class */
#define WND_CLASS_NAME "My Class"

/* Prototype of window function */ 
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* Main window function
 * ARGUMENTS:
 *  - Handle of operation instance:
 *    HINSTANCE hInstance;
 *  - Dummy handle of previous apperation:
 *    HINSTANCE hPrevInstance;
 *  - Command line string:
 *    char *CmdLine;
 *  - Show window command parametr:
 *    int CmdShow;
 * RETURNS:
 *  (int WINAPI) Error level for operation system.   
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, char *CmdLine, int CmdShow )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  SetDbgMemHooks();

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  hWnd = CreateWindow(WND_CLASS_NAME,
                      "Title", 
                      WS_OVERLAPPEDWINDOW, 
                      CW_USEDEFAULT, CW_USEDEFAULT, 
                      CW_USEDEFAULT, CW_USEDEFAULT, 
                      NULL, 
                      NULL, 
                      hInstance, 
                      NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);


  AG6_AnimUnitAdd(AG6_AnimUnitCreateCar());

  AG6_AnimUnitAdd(AG6_UnitCreateAxe());

  AG6_AnimUnitAdd(AG6_AnimUnitCreateSphere());

  AG6_AnimUnitAdd(AG6_UnitCreateSphere());

  AG6_AnimUnitAdd(AG6_UnitCreateTest());
                                                
  AG6_AnimUnitAdd(AG6_UnitCreatePlane());

  AG6_AnimUnitAdd(AG6_UnitCreateTess());

  AG6_AnimUnitAdd(AG6_UnitCreateCtrl());

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
} /* End of 'WinMain' function */


/* Main window message handle function
 * ARGUMENTS:
 *  - Window candle:
 *    HINSTANCE hInstance;
 *  - Message identifier:
 *    UINT Msg;
 *  - Message first parametr:
 *    WPARAM wParam;
 *  - Message seckond parametr:
 *    LPARAM lParam;
 * RETURNS:
 *  (LRESULT) message returns code.   
*/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  HDC hDC;
  char Buf[100];

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 5, NULL);
    AG6_AnimInit(hWnd);
    return 0;
  case WM_SIZE:
    AG6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    AG6_AnimRender(hWnd);
    sprintf(Buf, "FPS %f", AG6_Anim.FPS);
    SetWindowText(hWnd, Buf);
    InvalidateRect(hWnd, NULL, FALSE);
    return 0; 
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    AG6_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_MOUSEWHEEL:
    AG6_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_DESTROY:
    AG6_AnimClose();
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  case WM_CLOSE:
    if (MessageBox(NULL, "Do you want to exit?", "Close", MB_YESNO) == IDNO)
      return 0;
    break; 
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowfunc' function */

/* END OF 'MAIN.C' FILE */
