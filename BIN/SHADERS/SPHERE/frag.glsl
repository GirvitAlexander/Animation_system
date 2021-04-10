#version 430

layout(location = 0) out vec4 OutColor;

in vec3 DrawPos;
in vec3 DrawWPos;
in vec3 DrawN;

uniform vec3 CamLoc;
uniform bool IsWireFrame;


vec3 Shade( vec3 N )
{
  vec3 L = normalize(vec3(1, 1, 1));
  vec3 color = vec3(1, 0, 0) * max(dot(N, L), 0.00001);
  return color;
}

void main( void )
{
  if (IsWireFrame)
  {
    OutColor = vec4(1, 1, 1, 1);
    return;
  }
  vec3 N = normalize(DrawN);
  OutColor = vec4(Shade(N), 1);
}
