// ==========================================================================
// $Id: simple_shape.cpp,v 1.1 2014/01/18 16:43:12 jlang Exp $
// Simple shape for interactions
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
// $Log: simple_shape.cpp,v $
// Revision 1.1  2014/01/18 16:43:12  jlang
// Created solution for lab1 in OpenGL 4
//
// Revision 1.1  2011/01/15 00:23:37  jlang
// Created lab1 including skeleton
//
//
// ==========================================================================

#include "simple_shape.h"


const GLuint SimpleShape::g_primitives[] = { GL_POINTS,
					     GL_LINES,
					     GL_LINE_STRIP,
					     GL_TRIANGLES,
					     GL_TRIANGLE_STRIP,
					     GL_TRIANGLE_FAN,
					     GL_QUADS,
					     GL_QUAD_STRIP };

//const GLfloat SimpleShape::g_xVal[] =
//{ -3.0f, -3.0f, -2.0f, -2.0f, -1.0f, -1.0f,
//1.0f, 1.0f, 2.0f, 2.0f, 3.0f, 3.0f };
//const GLfloat SimpleShape::g_yVal[] =
//{ 1.0f, -1.0f, 1.2f, -0.8f, 1.0f, -1.0f,
//1.2f, -0.8f, 1.0f, -1.0f, 1.2f, -0.8f };





const int SimpleShape::g_nPoints = 26;

