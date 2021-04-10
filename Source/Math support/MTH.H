/* FILE NAME: MTH.H
 * PROGRAMMER: AG6
 * DATE: 07.01.2019
 * PURPOSE: Operations with vectors and matrixes
 */
#ifndef __MTH_H_
#define __MTH_H_

#include <math.h>

/* Pi number */
#define PI 3.14159265358979323846

/* Conventer angle to radians */
#define D2R(A) ((A) * (PI / 180.0))

/* Conventer angle to radians function */ 
#define Degree2Radian(a) D2R(a)

/* Multiplication three matrixes function */
#define MatrMulMatr3(a, b, c) MatrMulMatr(a, MatrMulMatr(b, c))

/* Basic double types */
typedef double DBL;
typedef float FLT;

/* Vector type */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;

/* Vector type 2*/
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;

/* Vector type */
typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;

/* Matrix type */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;

/* Setting vector function
 * ARGUMENTS:
 *  - coordinate of vector:
 *      FLT X, Y, Z;
 * RETURNS:
 *  (VEC) Vector.   
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;

  return v;
} /* End of 'VecSet' function */

/* Setting 2 coordinates vector function
 * ARGUMENTS:
 *  - coordinate of vector:
 *      FLT X, Y;
 * RETURNS:
 *  (VEC2) Vector.   
 */
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v;

  v.X = X;
  v.Y = Y;

  return v;
} /* End of 'Vec2Set' function */

/* Setting 4 coordinates vector function
 * ARGUMENTS:
 *  - coordinate of vector:
 *      FLT X, Y, Z, W;
 * RETURNS:
 *  (VEC4) Vector.   
 */
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  v.W = W;

  return v;
} /* End of 'Vec4Set' function */

/* Addition vectors function
 * ARGUMENTS:
 *  - first vector:
 *      VEC V1;
 *  - second vector:
 *      VEC V2;
 * RETURNS:
 *  (VEC) Vector V1 + V2.   
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Submition vectors function
 * ARGUMENTS:
 *  - first vector:
 *      VEC V1;
 *  - second vector:
 *      VEC V2;
 * RETURNS:
 *  (VEC) Vector V1 - V2.   
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Multiplication vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V1;
 *  - number:
 *      FLT N;
 * RETURNS:
 *  (VEC) Vector V1 * N.   
 */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Dividing vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V1;
 *  - number:
 *      FLT N;
 * RETURNS:
 *  (VEC) Vector V1 / N.   
 */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  if (N == 0)
    return VecSet(0, 0, 0);

  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */

/* Getting negative vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 * RETURNS:
 *  (VEC) Vector -V.   
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Dot product vector function
 * ARGUMENTS:
 *  - first vector:
 *      VEC V1;
 *  - second vector:
 *      VEC V2;
 * RETURNS:
 *  (FLT) Dot product.   
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  FLT Dot = V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;

  return Dot;
} /* End of 'VecDotVec' function */

/* Cross product vector function
 * ARGUMENTS:
 *  - first vector:
 *      VEC V1;
 *  - second vector:
 *      VEC V2;
 * RETURNS:
 *  (FLT) Cross product.   
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V2.Y * V1.Z, -V1.X * V2.Z + V2.X * V1.Z, V1.X * V2.Y - V2.X * V1.Y);
} /* End of 'VecDotVec' function */

/* Lenth vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 * RETURNS:
 *  (FLT) lenth of vector.   
 */
__inline FLT VecLen( VEC V )
{
  FLT len = sqrt(V.X * V.X + V.Y * V.Y + V.Z * V.Z);

  return len;
} /* End of 'VecLen' function */

/* Lenth vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 * RETURNS:
 *  (FLT) lenth of vector.   
 */
__inline FLT VecLen2( VEC V )
{
  FLT len = V.X * V.X + V.Y * V.Y + V.Z * V.Z;

  return len;
} /* End of 'VecLen2' function */

/* Normalize vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 * RETURNS:
 *  (VEC) normalize vector.   
 */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecLen(V);

  return VecSet(V.X / len, V.Y / len, V.Z / len);
} /* End of 'VecNormalize' function */

/* Multiplying not change matrix */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Matrix identity function
 * ARGUMENTS: none
 * RETURNS:
 *  (MATR) UnixMatrix.   
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Matrix translate function
 * ARGUMENTS:
 *  - vector:
 *      VEC T;
 * RETURNS:
 *  (MATR) matrix with vector coordinates.   
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;

  return m;
} /* End of 'MatrTranslate' function */ 

/* Matrix multiplication function
 * ARGUMENTS:
 *  - first matrix:
 *      MATR M1;
 *  - second matrix:
 *      MATR M2;
 * RETURNS:
 *  (MATR) multiplication of matrix.   
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  int i, j, k;
  MATR r = MatrIdentity();

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
} /* End of 'MatrMulMatr' function */

/* Multiplication matrix with vector function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *  (MATR) multiplication of matrix with vector.   
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecrMulMatr' function */

/* Counting determ matrix 3x3 function
 * ARGUMENTS:
 *  - elements of matrix:
 *     FLT A11, FLT A12, FLT A13,
 *     FLT A21, FLT A22, FLT A23,
 *     FLT A31, FLT A32, FLT A33;
 * RETURNS:
 *  (FLT) determ of matrix 3x3.   
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Counting determ matrix 4x4 function
 * ARGUMENTS:
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *  (FLT) determ of matrix 4x4.   
 */
__inline FLT MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) - 
    M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                              M.A[2][0], M.A[2][2], M.A[2][3],
                              M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) -
    M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                              M.A[2][0], M.A[2][1], M.A[2][2],
                              M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm' function */ 

