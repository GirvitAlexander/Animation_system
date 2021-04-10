#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform float Time;

out vec2 DrawTexCoord;

void main( void )
{
  DrawTexCoord = vec2(0, 1);
  gl_Position = vec4(-1, 1, 0, 1);
  EmitVertex();

  DrawTexCoord = vec2(0, 0);
  gl_Position = vec4(-1, -1, 0, 1);
  EmitVertex();
  
  DrawTexCoord = vec2(1, 1);
  gl_Position = vec4(1, 1, 0, 1);
  EmitVertex();

  DrawTexCoord = vec2(1, 0);
  gl_Position = vec4(1, -1, 0, 1);
  EmitVertex();
  EndPrimitive();
}
