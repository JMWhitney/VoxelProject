#include "voxel.h"
#include <GL/glut.h>
#include <iostream>

voxel::voxel()
{
    //default constructor
}

voxel::voxel(float x, float y, float z, int size, float cubeSize) :
            x{x}, y{y}, z{z},
            size{size}, cubeSize{cubeSize}
{
    //Allocate new memory for the 3d array and initialize it.
    arr = new bool**[size];
    for(int i = 0; i < size; ++i){
        arr[i] = new bool*[size];
        for(int j = 0; j < size; ++j){
            arr[i][j] = new bool[size];
            for(int k = 0; k < size; ++k){
                arr[i][j][k] = true;
            }
        }
    }
}

voxel::~voxel()
{
    //Free all allocated memory in the reverse order it was allocated
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
}

void voxel::draw()
{
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                if(arr[i][j][k] == true) {
                    glPushMatrix();
                        glTranslatef(cubeSize*(3*i+x),cubeSize*(3*j+y),cubeSize*(3*k+z));
                        glColor3f(float(i)/size, float(j)/size, float(k)/size);
                        glutSolidCube(cubeSize);
                    glPopMatrix();
                }
            }
        }
    }
}

void voxel::animateVoxel(int)
{
    //This function will cause the voxel to appear to ascend to its full height, then descend until it is empty.
    static bool ascending = true;
    static int j = 0;

    for(int i=0; i<size ; i++){
        for(int k=0; k<size ; k++){
            if(j<size && ascending){
                arr[i][j][k] = true;
            } else if(j >= 0 && !ascending) {
                arr[i][j][k] = false;
            }
        }
   }
    if(j >= size){
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
}
