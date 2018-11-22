/*Labyrinthe.c*/

#include "labyrinthe.h"


/*Premiere partie*/

labyrinthe creerMatrice (unsigned int lignes, unsigned int colonnes, char* A, char* IA, char* JA){
  /*A faire*/
}

void afficherMatrice( labyrinthe lab, unsigned int lignes, unsigned int colonnes ){
  /*A faire*/
}

int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){
  /*A faire*/
}

char verifierChemin( chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){
  /*A faire*/
}

void afficherChemin( chemin_t ch ){
  /*A faire*/
}


/*Seconde partie*/

chemin_t plusCourtCheminDynamique ( labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  /*A faire*/
}

chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  /*A faire*/
}
