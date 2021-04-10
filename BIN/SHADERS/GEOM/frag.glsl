#version 430

layout(location = 0) out vec4 OutColor;

uniform float Time;
uniform bool IsWireframe;
    
layout(binding = 0) uniform sampler2D Texture0;  
layout(binding = 1) uniform sampler2D TexturePerm;
layout(binding = 2) uniform sampler2D TextureN;

in vec2 FDrawTexCoord;


#define TAB_BITS 8
#define TAB_SIZE (1 << TAB_BITS)
#define TAB_MASK (TAB_BITS - 1)
int Perm( int i )
{
  return int((texelFetch(TexturePerm, ivec2(i, 0), 0).r));
}

int TabNoise( int i )
{
  return int((texelFetch(TextureN, ivec2(i, 0), 0).r));
}

#define INDEX1(X) (Perm((X) & TAB_MASK))
#define INDEX2(X, Y) (Perm((X + INDEX1(Y)) & TAB_MASK))
#define INDEX3(X, Y, Z) (Perm((X + INDEX2(Y, Z)) & TAB_MASK))
#define INDEX4(X, Y, Z, W) (Perm((X + INDEX3(Y, Z, W)) & TAB_MASK)) 

float Noise( float X )
{
  int ix = int(floor(X)), ix1;
  float fx;

  fx = X - ix;
  fx = (3 - 2 * fx) * fx * fx; 
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;

  return TabNoise(ix) * (1 - fx) + TabNoise(ix1) * fx;
} 


float NoiseTurb1D( float X, int Octaves )
{
  int i, frac = 1;
  float val = 0;

  for (i = 0; i < Octaves; i++)
  {
    val += Noise(X) / frac;
    X = (X + 25.47) * 2;
    frac *= 2;
  }
  return val * (1 << (Octaves - 1) / ((1 << Octaves) - 1));
} 

float Noise2D( float X, float Y )
{
  int ix = int(floor(X)), iy = int(floor(Y)), ix1, iy1;
  float fx, fy;

  fx = X - ix;
  fx = (3 - 2 * fx) * fx * fx; 
  ix &= TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;

  fy = Y - iy;
  fy = (3 - 2 * fy) * fy * fy; 
  iy &= TAB_MASK;
  iy1 = (iy + 1) & TAB_MASK;


  return TabNoise(INDEX2(iy, ix)) * (1 - fx) * (1 - fy) +
         TabNoise(INDEX2(iy, ix1)) * (1 - fx) * fy +
         TabNoise(INDEX2(iy1, ix)) * fx * (1 - fy) +
         TabNoise(INDEX2(iy1, ix1)) * fx * fy;
} 

float NoiseTurb2D( float X, float Y, int Octaves )
{
  int i, frac = 1;
  float val = 0;

  for (i = 0; i < Octaves; i++)
  {
    val += Noise2D(X, Y) / frac;
    X = (X + 25.47) * 2;
    Y = (Y + 25.47) * 2;
    frac *= 2;
  }
  return val * (1 << (Octaves - 1) / ((1 << Octaves) - 1));
}

void main( void )
{
  vec4 c = texture2D(Texture0, FDrawTexCoord);

  if (IsWireframe)
    c = vec4(1, 0.1, 0.5, 1);
  OutColor = c;
}
