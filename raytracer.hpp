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

class point
{
public:
    double *val_;
    int n;
    point(int ni=0, double vi=0.);
    point(const point& v);
    ~point();
    point& operator = (const point &p);
    double& val(int i);
    double val(int i) const;
    void print() const;
    point& ajoute(const point&p);
    point& retire(const point&p);
    point& multiplie(double a);
};

point somme(const point& p, const point& q);
point difference(const point& p, const point& q);
point produit(const point& p, double a);
point division(const point& p, double a);

class vecteur
{
private:
    double *val_;
public:
    int n;
    vecteur(int ni=0, double vi=0.);
    vecteur(const vecteur& v);
    vecteur(const point& p);
    vecteur(const point& p, const point& q);
    ~vecteur();
    vecteur& operator = (const vecteur &v);
    double& val(int i);
    double val(int i) const;
    void print() const;
    vecteur& ajoute(const vecteur&v);
    vecteur& retire(const vecteur&v);
    vecteur& multiplie(double a);
};

vecteur somme(const vecteur& u, const vecteur& v);
vecteur difference(const vecteur& u, const vecteur& v);
vecteur produit(const vecteur& u, double a);
vecteur division(const vecteur& u, double a);
double produit_scalaire(const vecteur& u, const vecteur& v);
double norme(const vecteur& u);

class sphere
{
public:
    point centre;
    double rayon;
    sphere(const point &p, double r);
    sphere(const sphere &S);
    sphere& operator = (const sphere &S);
};

bool intersection(const point&A, const vecteur&u, const sphere&S);


// Classe source

class Source 
{public:
    point P;
    uint8_t r; // valeurs rgb
    uint8_t g;
    uint8_t b;
};

class Maillage
{public:
    int N; // Nb de triangles
    vector<Triangle> Triangles(N);
};

class Triangle
{
    public:
    point A;
    point B;
    point C;
    point Intersection(rayon R);
    Triangle ()
    {
        A.x=0;
        A.y=0;
        A.z=0;
        B.x=0;
        B.y=0;
        B.z=0;
        C.x=0;
        C.y=0;
        C.z=0;
    }
    Triangle(point a, point b, point c)
    {
        A=a;
        B=b;
        C=c;
    }
};



class Pixel
{
    private :

    point centre;
    int largeur;
    vector<float> rgb(3);

    public :
    Pixel();
    Rayon Pixel::rayon_pixel(vector<float>(3) direction)
    {
        rayon r;
        r.origine = Pixel.centre;
        r.dir = direction;
        return r;
    }
};



class Grille
{

    private :
    int l_p;
    int h_p;
    float taille;
    vector<Pixel>(n) g;
    
    public :
    
    Grille(l,h,t);
};

Grille::Grille(l,h,t) // Constructeur de la classe grille, on initialise une grille de dimension donnée avec des pixels ayant (0,0,0 pour valeur rgb)

{
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
