#include "projet_3.hpp"

int main()
{
/*
  {
    //test output file
    ofstream myfile;
    myfile.open ("example.txt");
    myfile << "Writing this to a file.\n";
    myfile << "Writing some more.\n";
    myfile.close();
  }
*/
/*
  {
    //test de la classe Vecteur
    Vecteur O(1,1,0), P(1,0,-2), Q(0,3,1), R;
    cout << "O=" << O << " P=" << P << " Q=" << Q << " R=" << R << endl;
    cout << "O + P + 2.*Q - R/2.=" << (O+P+2.*Q-R/2.) << endl;
    cout << "O!=P -> " << (O!=P?"true":"false") << " O==P -> " << (O==P?"true":"false") << endl;
    cout << "O*P=" << O*P << "\n" << endl;
  }
*/
/*
  {
    //test de la classe Sphere
    Sphere S;
    cout << "S.centre=" << S.centre << " S.rayon=" << S.rayon << endl;
  }
*/
/*
  {
    //test de la classe Rayon
    Vecteur O(1,1,0), P(1,0,-2);
    Rayon I(O,P);
    cout << "I.origine=" << I.origine << " I.direction=" << I.direction << "\n" << endl;
  }
*/
/*
  {
    //test de la fonction intersection
    Vecteur O(0,2), e1(1,0), e2(3,2), P(6,2), Q(5,5);
    Sphere S1(P), S2(Q);
    Rayon R1(O,e1), R2(O,e2);
    cout << "R1 intersects S1 -> " << (intersection(R1,S1)?"true":"false") << endl;
    cout << "R1 intersects S2 -> " << (intersection(R1,S2)?"true":"false") << endl;
    cout << "R2 intersects S1 -> " << (intersection(R2,S1)?"true":"false") << endl;
    cout << "R2 intersects S2 -> " << (intersection(R2,S2)?"true":"false") << "\n" << endl;

    cout << "R1 intersects S1 at point " << intersection_point(R1,S1) << endl;
    cout << "R2 intersects S2 at point " << intersection_point(R2,S2) << "\n" << endl;
  }
*/
/*
  {
    //test de la class Source
    Vecteur O, P(1,1,1);
    uint8_t R = 2;
    cout << R << endl;
    cout << +R << "\n" << endl;

    Source S, T(P,8,75,255);
    cout << "S.position=" << S.position << endl;
    cout << "T.position=" << T.position << endl;
    cout << "S.rgb()=" << S << endl;
    cout << "T.rgb()=";
    T.rgb();
    cout << "\n";
  }
*/
/*
  {
    //test de la classe Pixel
    Vecteur O(1,0,-1);
    Pixel P;
    Pixel Q(O, 2., 15, 65, 115);
    cout << "P.centre=" << P.centre << " P.taille=" << P.taille << " P.rgb()=" << P << endl;
    cout << "Q.centre=" << Q.centre << " Q.taille=" << Q.taille << " Q.rgb()=";
    Q.rgb();
    cout << "\n";
  }
*/
/*
  {
    //test de la classe Grille
    Grille G(3,2,1.);
    int k = G.table.size();
    cout << "Nombre de pixels = " << k << endl;
    cout << "Liste positions pixels:" << endl;
    for (int i=0;i<k;i++)
    {
      cout << G.table[i].centre << " ";
    }
    cout << "\n" << endl;
  }
*/
  {
    Vecteur O(2,2,5); //centre de la sphere
    Sphere S(O); //sphere de centre O et de rayon 1
    vector<Sphere> scene(1); //contient tous les objets de la scene
    scene[0] = S;
    Vecteur P(2,6,5); //position de la source lumineuse
    Source L(P,255,255,255); //lumiere blanche
    Grille G(3,3,1); //grille de pixels
    G.creation_image();
    for (auto p=G.table.begin();p!=G.table.end();p++)
    {
      for (auto s=scene.begin();s!=scene.end();s++)
      {
        //cout << s->centre << endl;
      }
      //cout << *p << endl;
    }
  }
  return 0;
}
