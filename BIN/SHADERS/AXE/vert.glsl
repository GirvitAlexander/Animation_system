#version 430

layout(location = 0) in vec3 InPosition;
layout(location = 3) in vec4 InColor;

uniform mat4 MatrWVP;
uniform mat4 MatrW;

out vec4 DrawColor;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  DrawColor = MatrW * vec4(InPosition.xyz, 1);
}
