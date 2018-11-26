// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <comparateur_quantite.hpp>
#include <histogramme.hpp>

// Fonction principale //---------------------------------------------------------------------------
int main(void) {
 typedef Histogramme<>                              histo_tri_defaut_t;
 typedef Histogramme< ComparateurQuantite<Classe> > histo_tri_quantite_t;

 Echantillon ech;
 double      val;

 histo_tri_defaut_t h1(0.0,20.0,10);

 srand(time(0));
 std::cout << "Echantillon =";

 for (unsigned i = 0; i<20; ++i) {
  val=double(rand())/RAND_MAX*20.0;
  ech.ajouter(Valeur(val));
  std::cout << " " << val;
 }

 std::cout << std::endl;

 h1.ajouter(ech);
 std::cout << std::endl << "Histogramme tri par defaut:" << std::endl << h1;

 histo_tri_quantite_t h2(h1);

 std::cout << std::endl << "Histogramme tri par quantite:" << std::endl << h2;

 return 0;
}

// Fin //-------------------------------------------------------------------------------------------
