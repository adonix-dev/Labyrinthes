/*Labyrinthe.c*/

#include "labyrinthe.h"
#include <stdbool.h>

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

/*
X X X
X A X
X X X
*/
int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){

  int testor[16] = {-1,-1, 0,-1, 1,-1, 1,0, 1,1, 0,1, -1,1, -1,0};
  int possibilities = 0;

  for (int i = 0; i < 16-1; i = i+2) {

      int posX = testor[i] + posCourante.colonne;
      int posY = testor[i+1] + posCourante.ligne;

      if(posX >= 0 && posY >= 0 && posX < largeur && posY < longueur && (lab[posY][posX] == 0 || lab[posY][posX] == 2) ){
        coordPossibles[possibilities].colonne = posX;
        coordPossibles[possibilities].ligne = posY;
        ++possibilities;
      }
  }
  return possibilities;
}

char verifierChemin( chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){

  if((!ch.coordonnees[0].ligne || !ch.coordonnees[0].colonne)
    && !lab[ch.coordonnees[0].colonne][ch.coordonnees[0].ligne]){

    for (int p = 0; p < ch.taille-1; p++) {

      coordonnee_t * coordPossibles = (coordonnee_t*)malloc(8*sizeof(coordonnee_t));

      for(int c = 0; c < deplacementsPossibles(lab, largeur, longueur, ch.coordonnees[p], coordPossibles); ++c)
        if((coordPossibles[c].ligne == ch.coordonnees[c+1].ligne
          && coordPossibles[c].colonne == ch.coordonnees[c+1].colonne)
          || lab[ch.coordonnees[c+1].ligne][ch.coordonnees[c+1].colonne] == 2)
          return 1;

      free(coordPossibles);
    }
  }
  return 0;
}

void afficherChemin( chemin_t ch ){
  int i = 0;
  for (; i < ch.taille-1; i++) printf("(%d, %d),", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
  printf("(%d, %d)\n", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
}


/*Seconde partie*/
/*
chemin_t plusCourtCheminDynamique ( labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  //A faire
}

chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  //A faire
}
*/
