/*Labyrinthe.c*/

#include "labyrinthe.h"
#include <stdbool.h>
#include <unistd.h>

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

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
    for (unsigned int j = 0; j < colonnes; ++j) printf("%3d ", lab[i][j]);
    printf("\n");
  }
}

/*
X X X
X A X
X X X
*/
int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){

  int testor[16] = {-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};
  int possibilities = 0;

  for (int i = 0; i < 16-1; i = i+2) {

      int posX = testor[i] + posCourante.ligne;
      int posY = testor[i+1] + posCourante.colonne;

      if(posX >= 0 && posY >= 0 && posX < largeur && posY < longueur && (lab[posX][posY] == 0 || lab[posX][posY] == 2) ){
        coordPossibles[possibilities].ligne = posY;
        coordPossibles[possibilities].colonne = posX;
        ++possibilities;
      }
  }

  return possibilities;
}

char verifierChemin( chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){

  bool is_ok = false;

  if((!ch.coordonnees[0].ligne || !ch.coordonnees[0].colonne)
    && !lab[ch.coordonnees[0].colonne][ch.coordonnees[0].ligne]){

    for (int p = 0; p < ch.taille; p++) {

      coordonnee_t coordPossibles[8];

      for(int c = 0; c < deplacementsPossibles(lab, largeur, longueur, ch.coordonnees[p], coordPossibles); ++c)
        if((coordPossibles[c].ligne == ch.coordonnees[p+1].ligne
          && coordPossibles[c].colonne == ch.coordonnees[p+1].colonne
          && lab[ch.coordonnees[c].colonne][ch.coordonnees[c].ligne] == 0)
          || lab[ch.coordonnees[p+1].colonne][ch.coordonnees[p+1].ligne] == 2){
          is_ok = true;
          break;
        }
        else is_ok = false;
    }
  }
  return (char)is_ok;
}

void afficherChemin( chemin_t ch ){
  int i = 0;
  for (; i < ch.taille-1; i++) printf("(%d, %d),", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
  printf("(%d, %d)\n", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
}
/*
coord sortie explorer_rec(case_courante, val_precedente){
  if(case_courente = 2){
    return coord case_courente;
  }
  else{
    for chaque depaclement possible{
      explorer(depalacement possbile, val_courante);
    }
  }
  case_courente = val_precedante+1
}
*/

coordonnee_t explorer_rec(labyrinthe lab, labyrinthe M2, char largeur, char longueur, coordonnee_t current, char current_value){
  if(lab[current.ligne][current.colonne] == 2){
    //printf("mdr\n");
    return current;
  }
  else{
    //printf("lol\n");
    coordonnee_t coordPossibles[8];
    int possibilities = deplacementsPossibles(lab, largeur, longueur, current, coordPossibles);

    for (int i = 0; i < possibilities; i++) {
      printf("[%d][%d]\n", coordPossibles[i].ligne, coordPossibles[i].colonne);
    }

    /*
    for (int i = 0; i < possibilities; i++) {
      //printf("--%d\n", lab[coordPossibles[i].ligne][coordPossibles[i].colonne]);
      M2[current.ligne][current.colonne] = current_value + 1;
      explorer_rec(lab, M2, largeur, longueur, current, M2[current.ligne][current.colonne]);
    }*/

  }
  afficherMatrice(M2, 10, 10);
}
/*
coordonnee_t explorer(labyrinthe lab, labyrinthe M2, char largeur, char longueur, coordonnee_t depart){


}
*/
/*Seconde partie*/

chemin_t plusCourtCheminDynamique ( labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){


  //lab[depart.ligne][depart.colonne] = 56;
  M2[depart.ligne][depart.colonne] = 0 ;
  afficherMatrice(M2,10, 10);
  afficherMatrice(lab, 10, 10);



  coordonnee_t out = explorer_rec(lab, M2, largeur, longueur, depart, M2[depart.ligne][depart.colonne]);





  chemin_t ch;
  return ch;
}
/*
chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  //A faire
}
*/
