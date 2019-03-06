/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.
// Since all files need access to it, we define EXTERN as either blank or
// extern, depending on if included in the main program or not.

#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up

#ifdef MAINPROGRAM
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
vec3 center(0.0,0.0,0.0) ; // Center look at point
int amountinit = 5;
int w = 500, h = 500 ; // width and height

// New mod
int maxverts; // maxverts
int vertArray[maxverts][3]; // vertex array --
                            // vertArra[i][0] = x
                            // vertArra[i][1] = y
                            // vertArra[i][2] = z
int vertInd = 0; // vertex index, use to indicate which vertex is being processed
int triNum = 0; // number of triangles
std::vector<int> triVec; // vector that holds all triangle coordinates
int sphereInd = 0; // sphere index, use to indicate which sphere is bring processed
std::vector<double> sphereVec; // vector that holds all sphere coordinates

float fovy = 90.0 ; // For field of view
#else
EXTERN vec3 eyeinit ;
EXTERN vec3 upinit ;
EXTERN vec3 center ;
EXTERN int amountinit;
EXTERN int w, h ;
EXTERN float fovy ;
#endif

EXTERN bool useGlu; // Toggle use of "official" opengl/glm transform vs user
EXTERN GLuint vertexshader, fragmentshader, shaderprogram ; // shaders
EXTERN mat4 projection, modelview; // The mvp matrices
EXTERN GLuint projectionPos, modelviewPos; // Uniform locations of the above matrices
static enum {view, translate, scale} transop ; // which operation to transform
enum shape {cube, sphere, teapot} ;
EXTERN float sx, sy ; // the scale in x and y
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10 ;
EXTERN GLfloat lightposn [4*numLights] ; // Light Positions
EXTERN GLfloat lightcolor[4*numLights] ; // Light Colors
EXTERN GLfloat lightransf[4*numLights] ; // Lights transformed by modelview
EXTERN int numused ;                     // How many lights are used

// Materials (read from file)
// With multiple objects, these are colors for each.
EXTERN GLfloat ambient[3] ;
EXTERN GLfloat diffuse[3] ;
EXTERN GLfloat specular[3] ;
EXTERN GLfloat emission[4] ;
EXTERN GLfloat shininess ;

// For multiple objects, read from a file.
const int maxobjects = 10 ;
EXTERN int numobjects ;
EXTERN struct object {
  shape type ;
  GLfloat size ;
  GLfloat ambient[4] ;
  GLfloat diffuse[4] ;
  GLfloat specular[4] ;
  GLfloat emission[4] ;
  GLfloat shininess ;
  mat4 transform ;
} objects[maxobjects] ;

// Variables to set uniform params for lighting fragment shader
EXTERN GLuint lightcol ;
EXTERN GLuint lightpos ;
EXTERN GLuint numusedcol ;
EXTERN GLuint enablelighting ;
EXTERN GLuint ambientcol ;
EXTERN GLuint diffusecol ;
EXTERN GLuint specularcol ;
EXTERN GLuint emissioncol ;
EXTERN GLuint shininesscol ;
