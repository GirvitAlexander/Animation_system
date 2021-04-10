#version 430

layout(location = 0) out vec4 OutColor;

in vec2 DrawTexCoord;

uniform float Time;

uniform bool IsWireFrame;

layout(binding = 0) uniform sampler2D TexColor;
layout(binding = 1) uniform sampler2D TexNormal;

vec3 get( float x, float y )
{
  return texelFetch(TexColor, ivec2(gl_FragCoord.xy) + ivec2(x, y), 0).rgb;
}

void main( void )
{
  vec4 tc = texture(TexColor, DrawTexCoord);
  tc = texelFetch(TexColor, ivec2(gl_FragCoord.xy), 0);

  vec4 tc1 = texelFetch(TexNormal, ivec2(gl_FragCoord.xy), 0);
  vec3 f = (get(-1, -1) + get(0, -1) * 2 + get(1, -1)) -
           (get(-1, 1) + get(0, 1) * 2 + get(1, 1)),
       g = (get(-1, -1) + get(-1, 0) * 2 + get(-1, 1)) -
           (get(1, -1) + get(1, 0) * 2 + get(1, 1));
  if (texelFetch(TexNormal, ivec2(gl_FragCoord.xy), 0).a == 0.25)
  {
    OutColor = vec4(1, 0, 0, 1);
    return;
  }
  if (IsWireFrame)
    OutColor = vec4(tc.rgb, 1);
  else
    OutColor = /*vec4(0.4, 0.9, 0.6, 2) - */vec4(tc.rgb, 1);
}