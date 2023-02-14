#include "raytracer.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

namespace constantes
{
    double k_a=; //Coefficient de diffusion ambiante
    double I_a(3)=; //Intensité Lumineuse Ambiante
    double k_d=; //Coefficient de diffusion séculaire
    double k_r=; //Coefficient de réflexion séculaire
    int n=; //Coefficient caractérisant la réflexion du matériau
    int nb_objets=; //Nombre d'objets dans l'image
}

using namespace constantes;


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
/// Produit vectoriel

vecteur produit_vectoriel(const vecteur& u, const vecteur& v)
{
    if (u.n!=v.n)
    {
        cout << "produit vectoriel : dimension differentes" << endl;
        exit(-1);
    }
    vecteur w(3);
    w.val(0)=u.val(1)*v.val(2)-u.val(2)*v.val(1) ;  
    w.val(1)=u.val(2)*v.val(0)-u.val(0)*v.val(2) ;
    w.val(2)=u.val(0)*v.val(1)-u.val(1)*v.val(0) ;
    return w;
};

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


/// somme de deux points
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

///===============================================================
///                        Classe rayon
///===============================================================

/// constructeur
rayon::rayon(const point&p, const vecteur&v)
{
    origine = p;
    direction = v;
}

/// constructeur par copie
rayon::rayon(const rayon &R)
{
    origine = R.origine;
    direction = R.direction;
}

/// opérateur =
rayon & rayon::operator=(const rayon &R)
{
    origine = R.origine;
    direction = R.direction;
    return *this;
}
Écrire à Lancer de Rayons




Grille::Grille(l,h,t)
{
    l_p(l);
    h_p(h);
    taille(t);
    int n = l_p*h_p;
    for(int i; i<=n;i++) { //initialisation d'une grille, k*l_p<i<(k+1)*l_p - > k_ième ligne en partant du bas, i mod k eme colonne
        g[i].centre.x = t/2 + (i%k)*t
        g[i].centre.y = t/2 + floor(i/k)*t;
        g[i].centre.z = 0;
        g[i].largeur = t;
        g[i].rgb = (0,0,0); //initialisation du rgb à 0,0,0
    }
}
void Grille::creation_image()
{ //faire le main

std::ofstream outfile ("scene.ppm"); //Mettre l'arborescence correspondant au PC de clui qui compile²
outfile << "P3" << std::endl;
outfile << l_p << " " << h_p << std::endl;
outfile << "255" << std::endl;
n = l_p*h_p;
for(int i; i<=n; i++){
    outfile << Grille(i)[1] << " " << Grille(i)[2] << " " << Grille(i)[3] << " " << std::endl; // Attention index
}

}

// fstream pour écrire dans un fichier, format P3 -> .ppm


// Fonction de connection rayon-source


Source intersection_source(Source S, Point Int)
{
    vector<double> T=S.P-Int; 
    Ray R(Int,T);
    Source I(Int,k_a*I_a);
    for (int i=0;i<nb_objets;i++)
    {
        if (! Sphere[i].intersection(R)) 
        {
            vector<double> N=Int-Sphere[i];
            double theta=arcos(Th.)
            I.r+
            
        }
        
    }

}




// Intersection avec un triangle (Algorithme de Moller-Trumbore)

bool RayIntersectsTriangle(vecteur rayOrigin, 
                           vecteur rayVector, 
                           Triangle* inTriangle,
                           vecteur& outIntersectionPoint)
{
    const float EPSILON = 0.0000001;
    vecteur vertex0 = inTriangle->A;
    vecteur vertex1 = inTriangle->B;  
    vecteur vertex2 = inTriangle->C;
    vecteur edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = (vertex1,vertex0);
    edge2 = (vertex2,vertex0);
    h = produit_vectoriel(rayVector,edge2);
    a = produit_scalaire(edge1,h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // Le rayon est parallèle au triangle.

    f = 1.0/a;
    s = (rayOrigin,vertex0);
    u = f * (produit_scalaire(s,h));
    if (u < 0.0 || u > 1.0)
        return false;
    q = produit_vectoriel(s,edge1);
    v =f*produit_scalaire(rayVector,q);
    if (v < 0.0 || u + v > 1.0)
        return false;

    // On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
    float t = f * produit_scalaire(edge2,q);
    if (t > EPSILON) // Intersection avec le rayon
    {
        outIntersectionPoint = somme(rayOrigin,rayVector.multiplie(f));
        return true;
    }
    else // On a bien une intersection de droite, mais pas de rayon.
        return false;
}
