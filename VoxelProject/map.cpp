#include "map.h"


map::map(int length, int width, int maxHeight, int minHeight) :
        length{length},
        width{width},
        maxHeight{maxHeight},
        minHeight{minHeight}
{
    //calculate max height differential
    if ((maxHeight - minHeight) == 0) {size = 1;} //Need this so there isn't a division by 0 error in draw
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
    for(unsigned int i = 0; i < width; ++i){
        delete[] height[i];
    }
    //free the array of pointers
    delete[] height;
}

void map::init(void)
{
    //initialize the contents of the heightmap to a plane about z = 0.
    for(unsigned int i = 0; i < length; i++){
        for(unsigned int j = 0; j < width; j++) {
            height[i][j] = 0;
        }
    }
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
                    glColor3f(1,0,1);
                    glLineWidth(1);
                    glVertex3f(i-1, height[i-1][j], j);
                    glVertex3f(i, height[i][j], j);
                glEnd();

                //create y-axis lines
                glBegin(GL_LINES);
                    glColor3f(1,0,1);
                    glLineWidth(1);
                    glVertex3f(i, height[i][j-1], j-1);
                    glVertex3f(i, height[i][j], j);
                glEnd();


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

void map::animate(void)
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




