#version 430

layout(lines_adjacency) in;
layout(line_strip, max_vertices = 600) out;

uniform mat4 MatrWVP;

void Bezier( vec4 p0, vec4 p1, vec4 p2, vec4 p3 )
{
  float N = 32;
  float t = 0, step = 1.0 / N - 1.0;

  for (t = 0; t < 1; t += 0.01)
  {
    gl_Position = p0 * (1 - t) * (1 - t) * (1 - t) +
        p1 * 3 * (1 - t) * (1 - t) * t +
        p2 * 3 * (1 - t) * t * t +
        p3 * t * t * t;
    EmitVertex();
  }
  EndPrimitive();
}

void main( void )
{
  vec4 p[4];
  p[0] = gl_in[0].gl_Position,
  p[1] = gl_in[1].gl_Position,
  p[2] = gl_in[2].gl_Position,
  p[3] = gl_in[3].gl_Position;
  float a = 3.0 / 6.0;
                                                                         
  Bezier(p[1], p[1] + (p[2] - p[0]) * a, p[2] + (p[1] - p[3]) * a, p[2]);
}
