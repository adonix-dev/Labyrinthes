#include "labyrinthe.h"
#include "test_matrices.h"

int main(){
  /* Tests de la création et affichage de matrices */
  labyrinthe lab1,lab2,lab3,lab4;

  // test1
  lab1 = creerMatrice(4,4, testA1, testIA1, testJA1);
  printf("\nLabyrinthe créé:");
  afficherMatrice(lab1,4,4);
  printf("\nMatrice attendue:");
  printf("\n%s",strMat1());

  //test2
  lab2 = creerMatrice(10,10, testA2, testIA2, testJA2);
  printf("\nLabyrinthe créé:\n");
  afficherMatrice(lab2,10,10);
  printf("\nMatrice attendue:");
  printf("\n%s",strMat2());

  //test3
  lab3 = creerMatrice(10,10, testA3, testIA3, testJA3);
  printf("\nLabyrinthe créé\n");
  afficherMatrice(lab3,10,10);
  printf("\nMatrice attendue:");
  printf("\n%s",strMat3());

  //test4
  lab4 = creerMatrice(4,6, testA4, testIA4, testJA4);
  printf("\nLabyrinthe créé\n");
  afficherMatrice(lab4,4,6);

  /* Tests de la vérification et de l'affichage des chemins */

  coordonnee_t * coords = (coordonnee_t*) malloc(100*sizeof(coordonnee_t));
  coordonnee_t coord;

  coord.ligne=0;
  coord.colonne=0;
  coords[0]=coord;

  coord.ligne=1;
  coord.colonne=1;
  coords[1]=coord;

  coord.ligne=2;
  coord.colonne=0;
  coords[2]=coord;

  coord.ligne=3;
  coord.colonne=0;
  coords[3]=coord;


  chemin_t ch1;
  ch1.coordonnees=coords;
  ch1.taille=4;

  coord.ligne=0;
  coord.colonne=0;

  printf("\nTests chemins sur la matrice:\n");
  afficherMatrice(lab1,4,4);
  printf("\nChemin:");
  afficherChemin(ch1);
  //deplacementsPossibles(lab1, 4, 4, coord, coords);
  printf("\nverification chemin valide: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 1\n");

  coord.colonne = 1;
  coords[0]=coord;

  coord.colonne = 2;
  coords[1]=coord;
  ch1.taille=2;

  coord.colonne = 0;
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin, 1ere coordonnee: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 0\n");

  coords[0]=coord;

  coord.colonne =2;
  coords[1]=coord;
  ch1.taille=2;

  coord.colonne=0;
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin, coordonnees non adjacentes: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 0\n");


  coords[0]=coord;
  coord.ligne=1;
  coords[1]=coord;

  ch1.taille=2;

  coord.ligne=0;
  printf("\nChemin:");
  afficherChemin(ch1);
  printf("\nverification chemin, mur: %d", verifierChemin(ch1,lab1,4,4,coord));
  printf("\nvaleur attendue: 0\n");

/*
  coord.ligne = 1; //ligne
  coord.colonne = 0; //colonne

  char longueur = 4; //ligne
  char largeur = 6;   //colonne

  labyrinthe M2 = malloc(longueur*sizeof(int*));
  for (char i = 0; i < longueur; i++) {
    M2[(int)i] = malloc(largeur*sizeof(int));
    for (char j = 0; j < largeur; j++) M2[(int)i][(int)j] = longueur*largeur;
  }
  afficherMatrice(lab4, longueur, largeur);
  printf("\nChemin de la matrice LAB4: ");
  afficherChemin(plusCourtCheminDynamique(lab4, M2, largeur, longueur, coord));

  coord.ligne = 0; //ligne
  coord.colonne = 0; //colonne

  longueur = 10; //ligne
  largeur = 10;   //colonne

  for (char i = 0; i < longueur; i++) {
    M2[(int)i] = malloc(largeur*sizeof(char));
    for (char j = 0; j < largeur; j++) M2[(int)i][(int)j] = longueur*largeur;
  }

  afficherMatrice(lab3, longueur, largeur);
  printf("\nChemin de la matrice LAB3: ");
  afficherChemin(plusCourtCheminDynamique(lab3, M2, largeur, longueur, coord));
*/
  coord.ligne = 0; //ligne
  coord.colonne = 0; //colonne

  char longueur = 10; //ligne
  char largeur = 10;   //colonne

  labyrinthe M2 = malloc(longueur*sizeof(int*));

  for (char i = 0; i < longueur; i++) {
    M2[(int)i] = malloc(largeur*sizeof(char));
    for (char j = 0; j < largeur; j++) M2[(int)i][(int)j] = longueur*largeur;
  }
  afficherMatrice(lab2, longueur, largeur);
  printf("\nChemin de la matrice LAB2: ");
  afficherChemin(plusCourtCheminDynamique(lab2, M2, largeur, longueur, coord));
  afficherMatrice(M2, largeur, longueur);
  
  tousPlusCourtsChemins(lab2, M2, largeur, longueur, coord);

/*
  coord.ligne = 0; //ligne
  coord.colonne = 0; //colonne

  longueur = 4; //ligne
  largeur = 4;   //colonne

  for (char i = 0; i < longueur; i++) {
    M2[(int)i] = malloc(largeur*sizeof(char));
    for (char j = 0; j < largeur; j++) M2[(int)i][(int)j] = longueur*largeur;
  }
  afficherMatrice(lab1, longueur, largeur);
  printf("\n");
  printf("Chemin de la matrice LAB1: ");
  afficherChemin(plusCourtCheminDynamique(lab1, M2, largeur, longueur, coord));
  */
  return 1;
}
