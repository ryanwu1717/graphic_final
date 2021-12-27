//#include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
//#ifdef __APPLE__
//#include <OpenGL/OpenGL.h>
//#include <GLUT/glut.h>
//#else
//#include "glut.h"
//#endif
#include "imageloader.h"
#include "loadTGA.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stb_image.h>



using namespace std;

int ghurbe = 1;
int jolbe = 1;
float tx = 0.0f;
float ty = -2.0f;
float tz = -12.0f;
float _angle = 0.0f;
float britto = 0.0f;
int ghurarAngle = 2;
float scaleErZ = 1.0f;
int din = 1;
//sphere code
float radius = 0.3f;
//sphere code
float ballX = 3.0f;
float ballY = -0.3f;
float ballZ = -5.0f;
float colR = 3.0;
float colG = 1.5;
float colB = 1.0;
float bgColR = 0.0;
float bgColG = 0.0;
float bgColB = 0.0;
GLuint textureId;  //texture ID
static int flag = 1;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y){
    switch (key){
    case 27: //Escape key
        exit(0);
    }
    
    if (key == GLUT_KEY_RIGHT) {
        ballX -= 0.05f;
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_LEFT) {
        ballX += 0.05f;
        glutPostRedisplay();
    }
}

void drawBall(void) {
    glColor3f(colR, colG, colB); //set ball colour
    glTranslatef(ballX, ballY, ballZ); //moving it toward the screen a bit on creation
    glutSolidSphere(0.08, 30, 30); //create ball.
}

void drawAv(void) {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-0.9, -0.7, -1.0);
    glVertex3f(-0.5, -0.1, -1.0);
    glVertex3f(-0.2, -1.0, -1.0);
    glVertex3f(0.5, 0.0, -1.0);
    glVertex3f(0.6, -0.2, -1.0);
    glVertex3f(0.9, -0.7, -1.0);
    glEnd();
}
void drawClouds() {}


/*void drawScene2()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(bgColR, bgColG, bgColB, 0.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //Add ambient light
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    //drawing the SUN
    glPushMatrix();
    drawBall();
    glPopMatrix();
    //drawing the Mount Avarest
    glPushMatrix();
    drawAv();
    glPopMatrix();

    //drawing the Clouds
    glPushMatrix();
    drawClouds();
    glPopMatrix();

    glutSwapBuffers();
}*/

//float _angle = 30.0f;
void update5(int value) {

    if (ballX > 4.0f){
        ballX = -0.8f;
        ballY = -0.3f;
        flag = 1;
        colR = 2.0;
        colG = 1.50;
        colB = 1.0;
        bgColB = 0.0;
    }

    if (flag){
        ballX -= 0.001f;
        ballY += 0.0007f;
        colR -= 0.001;
        //colG+=0.002;
        colB += 0.005;
        bgColB += 0.001;

        if (ballX > 3)
            flag = 0;
    }
    if (!flag){
        ballX -= 0.001f;
        ballY -= 0.0007f;
        colR += 0.001;
        colB -= 0.01;
        bgColB -= 0.001;

        if (ballX < -0.3)
            flag = 1;
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update5, 0);
}

