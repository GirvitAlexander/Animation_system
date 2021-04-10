#version 430

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec2 DrawTexCoord;

layout(binding = 0) uniform sampler2D Texture0;

void main( void )
{
  vec4 tc = texture(Texture0, DrawTexCoord);
  if (tc.g < 0.00030)
    discard;

  OutColor = vec4(DrawColor.rgb, DrawColor.a * tc.g);
  //OutColor = vec4(1, 1, 1, 1);
}