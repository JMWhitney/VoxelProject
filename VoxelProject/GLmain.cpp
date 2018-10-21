#include <iostream>
#include <stdio.h>
#include "map.h"
#include "camera.h"
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <math.h>

/*******************To Do List ******************
        -Add user interface
        -Add ability to read/write data from a file
        -Add ability to modify contents of the program
***********************************************/

using namespace std;

    bool pause = false;
    float length = 1;
    const int R = 10;

bool voxel[R][R][R];
map heightMap(64,64,20,-20);
camera camera(-25 , 0 , -32 , 45 , 45 , 0 , 0.185);
//vec3 color = vec3(1.0,1.0,1.0);

void initVoxel()
{
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < R; j++) {
            for(int k = 0; k < R; k++) {
                voxel[i][j][k] = false;
            }
        }
    }
}

void animateVoxel(int)
{
    static bool ascending = true;
    static int j = 0;

    for(int i=0; i<R ; i++){
        for(int k=0; k<R ; k++){
            if(j<R && ascending){
                voxel[i][j][k] = true;
            } else if(j >= 0 && !ascending) {
                voxel[i][j][k] = false;
            }
        }
   }
    if(j >= R){
        ascending = false;
    }
    if(j <= 0){
        ascending = true;
    }
    if(ascending == true){
        j++;
    } else{
        j--;
    }
    cout << j << ", " << ascending << endl;
    glutPostRedisplay();
    if(!pause) {glutTimerFunc(100, animateVoxel,0);}
}

void drawVoxel()
{
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < R; j++) {
            for(int k = 0; k < R; k++) {
                if(voxel[i][j][k] == true) {
                    glPushMatrix();
                        glTranslatef(i,j,k);
                        glRotatef(0,0,1,0);
                        glColor4f(float(i)/R, float(j)/R, float(k)/R, .1);
                        glutSolidCube(length);
                    glPopMatrix();
                }
            }
        }
    }
}

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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800, 500);
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
    //drawGrid();
    heightMap.drawPoly();
    //drawVoxel();
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35,1.0f,0.1f,1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,1);
}

void keyboard(unsigned char key, int x, int y)
{
    if(key=='w'){camera.translate(0,0,1);} if(key=='s'){camera.translate(0,0,-1);}
    if(key=='a'){camera.translate(1,0,0);} if(key=='d'){camera.translate(-1,0,0);}
    if(key=='q'){camera.translate(0,-1,0);} if(key=='z'){camera.translate(0,1,0);}

    if(key=='e'){camera.rotate(2,0,0);}    if(key=='c'){camera.rotate(-2,0,0);}
    if(key=='.'){camera.rotate(0,2,0);}    if(key==','){camera.rotate(0,-2,0);}

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if((button == 3 || button == 4))
    {
        if(state == GLUT_UP) return;
        printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y); //print information
        (button == 3) ? camera.zoom(1.1) : camera.zoom(0.9);

    } else {
        printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    }

    /* Drawing lines
    if (button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
        dx = x;
        dy = y;
        cout << x << ',' << y << ' ';
        addLinePoint();
        }
    }
    */
    glutPostRedisplay();
}

void animateMap(int)
{
    heightMap.animate();
    glutPostRedisplay();
    glutTimerFunc(17,animateMap,0);
}

void reshape(int w, int h)
{
    glViewport(0 , 0 , w , h);
}
