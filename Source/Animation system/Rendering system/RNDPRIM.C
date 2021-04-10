/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: AG6
 * DATE: 30.01.2019
 * PURPOSE:.
 */
#include <string.h>
#include <stdio.h>

#include "anim.h"
#include "rnd.h"
#define VER 16

/* Setting primitive function
 * ARGUMENTS: 
 *   -primitive
 *       AG6PRIM *Pr;
 *   -Number of vertices 
 *       int NoofV;
 *   -Number of indecies 
 *       int NoofI;
 * RETURNS:
 *  (int) Error level for operation system.    
 */
VOID AG6_AutoNormal( ag6VERTEX *V, int NumOfV, int *Ind, int NumOfI )
{
  int i;
  VEC s1, s2, N;

  for (i = 0; i < NumOfV; i++)
    V[i].N = VecSet(0, 0, 0);
  for (i = 0; i < NumOfI; i += 3)
  {
    int n0 = Ind[i], n1 = Ind[i + 1], n2 = Ind[i + 2];
    VEC p0 = V[n0].P,
        p1 = V[n1].P,
        p2 = V[n2].P;
    s1 = VecSubVec(p1, p0);
    s2 = VecSubVec(p2, p0);
    N  = VecNormalize(VecCrossVec(s1, s2));
    V[n0].N = VecAddVec(V[n0].N, N);
    V[n1].N = VecAddVec(V[n1].N, N);
    V[n2].N = VecAddVec(V[n2].N, N);
  }
  for (i = 0; i < NumOfV; i++)
    V[i].N = VecNormalize(V[i].N);
} /* End of 'AG6_AutoNormal' function */

/* Setting primitive function
 * ARGUMENTS: 
 *   -primitive
 *       AG6PRIM *Pr;
 *   -Number of vertices 
 *       int NoofV;
 *   -Number of indecies 
 *       int NoofI;
 * RETURNS:
 *  (int) Error level for operation system.    
 */
int AG6_RndPrimCreate( ag6PRIM *Pr, TYPE Type, ag6VERTEX *V, int NumOfV, int *Ind, int NumOfI )
{
  memset(Pr, 0, sizeof(ag6PRIM));

  glGenBuffers(1, &Pr->VBuf);
  glGenVertexArrays(1, &Pr->VA);

  /* Vertexes */
  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ag6VERTEX) * NumOfV, V, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ag6VERTEX), (VOID *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(ag6VERTEX), (VOID *)sizeof(VEC));
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(ag6VERTEX), (VOID *)(sizeof(VEC) + sizeof(VEC2)));
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(ag6VERTEX), (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);

  /* Indexes */
  if (Ind != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * NumOfI, Ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Pr->NumOfI = NumOfI;
  }
  else
    Pr->NumOfI = NumOfV;
  Pr->Type = Type;
  Pr->Trans = MatrIdentity();
  return TRUE;
} /* End of 'AG6_RndPrimCreate' function */

/* Delete primitive function
 * ARGUMENTS: 
 *   -primitive
 *       AG6PRIM *Pr;
 * RETURNS: none.   
 */
VOID AG6_RndPrimFree( ag6PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);
  if (Pr->IBuf != 0)
    glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(ag6PRIM));
} /* End of 'AG6_RndPrimFree' function */

/* Drawing primitive function
 * ARGUMENTS: 
 *   -primitive
 *       AG6PRIM *Pr;
 *   -World matrix 
 *       MATR World;
 * RETURNS: none.    
 */
