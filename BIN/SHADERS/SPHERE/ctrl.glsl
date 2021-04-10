#version 430

uniform float Time;

layout(vertices = 1) out;

void main( void )
{
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

  float n = 64 - 63 * abs(sin(Time / 8));

  // Outer split values
  gl_TessLevelOuter[0] = n;  // by U0
  gl_TessLevelOuter[1] = n / 2;  // by V0
  gl_TessLevelOuter[2] = n;  // by U1
  gl_TessLevelOuter[3] = n / 2;  // by V1

  // Inner split values
  gl_TessLevelInner[0] = n;  // by U
  gl_TessLevelInner[1] = n / 2;  // by V
}
