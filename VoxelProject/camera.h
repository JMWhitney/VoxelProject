#ifndef CAMERA_H
#define CAMERA_H


class camera
{
    public:

        camera();
        camera(float x, float y, float z, float xAngle, float yAngle, float zAngle, float zoomFactor);
        ~camera();
        void translate(float cx, float cy, float cz);
        void zoom(float zf);
        void rotate(float ax, float ay, float az);
        void display(void);

    protected:

    private:

        //Camera's xyz position values
        float x;
        float y;
        float z;

        //Camera's up-down and left-right rotation angles
        float xAngle;
        float yAngle;
        float zAngle;

        //Scalar to adjust camera zoom
        float zoomFactor;
};

#endif // CAMERA_H
