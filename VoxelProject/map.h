#ifndef MAP_H
#define MAP_H


class map
{
    public:
        map(int length, int width, int maxHeight, int minHeight);
        void init(void);
        void drawLines(void);
        void drawCubes(void);
        void drawPoly(void);
        void animate(void);
        void animateSlow(void);
        ~map(void);

    protected:

    private:

        float noise(int x, int y);
        int length;
        int width;
        int maxHeight;
        int minHeight;
        int size;

        float** height;

};

#endif // MAP_H
