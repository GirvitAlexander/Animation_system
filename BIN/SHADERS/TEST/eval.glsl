#version 430

layout (isolines) in;

void main( void )
{
  vec4 p[5];
  p[0] = gl_in[0].gl_Position,
  p[1] = gl_in[1].gl_Position,
  p[2] = gl_in[2].gl_Position,
  p[3] = gl_in[3].gl_Position,
  p[4] = gl_in[4].gl_Position;

  float t = gl_TessCoord.x, a = 1/6;
  int i;

  for (i = 0; i < 5; i++)
  {
    vec4 pi1 = p[i] + (p[i + 1] - p[i - 1]) * a,
         pi2 = p[i + 2] + (p[i] - p[i + 2]) * a;
    
    if (i == 0)
    {
      pi1 = p[0];
      pi2 = p[i + 1] + (p[i] - p[i + 2]) * a;
    }
    if (i == 3)
    {
      pi1 = p[i] + (p[i + 1] - p[i - 1]) * a;
      pi2 = p[0];
    }
    if (i == 4)
    {
      pi1 = p[i] + (p[i + 1] - p[i - 1]) * a;
      pi2 = p[0];
    }
    else 
    {
      pi1 = p[i] + (p[i + 1] - p[i - 1]) * a;
      pi2 = p[i + 2] + (p[i] - p[i + 2]) * a;
    }
    

  
    gl_Position = p[i] * (1 - t) * (1 - t) * (1 - t) +
                  pi1 * 3 * (1 - t) * (1 - t) * t +
                  pi2 * 3 * (1 - t) * t * t +
                  p[i - 1] * t * t * t;
  } 
} 