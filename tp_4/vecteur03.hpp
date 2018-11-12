// Gardien //---------------------------------------------------------------------------------------
#ifndef _VECTEUR03_HPP_
#define _VECTEUR03_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include "complexe.hpp"
#include <stdexcept>
#include <algorithm>

// Classe  V e c t e u r //-------------------------------------------------------------------------
class Vecteur {
 //----------------------------------------------------------------------------------------Attributs
 private:
  unsigned     taille_;
  complexe_t * tableau_;

 //---------------------------------------------------------------------------------------Accesseurs
 public:
 
  unsigned getTaille(void) const { return taille_; }

/******************/

  complexe_t & operator[](unsigned i) 
  {
	if (i<taille_) 
	{
	   return tableau_[i];
	}

	throw std::out_of_range("");
  }

/******************/

  const complexe_t & operator[](unsigned i) const 
  {
	if (i<taille_)
	{
	    return tableau_[i];
	}
	
	throw std::out_of_range("");
  }

/******************/

	complexe_t * begin() const
	{
		return tableau_;
	}
	
/******************/

	complexe_t * end() const
	{
		return tableau_ + taille_;
	}
	
/******************/

 public:
  //-----------------------------------------------------------------------------Constructeur defaut
  explicit Vecteur(unsigned t = 10) : taille_(t),tableau_(new complexe_t[taille_]) {}

  //------------------------------------------------------------------------------Constructeur copie
  Vecteur(const Vecteur & v) : taille_(v.taille_),tableau_(new complexe_t[taille_]) 
  {
	  int i = 0;
	std::for_each(v.begin(), v.end(), [&](complexe_t &){ tableau_[i]=v[i];i++;});
   /*for (unsigned i = 0; i<taille_; ++i) tableau_[i]=v[i];*/
  }

  //-------------------------------------------------------------------------------------Destructeur
  ~Vecteur(void) { if (tableau_) delete [] tableau_; }

  //-------------------------------------------------------------------------------Affectation copie
  Vecteur & operator=(const Vecteur & v) {
   if (this!=&v) {
    if (taille_!=v.taille_) throw std::length_error("");
    int i = 0;
	std::for_each(v.begin(), v.end(), [&](complexe_t &){ tableau_[i]=v[i];i++;});
   }

   return *this;
  }
};

// Surcharge operateurs //--------------------------------------------------------------------------

//----------------------------------------------------------------------------------------operator<<
inline std::ostream & operator<<(std::ostream & flux,const Vecteur & v) {
 for (unsigned i = 0; i<v.getTaille(); ++i) flux << v[i] << " ";
 return flux;
}

//-----------------------------------------------------------------------------------------operator+
inline Vecteur operator+(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v;

 for (unsigned i = 0; i<v1.getTaille(); ++i) v[i]=v1[i]+v2[i];

 return v;
}

//-----------------------------------------------------------------------------------------operator*
inline Vecteur operator*(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v;

 for (unsigned i = 0; i<v1.getTaille(); ++i) v[i]=v1[i]*v2[i];

 return v;
}

// Fin //-------------------------------------------------------------------------------------------
#endif
