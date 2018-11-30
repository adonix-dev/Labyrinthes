/*Labyrinthe.c*/

#include "labyrinthe.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

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

int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){

  int testor[16] = {-1,-1, -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1};
  int possibilities = 0;

  for (int i = 0; i < 16-1; i = i+2) {

      int posX = testor[i] + posCourante.ligne;
      int posY = testor[i+1] + posCourante.colonne;

      if(posX >= 0 && posY >= 0 && posX < largeur && posY < longueur && (lab[posY][posX] == 0 || lab[posY][posX] == 2) ){
        coordPossibles[possibilities].ligne = posX;
        coordPossibles[possibilities].colonne = posY;
        ++possibilities;
      }
  }
  //printf("%d %d\n", posCourante.ligne, posCourante.colonne);
  for (int i = 0; i < possibilities; i++) {
  //  printf("[%d][%d]\n", coordPossibles[i].ligne, coordPossibles[i].colonne);
  }
  return possibilities;
}

void afficherChemin( chemin_t ch ){
  int i = 0;
  for (; i < ch.taille-1; i++) printf("(%d, %d),", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
  printf("(%d, %d)\n", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
}

char verifierChemin(chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart){

  char is_ok = 0;

  if((ch.coordonnees[0].ligne == depart.ligne && ch.coordonnees[0].colonne == depart.colonne)){ //Le Premiere saut du chemin est le meme que le point de depart
    for (int s = 0; s < ch.taille; s++) {
      switch (lab[ch.coordonnees[s].ligne][ch.coordonnees[s].colonne]) {
        case 0:                   //Le saut est un passage possbile
          if (abs(ch.coordonnees[s+1].ligne-ch.coordonnees[s].ligne) <= 1 && abs(ch.coordonnees[s+1].colonne-ch.coordonnees[s].colonne) <= 1) //Le prochain saut est adjacente
            is_ok = 1;
          else  return 0;  break;
        case 1: return 0;  break; //Le saut n'est pas un mur
        case 2: return 1;  break; //Le saut est la sortie
      }
    }
    return is_ok;
  }
  else return false;
}

/*Seconde partie*/
/*
coordonnee_t explorer(labyrinthe lab, labyrinthe M2, char largeur, char longueur, coordonnee_t current, char current_value){
  afficherMatrice(M2, 10, 10);
  if(lab[current.ligne][current.colonne] == 2){
    printf("Sortie\n");
    M2[current.ligne][current.colonne]++;
    return current;
  }
  else{
    coordonnee_t coordPossibles[8];
    int possibilities = deplacementsPossibles(lab, largeur, longueur, current, coordPossibles);
    for (int i = 0; i < possibilities; i++) {
      printf("[%d][%d] : %d\n", coordPossibles[i].ligne, coordPossibles[i].colonne, lab[coordPossibles[i].colonne][coordPossibles[i].ligne]);
      //explorer(lab, M2, largeur, longueur, coordPossibles[i], M2[current.ligne][current.colonne]);
    }
  }

}

chemin_t plusCourtCheminDynamique ( labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){

  M2[depart.ligne][depart.colonne] = 0 ;

  coordonnee_t out = explorer(lab, M2, largeur, longueur, depart, M2[depart.ligne][depart.colonne]);

  afficherMatrice(M2,10, 10);
  afficherMatrice(lab, 10, 10);

}
*/



/*
chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  //A faire
}
*/
