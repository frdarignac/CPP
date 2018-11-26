// Gardien //---------------------------------------------------------------------------------------
#ifndef _ECHANTILLON_HPP_
#define _ECHANTILLON_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <valeur.hpp>

// Classe  E c h a n t i l l o n //-----------------------------------------------------------------
class Echantillon {
 //----------------------------------------------------------------------------------------Attributs
 private:
  std::vector<Valeur> valeurs_;
 //---------------------------------------------------------------------------------------Accesseurs
 public:
  unsigned getTaille(void) const { return valeurs_.size(); }

  const Valeur & getValeur(unsigned indice) const {
   if (indice<valeurs_.size()) return valeurs_[indice];
   else throw std::out_of_range("Echantillon::getValeur()");
  }

  const Valeur & getMinimum(void) const {
   if (valeurs_.size()!=0) return *(std::min_element(valeurs_.begin(),valeurs_.end()));
   else throw std::domain_error("Echantillon::getMinimum()");
  }

  const Valeur & getMaximum(void) const {
   if (valeurs_.size()!=0) return *(std::max_element(valeurs_.begin(),valeurs_.end()));
   else throw std::domain_error("Echantillon::getMinimum()");
  }
 //-------------------------------------------------------------------------------Methodes publiques
 public:
  void ajouter(const Valeur & valeur) { valeurs_.push_back(valeur); }
};

// Fin //-------------------------------------------------------------------------------------------
#endif
