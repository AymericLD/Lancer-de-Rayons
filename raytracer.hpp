#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>


using namespace std;
class Point
{public:
    double x;
    double y;
    double z;
};
// Classe source
class Source 
{public:
    Point P;
    uint8_t r; // valeurs rgb
    uint8_t g;
    uint8_t b;
};
class Triangle
{public:
    Point A;
    Point B;
    Point C;
};
class Maillage
{public:
    int N; // Nb de triangles
    vector<Triangle> Triangles(N);
};

class Rayon{

};

class Pixel
{
    private :

    Point centre;
    int largeur;
    vector<int> rgb(3);

    public :
    Pixel();
    Rayon Pixel::rayon_pixel(vector<float>(3) direction)
    {
        Rayon r;
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


class Grille{

    public :
    int l_p;
    int h_p;
    float taille;
    vector<Pixel>(n) g;
    public:
    Grille(l,h,t);
};
Grille::Grille(l,h,t) {
    l_p(l);
    h_p(h);
    taille(t);
    int n = l_p*h_p;
    for(int i; i<=n;i++) { //initialisation d'une grille, k*l_p<i<(k+1)*l_p - > k_i�me ligne en partant du bas, i mod k eme colonne
        g[i].centre.x = t/2 + (i%k)*t
        g[i].centre.y = t/2 + floor(i/k)*t;
        g[i].centre.z = 0;
        g[i].largeur = t;
        g[i].rgb = (0,0,0); //initialisation du rgb � 0,0,0
    }
};
#endif