/* Getting inverse matrix function
 * ARGUMENTS:
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *  (MATR) inverse matrix.   
 */
__inline MATR MatrInverse( MATR M )
{
  int i, j, sign = 0;
  MATR r;
  FLT det = MatrDeterm(M);
  int p[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
  if (det == 0)
    return UnitMatrix;
  for (i = 0; i < 4; i++)
  {
    sign = !sign;
    for (j = 0; j < 4; j++)
      r.A[j][i] =
        MatrDeterm3x3(
          M.A[p[i][0]][p[j][0]], M.A[p[i][0]][p[j][1]], M.A[p[i][0]][p[j][2]],
          M.A[p[i][1]][p[j][0]], M.A[p[i][1]][p[j][1]], M.A[p[i][1]][p[j][2]],
          M.A[p[i][2]][p[j][0]], M.A[p[i][2]][p[j][1]], M.A[p[i][2]][p[j][2]]) /
        ((sign * 2 - 1) * det), sign = !sign;
  }
  return r;
} /* End of 'MatrInverse' function */

/* Rotating matrix function
 * ARGUMENTS:
 *  - angle:
 *      FLT AngleInDegree;
 *  - vector:
 *      VEC R;
 * RETURNS:
 *  (MATR) rotate matrix.   
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC R )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co),
         V.X * V.Y * (1 - co) + V.Z * si,
           V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si,
         co + V.Y * V.Y * (1 - co),
           V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si,
         V.Z * V.Y * (1 - co) - V.X * si,
           co + V.Z * V.Z * (1 - co),       0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotate' function */

/* Rotating matrix in vector X function
 * ARGUMENTS:
 *  - angle:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) rotate in X matrix.   
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, co, si, 0},
      {0, -si, co, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateX' function */

/* Rotating matrix in vector Y function
 * ARGUMENTS:
 *  - angle:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) rotate in Y matrix.   
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {co, 0, -si, 0},
      {0, 1, 0, 0},
      {si, 0, co, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateY' function */

/* Rotating matrix in vector Z function
 * ARGUMENTS:
 *  - angle:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) rotate in Z matrix.   
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {co, si, 0, 0},
      {-si, co, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateZ' function */

/* Matrix scaling function
 * ARGUMENTS:
 *  - vector:
 *      VEC S;
 * RETURNS:
 *  (MATR) matrix with scaling coordinates.   
 */
__inline MATR MatrScale( VEC S )
{
  MATR m = UnitMatrix;

  m.A[0][0] = S.X;
  m.A[1][1] = S.Y;
  m.A[2][2] = S.Z;

  return m;
} /* End of 'MatrScale' function */

/* Matrix transposing function
 * ARGUMENTS:
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *  (MATR) matrix with transposed elements.   
 */
__inline MATR MatrTranspose( MATR M )
{
  MATR A = 
  {
    {
      {M.A[0][0], M.A[1][0], M.A[2][0], M.A[3][0]},
      {M.A[0][1], M.A[1][1], M.A[2][1], M.A[3][1]},
      {M.A[0][2], M.A[1][2], M.A[2][2], M.A[3][2]},
      {M.A[0][3], M.A[1][3], M.A[2][3], M.A[3][3]}
    }
  };

  return A;
} /* End of 'MatrTranspose' function */

/* Point tranforming function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *  (VEC) transformed point.   
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]),
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]),
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]));
} /* End of 'PointTransform' function */

/* Vector tranforming function
 * ARGUMENTS:
 *  - vector:
 *      VEC V;
 *  - matrix:
 *      MATR M;
 * RETURNS:
 *  (VEC) transformed vector.   
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0]),
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1]),
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]));
} /* End of 'VectorTransform' function */

/* Matrix viewer function
 * ARGUMENTS:
 *  - radius vector position:
 *      VEC Loc;
 *  - looking on vector:
 *      VEC At;
 *  - nearly way of looking vector:
 *      VEC Up1;
 * RETURNS:
 *  (MATR) Viewer matrix.   
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC Dir = VecNormalize(VecSubVec(At, Loc)),
      Right = VecNormalize(VecCrossVec(Dir, Up1)),
      Up = VecCrossVec(Right, Dir);
  MATR M = 
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return M;
} /* End of 'MatrView' function */

/* Matrix ortographics function
 * ARGUMENTS:
 *  - left, right, bottom, top, near and far position:
 *      FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *  (MATR) Ortographics matrix.   
 */
__inline MATR MatrOrtho( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  MATR M = 
  {
    {
      {2 / (Right - Left), 0, 0, 0},
      {0, 2 / (Top - Bottom), 0, 0},
      {0, 0, -2 / (Far - Near), 0},
      {-(Right + Left) / (Right - Left),
      -(Top + Bottom) / (Top - Bottom),
      -(Far + Near) / (Far - Near), 1}
    }
  };

  return M;
}  /* End of 'MatrOrtho' function */

/* Matrix frustum function
 * ARGUMENTS:
 *  - left, right, bottom, top, near and far position:
 *      FLT l, r, b, t, n, f;
 * RETURNS:
 *  (MATR) Frustum matrix.   
 */
__inline MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  MATR M = 
  {
    {
      {2 * n / (r - l), 0, 0, 0},
      {0, 2 * n / (t - b), 0, 0},
      {(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1},
      {0, 0, -(2 * n * f) / (f - n), 0}
    }
  };

  return M;
}  /* End of 'MatrFrustum' function */

#endif /* __MTH_H_ */

/* END OF 'MTH.H' FILE */