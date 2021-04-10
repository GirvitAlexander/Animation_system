/* FILE NAME: RND.H
 * PROGRAMMER: AG6
 * DATE: 07.01.2019
 * PURPOSE:
 */
#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC
#include <glew.h>

#include "def.h"


#define TAB_BITS 10
#define TAB_SIZE (1 << TAB_BITS)
#define TAB_MASK (TAB_BITS - 1)

#define INDEX1(X) (Perm[(X) & TAB_MASK])
#define INDEX2(X, Y) (Perm[(X + INDEX1(Y)) & TAB_MASK])
#define INDEX3(X, Y, Z) (Perm[(X + INDEX2(Y, Z)) & TAB_MASK])
#define INDEX4(X, Y, Z, W) (Perm[(X + INDEX3(Y, Z, W)) & TAB_MASK])

/* Table of noise */
extern DBL TabNoise[TAB_SIZE];

/* Table of translation */
extern int Perm[TAB_SIZE]; 

/* Projection data */
extern DBL
  AG6_RndProjSize,     /* Project plane unit square size */
  AG6_RndProjDist,     /* Distance to project plane (near) */
  AG6_RndProjFarClip;  /* Distance to project far clip plane (far) */
extern int
  AG6_RndFrameW, AG6_RndFrameH; /* Viewport size */

/* Transformation matrix /*/
extern MATR
  AG6_RndMatrView, /* View coordinate system matrix */
  AG6_RndMatrProj, /* Projection matrix */
  AG6_RndMatrVP;   /* Precalculated matrix multiplication View by Proj */

/* OpenGL support */
extern HDC AG6_hRndDC;     /* Back frame buffer device context */
extern HWND AG6_hRndWnd;   /* Work window */
extern HGLRC AG6_hRndGLRC; /* OpenGL rendering context */

extern VEC AG6_hRndCamLoc, AG6_hRndCamRight, AG6_hRndCamUp, AG6_hRndCamDir;

extern int AG6_RndShdAddOn0, AG6_RndShdAddOn1, AG6_RndShdAddOn2;

extern int AG6_MouseWheel;

extern int AG6_TabTex, AG6_PermTex;



typedef enum
{
  AG6_PRIM_POINTS, AG6_PRIM_LINES, AG6_PRIM_TRIMESH, AG6_RND_PRIM_GRID, AG6_PRIM_STRIP, AG6_PRIM_PATCH1, AG6_PRIM_PATCH4, AG6_PRIM_LINES_STRIP, AG6_PRIM_PATCHLINE, AG6_PRIM_LINE_ADJ 
} TYPE;

/* Primitive representation type */
typedef struct tagag6VERTEX
{
  VEC P;   /* Vertex position */
  VEC2 T;  /* Vertex texture */
  VEC N;   /* Vertex normal */
  VEC4 C;  /* Vertex color */
} ag6VERTEX;

/* Geometry primitive representation type */
typedef struct tagag6PRIM
{
  int VA, IBuf, VBuf; /* OpenGL vertex array, vertex buffer and index buffer */
  int NumOfI;         /* Numbner of indexes */
  MATR Trans;         /* Additional transformation matrix */
  TYPE Type;
  int MtNo;
} ag6PRIM;

/* Setting projection function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndProjSet( VOID );

/* Setting matrixes function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndCamSet( VEC Loc, VEC At, VEC Up1 );

/* Inite function
 * ARGUMENTS:
 *   - window
 *     HWND hWnd;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndInit( HWND hWnd );

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
VOID AG6_RndResize( int W, int H );

/* Start function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndStart( VOID );

/* Coping frame function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndCopyFrame( HDC hDC );

/* End function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndEnd( VOID );

/* Closing function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndClose( VOID );

/* Setting primitive function
 * ARGUMENTS: 
 *   -primitive
 *       ag6PRIM *Pr;
 *   -Number of vertices 
 *       int NoofV;
 *   -Number of indecies 
 *       int NoofI;
 * RETURNS:
 *  (int) Error level for operation system.    
 */
int AG6_RndPrimCreate( ag6PRIM *Pr, TYPE Type, ag6VERTEX *V, int NumOfV, int *Ind, int NumOfI );

/* Delete primitive function
 * ARGUMENTS: 
 *   -primitive
 *       ag6PRIM *Pr;
 * RETURNS: none.   
 */
VOID AG6_RndPrimFree( ag6PRIM *Pr );

/* Drawing primitive function
 * ARGUMENTS: 
 *   -primitive
 *       ag6PRIM *Pr;
 *   -World matrix 
 *       MATR World;
 * RETURNS: none.    
 */
VOID AG6_RndPrimDraw( ag6PRIM *Pr, MATR World );

/* Loading primitive from file function
 * ARGUMENTS: 
 *   -primitive
 *       ag6PRIM *Pr;
 *   -File name 
 *        char *FileName;
 * RETURNS:
 *  (int) Error level for operation system.    
 */
int AG6_RndPrimLoad( ag6PRIM *Pr, char *FileName );

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       char *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT AG6_RndShaderLoad( char *FileNamePrefix );

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID AG6_RndShaderFree( UINT Prg );

/* Noise intialization function.
 * ARGUMENTS:
 *   None.
 * RETURNS: None.
 */
VOID NoiseInit( VOID );

/* Noise create function.
 * ARGUMENTS:
 *   - X coordinate:
 *      DBL X;
 * RETURNS: 
 *    (DBL) noise.
 */
DBL Noise( DBL X );

/* Noise turbulenced create function.
 * ARGUMENTS:
 *   - x coordinate
 *      DBL X;
 *   - octaves
 *      int Octaves;
 * RETURNS: (DBL) Noise.
 */
DBL NoiseTurb1D( DBL X, int Octaves );

/* Noise 2D create function.
 * ARGUMENTS:
 *   - x coordinate
 *      DBL X;
 *   - y coordinate
 *      DBL Y;
 *   - octaves
 *      int Octaves;
 * RETURNS: (DBL) Noise.
 */
DBL Noise2D( DBL X, DBL Y );

/* Noise2D turbulenced create function.
 * ARGUMENTS:
 *   - x coordinate
 *      DBL X;
 *   - y coordinate
 *      DBL Y;
 *   - octaves
 *      int Octaves;
 * RETURNS: (DBL) Noise.
 */
DBL NoiseTurb2D( DBL X, DBL Y, int Octaves );
VOID NoiseMakeTex( UINT TabTexId, UINT TabPermId );


/***
 * FBO function
 ***/

/* Inite function
 * ARGUMENTS:
 *   - window
 *     HWND hWnd;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgInit( VOID );

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
VOID AG6_RndTrgResize( int W, int H );

/* Start function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgStart( VOID );

/* Create function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgCreate( int W, int H );

/* End function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgEnd( VOID );

/* Closing function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgClose( VOID );

/* Free function
 * ARGUMENTS: none;
 * RETURNS:
 *  None.   
 */
VOID AG6_RndTrgFree( VOID );


#endif /* __RND_H_ */

/* END OF 'RND.C' FILE */





