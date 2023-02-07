#include <iostream>
#include <string>

using namespace std

class Pixel
{
    private :

    Point centre;
    int largeur;
    vector<int>(3) rgb;

    public :
    Pixel();
    Ray Pixel::rayon_pixel(vector<double> direction)
    {
        Ray r;
        r.origine = Pixel.centre;
        r.dir = direction;
        return r;
    }
};
Point p;
p.x = 0;
p.y = 0;
p.z = 0;
Pixel::Pixel() : centre(p), largeur (0), rgb((0,0,0));

