#ifndef MAP_H
#define MAP_H
#include <GL/glut.h>
#include <math.h>

class map
{
    public:
        map(int length, int width, int maxHeight, int minHeight);
        void init(void);
        void drawLines(void);
        void drawCubes(void);
        void animate(void);
        ~map(void);

    protected:

    private:

        int length;
        int width;
        int maxHeight;
        int minHeight;
        int size;

        float** height;

};

#endif // MAP_H
