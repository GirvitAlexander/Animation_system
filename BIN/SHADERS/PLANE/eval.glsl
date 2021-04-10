#version 430

layout (quads) in;

uniform float Time;

void main( void )
{
  int i;
  vec4 p[16];
  float u = gl_TessCoord.x, v = gl_TessCoord.y;

  for (i = 0; i < 16; i++)
    p[i] = gl_in[i].gl_Position;
  gl_Position = p[0] * (1 - u) * (1 - u) * (1 - u) * (1 - v) * (1 - v) * (1 - v) * 1 +
                p[1] * (1 - u) * (1 - u) * u       * (1 - v) * (1 - v) * (1 - v) * 3 +
                p[2] * (1 - u) * u       * u       * (1 - v) * (1 - v) * (1 - v) * 3 +
                p[3] * u       * u       * u       * (1 - v) * (1 - v) * (1 - v) * 1 +
                p[4] * (1 - u) * (1 - u) * (1 - u) * (1 - v) * (1 - v) * v       * 3 +
                p[5] * (1 - u) * (1 - u) * u       * (1 - v) * (1 - v) * v       * 9 +
                p[6] * (1 - u) * u       * u       * (1 - v) * (1 - v) * v       * 9 +
                p[7] * u       * u       * u       * (1 - v) * (1 - v) * v       * 3 +
                p[8] * (1 - u) * (1 - u) * (1 - u) * (1 - v) * v       * v       * 3 +
                p[9] * (1 - u) * (1 - u) * u       * (1 - v) * v       * v       * 9 +
                p[10] * (1 - u) * u       * u       * (1 - v) * v       * v      * 9 +
                p[11] * u       * u       * u       * (1 - v) * v       * v      * 3 +
                p[12] * (1 - u) * (1 - u) * (1 - u) * v       * v       * v      * 1 +
                p[13] * (1 - u) * (1 - u) * u       * v       * v       * v      * 3 +
                p[14] * (1 - u) * u       * u       * v       * v       * v      * 3 +
                p[15] * u       * u       * u       * v       * v       * v      * 1;
}
