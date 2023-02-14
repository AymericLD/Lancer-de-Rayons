#ifndef tp2H
#define tp2H

#include <iostream>
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

point somme(const point&p, const vecteur&v);

class sphere
{
public:
    point centre;
    double rayon;
    sphere(const point &p, double r);
    sphere(const sphere &S);
    sphere& operator = (const sphere &S);
    vecteur normale(const point &p);
};

class rayon
{
public:
    point origine;
    vecteur direction;
    rayon(const point&p, const vecteur &v);
    rayon(const rayon&R);
    rayon& operator = (const rayon &R);
};

bool intersection(const rayon&R, const sphere&S);

point intersection_point(const rayon&R, const sphere&S);

#endif
