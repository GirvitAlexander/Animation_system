#version 430

uniform float Time;

layout(vertices = 4) out;

void main( void )
{
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  int n = 64;

  gl_TessLevelOuter[0] = n;
  gl_TessLevelOuter[1] = n;
}
