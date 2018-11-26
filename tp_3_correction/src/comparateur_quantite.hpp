// Gardien //---------------------------------------------------------------------------------------
#ifndef _COMPARATEUR_QUANTITE_HPP_
#define _COMPARATEUR_QUANTITE_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <functional>

// Classe  C o m p a r a t e u r Q u a n t i t e //-------------------------------------------------
template <typename T>
struct ComparateurQuantite : public std::binary_function<T,T,bool> {
 //--------------------------------------------------------------------------------------operator ()
 bool operator () (const T & a,const T & b) const {
  return (a.getQuantite()==b.getQuantite() ? a<b : a.getQuantite()>b.getQuantite());
 }
};

// Fin //-------------------------------------------------------------------------------------------
#endif
