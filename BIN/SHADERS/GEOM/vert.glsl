#version 430

layout(location = 0) in vec3 InPosition;

void main( void )
{
  gl_Position = vec4(InPosition, 1);
}