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
 * Helper structure for the array of vertices (the star)
 */
struct VArray {
  static const GLuint numVerts= 26;
  glm::vec2 vertex[numVerts];
  VArray() {
    for (int i = 0; i != numVerts; ++i){
      vertex[i] = glm::vec2(g_myShape.getX(i),g_myShape.getY(i));
    }
  }
 
}; 

// The star's face vertices
struct VArray2 {
	static const GLuint numVerts = 18;
	glm::vec2 vertex[numVerts];
	VArray2() {
		    // Eyes
			vertex[0] = glm::vec2(-0.002, 0.005);
			vertex[1] = glm::vec2(0.002, 0.005);
			// Nose
			vertex[2] = glm::vec2(0.000, 0.002);
			vertex[3] = glm::vec2(0.000, 0.0015);
			vertex[4] = glm::vec2(0.000, 0.0010);
			vertex[5] = glm::vec2(0.000, 0.0005);
			vertex[6] = glm::vec2(0.000, 0.0000);
			// Smile
			vertex[7] = glm::vec2(-0.002, -0.004);
			vertex[8] = glm::vec2(-0.0015, -0.0045);
			vertex[9] = glm::vec2(-0.001, -0.005);
			vertex[10] = glm::vec2(-0.0005, -0.0055);
			vertex[11] = glm::vec2(0.0005, -0.0063);
			vertex[12] = glm::vec2(0.000, -0.006);
			vertex[13] = glm::vec2(0.001, -0.006);
			vertex[14] = glm::vec2(0.0015, -0.0055);
			vertex[15] = glm::vec2(0.002, -0.005);
			vertex[16] = glm::vec2(0.0025, -0.0045);
			vertex[17] = glm::vec2(0.003, -0.004);



	}

};

VArray g_array;
VArray2 g_array2;


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
GLuint g_bufferObject2 = 0;
GLuint g_program;
GLuint g_program2;
GLuint vao;
GLuint vao2;
GLfloat scale_up = 2.0f;
GLfloat scale_down = 0.5f;

/**
 * Display routine - vertex array object
 */
void interactDisplay( void ) {
  // Clear the window
  glClear( GL_COLOR_BUFFER_BIT );

  glUseProgram(g_program);
  errorOut();
  errorOut();
  // find the locations of our uniforms and store them in a global structure for later access
  g_tfm.locMV = glGetUniformLocation(g_program, "ModelViewMatrix");
  g_tfm.locP = glGetUniformLocation(g_program, "ProjectionMatrix");
  errorOut();

  // set the projection matrix with a uniform
  glm::mat4 Projection = glm::ortho(-g_winSize.width / 2.0f, g_winSize.width / 2.0f, -g_winSize.height / 2.0f, g_winSize.height / 2.0f);
  glUniformMatrix4fv(g_tfm.locP, 1, GL_FALSE, glm::value_ptr(Projection));
  errorOut();


  // Load identity
  glm::mat4 ModelView = glm::mat4(1.0f);
  // Set translation, rotation and scaling  
  glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(g_myShape.d_scale));
  // Update uniform ModelView for this drawing
  ModelView = ModelView * scale;
  glUniformMatrix4fv(g_tfm.locMV, 1, GL_FALSE, glm::value_ptr(ModelView));
  // Bind VAO and draw
  glBindVertexArray(vao);
  glDrawArrays(g_myShape.getPrimitive(), 0, g_array.numVerts );
  errorOut();





  // Unbind current VAO, use other shader program and VAO
  glBindVertexArray(0); 
  glUseProgram(g_program2);
  glBindVertexArray(vao2);

  // find the locations of our uniforms and store them in a global structure for later access
  g_tfm.locMV = glGetUniformLocation(g_program2, "ModelViewMatrix");
  g_tfm.locP = glGetUniformLocation(g_program2, "ProjectionMatrix");
  errorOut();

  glUniformMatrix4fv(g_tfm.locP, 1, GL_FALSE, glm::value_ptr(Projection));
  errorOut();

  glUniformMatrix4fv(g_tfm.locMV, 1, GL_FALSE, glm::value_ptr(ModelView));
  glEnable(GL_PROGRAM_POINT_SIZE);

  glDrawArrays(GL_POINTS, 0, g_array2.numVerts);
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
  glGenVertexArrays(1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &g_bufferObject );
  errorOut();
  glBindBuffer(GL_ARRAY_BUFFER, g_bufferObject );
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * g_array.numVerts, g_array.vertex, GL_STATIC_DRAW);
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








  glBindVertexArray(0); //unbindVAO
  // Generate and bind a second VAO
  glGenVertexArrays(1, &vao2);
  glBindVertexArray(vao2);

  glGenBuffers(1, &g_bufferObject2);
  errorOut();
  glBindBuffer(GL_ARRAY_BUFFER, g_bufferObject2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * g_array2.numVerts, g_array2.vertex, GL_STATIC_DRAW);
  // pointer into the array of vertices which is now in the VAO
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  errorOut();
  // Load the second set of shaders
  vector<GLuint> sHandles2;
  GLuint handle2;
  Shader triangle2;
  if (!triangle2.load("interact2.vs", GL_VERTEX_SHADER)) {
	  triangle2.installShader(handle2, GL_VERTEX_SHADER);
	  Shader::compile(handle2);
	  sHandles2.push_back(handle2);
  }
  if (!triangle2.load("interact2.fs", GL_FRAGMENT_SHADER)) {
	  triangle2.installShader(handle2, GL_FRAGMENT_SHADER);
	  Shader::compile(handle2);
	  sHandles2.push_back(handle2);
  }
  cerr << "No of handles: " << sHandles2.size() << endl;
  Shader::installProgram(sHandles2, g_program2);
  // End of Load the second set of shaders


  glBindVertexArray(0); //unbindVAO

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
