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
