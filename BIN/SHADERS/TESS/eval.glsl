#version 430

layout (isolines) in;

void main( void )
{
  vec4 p0 = gl_in[0].gl_Position,
  p1 = gl_in[1].gl_Position,
  p2 = gl_in[2].gl_Position,
  p3 = gl_in[3].gl_Position;

  float t = gl_TessCoord.x;
  
  gl_Position = p0 * (1 - t) * (1 - t) * (1 - t) +
                  p1 * 3 * (1 - t) * (1 - t) * t +
                  p2 * 3 * (1 - t) * t * t +
                  p3 * t * t * t; 
} 