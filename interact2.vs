
#version 330 core

layout (location=0) in vec4 position;

out vec4 colorVertFrag; // Pass the color on to rasterization

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {
  const vec4 vertColor = vec4( 0.0, 0.0, 0.0, 0.0 );
  gl_PointSize = 10.0;	
  // map the vertex position into clipping space 
  gl_Position = ProjectionMatrix * ModelViewMatrix * position;
  colorVertFrag = vertColor;
}

