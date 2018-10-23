#ifndef VOXEL_H
#define VOXEL_H

class voxel
{
    public:
        voxel();
        voxel(float x, float y, float z, int size, float cubeSize);
        void draw(void);
        void animateVoxel(int);
        void place();
        void save(void);
        ~voxel();

    protected:

    private:

        //Origin location of the voxel
        float x;
        float y;
        float z;

        int size;           //Maximum size of the array
        float cubeSize;     //Size of the individual cubes

        //Array containing voxel information
        bool*** arr;

};

#endif // VOXEL_H
