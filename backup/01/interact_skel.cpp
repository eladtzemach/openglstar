#define NOMINMAX
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>

// glm types
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
// matrix manipulation
#include <glm/gtc/matrix_transform.hpp>
// value_ptr
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "simple_shape.h"
#include "basic_menu_skel.h"

using namespace CSI4130;
#include <iostream>
using namespace std;

/** Global variables */
SimpleShape g_myShape;
BasicMenu g_basicMenu( g_myShape );

/*
 * Helper structure for the array of vertices
 */
struct VArray {
  static const GLuint numVerts= 26;
  glm::vec2 vertex[numVerts];
  VArray() {
    for (int i = 0; i != numVerts; ++i){
      vertex[i] = glm::vec2(g_myShape.getX(i),g_myShape.getY(i));
	  cout << g_myShape.getX(i) << " " << g_myShape.getY(i) << endl;
    }
  }
 
}; 
VArray g_array;


/*
 * Helper structure holding the locations of the uniforms to transform matrices
 */
struct Transformations {
  GLint locMV;
  GLint locP;
  Transformations() : locMV(-1), locP(-1) {}
};
Transformations g_tfm;


/*
 * Window dimensions
 */
struct WindowSize {
  GLint widthPixel;
  GLfloat width;
  GLint heightPixel;
  GLfloat height;
  WindowSize() : widthPixel(512), width(20.0f),
		 heightPixel(512), height(20.0f) {}
}; 
WindowSize g_winSize;  

GLuint g_bufferObject=0;
GLuint g_program;
GLfloat scale_up = 2.0f;
GLfloat scale_down = 0.5f;

/**
 * Display routine - vertex array object
 */
void interactDisplay( void ) {
  // Clear the window
  glClear( GL_COLOR_BUFFER_BIT );
  // Use glm to emulate fixed function pipeline
  // Load identity
  glm::mat4 ModelView = glm::mat4(1.0f);
  // Set translation, rotation and scaling
  
  glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(g_myShape.d_scale));
  ModelView = ModelView * scale;
  glUniformMatrix4fv(g_tfm.locMV, 1, GL_FALSE, glm::value_ptr(ModelView));
  

  // Update uniform ModelView for this drawing

  // VAO is still bound - simply draw with the current primitive
  glDrawArrays(g_myShape.getPrimitive(), 0, g_array.numVerts );
  errorOut();
  // swap buffers
  glutSwapBuffers();
}


/**
 * Idle routine - rotate basic shape when we have
 * nothing else to do 
 */
void interactIdleFunc() {

}

/**
 * Menu callback
 */
void interactMenuFunc( int _val ) {
  g_basicMenu.menu( _val, interactIdleFunc );
}

/**
 * Keyboard routine - handle keyboard input
 */
void interactKeyboardFunc(unsigned char _key, int _x, int _y ) {
  // printf( "Key %c code %d\n", _key, _key );
  switch( _key ) {
  case 'p':
    // Toggle between geometric primitives
    g_myShape.nextPrimitive();
    break;

  case 'z': 
	  g_myShape.zoom(scale_up);
	  break; 
  case 'x': 
	  g_myShape.zoom(scale_down);
	  break; 





  case 'a':
    {
      // Toggle animation



    }
    break;
  case 'q':
  case 27:
    // q or ESC to quit
    exit(0);
    break;
  }
  glutPostRedisplay();
  return;
}

/**
 * Special key routine
 */
void interactSpecialKeyboardFunc( int _key , int _x, int _y ) {
  switch( _key ) 
    {
    case GLUT_KEY_LEFT:	
      break;





    default: 
      break;
    }
  // Make sure to redraw
  glutPostRedisplay();
  return;
}


/**
 * OpenGL reshape function - main window
 */
