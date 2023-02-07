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

Point Triangle::Intersection(Ray R)
{
    

}
