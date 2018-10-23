#include <iostream>
#include <stdio.h>
#include "map.h"
#include "camera.h"
#include "voxel.h"
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <math.h>

/*******************To Do List ******************
        -Add user interface
        -Add ability to read/write data from a file
        -Add ability to modify contents of the program
***********************************************/

using namespace std;

    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;
    float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

map heightMap(128,128,20,-20);
//camera camera(-25 , 0 , -32 , 45 , 45 , 0 , 0.185);
camera camera(0 , 0 , -32 , 45 , 45 , 0, 0.185);
//voxel voxel(-15,-15,-15,10,2);

void drawGrid()
{
    int i;
    for(i = 0; i<100; i++)
    {
        glPushMatrix();
        if(i<50) { glTranslatef(-12,0,i-12);}
        if(i>=50) { glTranslatef(i-62,0,-12); glRotatef(-90,0,1,0);}

        glBegin(GL_LINES);
        glColor3f(1,1,1); glLineWidth(2);
        glVertex3f(0,-0.1,0); glVertex3f(50,-0.1,0);
        glEnd();
        glPopMatrix();
    }
}


void display();
void init();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void animateMap(int);
void reshape(int w, int h);
void CameraTranslate(int vx, int vy, int vz);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("VoxelProject");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1,animateMap,0);
    init();


    glutMainLoop();
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.display();

    //voxel.draw();
    //drawGrid();
    heightMap.drawPoly();

    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,ASPECT_RATIO,0.1f,1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,1);
    //glutSetCursor(GLUT_CURSOR_NONE); //Make Cursor invisible
}

void keyboard(unsigned char key, int x, int y)
{
    if(key=='w'){camera.translate(0,0,1);}  if(key=='s'){camera.translate(0,0,-1);}
    if(key=='a'){camera.translate(1,0,0);}  if(key=='d'){camera.translate(-1,0,0);}
    if(key=='q'){camera.translate(0,-1,0);} if(key=='z'){camera.translate(0,1,0);}

    if(key=='e'){camera.rotate(2,0,0);}     if(key=='c'){camera.rotate(-2,0,0);}
    if(key=='.'){camera.rotate(0,2,0);}     if(key==','){camera.rotate(0,-2,0);}

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    //On mouse action a callback will be generated and this function will be called.
    //What I want to do is be able to rotate the camera based on mouse input.

    static float x1, y1, x2, y2, dx, dy, ax, ay;
    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        x1 = x;
        y1 = y;
        cout << x1 << ',' << y1 << endl;
        return;
    }

    if((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        x2 = x;
        y2 = y;

        //calculate camera angle rotation based on the difference of the starting and ending mouse coordinates
        dx = x2 - x1;
        dy = y2 - y1;
        ax = 360 * dx / float(SCREEN_WIDTH);
        ay = 180 * dy / float(SCREEN_HEIGHT);
        camera.rotate(ay,ax,0);
        cout << x2 << ',' << y2 << ',' << endl
             << dx << ',' << dy << ',' << endl
             << ax << ',' << ay << endl;

    }
    /*if((button == 3 || button == 4))
    {
        if(state == GLUT_UP) return;
        printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y); //print information
        (button == 3) ? camera.zoom(1.1) : camera.zoom(0.9);

    } else {
        printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);


    }
    */

    glutPostRedisplay();
}

void animateMap(int)
{
    heightMap.animate();
    glutTimerFunc(17,animateMap,0);
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    SCREEN_WIDTH = w;
    SCREEN_HEIGHT = h;
    ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    glViewport(0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT);
}

void CameraTranslate(int vx, int vy, int vz)
{
    camera.translate(vx,vy,vz);
    //glutTimerFunc(17, CameraTranslate, 0);
}
