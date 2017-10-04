
#ifndef CSI4130_SIMPLE_SHAPE_H_
#define CSI4130_SIMPLE_SHAPE_H_

#include <cassert>
#include <math.h> 

#include <GL/glew.h>
#if WIN32
#include <gl/wglew.h>
#else
#include <GL/glext.h>
#endif

#include <iostream>
using namespace std;


class SimpleShape {
private:
  const static int g_nPoints;

  const static GLuint g_primitives[];

  bool d_animated;

  int d_index;
public:
  GLfloat g_xVal[26];
  GLfloat g_yVal[26];

  GLfloat d_xPos;
  GLfloat d_yPos;

  GLfloat d_scale;
  GLfloat d_angle;


public:
  inline SimpleShape(); 
  
  inline void zoom( GLfloat _scale );
  inline void rotate( GLfloat _theta );
  inline void moveHorizontal( GLfloat _xShift );
  inline void moveVertical( GLfloat _yShift );
  inline int getNPoints() const;
  inline GLfloat getX( int _num );
  inline GLfloat getY( int _num );
  inline void nextPrimitive();
  inline GLuint getPrimitive();

  inline bool toggleAnimate();
};


SimpleShape::SimpleShape()
  : d_xPos(0.0f), d_yPos(0.0f),
  d_scale(1.0), d_angle(0.0f)
{

  const float kfPi = 3.1415926535897932384626433832795;
  const float kfRadius = 0.0616/2.0;
  const float kfInnerRadius = kfRadius*(1.0/(sin((2.0*kfPi)/5.0)*2.0*cos(kfPi/10.0) + sin((3.0*kfPi)/10.0)));
  int index = 1;

  g_xVal[0] = 0.0;
  g_yVal[0] = 0.0;

  for (int iVertIndex = 0; iVertIndex < 20; ++iVertIndex) {
      float fAngleStart = kfPi/2.0 + (iVertIndex*2.0*kfPi)/20.0;
      float fAngleEnd   = fAngleStart + kfPi/10.0;
      if (iVertIndex % 2 == 0) {
        g_xVal[index] = kfRadius*cos(fAngleStart)/1.9;
        g_yVal[index] = kfRadius*sin(fAngleStart);
        g_xVal[index+1] = kfInnerRadius*cos(fAngleEnd)/1.9;
        g_yVal[index+1] = kfInnerRadius*sin(fAngleEnd);
        index++;
      } else {
        g_xVal[index] = kfInnerRadius*cos(fAngleStart)/1.9;
        g_yVal[index] = kfInnerRadius*sin(fAngleStart);
        g_xVal[index+1] = kfRadius*cos(fAngleEnd)/1.9;
        g_yVal[index+1] = kfRadius*sin(fAngleEnd);
        index++;
  }}



}



void SimpleShape::zoom( GLfloat _scale ) {
  // scale in x and y
  d_scale *= _scale;
  return;
}

void SimpleShape::moveHorizontal( GLfloat _xShift ) {
  d_xPos += _xShift;
  return;
}

void SimpleShape::moveVertical( GLfloat _yShift ) {
  d_yPos += _yShift;
  return;
}

void SimpleShape::rotate( GLfloat _theta ) {
  d_angle += _theta;
  if ( d_angle > 360.0 ) d_angle -= 360.0;
  return;
} 

int SimpleShape::getNPoints() const {
  return g_nPoints;
}

GLfloat SimpleShape::getX( int _num ) {
  assert( _num < g_nPoints );
  return g_xVal[_num];
}

GLfloat SimpleShape::getY( int _num ) {
  assert( _num < g_nPoints );
  return g_yVal[_num];
}


void SimpleShape::nextPrimitive() {
  d_index = (++d_index)%8;
  return;
}

GLuint SimpleShape::getPrimitive() {
  return g_primitives[d_index];
}

bool SimpleShape::toggleAnimate() {
  d_animated = !d_animated;
  return d_animated;
}

#endif
