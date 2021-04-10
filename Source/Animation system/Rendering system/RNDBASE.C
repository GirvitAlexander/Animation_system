/* FILE NAME: RND.C
 * PROGRAMMER: AG6
 * DATE: 30.01.2019
 * PURPOSE:
 */

#include <time.h>

#include "rnd.h"
#include "anim.h"

/* Setting projection function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = AG6_RndProjSize / 2;
  if (AG6_RndFrameW > AG6_RndFrameH) 
    ratio_x *= (DBL)AG6_RndFrameW / AG6_RndFrameH;
  else
    ratio_y *= (DBL)AG6_RndFrameH / AG6_RndFrameW;

  AG6_RndMatrProj =
    MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
      AG6_RndProjDist, AG6_RndProjFarClip);
  AG6_RndMatrVP = MatrMulMatr(AG6_RndMatrView, AG6_RndMatrProj);
} /* End of 'AG6_RndProjSet' function */

/* Setting matrixes function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  VEC Dir = VecNormalize(VecSubVec(At, Loc));

  AG6_RndMatrView = MatrView(Loc, At, Up1);
  AG6_RndMatrVP = MatrMulMatr(AG6_RndMatrView, AG6_RndMatrProj);
  AG6_hRndCamLoc = Loc;
  AG6_hRndCamUp = VecSet(AG6_RndMatrVP.A[0][1], AG6_RndMatrVP.A[1][1], AG6_RndMatrVP.A[2][1]);
  AG6_hRndCamRight = VecSet(AG6_RndMatrVP.A[0][0], AG6_RndMatrVP.A[1][0], AG6_RndMatrVP.A[2][0]);
  AG6_hRndCamDir = Dir;
} /* End of 'AG6_RndCamSet' function */

/* Inite function
 * ARGUMENTS:
 *   - window
 *     HWND hWnd;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndInit( HWND hWnd )
{
  int i;
  unsigned long int Dummy = 0;
  PIXELFORMATDESCRIPTOR pfd = {0};

  AG6_hRndDC = GetDC(AG6_hRndWnd = hWnd);
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(AG6_hRndDC, &pfd);
  DescribePixelFormat(AG6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(AG6_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  AG6_hRndGLRC = wglCreateContext(AG6_hRndDC);
  wglMakeCurrent(AG6_hRndDC, AG6_hRndGLRC);

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    exit(0);

  /* Setup default values */
  glClearColor(0.3, 0.5, 0.7, 1);
  /* glClearColor(0.1, 0, 0, 1); */
  glEnable(GL_DEPTH_TEST);

  AG6_RndProjDist = 0.1;
  AG6_RndProjFarClip = 1000000.0;
  AG6_RndProjSize = AG6_RndProjDist;

  AG6_RndFrameW = 47;
  AG6_RndFrameH = 47;
  AG6_RndProjSet();
  AG6_RndCamSet(VecSet(18, 18, 18), VecSet(0, 0, 0), VecSet(0, 1, 0));
  /*
  NoiseInit();
  AG6_TabTex = AG6_RndTextureAdd("Noise Table", TAB_SIZE, 1, &Dummy);
  AG6_PermTex = AG6_RndTextureAdd("Noise Perm", TAB_SIZE, 1, &Dummy);
  NoiseMakeTex(AG6_TabTex, AG6_PermTex);
  */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  AG6_RndResInit();
  AG6_RndTrgInit();
} /* End of 'AG6_RndInit' function */

/* Resize init function
 * ARGUMENTS:
 *   - window
 *     HWND hWnd;
 *   - 
 *   LONG loWord;
 *   - 
 *   LONG hiWord;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndResize( int W, int H )
{
  glViewport(0, 0, W, H);
  AG6_RndFrameW = W;
  AG6_RndFrameH = H;
  AG6_RndProjSet();
  AG6_RndTrgResize(W, H);
} /* End of 'AG6_RndResize' function */

/* Start function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndStart( VOID )
{
  LONG t = clock();
  static LONG ReloadStart;

  /* Reload shader */
  if (ReloadStart == 0)
    ReloadStart = t;
  if (t - ReloadStart > 3 * CLOCKS_PER_SEC)
  {
    ReloadStart = t;

    AG6_RndShadersUpdate();
  }
  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  AG6_RndTrgStart();
} /* End of 'AG6_RndStart' function */

/* Coping frame function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndCopyFrame( HDC hDC )
{
  SwapBuffers(AG6_hRndDC);
} /* End of 'AG6_RndCopyFrame' function */ /* End of 'AG6_RndStart' function */

/* End function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndEnd( VOID )
{
  glFinish();
  AG6_RndTrgEnd();
} /* End of 'AG6_RndEnd' function */

/* Closing function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AG6_hRndGLRC);
  ReleaseDC(AG6_hRndWnd, AG6_hRndDC);
  AG6_RndResClose();
  AG6_RndTrgClose();
} /* End of 'AG6_RndClose' function */

/* END OF 'RND.C' FILE */

