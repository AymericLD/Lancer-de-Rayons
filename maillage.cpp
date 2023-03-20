#include "lancer_rayon.h"
#include "math.h"

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
Vecteur operator % (const Vecteur &u, const Vecteur &v)
{
  Vecteur w(0,0,0);
  w.x=u.y*v.z-u.z*v.y;
  w.y=u.z*v.x-u.x*v.z;
  w.z=u.x*v.y-u.y*v.x;
  return w;
}


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

bool intersection2(const Rayon&R, const Sphere&S)
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
  return (delta = 0);
}

///--------Classe Sphère----------

bool operator != (const Sphere& S1 ,const Sphere& S2)
{
  if (S1.centre!=S2.centre || S1.rayon!=S2.rayon)
  {
    return true;
  }
  return false;
}

bool operator == (const Sphere& S1 ,const Sphere& S2)
{
  if (S1.centre==S2.centre && S1.rayon==S2.rayon)
  {
    return true;
  }
  return false;
}

///-------- Classe Triangle

bool operator != (const Triangle& T1 ,const Triangle &T2)
{
  if (T1.s != T2.s)
  {
    return true;
  }
  return false;
}

bool operator == (const Triangle& T1 ,const Triangle& T2)
{
  if (T1.s == T2.s)
  {
    return true;
  }
  return false;
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
    table[i].centre.y = taille_pixel/2 + floor(i/largeur)*taille_pixel;
    table[i].centre.z = 0;
    table[i].taille = taille_pixel;
    table[i].r = 0;
    table[i].g = 0;
    table[i].b = 0;
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
      outfile << table[i].r << " " << table[i].g << " " << table[i].b << endl;
  }
}

///Translation du maillage (faire attention)

void Maillage::translation()
{

    for(int i = 0; i<nombre; i++)
    {
        t[i].s[0].z = t[i].s[0].z + 10; //vérifier ordre
        t[i].s[1].z = t[i].s[1].z + 10;
        t[i].s[2].z = t[i].s[2].z + 10;
    }

}

///


void calcul_intensite(Pixel &P, Source &L, Vecteur &point_inter, Sphere &S, vector<double> &k, int &n)
{
  double ka = k[0]; double kd = k[1]; double kr = k[2];
  Vecteur T = L.position - point_inter; // Direction entre point d'intersection et source
  Vecteur N = S.normale(point_inter); // Normale à la sphère au point d'intersection
  Vecteur O = P.centre - point_inter; // Direction d'observation

  double theta=acos((T*N)/(sqrt(T*T)*sqrt(N*N)));

  // Rotation de T par rapport à N d'un angle 2*theta par la formule de Rodrigues

  Vecteur U=cos(2*theta)*T+sin(2*theta)*(N%T)+(1-cos(2*theta))*(N*T)*N;

  double alpha=acos((O*U)/(sqrt(O*O)*sqrt(U*U)));

  P.r = min(abs(L.r * (kd*cos(theta) + kr*(pow(cos(alpha),n)))),255.0);
  P.g = min(abs(L.g * (kd*cos(theta) + kr*(pow(cos(alpha),n)))),255.0);
  P.b = min(abs(L.b * (kd*cos(theta) + kr*(pow(cos(alpha),n)))),255.0);


}



/// Intersection avec un triangle

bool intersection_triangle_bool (const Rayon&R, const Triangle&T)
{
    Vecteur O = Vecteur(0,0,0);
    Vecteur a1 = O-R.direction;
    Vecteur a2 = T.s[1]-T.s[0];
    Vecteur a3 = T.s[2]-T.s[0];
    Vecteur b = R.origine - T.s[0];
    double det = a1*(a2%a3); //a verifier au cas où (signe)
    if(det>0.00001)
    {
        double t_r = (b*(a2%a3))/det;
        double t = (a1*(b%a3))/det;
        double u = (a1*(a2%b))/det;
        return(t >= 0 && u >= 0 && u+t <= 1);
    }
    else {
        return false;
    }
}

Vecteur intersection_triangle_point (const Rayon&R, const Triangle&T)
{
    if(!intersection_triangle_bool(R,T)) {exit(-1);}
    Vecteur O = Vecteur(0,0,0);
    Vecteur a1 = O-R.direction;
    Vecteur a2 = T.s[1]-T.s[0];
    Vecteur a3 = T.s[2]-T.s[0];
    Vecteur b = R.origine - T.s[0];
    double det = a1*(a2%a3); //a verifier au cas où (signe)
    double t_r = (b*(a2%a3))/det;
    double t = (a1*(b%a3))/det;
    double u = (a1*(a2%b))/det;
    Vecteur P = R.origine + t*R.direction;
    return P;
}

void calcul_intensite_triangle(Pixel &P, Source &L, Vecteur &point_inter, Triangle &T, vector<double> &k, int &n)
{
  Vecteur N = ((T.s[1]-T.s[0])%(T.s[2]-T.s[0])); // Vecteur normal au triangle (orientation ?)

  double ka = k[0]; double kd = k[1]; double kr = k[2];
  Vecteur A = L.position - point_inter;
  Vecteur O = P.centre - point_inter;

  double theta=acos((A*N)/(sqrt(A*A)*sqrt(N*N)));

  // Rotation de T par rapport à N d'un angle 2*theta par la formule de Rodrigues

  Vecteur U=cos(2*theta)*A+sin(2*theta)*(N%A)+(1-cos(2*theta))*(N*A)*N;

  double alpha=acos((O*U)/(sqrt(O*O)*sqrt(U*U)));

  P.r = min(abs(L.r * (kd*cos(theta) + kr*(pow(cos(alpha),n)))),255.0);
  P.g = min(abs(L.g * (kd*cos(theta) + kr*(pow(cos(alpha),n)))),255.0);
  P.b = min(abs(L.b * (kd*cos(theta) + kr*(pow(cos(alpha),n)))),255.0);


}





