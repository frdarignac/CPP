// Gardien //---------------------------------------------------------------------------------------
#ifndef _VALEUR_HPP_
#define _VALEUR_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <string>

// Classe  V a l e u r //---------------------------------------------------------------------------
class Valeur {
 //----------------------------------------------------------------------------------------Attributs
 private:
  // double nombre_;
  std::string etudiant_;
  double      note_;
 //---------------------------------------------------------------------------------------Accesseurs
 public:
  // double getNombre(void) const { return nombre_; }
  double              getNombre(void) const { return note_; }
  const std::string & getEtudiant(void) const { return etudiant_; }
  double              getNote(void) const     { return note_; }

  // void setNombre(double nombre) { nombre_=nombre; }
  void setNombre(double nombre) { note_=nombre; }
  void setEtudiant(const std::string & etudiant) { etudiant_=etudiant; }
  void setNote(double note) { note_=note; }
 //------------------------------------------------------------------------------------Constructeurs
 public:
  // Valeur(double nombre = 0.0) : nombre_(nombre) {}
  Valeur(double note = 0.0,const std::string & etudiant = "inconnu")
  : etudiant_(etudiant),note_(note) {}
};

// Fonctions inline //------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------Operator <
inline bool operator < (const Valeur & valeur1,const Valeur & valeur2) {
 return (valeur1.getNombre() < valeur2.getNombre());
}

//---------------------------------------------------------------------------------------Operator <<
inline std::ostream & operator << (std::ostream & flux,const Valeur & valeur) {
 // flux << valeur.getNombre();
 flux << "(" << valeur.getEtudiant() << ";" << valeur.getNote() << ")";
 return flux;
}

// Fin //-------------------------------------------------------------------------------------------
#endif
