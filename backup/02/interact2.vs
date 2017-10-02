// ==========================================================================
// $Id: interact.vs,v 1.3 2014/09/13 14:32:13 jlang Exp $
// Basic shader emulating fixed pipeline functionality
// ==========================================================================
// (C)opyright:
//
//   Jochen Lang
//   SITE, University of Ottawa
//   800 King Edward Ave.
//   Ottawa, On., K1N 6N5
//   Canada.
//   http://www.site.uottawa.ca
//
// Creator: jlang (Jochen Lang)
// Email:   jlang@site.uottawa.ca
// ==========================================================================
// $Log: interact.vs,v $
// Revision 1.3  2014/09/13 14:32:13  jlang
// Added core keyword in shader.
//
// Revision 1.2  2014/01/26 16:28:02  jlang
// Adapted program to run in OpenGL 3.3
//
// Revision 1.1  2014/01/18 16:43:12  jlang
// Created solution for lab1 in OpenGL 4
//
// Revision 1.1  2011/01/15 00:23:36  jlang
// Created lab1 including skeleton
//
// Revision 1.1  2011/01/08 04:36:11  jlang
// Lab 0 solution
//
// ==========================================================================
#version 330 core

layout (location=0) in vec4 position;

out vec4 colorVertFrag; // Pass the color on to rasterization

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {
  const vec4 vertColor = vec4( 1.0, 0.0, 0.0, 0.0 );
  gl_PointSize = 10.0;	
  // map the vertex position into clipping space 
  gl_Position = ProjectionMatrix * ModelViewMatrix * position;
  colorVertFrag = vertColor;
}

