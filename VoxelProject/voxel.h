#ifndef VOXEL_H
#define VOXEL_H



class voxel
{
    public:
        voxel();
      //  voxel(int size , float cubeSize , point3f);
      //  void draw();
        ~voxel();

    protected:

    private:

        int size;
        float cubeSize;
      //  point3f origin;
        int*** arr;

};

#endif // VOXEL_H
