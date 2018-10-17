#include "camera.h"
#include <GL/glut.h>

camera::camera() :
                //Initialization list
                x{0.0} , y{0.0} , z{0.0},
                xAngle{45.0} , yAngle{0.0}, zAngle{45.0},
                zoomFactor{0.5}
{
    //Default constructor
}

camera::camera(float x, float y, float z, float xAngle, float yAngle, float zAngle, float zoomFactor) :
                //Initialization list
                x{x} , y{y} , z{z},
                xAngle{xAngle} , yAngle{yAngle} , zAngle{zAngle},
                zoomFactor{zoomFactor}
{

}

camera::~camera()
{
    //Default destructor
}

void camera::translate(float cx, float cy, float cz)
{
    x += cx;
    y += cy;
    z += cz;
}

void camera::zoom(float zf)
{
    zoomFactor *= zf;
}

void camera::rotate(float ax, float ay, float az)
{
    xAngle += ax;
    yAngle += ay;
    zAngle += az;
}

void camera::display(void)
{
    glTranslatef(x,y,z);
    glRotatef(xAngle,1,0,0);
    glRotatef(yAngle,0,1,0);
    glRotatef(zAngle,0,0,1);
    glScalef(zoomFactor, zoomFactor, zoomFactor);
}
