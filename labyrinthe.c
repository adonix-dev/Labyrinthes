/*Labyrinthe.c*/
/* * * * * * * * * * * * * * * * * * * *
 * LAGET Antony                        *
 * TPA12                               *
 * Dimanche 2 Décembre 2018            *
 * github.com/adonix-dev/Labyrinthes   *
 * * * * * * * * * * * * * * * * * * * */

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
  return possibilities;
}

void afficherChemin( chemin_t ch ){
  int i = 0;
  for (; i < ch.taille-1; i++) printf("(%d, %d),", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
  printf("(%d, %d)\n", ch.coordonnees[i].ligne, ch.coordonnees[i].colonne);
}

char verifierChemin(chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart){

  if((ch.coordonnees[0].ligne == depart.ligne && ch.coordonnees[0].colonne == depart.colonne)){ //Le Premiere saut du chemin est le meme que le point de depart
    char is_ok = 0;
    for (int s = 0; s < ch.taille; s++) {
      switch (lab[ch.coordonnees[s].ligne][ch.coordonnees[s].colonne]) {
        case 0:                   //Le saut est un passage possbile
          if (abs(ch.coordonnees[s+1].ligne-ch.coordonnees[s].ligne) <= 1 && abs(ch.coordonnees[s+1].colonne-ch.coordonnees[s].colonne) <= 1) //Le prochain saut est adjacente
            is_ok = 1;
          else  return 0; break;
        case 1: return 0; break; //Le saut n'est pas un mur
        case 2: return 1; break; //Le saut est la sortie
      }
    }
    return is_ok;
  }
  return false;
}

/*Seconde partie*/

/*usleep(500000);
clearScreen();
afficherMatrice(M2, longueur, largeur);*/
//printf("[%d][%d]: %d\n", current.ligne, current.colonne,lab[current.colonne][current.ligne]);

void explorer(labyrinthe lab, labyrinthe M2, char largeur, char longueur, coordonnee_t current, int current_value, coordonnee_t* out){
  M2[current.colonne][current.ligne] = current_value + 1;
  if(lab[current.colonne][current.ligne] == 2) *out = current; //On remonte la sortie du labyrinthe
  else{
    coordonnee_t coordPossibles[8];
    for (int i = 0; i < deplacementsPossibles(lab, largeur, longueur, current, coordPossibles); i++)
      if(M2[coordPossibles[i].colonne][coordPossibles[i].ligne] > M2[current.colonne][current.ligne])
        explorer(lab, M2, largeur, longueur, coordPossibles[i], M2[current.colonne][current.ligne], out);
  }
}

chemin_t calculerChemin(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t current){

  chemin_t ch;
  ch.coordonnees = (coordonnee_t*) malloc(largeur*longueur*sizeof(coordonnee_t));
  ch.taille = M2[current.colonne][current.ligne];
  int a = ch.taille;

  while (a >= 0) {
    ch.coordonnees[a].ligne = current.colonne;
    ch.coordonnees[a].colonne = current.ligne; // Pour affichage (ligne, colonne)
    coordonnee_t coordPossibles[8];
    for (int i = 0; i < deplacementsPossibles(lab, largeur, longueur, current, coordPossibles); i++)
      if(M2[coordPossibles[i].colonne][coordPossibles[i].ligne] == a-1){
        current = coordPossibles[i];
        break;
      }
    a--;
  }
  ch.taille++;

  return ch;
}

chemin_t plusCourtCheminDynamique(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){

  coordonnee_t sortie;

  int tmp = depart.colonne;       //
  depart.colonne = depart.ligne;  //   Correctif
  depart.ligne = tmp;             //

  M2[depart.colonne][depart.ligne] = 0;

  explorer(lab, M2, largeur, longueur, depart, M2[depart.colonne][depart.ligne]-1, &sortie);

  return calculerChemin(lab, M2, largeur, longueur, sortie);

}

chemin_t* tousPlusCourtsChemins_rec(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t current, chemin_t* ch_tab, int ch_num){

  printf("Pseudo code en commentaire\n");

  /*
  * - Explorer les possibilitees de mouvement depuis une coordonnee "current"
  * tel que celle ci est une valeur dans M2 qui soit la valeur de la coordonnee courante - 1.
  * - Chaque possibilitees cree un nouveau chemin qu'on alloue dans "ch_tab" et qu'on numérote.
  * - On prend le soin de recopier les cases passées dans le nouveau chemin.
  * - Quand on avance à une case suivante on l'ajoute au chemin "ch_num" correspondant.
  * - On s'arrete quand on arrive à la case de depart du labyrinthe, c'est à dire 0 dans M2.
  */
  return (ch_tab);

}

chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){

  coordonnee_t sortie;
  chemin_t* ch_tab = (chemin_t*)malloc(largeur*longueur*sizeof(coordonnee_t));

  int tmp = depart.colonne;       //
  depart.colonne = depart.ligne;  //   Correctif
  depart.ligne = tmp;             //

  M2[depart.colonne][depart.ligne] = 0;

  explorer(lab, M2, largeur, longueur, depart, M2[depart.colonne][depart.ligne]-1, &sortie);

  printf("Sortie du labyrinthe: [%d][%d]\n", sortie.colonne, sortie.ligne);

  tousPlusCourtsChemins_rec(lab, M2, largeur, longueur, sortie, ch_tab, 0);

  return ch_tab;

}
