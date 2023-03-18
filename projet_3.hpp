#ifndef lancer_rayon_h
#define lancer_rayon_h

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;

///-------- Classe Vecteur 3D --------

class Vecteur
{public:
  double x;
  double y;
  double z;
  Vecteur(double x0=0,double y0=0, double z0=0):x(x0),y(y0),z(z0){} //constructeur commun
  Vecteur& operator += (const Vecteur & P) {x+=P.x;y+=P.y;z+=P.z;return *this;}
  Vecteur& operator -= (const Vecteur & P) {x-=P.x;y-=P.y;z-=P.z;return *this;}
  Vecteur& operator *= (double a){x*=a;y*=a;z*=a;return *this;}
  Vecteur& operator /= (double a){x/=a;y/=a;z/=a;return *this;}
};

//fonctions externes
Vecteur operator + (const Vecteur& ,const Vecteur&);
Vecteur operator - (const Vecteur& ,const Vecteur&);
Vecteur operator * (const Vecteur& ,double a);
Vecteur operator * (double a,const Vecteur & );
Vecteur operator / (const Vecteur& ,double a);
double operator * (const Vecteur&, const Vecteur&); //produit scalaire
bool operator == (const Vecteur& ,const Vecteur& );
bool operator != (const Vecteur& ,const Vecteur& );
bool operator<(const Vecteur&, const Vecteur&);
ostream & operator <<(ostream &, const Vecteur &); //affichage dans ostream

///-------- Classe Sphere --------

class Sphere
{
public:
  Vecteur centre;
  double rayon;
  Sphere(double r=1):rayon(r){Vecteur P; centre=P;} //constructeur
  Sphere(const Vecteur&P, double r=1):rayon(r){centre=P;} //constructeur
  Vecteur normale(const Vecteur &P) {Vecteur Q = P-centre;return Q;}
};

///-------- Classe Rayon --------

class Rayon
{
public:
  Vecteur origine;
  Vecteur direction;
  Rayon(const Vecteur&P, const Vecteur&Q){origine=P;direction=Q;} //constructeur
};

///-------- Fonction intersection --------

bool intersection(const Rayon&, const Sphere&);

Vecteur intersection_point(const Rayon&, const Sphere&);

///-------- Class Source -------

class Source
{
public:
  Vecteur position;
  int r;
  int g;
  int b;
  Source (uint8_t r0=0, uint8_t g0=0, uint8_t b0=0):r(r0),g(g0),b(b0){Vecteur P; position=P;}
  Source (const Vecteur&P, uint8_t r0=0, uint8_t g0=0, uint8_t b0=0):r(r0),g(g0),b(b0){position=P;} //constructeur
  void rgb() const {cout <<"(" << +r << "," << +g << "," << +b << ")" << endl;} //affichage
};

//fonctions externes
ostream & operator <<(ostream &, const Source &); //affichage des valeurs rgb de la source dans ostream

///-------- Classe Pixel -------

class Pixel
{
public:
  Vecteur centre;
  double taille;
  double r;
  double g;
  double b;
  //Pixel (double t0=1, float r0=0,  float g0=0, float b0=0):taille(t0),r(r0),g(g0),b(b0){Vecteur P; centre=P;} //constructeur
  //Pixel (float Vecteur&P, float t0=1, float r0=0, float g0=0, float b0=0):taille(t0),r(r0),g(g0),b(b0){centre=P;} //constructeur
  void rgb() const {cout << +r << " " << +g << " " << +b << endl;} //affichage
};

//fonctions externes
ostream & operator <<(ostream &, const Pixel &); //affichage des valeurs rgb du pixel dans ostream

///------- Classe Grille -------

class Grille
{
public:
  int hauteur;
  int largeur;
  double taille_pixel;
  vector<Pixel> table;
  Grille(int h0=1, int l0=1, double t0=1); //constructeur
  void creation_image();
};

#endif // LANCER_RAYON_H_INCLUDED
