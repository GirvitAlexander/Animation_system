#version 430

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform mat4 MatrWVP;
uniform mat4 MatrW;
uniform mat4 MatrN;

uniform float Time;

out vec4 DrawColor;
out vec3 DrawNormal;
out vec3 DrawPos;
out vec2 DrawTexCoord;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);  
  DrawColor = InColor;
  DrawNormal = mat3(MatrN) * InNormal;
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawTexCoord = InTexCoord;
}