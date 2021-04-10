#version 430

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D TextureKd;
layout(binding = 1) uniform sampler2D TextureMask;

in vec2 DrawTexCoord;
in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;

uniform float Time;
uniform vec3 CamLoc;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ph;
uniform float Trans;

uniform bool IsTexture0;

vec3 Shade( vec3 P, vec3 N, vec3 L, vec3 LC )
{
  vec3 color;                                  
  vec3 V = normalize(P - CamLoc);
  vec3 R = reflect(V, N);
  vec4 tc = vec4(1, 1, 1, Trans);

  if (IsTexture0)
  {
    tc = texture(TextureKd, DrawTexCoord * vec2(1, -1));
    return tc.rgb / tc.a;
  }

  color = Ka;
  color += Kd * LC * max(dot(N, L), 0) * tc.rgb; 
  color += Ks * max(0, pow(dot(R, L), Ph)) * LC;

  return color;
}


void main( void )
{
  OutColor = vec4(Shade(DrawPos, normalize(DrawNormal), normalize(vec3(8 * sin(1.3 * Time), 1, 1)), vec3(1, 1, 1)), Trans);
}