void interactReshapeFunc( GLsizei _width, GLsizei _height ) {
  GLfloat minDim = std::min(g_winSize.width,g_winSize.height);
  // adjust the view volume to the correct aspect ratio




  glm::mat4 Projection = glm::ortho( -g_winSize.width/2.0f, g_winSize.width/2.0f, 
				     -g_winSize.height/2.0f, g_winSize.height/2.0f ); 
  glUniformMatrix4fv(g_tfm.locP, 1, GL_FALSE, glm::value_ptr(Projection));
  g_winSize.widthPixel = _width;
  g_winSize.heightPixel = _height;
  // reshape our viewport
  glViewport( 0, 0, 
	      g_winSize.widthPixel,
	      g_winSize.heightPixel );
}


/**
 * OpenGL initialization - set the state machine
 */
void interactInit( void ) {
  // glut menu -- register call back
  g_basicMenu.init(interactMenuFunc);
  // darkgray background
  glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );
  // Point size to something visible
  glPointSize( 2.0f );
  
  // Make sure that our shaders run
  int major, minor;
  getGlVersion( major, minor );
  cerr << "Running OpenGL "<< major << "." << minor << endl; 
  if ( major < 4 ) {
    cerr << "No OpenGL 4.x or higher" <<endl;
    exit(-1);
  }

  // Generate a VAO
  GLuint vao;
  glGenVertexArrays(1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &g_bufferObject );
  errorOut();
  glBindBuffer(GL_ARRAY_BUFFER, g_bufferObject );
  glBufferData(GL_ARRAY_BUFFER, 
	       sizeof(glm::vec2) * g_array.numVerts,
	       g_array.vertex, GL_STATIC_DRAW);
  // pointer into the array of vertices which is now in the VAO
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray(0);
  errorOut();

  // Load shaders
  vector<GLuint> sHandles;
  GLuint handle;
  Shader triangle;
  if ( !triangle.load("interact.vs", GL_VERTEX_SHADER )) {
    triangle.installShader( handle, GL_VERTEX_SHADER );
    Shader::compile( handle );
    sHandles.push_back( handle );
  }
  if ( !triangle.load("interact.fs", GL_FRAGMENT_SHADER )) {
    triangle.installShader( handle, GL_FRAGMENT_SHADER ); 
    Shader::compile( handle );
    sHandles.push_back( handle );
  }
  cerr << "No of handles: " << sHandles.size() << endl;
  Shader::installProgram(sHandles, g_program); 
  // enable the shaders
  glUseProgram(g_program);
  errorOut();
  errorOut();   
  // find the locations of our uniforms and store them in a global structure for later access
  g_tfm.locMV = glGetUniformLocation( g_program, "ModelViewMatrix");
  g_tfm.locP = glGetUniformLocation( g_program, "ProjectionMatrix");
  errorOut();

  // set the projection matrix with a uniform
  glm::mat4 Projection = glm::ortho( -g_winSize.width/2.0f, g_winSize.width/2.0f, 
				     -g_winSize.height/2.0f, g_winSize.height/2.0f);
  glUniformMatrix4fv(g_tfm.locP, 1, GL_FALSE, glm::value_ptr(Projection));
  errorOut();

  return;
}


/**
 * Main for a simple GLUT application
 */
int main( int argc, char** argv ) {
  // Pass the program name on
  glutInit(&argc, argv);
  // Set the glut state
  // Double buffering and RGB color 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );

  // Set-up the glut OpenGL window
  // glut's coordinate system has origin at top-left corner
  // ( column, row )
  glutInitWindowPosition( 0, 0 );
  // Window w/h according to g_winSize
  glutInitWindowSize( g_winSize.widthPixel, g_winSize.heightPixel);
  glutCreateWindow( "Simple shape" );
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    cerr << "Error: " << glewGetErrorString(err) << endl;
    return -1;
  }
  cerr << "Using GLEW " << glewGetString(GLEW_VERSION) << endl;

  // Initialize OpenGL state
  interactInit();

  // Set up callback functions for key presses
  glutKeyboardFunc( interactKeyboardFunc ); // Handles ascii symbols
  glutSpecialFunc( interactSpecialKeyboardFunc ); // Handles function keys

  // Set the reshape callback
  glutReshapeFunc( interactReshapeFunc );

  // drawing callback
  glutDisplayFunc( interactDisplay );

  // Go into forever loop and process events
  glutMainLoop(  );

  // never reached
  return 0;	
}
