#include <iostream>
#include <string>
#include <cmaths>
#include <fstream>
using namespace std
using namespace std;
//normale tq pscalaire négatif
class Grille

    private :
    int l_p;
    int h_p;
    float taille;
    vector<Pixel> g;
    public:
    Grille(l,h,t);
    double operator()(int i) const {return g[i].rgb}; //surcharge de l'opérateur () d'accès au vecteur rgb du pixel i
    void creation_image(Grille g);
};
Grille::Grille(l,h,t) {
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
void Grille::creation_image() { //faire le main

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