VOID AG6_RndPrimDraw( ag6PRIM *Pr, MATR World )
{
  MATR 
    WVP = MatrMulMatr(Pr->Trans, MatrMulMatr(World, AG6_RndMatrVP)),
    W = MatrMulMatr(Pr->Trans, World),
    MatrN = MatrTranspose(MatrInverse(W)),
    Ortho = MatrOrtho(AG6_RndFrameW - 1, 0, AG6_RndFrameH - 1, 0, 0, 0);
  int loc,     
    PrimType =
      Pr->Type == AG6_PRIM_POINTS ? GL_POINTS :
      Pr->Type == AG6_PRIM_LINES  ? GL_LINES :
      Pr->Type == AG6_PRIM_STRIP ? GL_LINE_STRIP :
      Pr->Type == AG6_PRIM_PATCH4 ? GL_PATCHES :
      Pr->Type == AG6_PRIM_PATCH1 ? GL_PATCHES :
      Pr->Type == AG6_PRIM_LINE_ADJ ? GL_LINE_STRIP_ADJACENCY :
      Pr->Type == AG6_PRIM_PATCHLINE ? GL_PATCHES :
      Pr->Type == AG6_RND_PRIM_GRID ? GL_TRIANGLE_STRIP :
      Pr->Type == AG6_PRIM_LINES_STRIP ? GL_LINE_STRIP :
      Pr->Type == AG6_PRIM_TRIMESH  ? GL_TRIANGLES : GL_POINTS;
  UINT ProgId;

  glLoadMatrixf(WVP.A[0]);

  /* Draw triangles */
  glBindVertexArray(Pr->VA);
  if (Pr->Type == AG6_PRIM_PATCH4)
    glPatchParameteri(GL_PATCH_VERTICES, 4);
  if (Pr->Type == AG6_PRIM_PATCH1)
    glPatchParameteri(GL_PATCH_VERTICES, 1);
  if (Pr->Type == AG6_PRIM_PATCHLINE)
    glPatchParameteri(GL_PATCH_VERTICES, VER);
 

  ProgId = AG6_RndMaterialApply(Pr->MtNo);

  /* Setup transform coefficients */
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, WVP.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrOrtho")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, Ortho.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, W.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrN")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MatrN.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, AG6_Anim.Time);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &AG6_hRndCamLoc.X);
  if ((loc = glGetUniformLocation(ProgId, "CamRight")) != -1)
    glUniform3fv(loc, 1, &AG6_hRndCamRight.X);
  if ((loc = glGetUniformLocation(ProgId, "CamUp")) != -1)
    glUniform3fv(loc, 1, &AG6_hRndCamUp.X);
  if ((loc = glGetUniformLocation(ProgId, "IsWireFrame")) != -1)
    glUniform1f(loc, AG6_Anim.IsWireFrame);

  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(PrimType, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  else
    glDrawArrays(PrimType, 0, Pr->NumOfI);

  glUseProgram(0);

  glBindVertexArray(0);
} /* End of 'AG6_RndPrimDraw' function */

/* Loading primitive from file function
 * ARGUMENTS: 
 *   -primitive
 *       AG6PRIM *Pr;
 *   -File name 
 *        char *FileName;
 * RETURNS:
 *  (int) Error level for operation system.    
 */
int AG6_RndPrimLoad( ag6PRIM *Pr, char *FileName ) 
{
  int nv, ni, size, *I;
  ag6VERTEX *V;
  FILE *F;
  char Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(ag6PRIM));

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      ni += 3;

  /* Calculate memory size for primitive data */
  size = sizeof(ag6VERTEX) * nv + sizeof(int) * ni;

  /* Allocate arrays for virtexes and indexes */
  V = malloc(size);
  if (V == NULL)
    return FALSE;

  /* Fill all allocated memory by 0 */
  memset(V, 0, size);

  /* Set index array pointer */
  I = (int *)(V + nv);

  /* Load primitive data */
  rewind(F);
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;

      sscanf(Buf + 2, "%f%f%f", &x, &y, &z);
      V[nv].P = VecSet(x, y, z);
      V[nv].T = Vec2Set(0, 0);
      V[nv].N = VecSet(0, 0, 0);
      V[nv++].C = Vec4Set(1.0, 1.0 , 0, 0);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      int n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);

      I[ni++] = n1 - 1;
      I[ni++] = n2 - 1;
      I[ni++] = n3 - 1;
    }
  fclose(F);

  AG6_AutoNormal(V, nv, I, ni);

  AG6_RndPrimCreate(Pr, AG6_PRIM_TRIMESH, V, nv, I, ni);
  free(V);

  return TRUE;
} /* End of 'AG6_RndPrimLoad' function */

/* END OF 'RNDPRIM.C' FILE */
