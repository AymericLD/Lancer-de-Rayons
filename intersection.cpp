#include <cstdlib>
#include <cmath>
#include "intersection.hpp"

using namespace std;

///===============================================================
///                        Classe vecteur
///===============================================================


/// constructeur dimension et val. initiale
vecteur::vecteur(int ni, double v) : val_(0), n(ni)
{
    if (n<0) {cout << "dimension negative !?" << endl; exit(-1);}
    if (n==0) return;
    val_ = new double[n];
    for (int i=0; i<n ; i++) val_[i] = v;
}

/// constructeur par copie
vecteur::vecteur(const vecteur &v): val_(0), n(v.n)
{
    if (v.val_!=0) val_=new double[n];
    for (int k=0;k<n;k++) val_[k]=v.val_[k];
}

/// constructeur à partir d'un point
vecteur::vecteur(const point&p): val_(0), n(p.n)
{
    if (p.val_!=0) val_=new double[n];
    for (int k=0;k<n;k++) val_[k]=p.val_[k];
}

/// constructeur à partir de deux points
vecteur::vecteur(const point&p, const point&q): val_(0), n(p.n)
{
    point r = difference(q,p);
    if (r.val_!=0) val_=new double[n];
    for (int k=0;k<n;k++) val_[k]=r.val_[k];
}

/// opérateur =
vecteur& vecteur::operator=(const vecteur &v)
{
    if (n!= v.n && val_!=0)
    {
        delete[] val_;
        val_=0;
    }
    if (val_==0) val_=new double[v.n];
    n = v.n;
    for (int k=0;k<n;k++) val_[k] = v.val_[k];
    return *this;
}

/// destructeur
vecteur::~vecteur() {if (val_!=0) delete[] val_;}

/// accès au terme i=1 à n
double& vecteur::val(int i) {return val_[i-1];}
double vecteur::val(int i) const {return val_[i-1];}

/// ajoute un vecteur au vecteur courant
vecteur& vecteur::ajoute(const vecteur& v)
{
    if (n!=v.n)
    {
        cout << "ajoute vecteur : dimensions differentes" << endl;
        exit(-1);
    }
    for (int k=0; k<n; k++) val_[k] += v.val_[k];
    return *this;
}

/// retire un vecteur au vecteur courant
vecteur& vecteur::retire(const vecteur& v)
{
    if (n!=v.n)
    {
        cout << "retire vecteur : dimensions differentes" << endl;
        exit(-1);
    }
    for(int k=0; k<n; k++) val_[k] -= v.val_[k];
    return *this;
}

/// multiplication par un scalaire du vecteur courant
vecteur & vecteur::multiplie(double a)
{
    for (int k=0;k<n;k++) val_[k]*=a;
    return *this;
}

///affichage
void vecteur::print() const
{
    if (n==0) {cout << "[]" << endl; return;}
    cout << "[";
    for (int i=0;i<n-1;i++) cout << val_[i] << " ";
    cout << val_[n-1] << "]" << endl;
}

/// somme de deux vecteurs
vecteur somme(const vecteur& u, const vecteur& v)
{
    vecteur r(u);
    return r.ajoute(v);
}

/// différence de deux vecteurs
vecteur difference(const vecteur& u, const vecteur& v)
{
    vecteur r(u);
    return r.retire(v);
}

/// produit d'un vecteur par un scalaire
vecteur produit(const vecteur& u, double a)
{
    vecteur r(u);
    return r.multiplie(a);
}

/// division d'un vecteur par un scalaire
vecteur division(const vecteur& u, double a)
{
    if (a==0) {cout << "division par 0"; exit(-1);}
    vecteur r(u);
    return r.multiplie(1./a);
}

/// produit scalaire
double produit_scalaire(const vecteur& u, const vecteur& v)
{
    if (u.n!=v.n)
    {
        cout << "produit scalaire : dimension differentes" << endl;
        exit(-1);
    }
    double r=0;
    for (int k=1; k<=u.n; k++) r+=u.val(k)*v.val(k);
    return r;
}

/// norme d'un vecteur
double norme(const vecteur& u) {return sqrt(produit_scalaire(u,u));}

///===============================================================
///                        Classe point
///===============================================================

/// constructeur dimension et val. initiale
point::point(int ni, double v) : val_(0), n(ni)
{
    if (n<0) {cout << "dimension negative !?" << endl; exit(-1);}
    if (n==0) return;
    val_ = new double[n];
    for (int i=0; i<n ; i++) val_[i] = v;
}

/// constructeur par copie
point::point(const point &p): val_(0), n(p.n)
{
    if (p.val_!=0) val_=new double[n];
    for (int k=0;k<n;k++) val_[k]=p.val_[k];
}

/// opérateur =
point& point::operator=(const point &p)
{
    if (n!= p.n && val_!=0)
    {
        delete[] val_;
        val_=0;
    }
    if (val_==0) val_=new double[p.n];
    n = p.n;
    for (int k=0;k<n;k++) val_[k] = p.val_[k];
    return *this;
}

/// destructeur
point::~point() {if (val_!=0) delete[] val_;}

/// accès au terme i=1 à n
double& point::val(int i) {return val_[i-1];}
double point::val(int i) const {return val_[i-1];}

/// ajoute un point au point courant
point& point::ajoute(const point& p)
{
    if (n!=p.n)
    {
        cout << "ajoute point : dimensions differentes" << endl;
        exit(-1);
    }
    for (int k=0; k<n; k++) val_[k] += p.val_[k];
    return *this;
}

/// retire un point au point courant
point& point::retire(const point& p)
{
    if (n!=p.n)
    {
        cout << "retire point : dimensions differentes" << endl;
        exit(-1);
    }
    for(int k=0; k<n; k++) val_[k] -= p.val_[k];
    return *this;
}


/// multiplication par un scalaire du point courant
point & point::multiplie(double a)
{
    for (int k=0;k<n;k++) val_[k]*=a;
    return *this;
}

///affichage
void point::print() const
{
    if (n==0) {cout << "()" << endl; return;}
    cout << "(";
    for (int i=0;i<n-1;i++) cout << val_[i] << " ";
    cout << val_[n-1] << ")" << endl;
}


/// somme de deux point
point somme(const point& p, const point& q)
{
    point r(p);
    return r.ajoute(q);
}


/// différence de deux points
point difference(const point& p, const point& q)
{
    point r(p);
    return r.retire(q);
}

/// produit d'un point par un scalaire
point produit(const point& p, double a)
{
    point r(p);
    return r.multiplie(a);
}

/// division d'un points par un scalaire
point division(const point& p, double a)
{
    if (a==0) {cout << "division par 0"; exit(-1);}
    point r(p);
    return r.multiplie(1./a);
}

///===============================================================
///                        Classe sphere
///===============================================================

sphere::sphere(const point&p, double r)
{
    centre = p;
    rayon = r;
}

sphere::sphere(const sphere &S)
{
    centre = S.centre;
    rayon = S.rayon;
}

sphere & sphere::operator=(const sphere &S)
{
    centre = S.centre;
    rayon = S.rayon;
    return *this;
}

bool intersection(const point&A, const vecteur&u, const sphere&S)
{
    vecteur CA(A,S.centre);
    double delta = 4*pow(produit_scalaire(u,CA),2) - 4*pow(norme(u),2)*(pow(norme(CA),2) - pow(S.rayon,2));
    return (delta>=0);
}
