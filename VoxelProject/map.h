#ifndef MAP_H
#define MAP_H
#include <GL/glut.h>
#include <math.h>

class map
{
    public:
        map(unsigned int length, unsigned int width, int maxHeight, int minHeight);
        void init(void);
        void draw(void);
        void animate(void);
        ~map(void);

    protected:

    private:

        unsigned int length;
        unsigned int width;
        int maxHeight;
        int minHeight;
        int size;

        float** height;

};

#endif // MAP_H
