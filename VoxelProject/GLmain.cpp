#include <iostream>
#include <stdio.h>
#include "map.h"
//#include <thread>
//#include <chrono>

/*******************To Do List ******************
    > separate objects into their own class files
    > clean, organize, and document code
    > Create octree data structure to store voxel data
    > commit version control to git with documentation of changes, problems, solutions, and lessons learned.
    > Optimize code.
    > Test different storage methods (data structures) for voxel data.
        To increase efficiency I want to be updating only the blocks of the voxel
        that I need to each frame loop.
    > Create a list of hard coded animations for the cube
    > Increase user interactability (rotate, zoom, translate sceen using mouse)
    > Create a user interface? (select animation)

***********************************************/

using namespace std;

    int cx = -13, cy = 0, cz = -45;
    int dx = 0, dy = 0, dz = 0;
    float zf = 1;
    int cn, ln;
    float theta = 0;


    bool pause = false;
    float length = 1;
    const int R = 10;

bool voxel[R][R][R];
map heightMap(128,128,20,-20);

void initVoxel()
{
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < R; j++) {
            for(int k = 0; k < R; k++){
                voxel[i][j][k] = false;
            }
        }
    }
}

void animateMap(int)
{
    heightMap.animate();
    glutPostRedisplay();
    glutTimerFunc(17,animateMap,0);
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
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(cx,cy,cz);
    glRotatef(60,1,1,0);
    glTranslatef(10,0,10);
    glRotatef(theta,0,1,0);
    glScalef(zf, zf, zf);
    glTranslatef(-10,0,-10);


    //drawGrid();
    heightMap.draw();
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
    glClearColor(0.2,0.2,0.2,1);
}

void keyboard(unsigned char key, int x, int y)
{
    if(key=='w'){cz+=1;} if(key=='s'){cz-=1;}
    if(key=='a'){cx+=1;} if(key=='d'){cx-=1;}
    if(key=='q'){cy-=1;} if(key=='z'){cy+=1;}
    if(key=='.'){theta+=2;}
    if(key==','){theta-=2;}
    if(key=='p' && !pause){pause=true;}
    else if(key=='p' && pause){pause=false; glutTimerFunc(10,animateVoxel,0);}

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if((button == 3 || button == 4))
    {
        if(state == GLUT_UP) return;
        printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y); //print information
        (button == 3) ? zf *= 1.1 : zf *= .9;
        cout << zf;
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


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800, 600);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1,animateMap,0);
    init();

    glutMainLoop();
    return 0;
}


