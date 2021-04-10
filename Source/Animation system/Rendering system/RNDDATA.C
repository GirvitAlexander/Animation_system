/* FILE NAME: RNDDATA.C
 * PROGRAMMER: AG6
 * DATE: 07.01.2019
 * PURPOSE:
 */
#include "rnd.h"

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")

/* Projection data */
DBL
  AG6_RndProjSize = 1.0,     /* Project plane unit square size */
  AG6_RndProjDist = 0.1,     /* Distance to project plane (near) */
  AG6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
int
  AG6_RndFrameW, AG6_RndFrameH; /* Viewport size */

/* Transformation matrix /*/
MATR
  AG6_RndMatrView, /* View coordinate system matrix */
  AG6_RndMatrProj, /* Projection matrix */
  AG6_RndMatrVP;   /* Precalculated matrix multiplication View by Proj */

/* OpenGL support */
HDC AG6_hRndDC;     /* Back frame buffer device context */
HWND AG6_hRndWnd;   /* Work window */
HGLRC AG6_hRndGLRC; /* OpenGL rendering context */

VEC AG6_hRndCamLoc, AG6_hRndCamRight, AG6_hRndCamUp, AG6_hRndCamDir;

int AG6_RndShdAddOn0, AG6_RndShdAddOn1, AG6_RndShdAddOn2;

int AG6_MouseWheel;
/* Table of noise */
DBL TabNoise[TAB_SIZE];

/* Table of translation */
int Perm[TAB_SIZE];

int AG6_TabTex, AG6_PermTex;




/* END OF 'RNDDATA.C' FILE */