#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 40) out;
uniform mat4 MatrWVP;
uniform float Time;
uniform vec3 CamRight;
uniform vec3 CamUp;

out vec2 FDrawTexCoord;

void main( void )
{
  int n = 10;
  float T = Time;
  float s = 10.30;
  vec3 p = gl_in[0].gl_Position.xyz;

  for (int i = 0; i < n; i++)
  {
    float angle = 0.1 * Time * (i + 1);
    float si = sin(angle), co = cos(angle);
    vec3 r = CamRight * co + CamUp * si;
    vec3 u = CamRight * -si + CamUp * co;
    
    p += vec3(0, s / 2, 0);
    gl_Position = MatrWVP * vec4(p + r * -s + u * s, 1);
    FDrawTexCoord = vec2(0, 1);
    EmitVertex();
    gl_Position = MatrWVP * vec4(p + r * -s + u * -s, 1);
    FDrawTexCoord = vec2(0, 0);
    EmitVertex();
    gl_Position = MatrWVP * vec4(p + r * s + u * s, 1);
    FDrawTexCoord = vec2(1, 1);
    EmitVertex();
    gl_Position = MatrWVP * vec4(p + r * s + u * -s, 1);
    FDrawTexCoord = vec2(1, 0);
    EmitVertex();
    EndPrimitive();
  } 
}
