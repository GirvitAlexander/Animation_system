#version 430

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 3) in vec4 InColor;

uniform mat4 MatrWVP;
uniform mat4 MatrOrtho;

out vec4 DrawColor;
out vec2 DrawTexCoord;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  DrawColor = InColor;
  DrawTexCoord = InTexCoord;
}