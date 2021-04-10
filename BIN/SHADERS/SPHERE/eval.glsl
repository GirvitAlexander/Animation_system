/* glsl GEOMETRY SHADER */

#version 430

layout(quads, fractional_even_spacing) in;

uniform mat4 MatrWVP;
uniform mat4 MatrW;
uniform mat4 MatrV;
uniform mat4 MatrN;

uniform float Time;

out vec3 DrawN;

vec3 get_p( float u, float v )
{
  float phy = u * 2 * acos(-1);
  float theta = v * acos(-1);
  float r = 0.5;
  vec3 p;

  p.x = r * sin(phy) * sin(theta);
  p.y = r * cos(theta);
  p.z = r * cos(phy) * sin(theta);

  return p;
}

void main( void )
{
  vec3 p = get_p(gl_TessCoord.x, gl_TessCoord.y);
  gl_Position = MatrWVP * vec4(p, 1);
  DrawN = normalize(p);
}
