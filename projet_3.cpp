#include "projet_3.hpp"

///-------- Classe Vecteur 3D --------

Vecteur operator+(const Vecteur & P,const Vecteur &Q)
{Vecteur R(P); return R+=Q;}
Vecteur operator-(const Vecteur & P,const Vecteur &Q)
{Vecteur R(P); return R-=Q;}
Vecteur operator*(const Vecteur & P,double a)
{Vecteur R(P); return R*=a;}
Vecteur operator* (double a,const Vecteur & P)
{Vecteur R(P); return R*=a;}
Vecteur operator/ (const Vecteur & P,double a)
{Vecteur R(P); return R/=a;}
double operator* (const Vecteur &P, const Vecteur &Q)
{return P.x*Q.x + P.y*Q.y + P.z*Q.z;}
bool operator ==(const Vecteur & P,const Vecteur &Q)
{return (P.x==Q.x) && (P.y==Q.y) && (P.z==Q.z);}
bool operator !=(const Vecteur & P,const Vecteur &Q)
{return !(P==Q);}
ostream & operator <<(ostream & os, const Vecteur &P)
{os<<"("<<P.x<<","<<P.y<<","<<P.z<<")"; return os;}

///-------- Fonction intersection --------

bool intersection(const Rayon&R, const Sphere&S)
{
  Vecteur E = R.origine - S.centre;
  double a = pow(sqrt(R.direction*R.direction),2);
//  cout << "a=" << a;
  double b = 2*R.direction*E;
//  cout << ", b=" << b;
  double c = pow(sqrt(E*E),2) - pow(S.rayon,2);
//  cout << ", c=" << c;
  double delta = pow(b,2) - 4*a*c;
//  cout << ", delta=" << delta << endl;
  return (delta >= 0);
}

Vecteur intersection_point(const Rayon&R, const Sphere&S)
{
  if (!intersection(R,S)){cout << "aucune intersection" << endl; exit(-1);}
  Vecteur E = R.origine - S.centre;
  double a = pow(sqrt(R.direction*R.direction),2);
  double b = 2*R.direction*E;
  double c = pow(sqrt(E*E),2) - pow(S.rayon,2);
  double delta = pow(b,2) - 4*a*c;
  double t = (-b-sqrt(delta))/(2*a);
//  cout << "t=" << t << endl;
  Vecteur P;
  P = R.origine + t*R.direction;
  return P;
}

///-------- Classe Source --------

ostream & operator <<(ostream & os, const Source &S)
{os<<"("<<+S.r<<","<<+S.g<<","<<+S.b<<")"; return os;}

///-------- Classe Pixel --------

ostream & operator <<(ostream & os, const Pixel &P)
{os<<+P.r<<" "<<+P.g<<" "<<+P.b; return os;}

///------- Classe Grille --------

Grille::Grille(int h0, int l0, double t0): hauteur(h0), largeur(l0), taille_pixel(t0)
{
  int n = hauteur*largeur;
  table.resize(n);
  for (int i=0;i<n;i++)
  {
    table[i].centre.x = taille_pixel/2 + (i%largeur)*taille_pixel;
    table[i].centre.y = taille_pixel/2 + (i/largeur)*taille_pixel;
    table[i].centre.z = 0;
    table[i].taille = taille_pixel;
    table[i].r = 0;
    table[i].g = 0;
    table[i].b = 255;
  }
}

void Grille::creation_image()
{
  ofstream outfile ("scene.ppm");
  outfile << "P3" << endl;
  outfile << largeur << " " << hauteur << endl;
  outfile << "255" << endl;
  int n = largeur*hauteur;
  for(int i=0; i<n; i++){
      outfile << table[i] << endl;
  }
}

void calcul_intensite(Pixel &P, Source &L, Vecteur &point_inter, Sphere &S, vector<double> &k, int &n)
{
  double ka = k[0]; double kd = k[1]; double kr = k[2];
  Vecteur T = L.position - point_inter; // Direction entre point d'intersection et source
  Vecteur N = S.normale(point_inter); // Normale à la sphère au point d'intersection
  Vecteur O = P.centre - point_inter; // Direction d'observation

  double theta=acos((T*N)/(sqrt(T*T)*sqrt(N*N)));
  // Rotation de T par rapport à N d'un angle 2*theta par la formule de Rodrigues
  Vecteur U=ctheta*T+
  double alpha=acos((O*N)/(sqrt(O*O)*sqrt(N*N))) - acos(ctheta); // faux

  P.r = L.r * (kd*ctheta + kr*(pow(cos(alpha),n)));
  P.g = L.g * (kd*ctheta + kr*(pow(cos(alpha),n)));
  P.b = L.b * (kd*ctheta + kr*(pow(cos(alpha),n)));
}
