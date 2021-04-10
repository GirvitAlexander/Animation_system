/* FILE NAME: RNDGRID.C
 * PROGRAMMER: ag6
 * DATE: 29.01.2019
 * PURPOSE: 
 */

#include "rndres.h"

/* Grid program free function.
 * ARGUMENTS:
 *   - GRID struct:
 *       ag6GRID *G;
 * RETURNS: None.
 */
VOID AG6_RndGridFree( ag6GRID *G )
{
  if (G->V != NULL)
    free(G->V);
  memset(G, 0, sizeof(ag6GRID));
} /* End of 'AG6_RndGridFree' function */

/* Create grid function.
 * ARGUMENTS:
 *   - grid structure:
 *       ag6GRID *G;
 *   - weight and high:
 *       int W, H;
 * RETUNRS:
 *   (int) TRUE if successful, FALSE otherwise.
 */
int AG6_RndGridCreate( ag6GRID *G, int W, int H )
{
  int i, v, j;

  memset(G, 0, sizeof(ag6GRID));
  if ((G->V = malloc(W * H * sizeof(ag6VERTEX))) == NULL)
    return FALSE;
  /* Setup all vertices */
  for (i = 0, v = 0; i < H; i++)
    for (j = 0; j < W; j++, v++)
    {
      G->V[v].P = VecSet(i, 0, j);
      G->V[v].T = Vec2Set(j / (W - 1.0), i / (H - 1.0));
      G->V[v].N = VecSet(0, 1, 0);
      G->V[v].C = Vec4Set(1, 1, 1, 1);
    }
    G->H = H;
    G->W = W;
    return TRUE;
}

/* Loading primitive from grid function.
 * ARGUMENTS:
 *   - PRIM struct:
 *       ag6PRIM *Pr;
 *   - GRID struct:
 *       ag6GRID *G;
 * RETURNS: None.
 */
VOID AG6_RndPrimFromGrid( ag6PRIM *Pr, ag6GRID *G )
{
  int *Ind, i, k, v, j;

  memset(Pr, 0, sizeof(ag6PRIM));
  /* Index array allocation */
  if ((Ind = malloc((G->H - 1) * (G->W * 2 + 1) * sizeof(int))) == NULL)
    return;
  for (i = 0, k = 0, v = 0; i < G->H - 1; i++)
  {
    for (j = 0; j < G->W; j++)
    {
      Ind[k++] = v + G->W;
      Ind[k++] = v++;
    }
    if (i < G->H - 2)
      Ind[k++] = -1;
  }
  /* Create primitive */
  AG6_RndPrimCreate(Pr, AG6_RND_PRIM_GRID,
    G->V, G->W * G->H, Ind, (G->H - 1) * (G->W * 2 + 1) - 1);
  free(Ind);
} /* End of 'AG6_RndPrimFromGrid' function */


/* Creating normals function.
 * ARGUMENTS:
 *   - GRID struct:
 *       ag6GRID *G;
 * RETURNS: None.
 */
VOID AG6_RndGridEvalNormals( ag6GRID *G )
{
  int i, k, j;

  /* Set all vertex normals to (0, 0, 0) */
  for (i = 0, k = 0; i < G->H; i++)
    for (j = 0; j < G->W; j++)
      G->V[k++].N = VecSet(0, 0, 0);

  /* Evaluate all triangles normals */
  for (i = 0, k = 0; i < G->H - 1; i++)
    for (j = 0; j < G->W - 1; j++, k++)
    {
      ag6VERTEX
        *p00= &G->V[k],
        *p01= &G->V[k + 1],
        *p10= &G->V[k + G->W],
        *p11= &G->V[k + G->W + 1];
      VEC N;
      N = VecNormalize(VecCrossVec(VecSubVec(p00->P, p10->P),
                                   VecSubVec(p11->P, p10->P)));
      p00->N = VecAddVec(p00->N, N);
      p10->N = VecAddVec(p10->N, N);
      p11->N = VecAddVec(p11->N, N);

      N = VecNormalize(VecCrossVec(VecSubVec(p11->P, p01->P),
                                   VecSubVec(p00->P, p01->P)));
      p00->N = VecAddVec(p00->N, N);
      p01->N = VecAddVec(p01->N, N);
      p11->N = VecAddVec(p11->N, N);
    }

    /* Normalize all vertex normals */
    for (i = 0; i < G->H * G->W; i++)
      G->V[i].N = VecNormalize(G->V[i].N);
} /* End of 'AG6_RndGridEvalNormals' function */

/* Create grid sphere function.
 * ARGUMENTS:
 *   - grid structure:
 *       ag6GRID *G;
 *   - weight and high:
 *       int W, H;
 *   - vector:
 *       VEC C;
 *   - radius sphare;
 *       FLT R;
 * RETUNRS:
 *   (int) TRUE if successful, FALSE otherwise.
 */
int AG6_RndGridCreateSphere( ag6GRID * G, int W, int H, VEC C, FLT R, FLT R2 )
{
  int i, v, j;

  if (!AG6_RndGridCreate(G, W, H))
    return FALSE;
  /* Setup all vertices */
  for (i = 0, v = 0; i < H; i++)
  {
    DBL
      theta = (H - 1 - i) * 2 * PI / (H - 1),
      sit = sin(theta), cot = cos(theta);
    for (j = 0; j < W; j++, v++)
    {
      DBL
        phi = j * 2 * PI / (W - 1),
        sip = sin(phi), cop = cos(phi),
        x = (R + R2 * cop) * cot,
        y = (R + R2 * cop) * sit,
        z = R * sip / 3;
      G->V[v].P = VecSet(C.X + x,
                         C.Y + y,
                         C.Z + z);
      G->V[v].N = VecSet(x, y, z);
    }
  }
  return TRUE;
} /* End of 'AG6_RndGridCreateSphere' function */



/* END OF 'RNDGRID.C' FILE */