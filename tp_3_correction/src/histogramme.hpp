// Gardien //---------------------------------------------------------------------------------------
#ifndef _HISTOGRAMME_HPP_
#define _HISTOGRAMME_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <map>
#include <set>
#include <classe.hpp>
#include <echantillon.hpp>

// Classe  H i s t o g r a m m e //-----------------------------------------------------------------
template <typename COMPARATEUR = std::less<Classe> > class Histogramme {
 //--------------------------------------------------------------------------------------------Types
 public:
  typedef std::set<Classe,COMPARATEUR> classes_t;
  typedef std::multimap<Classe,Valeur> valeurs_t;
  typedef valeurs_t::const_iterator    it_valeurs_t;
 //----------------------------------------------------------------------------------------Attributs
 private:
  double    borneInf_;
  double    borneSup_;
  classes_t classes_;
  valeurs_t valeurs_;
 //---------------------------------------------------------------------------------------Accesseurs
 public:
  double getBorneInf(void) const { return borneInf_; }
  double getBorneSup(void) const { return borneSup_; }

  const classes_t & getClasses(void) const { return classes_; }
  unsigned          getNbClasse(void) const { return classes_.size(); }

  const valeurs_t & getValeurs(void) const { return valeurs_; }
  unsigned          getNbValeur(void) const { return valeurs_.size(); }

  std::pair<it_valeurs_t,it_valeurs_t> getValeurs(const Classe & classe) const
  { return valeurs_.equal_range(classe); }
 //------------------------------------------------------------------------------------Constructeurs
 public:
  Histogramme(double borneInf,double borneSup,unsigned nbClasse,
              const COMPARATEUR & = COMPARATEUR());

  template <typename AUTRE_COMPARATEUR> Histogramme(const Histogramme<AUTRE_COMPARATEUR> &);
 //---------------------------------------------------------------------------------Methodes privees
 private:
  void creerClasses(unsigned);
 //-------------------------------------------------------------------------------Methodes publiques
 public:
  void ajouter(const Valeur &);
  void ajouter(const Echantillon &);
};

// Implementation  H i s t o g r a m m e //---------------------------------------------------------

//-----------------------------------------------------------Constructeur(double,double,COMPARATEUR)
template <typename COMPARATEUR>
Histogramme<COMPARATEUR>::Histogramme(double borneInf,double borneSup,unsigned nbClasse,
                                      const COMPARATEUR & comparateur)
: borneInf_(borneInf),borneSup_(borneSup),classes_(comparateur) {
 creerClasses(nbClasse);
}

//------------------------------------------------------Constructeur(Histogramme<AUTRE_COMPARATEUR>)
template <typename COMPARATEUR>
template <typename AUTRE_COMPARATEUR>
Histogramme<COMPARATEUR>::Histogramme(const Histogramme<AUTRE_COMPARATEUR> & histo)
: borneInf_(histo.getBorneInf()),borneSup_(histo.getBorneSup()) {
 typedef typename Histogramme<AUTRE_COMPARATEUR>::classes_t::const_iterator iterator_t;

 iterator_t it = histo.getClasses().begin();

 while (it!=histo.getClasses().end()) classes_.insert(*(it++));
 valeurs_.insert(histo.getValeurs().begin(),histo.getValeurs().end());
}

//--------------------------------------------------------------------------------------creerClasses
template <typename COMPARATEUR>
void Histogramme<COMPARATEUR>::creerClasses(unsigned nbClasse) {
 double intervalle = (borneSup_-borneInf_)/nbClasse;

 for (unsigned i = 0; i<nbClasse; ++i)
  classes_.insert(Classe(borneInf_+intervalle*i,borneInf_+intervalle*(i+1)));
}

//-----------------------------------------------------------------------------------ajouter(Valeur)
template <typename COMPARATEUR>
void Histogramme<COMPARATEUR>::ajouter(const Valeur & valeur) {
 typename classes_t::iterator it     = classes_.begin();
 bool                         trouve = false;

 while (it != classes_.end() && !trouve)
  if (valeur.getNombre() >= it->getBorneInf() && valeur.getNombre() < it->getBorneSup())
   trouve=true;
  else ++it;

 if (trouve) {
  Classe c = *it;

  c.ajouter();
  classes_.erase(it);
  classes_.insert(c);

  valeurs_.insert(std::make_pair(c,valeur));
 }
}

//------------------------------------------------------------------------------ajouter(Echantillon)
template <typename COMPARATEUR>
void Histogramme<COMPARATEUR>::ajouter(const Echantillon & echantillon) {
 for (unsigned i = 0; i<echantillon.getTaille(); ++i) ajouter(echantillon.getValeur(i));
}

// Implementation fonctions //----------------------------------------------------------------------

//---------------------------------------------------------------------------------------operator <<
template <typename COMPARATEUR>
std::ostream & operator << (std::ostream & flux,const Histogramme<COMPARATEUR> & histo) {
 typedef typename Histogramme<COMPARATEUR>::classes_t::const_iterator it_classes_t;
 typedef typename Histogramme<COMPARATEUR>::valeurs_t::const_iterator it_valeurs_t;

 std::pair<it_valeurs_t,it_valeurs_t> interval;

 it_classes_t it = histo.getClasses().begin();

 while (it!=histo.getClasses().end()) {
  flux << *it << " = " << it->getQuantite() << " :";
  interval=histo.getValeurs(*it);

  while (interval.first!=interval.second) {
   flux << " " << interval.first->second;
   ++(interval.first);
  }

  flux << std::endl;
  ++it;
 }

 return flux;
}

// Fin //-------------------------------------------------------------------------------------------
#endif
