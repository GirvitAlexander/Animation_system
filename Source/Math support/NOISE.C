/* FILE NAME: NOISE.C
 * PROGRAMMER: AG6
 * DATE: 11.02.2019
 * PURPOSE: ANIMATIOM SYSTEM
 */

#include "rnd.h"

#define TAB_BITS 10
#define TAB_SIZE (1 << TAB_BITS)
#define TAB_MASK (TAB_BITS - 1)

#define INDEX1(X) (Perm[(X) & TAB_MASK])
#define INDEX2(X, Y) (Perm[(X + INDEX1(Y)) & TAB_MASK])
#define INDEX3(X, Y, Z) (Perm[(X + INDEX2(Y, Z)) & TAB_MASK])
#define INDEX4(X, Y, Z, W) (Perm[(X + INDEX3(Y, Z, W)) & TAB_MASK])

/* Table of noise */
DBL TabNoise[TAB_SIZE];

/* Table of translation */
int Perm[TAB_SIZE]; 


/* Noise intialization function.
 * ARGUMENTS:
 *   None.
 * RETURNS: None.
 */
VOID NoiseInit( VOID )
{
  int i;

  for (i = 0; i < TAB_SIZE; i++)
    TabNoise[i] = (DBL)rand() / RAND_MAX;
  for (i = 0; i < TAB_SIZE; i++)
    Perm[i] = i;
  for (i = 0; i < TAB_SIZE * 8; i++)
  {
    int
      a = rand() & TAB_MASK,
      b = rand() & TAB_MASK,
      tmp = Perm[a];

    Perm[a] = Perm[b];
    Perm[b] = tmp;
  }
} /* End of 'NoiseInit' function */

/* Noise create function.
 * ARGUMENTS:
 *   - X coordinate:
 *      DBL X;
 * RETURNS: 
 *    (DBL) noise.
 */
DBL Noise( DBL X )
{
  int ix = floor(X), ix1;
  DBL fx;

  fx = X - ix;
  fx = (3 - 2 * fx) * fx * fx; 
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;

  return TabNoise[ix] * (1 - fx) + TabNoise[ix1] * fx;
} /* End of 'Noise' function */

/* Noise turbulenced create function.
 * ARGUMENTS:
 *   - x coordinate
 *      DBL X;
 *   - octaves
 *      int Octaves;
 * RETURNS: (DBL) Noise.
 */
DBL NoiseTurb1D( DBL X, int Octaves )
{
  int i, frac = 1;
  DBL val = 0;

  for (i = 0; i < Octaves; i++)
  {
    val += Noise(X) / frac;
    X = (X + 25.47) * 2;
    frac *= 2;
  }
  return val * (1 << (Octaves - 1) / ((1 << Octaves) - 1));
} /* End of 'NoiseTurb1D' function */

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
DBL Noise2D( DBL X, DBL Y )
{
  int ix = floor(X), iy = floor(Y), ix1, iy1;
  DBL fx, fy;

  fx = X - ix;
  fx = (3 - 2 * fx) * fx * fx; 
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;

  fy = Y - iy;
  fy = (3 - 2 * fy) * fy * fy; 
  iy &= TAB_MASK;
  iy1 = (iy + 1) & TAB_MASK;


  return TabNoise[INDEX2(iy, ix)] * (1 - fx) * (1 - fy) +
         TabNoise[INDEX2(iy, ix1)] * (1 - fx) * fy +
         TabNoise[INDEX2(iy1, ix)] * fx * (1 - fy) +
         TabNoise[INDEX2(iy1, ix1)] * fx * fy;
} /* End of 'NoiseTurb1D' function */


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
DBL NoiseTurb2D( DBL X, DBL Y, int Octaves )
{
  int i, frac = 1;
  DBL val = 0;

  for (i = 0; i < Octaves; i++)
  {
    val += Noise2D(X, Y) / frac;
    X = (X + 25.47) * 2;
    Y = (Y + 25.47) * 2;
    frac *= 2;
  }
  return val * (1 << (Octaves - 1) / ((1 << Octaves) - 1));
} /* End of 'NoiseTurb1D' function */

VOID NoiseMakeTex( UINT TabTexId, UINT TabPermId )
{
  int i, h, w;
  static FLT Tab[TAB_SIZE];

  for (i = 0; i < TAB_SIZE; i++)
    Tab[i] = TabNoise[i];

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindTexture(GL_TEXTURE_2D, TabTexId + 1);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, TAB_SIZE, 1);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TAB_SIZE, 1, GL_RED, GL_FLOAT, Tab);

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindTexture(GL_TEXTURE_2D, TabPermId + 1);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32I, TAB_SIZE, 1);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TAB_SIZE, 1, GL_RED, GL_INT, Perm);

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
 
  glBindTexture(GL_TEXTURE_2D, 0);
} /* End of 'NoiseMakeTex' function */



/* END OF 'NOISE.C' FILE */