#include "map.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <fstream>


using namespace std;
map::map(int length, int width, int maxHeight, int minHeight) :
        length{length},
        width{width},
        maxHeight{maxHeight},
        minHeight{minHeight}
{
    //calculate max height differential
    if ((maxHeight - minHeight) == 0) {size = 1;} //Need this so there can't be a division by 0 error in draw
    else {size = maxHeight -  minHeight;}

    //Dynamically create an array of pointers that point to sub-arrays
    height = new float*[length];
    for(int i = 0; i < width; ++i) {
        height[i] = new float[width];
    }

    init();
}

map::~map(void)
{
    //free each sub-array
    for(int i = 0; i < width; ++i){
        delete[] height[i];
    }
    //free the array of pointers
    delete[] height;
}

void map::init(void)
{
    //initialize the contents of the heightmap to a plane about z = 0.
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++) {
            height[i][j] = 0;
        }
    }
}

float map::noise(int x, int y)
{
    //Unused at this time

}

void map::drawLines(void)
{
    //Iterate through the contents of the heightmap,
    //drawing two sets of orthogonal lines
    //depending on the height at each coordinate.

    for(int i = 1; i < length; i++) {
        for(int j = 1; j < width; j++) {
            glPushMatrix();

                //create x-axis lines
                glBegin(GL_LINES);
                    glColor3f(0,0,1);
                    glLineWidth(1);
                    glVertex3f(i-1, height[i-1][j], j);
                    glVertex3f(i, height[i][j], j);
                glEnd();

                /*
                //create y-axis lines
                glBegin(GL_LINES);
                    glColor3f(1,0,1);
                    glLineWidth(1);
                    glVertex3f(i, height[i][j-1], j-1);
                    glVertex3f(i, height[i][j], j);
                glEnd();
                */

            glPopMatrix();
        }
    }
}
void map::drawCubes(void)
{
    //Iterate through the map array, drawing cubes at a height specified by the heightmap array.
    //Map the RGB color of each cube to the XYZ coordinate respectively.
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            glPushMatrix();
                glTranslatef(i,height[i][j],j);
                glRotatef(0,0,1,0);
                glColor3f(float(i)/length, float(j)/width, float(height[i][j])/(.25*size));
                glutSolidCube(1.5);
            glPopMatrix();
        }
    }
}

void map::drawPoly(void)
{
    //Iterate through the map array, drawing triangular polygons with vertices specified by the heightmap array.
    //Color them depending on the position in the array
    for(int i = 1; i < length; i++) {
        for(int j = 1; j < width; j++) {
            glPushMatrix();
                glBegin(GL_TRIANGLES);
                    glColor3f(float(i)/length, float(j)/width, float(height[i][j])/(.25*size));
                    glVertex3f(i-1, height[i-1][j-1], j-1);
                    glVertex3f(i-1, height[i-1][j], j);
                    glVertex3f(i,   height[i][j-1],   j-1);
                glEnd();

                glBegin(GL_TRIANGLES);
                    glColor3f(float(i)/length, float(j)/width, float(height[i][j])/(.25*size));
                    glVertex3f(i, height[i][j], j);
                    glVertex3f(i-1, height[i-1][j], j);
                    glVertex3f(i,   height[i][j-1],   j-1);
                glEnd();
            glPopMatrix();
        }
    }

}

void map::animateSlow(void)
{
    static double offset = 0;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            height[i][j] = size*cos(.16*(sqrt(pow(i - (length/2), 2.0) + pow(j - (width/2),2.0))) + offset) / (.25* sqrt(pow(i - (length/2), 2.0) + pow(j - (width/2),2.0)) + 1);
        }
    }
    offset -= 0.033;
    if(offset > 6.28) {offset = 0;}
}

void map::animate(void)
{
    //The difference between this function and animateSlow() is that
    //This function only calculates the mathematical function values
    //For 1/4 of the array and mirrors the contents to the other quadrants.
    //This speeds up the time it takes to load the array by a factor of  3.7 - 4.0.
    //This exploits the symmetry of the function itself. Further optimization may be possible.

    float h;
    static double offset = 0;
    for(int i = 0 ; i <= ((length/2)-1) ; i++) {
        for(int j = 0 ; j <= ((width/2)-1) ; j++){
            h = size*cos(.16*(sqrt(pow(i - (length/2), 2.0) + pow(j - (width/2),2.0))) + offset) / (.25* sqrt(pow(i - (length/2), 2.0) + pow(j - (width/2),2.0)) + 1);
            height[i][j] = h;
            height[length-i-1][j] = h;
            height[i][width-j-1] = h;
            height[length-i-1][width-j-1] = h;
        }
    }
    offset -= 0.033;
    if(offset > 6.28) {offset = 0;}
}




