
#version 330 core

layout (location=0) in vec4 position;
layout(location=12) in vec4 color;

out vec4 colorVertFrag; // Pass the color on to rasterization

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {

  // map the vertex position into clipping space 
  gl_Position = ProjectionMatrix * ModelViewMatrix * position;
  colorVertFrag = color;
}