//loadTexture function takes an Image object and returns a GLuint (which is kind of like an unsigned int) giving the id that OpenGL assigned to the texture.
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image)
{
    GLuint textureId;

    //The first argument is the number of textures we need, and the second is an array where OpenGL will store the id's of the textures.
    glGenTextures(1, &textureId); //Make room for our texture
    // to assign the texture id to our image data.
//	We call glBindTexture(GL_TEXTURE_2D, textureId) to let OpenGL know
// that we want to work with the texture we just created. Then, we call glTexImage2D to load the image into OpenGL.
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
        0,                            //0 for now
        GL_RGB,                       //Format OpenGL uses for image
        image->width, image->height,  //Width and height
        0,                            //The border of the image
        GL_RGB, //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
        //as unsigned numbers
        image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId2; //The id of the texture
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;
GLuint _textureId7;
GLuint _textureId8;
GLuint _textureId9;

//Initializes 3D rendering
void initRendering()
{

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);


    //you can have upto 8 lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #0
    glEnable(GL_LIGHT2); //Enable light #0
    glEnable(GL_LIGHT3); //Enable light #0

    glEnable(GL_NORMALIZE); //Automatically normalize normals
    glShadeModel(GL_SMOOTH); //Enable smooth shading

    //Take a look at imageloader.h. This gives us the basic idea of what loadBMP does.
    //(The actual code for loadBMP is in imageloader.cpp.) Given a filename, it returns an Image object,
    //which contains the width and height of the image, as well as the array pixels,
    //which stores the pixels' colors in the format we want.
    Image* image = loadBMP("mati.bmp");
    _textureId = loadTexture(image);

    image = loadBMP("prmd.bmp");
    _textureId2 = loadTexture(image);

    image = loadBMP("sky1.bmp");
    _textureId3 = loadTexture(image);

    image = loadBMP("sky2.bmp");
    _textureId4 = loadTexture(image);

    image = loadBMP("sky3.bmp");
    _textureId5 = loadTexture(image);

    image = loadBMP("sand03.bmp");
    _textureId6 = loadTexture(image);




    delete image;
}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //drawing the SUN
    glPushMatrix();
    drawBall();
    glPopMatrix();

    //gluLookAt ( 0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    glTranslatef(tx, ty, tz);
    //Add ambient light
    //sh that shines everywhere in our scene by the same amount
    //every face gets the same amount
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2) and intensity //can be greater than 1 so not like color
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    glShadeModel(GL_SMOOTH); //Enable smooth shading
    //Add positioned light
    GLfloat lightColor0[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Color (0.5, 0.5, 0.5)
    GLfloat lightaColor0[] = { 0.2f, 0.2f, 0.2f, 0.2f }; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = { 0.0f, 3.0f, 6.0f, 1.0f }; //Positioned at (2, 4, 3)
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightaColor0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    GLfloat lightColor4[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //Color (0.5, 0.2, 0.2)
    GLfloat lightPos4[] = { 0.0f, 6.0f, 6.0f, 1.0f };
    //glLightfv(GL_LIGHT4, GL_AMBIENT, lightColor4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, lightColor4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, lightColor4);
    glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);

    //On to drawScene. We start by calling glEnable(GL_TEXTURE_2D) to enable applying textures
    //	and glBindTexture(GL_TEXTURE_2D, _textureId) to tell OpenGL that we want to use the texture with id _textureId.
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    //The first call tells OpenGL to use the blocky mapping (GL_NEAREST)
    //	when the texture is far away from us, and the second call tells it to use blocky mapping when the texture is close.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // blurry mapping, we'd pass GL_LINEAR as the third parameter of these two functions.
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*
                if(ghurarAngle==1)
                glRotatef(_angle, 1.0f, 0.0f, 0.0f);
                else if(ghurarAngle==2)
                glRotatef(_angle, 0.0f, 1.0f, 0.0f);
                else if(ghurarAngle==3)
                glRotatef(_angle, 0.0f, 0.0f, 1.0f);

    /**/

    glColor3f(1.0f, 1.0f, 1.0f);
    glScalef(1.0f, 1.0f, scaleErZ);
    glRotatef(8.0f, 1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
    glTranslatef(-1.46f, 1.25f, 1.7f);
    //glTranslatef(-2.52113f, 1.99764f, 0.69634f);
    //glRotatef(90.379f, 1.0f, 0.0f, 0.0f);
    //glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-49.686f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.036f, -0.7143f, 0.2396f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.3193f, 0.2396f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.036f, -0.3193f, 0.2396f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0025f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glNormal3f(0.0025f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.95f, 0.9438f);
    glNormal3f(0.0025f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.7071f, 0.7071f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(-0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glNormal3f(-0.7071f, 0.7071f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.5249f, -1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.2396f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.23f, -0.23f, 0.23f);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.23f, -0.23f, -0.23f);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.23f, -0.23f, -0.23f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.23f, -0.23f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.2396f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.3193f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.5988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.009f, -0.0544f, 0.9985f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glNormal3f(-0.009f, -0.0544f, 0.9985f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(-0.009f, -0.0544f, 0.9985f);
    glVertex3f(0.1f, -0.7143f, 0.5988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0006f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(0.0006f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glNormal3f(0.0006f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7311f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0116f, -0.0544f, 0.9985f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glNormal3f(-0.0116f, -0.0544f, 0.9985f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(-0.0116f, -0.0544f, 0.9985f);
    glVertex3f(0.1f, -0.7311f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0008f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(0.0008f, 0.9985f, -0.0546f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glNormal3f(0.0008f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.748f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0142f, -0.0544f, 0.9984f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glNormal3f(-0.0142f, -0.0544f, 0.9984f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(-0.0142f, -0.0544f, 0.9984f);
    glVertex3f(0.1f, -0.748f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0009f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(0.0009f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glNormal3f(0.0009f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7648f, 0.6741f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0168f, -0.0544f, 0.9984f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glNormal3f(-0.0168f, -0.0544f, 0.9984f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(-0.0168f, -0.0544f, 0.9984f);
    glVertex3f(0.1f, -0.7648f, 0.6741f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0011f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(0.0011f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glNormal3f(0.0011f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7816f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0195f, -0.0544f, 0.9983f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glNormal3f(-0.0195f, -0.0544f, 0.9983f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(-0.0195f, -0.0544f, 0.9983f);
    glVertex3f(0.1f, -0.7816f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0012f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(0.0012f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glNormal3f(0.0012f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.7985f, 0.7243f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0221f, -0.0544f, 0.9983f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glNormal3f(-0.0221f, -0.0544f, 0.9983f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(-0.0221f, -0.0544f, 0.9983f);
    glVertex3f(0.1f, -0.7985f, 0.7243f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0013f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(0.0013f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glNormal3f(0.0013f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.8153f, 0.7493f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0247f, -0.0544f, 0.9982f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glNormal3f(-0.0247f, -0.0544f, 0.9982f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(-0.0247f, -0.0544f, 0.9982f);
    glVertex3f(0.1f, -0.8153f, 0.7493f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0015f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(0.0015f, 0.9985f, -0.0546f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glNormal3f(0.0015f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.8321f, 0.7744f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0273f, -0.0544f, 0.9981f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glNormal3f(-0.0273f, -0.0544f, 0.9981f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(-0.0273f, -0.0544f, 0.9981f);
    glVertex3f(0.1f, -0.8321f, 0.7744f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0016f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(0.0016f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glNormal3f(0.0016f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.849f, 0.7995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0299f, -0.0544f, 0.9981f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glNormal3f(-0.0299f, -0.0544f, 0.9981f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(-0.0299f, -0.0544f, 0.9981f);
    glVertex3f(0.1f, -0.849f, 0.7995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0018f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(0.0018f, 0.9985f, -0.0546f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glNormal3f(0.0018f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.8658f, 0.8246f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0324f, -0.0544f, 0.998f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glNormal3f(-0.0324f, -0.0544f, 0.998f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(-0.0324f, -0.0544f, 0.998f);
    glVertex3f(0.1f, -0.8658f, 0.8246f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0019f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(0.0019f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glNormal3f(0.0019f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.8827f, 0.8497f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.035f, -0.0544f, 0.9979f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glNormal3f(-0.035f, -0.0544f, 0.9979f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(-0.035f, -0.0544f, 0.9979f);
    glVertex3f(0.1f, -0.8827f, 0.8497f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0021f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(0.0021f, 0.9985f, -0.0546f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glNormal3f(0.0021f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.8995f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0376f, -0.0544f, 0.9978f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glNormal3f(-0.0376f, -0.0544f, 0.9978f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(-0.0376f, -0.0544f, 0.9978f);
    glVertex3f(0.1f, -0.8995f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0022f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(0.0022f, 0.9985f, -0.0545f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glNormal3f(0.0022f, 0.9985f, -0.0545f);
    glVertex3f(0.1f, -0.9163f, 0.8998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0402f, -0.0544f, 0.9977f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glNormal3f(-0.0402f, -0.0544f, 0.9977f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(-0.0402f, -0.0544f, 0.9977f);
    glVertex3f(0.1f, -0.9163f, 0.8998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0023f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(0.0023f, 0.9985f, -0.0546f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glNormal3f(0.0023f, 0.9985f, -0.0546f);
    glVertex3f(0.1f, -0.9332f, 0.9249f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0428f, -0.0544f, 0.9976f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glNormal3f(-0.0428f, -0.0544f, 0.9976f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glNormal3f(-0.0428f, -0.0544f, 0.9976f);
    glVertex3f(0.1f, -0.9332f, 0.9249f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8246f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7985f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.748f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8246f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8658f, 0.8246f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6741f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.648f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8236f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6741f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7648f, 0.6741f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8827f, 0.8497f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6731f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8487f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7816f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8995f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6982f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8998f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8738f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7985f, 0.7243f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.5988f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8998f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9163f, 0.8998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7233f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9249f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8153f, 0.7493f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9332f, 0.9249f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9239f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9249f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7744f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7483f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5988f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.5988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7744f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8321f, 0.7744f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5978f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7995f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7311f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.9946f, -0.1038f, 0.0f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glNormal3f(-0.9946f, -0.1038f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glNormal3f(-0.9946f, -0.1038f, 0.0f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7995f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.849f, 0.7995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6229f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.648f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6982f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.5249f, -1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.5249f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.5249f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.5249f, 1.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.5249f, -1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.5249f, 1.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.95f, -0.95f, -0.9761f);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, -0.5878f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, 0.5878f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.95f, -0.95f, -0.9761f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.95f, -0.95f, 0.9761f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, -0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.95f, -0.95f, -0.9761f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.5118f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, 0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0327f, 0.0f, 0.9995f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glNormal3f(0.0327f, 0.0f, 0.9995f);
    glVertex3f(0.7915f, -1.2954f, -0.5878f);
    glNormal3f(0.0327f, 0.0f, 0.9995f);
    glVertex3f(0.7915f, -0.95f, -0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0327f, 0.0f, -0.9995f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glNormal3f(0.0327f, 0.0f, -0.9995f);
    glVertex3f(0.3115f, -1.2954f, 0.5721f);
    glNormal3f(0.0327f, 0.0f, -0.9995f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.543f, -0.9489f, 0.5118f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.386f, -1.2954f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9212f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.543f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.543f, -1.2954f, 0.5118f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.386f, -0.9187f, 0.02f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.3115f, -0.9187f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.386f, -0.9187f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.02f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.438f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.3049f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.438f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4388f, -0.9187f, 0.3049f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4385f, -0.9212f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9187f, 0.438f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9212f, 0.4383f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9212f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.438f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4385f, -0.9212f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.438f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.543f, -0.9489f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.543f, -0.9489f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5257f, -0.9439f, 0.4995f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5257f, -0.9439f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5257f, -0.9439f, 0.4995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5083f, -0.9389f, 0.4872f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5083f, -0.9389f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5083f, -0.9389f, 0.4872f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4909f, -0.9338f, 0.4749f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4909f, -0.9338f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4909f, -0.9338f, 0.4749f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4736f, -0.9288f, 0.4626f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4736f, -0.9288f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4736f, -0.9288f, 0.4626f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4562f, -0.9238f, 0.4503f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4562f, -0.9238f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4562f, -0.9238f, 0.4503f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9464f, 0.4998f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9464f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9464f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9439f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9439f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9414f, 0.4875f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9414f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9414f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9389f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9389f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9363f, 0.4752f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9363f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9363f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9338f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9338f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9313f, 0.4629f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9313f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9313f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9288f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9288f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9263f, 0.4506f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9263f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9263f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9238f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9238f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9212f, 0.4383f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9212f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9464f, 0.4998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.3115f, -0.9464f, 0.4998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9414f, 0.4875f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9414f, 0.4875f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9363f, 0.4752f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.3115f, -0.9363f, 0.4752f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9313f, 0.4629f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9313f, 0.4629f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9263f, 0.4506f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9263f, 0.4506f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9212f, 0.4383f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.543f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5257f, -0.9439f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5257f, -0.9439f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5083f, -0.9389f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5083f, -0.9389f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4909f, -0.9338f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4909f, -0.9338f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4736f, -0.9288f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4736f, -0.9288f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9238f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4562f, -0.9238f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4562f, -0.9238f, 0.3049f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4385f, -0.9212f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9464f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9464f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9464f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9439f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9414f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9414f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9414f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9389f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9363f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9363f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9363f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9338f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9313f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9313f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9313f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9288f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9263f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9263f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9238f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9263f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9238f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9238f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0592f, 0.0204f, 0.998f);
    glVertex3f(-0.036f, -0.7143f, 0.2396f);
    glNormal3f(-0.0592f, 0.0204f, 0.998f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glNormal3f(-0.0592f, 0.0204f, 0.998f);
    glVertex3f(0.1f, -0.3193f, 0.2396f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0024f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glNormal3f(0.0024f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.9514f, 0.9179f);
    glNormal3f(0.0024f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.95f, 0.9438f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.23f, -0.23f, -0.23f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0299f, 0.4069f, -0.913f);
    glVertex3f(0.95f, -0.95f, -0.9761f);
    glNormal3f(-0.0299f, 0.4069f, -0.913f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glNormal3f(-0.0299f, 0.4069f, -0.913f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0299f, 0.4069f, 0.913f);
    glVertex3f(0.95f, -0.95f, 0.9761f);
    glNormal3f(-0.0299f, 0.4069f, 0.913f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(-0.0299f, 0.4069f, 0.913f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.23f, -0.23f, 0.23f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.1f, -0.3193f, 0.3193f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0203f, 0.8944f, 0.4468f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(-0.0203f, 0.8944f, 0.4468f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glNormal3f(-0.0203f, 0.8944f, 0.4468f);
    glVertex3f(-0.036f, -0.95f, 0.9438f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0049f, 0.7036f, 0.7106f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(0.0049f, 0.7036f, 0.7106f);
    glVertex3f(-0.036f, -0.95f, 0.9438f);
    glNormal3f(0.0049f, 0.7036f, 0.7106f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, -1.5249f, -1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.5249f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.2396f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.3193f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.2396f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, 0.23f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.23f, -0.23f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.23f, -0.23f, -0.23f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.95f, 0.9438f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9514f, 0.9179f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9346f, 0.8932f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9177f, 0.8684f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9009f, 0.8437f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8841f, 0.819f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8672f, 0.7943f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8504f, 0.7695f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8336f, 0.7448f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8167f, 0.7201f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7999f, 0.6954f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7831f, 0.6706f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7662f, 0.6459f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7494f, 0.6212f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7325f, 0.5964f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.2396f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.2396f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.2396f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.95f, 0.9438f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.036f, -0.3193f, 0.2396f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.2396f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.3193f, 0.3193f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.2396f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0103f, -0.0641f, 0.9979f);
    glVertex3f(-0.036f, -0.7143f, 0.5976f);
    glNormal3f(-0.0103f, -0.0641f, 0.9979f);
    glVertex3f(-0.036f, -0.7325f, 0.5964f);
    glNormal3f(-0.0103f, -0.0641f, 0.9979f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0006f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(0.0006f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7325f, 0.5964f);
    glNormal3f(0.0006f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0129f, -0.0641f, 0.9979f);
    glVertex3f(-0.036f, -0.7311f, 0.6223f);
    glNormal3f(-0.0129f, -0.0641f, 0.9979f);
    glVertex3f(-0.036f, -0.7494f, 0.6212f);
    glNormal3f(-0.0129f, -0.0641f, 0.9979f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0007f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(0.0007f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7494f, 0.6212f);
    glNormal3f(0.0007f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0155f, -0.0641f, 0.9978f);
    glVertex3f(-0.036f, -0.748f, 0.6471f);
    glNormal3f(-0.0155f, -0.0641f, 0.9978f);
    glVertex3f(-0.036f, -0.7662f, 0.6459f);
    glNormal3f(-0.0155f, -0.0641f, 0.9978f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0009f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(0.0009f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7662f, 0.6459f);
    glNormal3f(0.0009f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0181f, -0.0641f, 0.9978f);
    glVertex3f(-0.036f, -0.7648f, 0.6718f);
    glNormal3f(-0.0181f, -0.0641f, 0.9978f);
    glVertex3f(-0.036f, -0.7831f, 0.6706f);
    glNormal3f(-0.0181f, -0.0641f, 0.9978f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.001f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(0.001f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7831f, 0.6706f);
    glNormal3f(0.001f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0207f, -0.0641f, 0.9977f);
    glVertex3f(-0.036f, -0.7816f, 0.6965f);
    glNormal3f(-0.0207f, -0.0641f, 0.9977f);
    glVertex3f(-0.036f, -0.7999f, 0.6954f);
    glNormal3f(-0.0207f, -0.0641f, 0.9977f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0011f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(0.0011f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7999f, 0.6954f);
    glNormal3f(0.0011f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0233f, -0.0641f, 0.9977f);
    glVertex3f(-0.036f, -0.7985f, 0.7213f);
    glNormal3f(-0.0233f, -0.0641f, 0.9977f);
    glVertex3f(-0.036f, -0.8167f, 0.7201f);
    glNormal3f(-0.0233f, -0.0641f, 0.9977f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0013f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(0.0013f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8167f, 0.7201f);
    glNormal3f(0.0013f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0259f, -0.0641f, 0.9976f);
    glVertex3f(-0.036f, -0.8153f, 0.746f);
    glNormal3f(-0.0259f, -0.0641f, 0.9976f);
    glVertex3f(-0.036f, -0.8336f, 0.7448f);
    glNormal3f(-0.0259f, -0.0641f, 0.9976f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0014f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(0.0014f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8336f, 0.7448f);
    glNormal3f(0.0014f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0285f, -0.0641f, 0.9975f);
    glVertex3f(-0.036f, -0.8321f, 0.7707f);
    glNormal3f(-0.0285f, -0.0641f, 0.9975f);
    glVertex3f(-0.036f, -0.8504f, 0.7695f);
    glNormal3f(-0.0285f, -0.0641f, 0.9975f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0016f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(0.0016f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8504f, 0.7695f);
    glNormal3f(0.0016f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0311f, -0.064f, 0.9975f);
    glVertex3f(-0.036f, -0.849f, 0.7954f);
    glNormal3f(-0.0311f, -0.064f, 0.9975f);
    glVertex3f(-0.036f, -0.8672f, 0.7943f);
    glNormal3f(-0.0311f, -0.064f, 0.9975f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0017f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(0.0017f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8672f, 0.7943f);
    glNormal3f(0.0017f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0337f, -0.064f, 0.9974f);
    glVertex3f(-0.036f, -0.8658f, 0.8202f);
    glNormal3f(-0.0337f, -0.064f, 0.9974f);
    glVertex3f(-0.036f, -0.8841f, 0.819f);
    glNormal3f(-0.0337f, -0.064f, 0.9974f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0019f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(0.0019f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8841f, 0.819f);
    glNormal3f(0.0019f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0363f, -0.064f, 0.9973f);
    glVertex3f(-0.036f, -0.8827f, 0.8449f);
    glNormal3f(-0.0363f, -0.064f, 0.9973f);
    glVertex3f(-0.036f, -0.9009f, 0.8437f);
    glNormal3f(-0.0363f, -0.064f, 0.9973f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.002f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(0.002f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.9009f, 0.8437f);
    glNormal3f(0.002f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0389f, -0.064f, 0.9972f);
    glVertex3f(-0.036f, -0.8995f, 0.8696f);
    glNormal3f(-0.0389f, -0.064f, 0.9972f);
    glVertex3f(-0.036f, -0.9177f, 0.8684f);
    glNormal3f(-0.0389f, -0.064f, 0.9972f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0021f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(0.0021f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.9177f, 0.8684f);
    glNormal3f(0.0021f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0415f, -0.064f, 0.9971f);
    glVertex3f(-0.036f, -0.9163f, 0.8943f);
    glNormal3f(-0.0415f, -0.064f, 0.9971f);
    glVertex3f(-0.036f, -0.9346f, 0.8932f);
    glNormal3f(-0.0415f, -0.064f, 0.9971f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0023f, 0.9985f, -0.0549f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(0.0023f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.9346f, 0.8932f);
    glNormal3f(0.0023f, 0.9985f, -0.0549f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0441f, -0.064f, 0.997f);
    glVertex3f(-0.036f, -0.9332f, 0.9191f);
    glNormal3f(-0.0441f, -0.064f, 0.997f);
    glVertex3f(-0.036f, -0.9514f, 0.9179f);
    glNormal3f(-0.0441f, -0.064f, 0.997f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8658f, 0.8246f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8246f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.648f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8236f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8246f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7662f, 0.648f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7648f, 0.6741f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6741f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8841f, 0.8236f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8827f, 0.8497f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6731f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6741f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8487f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7831f, 0.6731f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7816f, 0.6992f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9009f, 0.8487f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8995f, 0.8748f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6982f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8738f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7999f, 0.6982f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7985f, 0.7243f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9177f, 0.8738f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9163f, 0.8998f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7233f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.5988f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5988f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8988f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8167f, 0.7233f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8153f, 0.7493f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9346f, 0.8988f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9332f, 0.9249f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9249f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7483f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9332f, 0.9249f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.9514f, 0.9239f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8336f, 0.7483f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8321f, 0.7744f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7744f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5978f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7744f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7325f, 0.5978f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7311f, 0.6239f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8504f, 0.7734f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.849f, 0.7995f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6229f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7143f, 0.2477f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.8672f, 0.7985f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7985f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.7494f, 0.6229f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.748f, 0.649f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, -0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5988f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5978f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9239f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8988f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9249f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.9239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.8738f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.8998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8988f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8998f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8988f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8487f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8748f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.2477f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5978f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8497f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8236f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7985f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8246f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8236f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.8236f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7985f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7985f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7995f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7985f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7483f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7744f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7483f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7734f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.5978f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6239f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6229f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.7233f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.7493f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.6229f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7233f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6229f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.7233f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.649f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.648f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.6982f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.7243f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, -0.95f, 0.648f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6741f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6731f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.648f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6741f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.1f, -0.95f, 0.6992f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.5249f, -1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.5249f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.5249f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.5249f, -1.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.5249f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.5249f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.5249f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.5249f, 1.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.5249f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.95f, -0.95f, -0.9761f);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.95f, -0.95f, 0.9761f);
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, -0.5878f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, -0.5878f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, 0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.95f, -0.95f, -0.9761f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, -0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, -0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, -0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.153f, -0.95f, 0.95f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.95f, -0.95f, 0.9761f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, 0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, -0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, -0.5721f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.386f, -1.2954f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.386f, -1.2954f, 0.02f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.5118f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5118f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, -0.5721f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.386f, -1.2954f, 0.02f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, -0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.5118f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5721f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, 0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.7915f, -1.2954f, -0.5878f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.386f, -1.2954f, 0.02f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0327f, 0.0f, 0.9995f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glNormal3f(0.0327f, 0.0f, 0.9995f);
    glVertex3f(0.3115f, -1.2954f, -0.5721f);
    glNormal3f(0.0327f, 0.0f, 0.9995f);
    glVertex3f(0.7915f, -1.2954f, -0.5878f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0327f, 0.0f, -0.9995f);
    glVertex3f(0.7915f, -0.95f, 0.5878f);
    glNormal3f(0.0327f, 0.0f, -0.9995f);
    glVertex3f(0.7915f, -1.2954f, 0.5878f);
    glNormal3f(0.0327f, 0.0f, -0.9995f);
    glVertex3f(0.3115f, -1.2954f, 0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, -0.5721f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, -0.5721f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5721f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.95f, 0.5721f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5118f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.543f, -0.9489f, 0.3049f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.543f, -0.9489f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(-0.0567f, 0.0f, 0.9984f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.3115f, -1.2954f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.3115f, -0.9489f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.386f, -1.2954f, 0.02f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9212f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.543f, -1.2954f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -1.2954f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.543f, -1.2954f, 0.5118f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.543f, -0.9489f, 0.5118f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -1.2954f, 0.5118f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.386f, -0.9187f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.386f, -0.9187f, 0.02f);
    glNormal3f(0.9772f, -0.0f, -0.2124f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.386f, -0.9489f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.3115f, -0.9489f, 0.02f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.3115f, -0.9187f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.02f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.438f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.3049f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.2971f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4479f, -0.9187f, 0.3049f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4388f, -0.9187f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4388f, -0.9187f, 0.438f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9187f, 0.438f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9212f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9212f, 0.4383f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9187f, 0.438f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4385f, -0.9212f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4388f, -0.9187f, 0.438f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.543f, -0.9489f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5257f, -0.9439f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5257f, -0.9439f, 0.4995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5257f, -0.9439f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5083f, -0.9389f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.5083f, -0.9389f, 0.4872f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.5083f, -0.9389f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4909f, -0.9338f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4909f, -0.9338f, 0.4749f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4909f, -0.9338f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4736f, -0.9288f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4736f, -0.9288f, 0.4626f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4736f, -0.9288f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4562f, -0.9238f, 0.3049f);
    glNormal3f(0.9921f, -0.1251f, 0.0f);
    glVertex3f(0.4562f, -0.9238f, 0.4503f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4562f, -0.9238f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4385f, -0.9212f, 0.3049f);
    glNormal3f(0.141f, 0.99f, 0.0f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9464f, 0.4998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9464f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9464f, 0.4998f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9439f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9414f, 0.4875f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9414f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9414f, 0.4875f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9389f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9363f, 0.4752f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9363f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9363f, 0.4752f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9338f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9313f, 0.4629f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9313f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9313f, 0.4629f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9288f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9263f, 0.4506f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9263f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9263f, 0.4506f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9238f, 0.2971f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.3115f, -0.9212f, 0.4383f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9489f, 0.5118f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.543f, -0.9489f, 0.5118f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.5253f, -0.9464f, 0.4998f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.5257f, -0.9439f, 0.4995f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9439f, 0.4995f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.5257f, -0.9439f, 0.4995f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.508f, -0.9414f, 0.4875f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.5083f, -0.9389f, 0.4872f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9389f, 0.4872f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.5083f, -0.9389f, 0.4872f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.4906f, -0.9363f, 0.4752f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.4909f, -0.9338f, 0.4749f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9338f, 0.4749f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4909f, -0.9338f, 0.4749f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4732f, -0.9313f, 0.4629f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.4736f, -0.9288f, 0.4626f);
    glNormal3f(0.0f, 0.1067f, 0.9943f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9288f, 0.4626f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4736f, -0.9288f, 0.4626f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.4559f, -0.9263f, 0.4506f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.4562f, -0.9238f, 0.4503f);
    glNormal3f(0.0f, 0.1068f, 0.9943f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.3115f, -0.9238f, 0.4503f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4562f, -0.9238f, 0.4503f);
    glNormal3f(-0.0f, 0.9787f, 0.2051f);
    glVertex3f(0.4385f, -0.9212f, 0.4383f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9489f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9464f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5253f, -0.9464f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9464f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9414f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.508f, -0.9414f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9414f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9363f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4906f, -0.9363f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9363f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9313f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4732f, -0.9313f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9313f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9263f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4559f, -0.9263f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9263f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9238f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4562f, -0.9238f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9238f, 0.3049f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9489f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9464f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9464f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9464f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9439f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9439f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9439f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9414f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9414f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9414f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9389f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9389f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9389f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9363f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9363f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9363f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9338f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9338f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9338f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9313f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9313f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9313f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9288f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9288f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9288f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9263f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9263f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9263f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9238f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9238f, 0.3049f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9238f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.3115f, -0.9212f, 0.2971f);
    glNormal3f(0.0567f, 0.0f, -0.9984f);
    glVertex3f(0.4479f, -0.9212f, 0.3049f);
    glEnd();
    glPopMatrix();


    //first pyramid
    glBegin(GL_TRIANGLES);
    //Front
    glNormal3f(0.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.2f, 0.0f, 1.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.6f, 0.0f, 1.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 2.3f, 0.0f);

    //Left

    glNormal3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.2f, 0.0f, 1.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.7f, 0.0f, -1.2f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, 2.3f, 0.0f);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //3rd pyramid
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_TRIANGLES);
    //Front
    glNormal3f(0.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.0f, 3.0f, -2.0f);

    //left
    glNormal3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, -3.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.0f, 3.0f, -2.0f);

    glEnd();

    // Backmost Pyramid
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_TRIANGLES);
    //Front
    glNormal3f(0.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(6.5f, 0.0f, -3.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.75f, 2.4f, -4.0f);

    //left

    glNormal3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(3.2f, 0.0f, -5.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.75f, 2.4f, -4.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, _textureId6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //floor
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, 0.0f, 7.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 7.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(11.5f, 0.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-11.5f, 0.0f, -5.0f);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //aakash
   /* glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-15.0f, 11.3f, -10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(15.0f, 11.3f, -10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(15.0f, -5.0f, -10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-15.0f, -5.0f, -10.0f);
    glEnd();*/
    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, _textureId3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0); //bottom floor
    glTexCoord2f(0.25, 0); glVertex3f(-300.0, -300.0, 300.0);
    glTexCoord2f(0.5, 0); glVertex3f(300.0, -300.0, 300.0);
    glTexCoord2f(0.5, 0.33); glVertex3f(300.0, -300.0, -300.0);
    glTexCoord2f(0.25, 0.33); glVertex3f(-300.0, -300.0, -300.0);

    glNormal3f(0.0, -1.0, 0.0); //top wall
    //glTexCoord2f(0.0f, 0.0f); glVertex3f(-11.5f, 10.0f, -5.0f);
    //glTexCoord2f(1.0f, 0.0f); glVertex3f(11.5f, 10.0f, -5.0f);
    //glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 1.0f, 7.5f);
    //glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 1.0f, 7.5f);

    glNormal3f(0.0, 0.0, 1.0); //front wall
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, 7.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, 7.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 1.0f, 7.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 1.0f, 7.5f);

    glNormal3f(0.0, 0.0, -1.0); //back wall
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-11.5f, 0.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(11.5f, 0.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(11.5f, 10.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-11.5f, 10.0f, -5.0f);

    glNormal3f(1.0, 0.0, 0.0); //left wall
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, 7.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-11.5f, 0.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-11.5f, 10.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 10.0f, 7.5f);

    glNormal3f(-1.0, 0.0, 0.0); //right wall
    glTexCoord2f(0.0f, 0.0f); glVertex3f(11.5f, 0.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, 7.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 10.0f, 7.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(11.5f, 10.0f, -5.0f);

   

    glEnd();
    
    glDisable(GL_TEXTURE_2D);

    if (din == 1)
    {
        //sphere code
        glTranslatef(4.0f, 7.0f, 4.0f);
        glColor3f(0.99609f, 0.9375f, 0.0f);
        glScalef(1.0f, 1.0f, scaleErZ);
        glutSolidSphere(radius, 20, 20);
        // Flush buffers to screen
        glFlush();
        //sphere code
    }
    if (din == 0)
    {
        //sphere code
        glTranslatef(-4.0f, 7.0f, 4.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glScalef(1.0f, 1.0f, scaleErZ);
        glutSolidSphere(radius, 20, 20);
        // Flush buffers to screen
        glFlush();
        //sphere code
    }
    glutSwapBuffers();
}
void update(int value)
{

    if (ghurbe == 1)
    {
        _angle += 0.2f;
        if (_angle > 360)
        {
            _angle -= 360;
        }

        glutPostRedisplay();
        glutTimerFunc(25, update, 0);
    }
    else if (ghurbe == 0)
    {
        _angle = _angle;
        if (_angle > 360)
        {
            _angle -= 360;
        }
        glutPostRedisplay();
        glutTimerFunc(25, update, 0);
    }
}

void update1(int value)
{

    if (ghurbe == 1)
    {
        _angle -= 0.2f;
        if (_angle > 360)
        {
            _angle -= 360;
        }
        glutPostRedisplay();
        glutTimerFunc(25, update1, 0);
    }
    else if (ghurbe == 0)
    {
        _angle = _angle;
        if (_angle > 360)
        {
            _angle -= 360;
        }
        glutPostRedisplay();
        glutTimerFunc(25, update1, 0);
    }
}

void my_keyboard(unsigned char key, int x, int y)
{
    if (key == 'x')
        ghurarAngle = 1;
    if (key == 'y')
        ghurarAngle = 2;
    if (key == 'z')
        ghurarAngle = 3;
    if (key == 'd') //din
    {
        din = 1;
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT4);
    }
    if (key == 'n') //rat
    {
        din = 0;
        glEnable(GL_LIGHT4);
        glDisable(GL_LIGHT0);
    }
    if (key == 'o')//zoom in
        tz -= 0.5;
    if (key == 'i')//zoom out
        tz += 0.5;
}

void spe_key(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_LEFT:
        tx -= .15;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        tx += .15;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        ty += .15;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        ty -= .15;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F1:
        tz -= .15;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F2:
        tz += .15;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void my_mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutTimerFunc(50, update, 0);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutTimerFunc(50, update1, 0);
        break;
    default:
        break;
    }
}



void skybox()
{
    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0); //bottom floor
    glTexCoord2f(0.25, 0); glVertex3f(-300.0, -300.0, 300.0);
    glTexCoord2f(0.5, 0); glVertex3f(300.0, -300.0, 300.0);
    glTexCoord2f(0.5, 0.33); glVertex3f(300.0, -300.0, -300.0);
    glTexCoord2f(0.25, 0.33); glVertex3f(-300.0, -300.0, -300.0);

    glNormal3f(0.0, -1.0, 0.0); //top wall
    glTexCoord2f(0.25, 1); glVertex3f(-300.0, 300.0, 300.0);
    glTexCoord2f(0.5, 1); glVertex3f(300.0, 300.0, 300.0);
    glTexCoord2f(0.5, 0.66); glVertex3f(300.0, 300.0, -300.0);
    glTexCoord2f(0.25, 0.66); glVertex3f(-300.0, 300.0, -300.0);

    glNormal3f(0.0, 0.0, 1.0); //front wall
    glTexCoord2f(0.25, 0.5); glVertex3f(-300.0, -300.0, -300.0);
    glTexCoord2f(0.5, 0.5); glVertex3f(300.0, -300.0, -300.0);
    glTexCoord2f(0.5, 0.66); glVertex3f(300.0, 300.0, -300.0);
    glTexCoord2f(0.25, 0.66); glVertex3f(-300.0, 300.0, -300.0);

    glNormal3f(1.0, 0.0, 0.0); //left wall
    glTexCoord2f(0, 0.5); glVertex3f(-300.0, -300.0, 300.0);
    glTexCoord2f(0.25, 0.5); glVertex3f(-300.0, -300.0, -300.0);
    glTexCoord2f(0.25, 0.66); glVertex3f(-300.0, 300.0, -300.0);
    glTexCoord2f(0, 0.66); glVertex3f(-300.0, 300.0, 300.0);

    glNormal3f(-1.0, 0.0, 0.0); //right wall
    glTexCoord2f(0.75, 0.5); glVertex3f(300.0, -300.0, 300.0);
    glTexCoord2f(0.5, 0.5); glVertex3f(300.0, -300.0, -300.0);
    glTexCoord2f(0.5, 0.66); glVertex3f(300.0, 300.0, -300.0);
    glTexCoord2f(0.75, 0.66); glVertex3f(300.0, 300.0, 300.0);

    glNormal3f(0.0, 0.0, -1.0); //back wall
    glTexCoord2f(1, 0.5); glVertex3f(-300.0, -300.0, 300.0);
    glTexCoord2f(0.75, 0.5); glVertex3f(300.0, -300.0, 300.0);
    glTexCoord2f(0.75, 0.66); glVertex3f(300.0, 300.0, 300.0);
    glTexCoord2f(1, 0.66); glVertex3f(-300.0, 300.0, 300.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void initialize(void)
{
    float grey[] = { 0.2, 0.2, 0.2, 1.0 }; //for lighting purpose
    float white[] = { 1.0, 1.0, 1.0, 1.0 }; //diffuse and specular for light

    float mat_red[] = { 1.0, 0.0, 0.0, 1.0 }; //material ambient and diffuse
    float mat_white[] = { 1.0, 1.0, 1.0, 1.0 }; //material specular
    gluNewQuadric();

    glGenTextures(1, &textureId); 				// Create a Texture object
    glBindTexture(GL_TEXTURE_2D, textureId);		//Use the texture
    loadTGA("project.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	//set background colour to white
    glClearDepth(1.0f);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);	//enable light
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, mat_red); //give them a nice sunset specular reflection
    glLightfv(GL_LIGHT1, GL_DIFFUSE, mat_red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, mat_white);
    glLightf(GL_LIGHT1, GL_SHININESS, 60.0);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 1000);
}

void display(void)
{
    float lpos[] = { 10.0, 40.0, 10.0, 1.0 };  //light's position
    float shadowMat[] = { 40, 0, 0, 0, -10, 0, -10, -1, 0, 0, 40, 0, 0, 0, 0, 40 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

   // gluLookAt(cpx, cpy, cpz, epx, epy, epz, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);

    glColor4f(1.0, 1.0, 1.0, 1.0);
  //  if (mode1) {
  //      glRotatef(angle, 0.0, 1.0, 0.0); //for camera's left and right rotate
  //  }
    skybox();
    glutSwapBuffers();
}


unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
vector<std::string> faces
{
    ("sky.bmp"),
   ("sky1.bmp"),
   ("sky2.bmp"),
   ("sky3.bmp"),
   ("sky101.bmp"),
   ("sky101.bmp")
};


int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(300, 150);
    glutCreateWindow("The Pyramid of Giza");
    initRendering();
    //initialize();
    //glutDisplayFunc(display);
   // unsigned int cubemapTexture = loadCubemap(faces);
   // glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(my_keyboard);
    glutSpecialFunc(spe_key);
    glutMouseFunc(my_mouse);
    glutTimerFunc(25, update, 0); //Add a timer
    glutTimerFunc(25, update5, 0);
    glutMainLoop();
    return 0;
}
