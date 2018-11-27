/*Labyrinthe.c*/

#include "labyrinthe.h"

/*Premiere partie*/

labyrinthe creerMatrice (unsigned int lignes, unsigned int colonnes, char* A, char* IA, char* JA){
  labyrinthe lab = calloc(lignes,sizeof(unsigned char*));
  for (unsigned int i = 0; i < lignes; i++) {
      lab[i] = calloc(colonnes,sizeof(unsigned char));
      for (unsigned int j = IA[i]; j < IA[i+1] ; j++) lab[i][(unsigned int)JA[j]] = A[j];
  }
  return lab;
}

void afficherMatrice( labyrinthe lab, unsigned int lignes, unsigned int colonnes ){
  printf("\n");
  for (unsigned int i = 0; i < lignes; ++i){
    for (unsigned int j = 0; j < colonnes; ++j) printf("%d ", lab[i][j]);
    printf("\n");
  }
}

int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){

  int testor[16] = {-1,-1, 0,-1, 1,-1, 1,0, 1,1, 0,1, -1,1, -1,0};
  int possibilities = 0;

  for (int i = 0; i < 16-1; i = i+2) {

      int posX = testor[i] + posCourante.colonne;
      int posY = testor[i+1] + posCourante.ligne;

      if(x >= 0 && y >= 0 && x < largeur && y < longueur && lab[posY][posX] == 0){
        coordPossibles[possibilities].colonne = posX;
        coordPossibles[possibilities].ligne = posY;
        ++possibilities;
      }
  }
  return possibilities;
}

/*
0 0 0
0 A 0
0 0 0
*/

/*
char verifierChemin( chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){
  //A faire
}

void afficherChemin( chemin_t ch ){
  //A faire
}
*/

/*Seconde partie*/
/*
chemin_t plusCourtCheminDynamique ( labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  //A faire
}

chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  //A faire
}
*/
