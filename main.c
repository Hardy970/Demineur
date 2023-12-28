#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include <windows.h>
int main()
{
    int recommencer=0,choix=0,nombreDeCaseOuverte=0;
    int tab1[8][8],tab2[8][8];
    do{
    initTableau(tab1);//initialiser la matrice qui représente notre jeu en mémoire
    initTableau(tab2);//initialiser la seconde matrice qui va marquer les cellules ouvertes
    char action,casejouer[3];
    int i,j,nombreDeMines,minesRestantes,coord1,coord2,perdu=0,gagne=0;
    do{
    printf("\t\t\t\t\t\t*********BIENVENU DANS DEMINEUR*********\n\n");
    printf("Combien de mines voulez-vous?(Ce nombre est compris entre 8 et 12):");
    scanf("%d",&nombreDeMines);
    }while(nombreDeMines<8 || nombreDeMines>12);//controler la saisie
    miner(tab1,nombreDeMines);//placer les mines dans notre matrice
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            renseigner(tab1,i,j); //renseigner chaque cellule de la matrice
        }
    }
    minesRestantes=nombreDeMines;
    printf("\nBONNE CHANCE!");
    clrscr();//effacer l'écran
    gotoxy(8,4);printf("NOMBRE DE MINES:%d",nombreDeMines);
    gotoxy(8,6);printf("MINES RESTANTES:%d",minesRestantes);
    gotoxy(8,15);printf("M-Pour marquer une mine");
    gotoxy(8,16); printf("V-Pour ouvrir une case vide");
    gotoxy(8,17); printf("V-Pour ouvrir les voisins");
    gotoxy(9,18); printf("d'une case vide deja jouee");
    afficheGrille(50,3,8,8);//afficher la grille
    do{
      do{
    gotoxy(50,20);
    printf("Quelle case jouee?:");
    scanf("%d",&coord1);
    gotoxy(71,20);
    scanf("%d",&coord2);fflush(stdin);
    gotoxy(73,20);
    scanf("%c",&action);
    }while(coord1>7 && coord1<0 && coord2>7 && coord2<0 && action!='V' && action!='M');
    if(action=='V'&& tab2[coord1][coord2]==0)//si l'action c'est ouvrir et la cellule n'a pas encore été ouverte
    {
        afficheMatrice(tab1,50,3,coord1,coord2);//afficher la cellule
        tab2[coord1][coord2]=1;//marquer dans la seconde matrice qu'on vient d'afficher cette cellule
        nombreDeCaseOuverte=nombreDeCasesOuvertes(tab2);//mettre dans nombreDeCaseOuverte le nombre de case ouvertes
        if(tab1[coord1][coord2]==-1)//si la case qu'on veut afficher comporte une mine
        {
            perdu=1;//mettre perdu à 1
        }
        if(nombreDeCaseOuverte==(64-nombreDeMines))//si nombre de cases ouvertes est égal au nombre de cases non minées
        {
            gagne=1;
        }
        continue;//pour ne pas exécuter les actions du prochain
    }
    if(action=='V' && tab2[coord1][coord2]==1)//si action est V et la case a été deja affichée
    {
        perdu=afficheVoisin(tab1,tab2,50,3,coord1,coord2);//afficher ses voisins et renvoyer le résultat de la fonction dans perdu
        nombreDeCaseOuverte=nombreDeCasesOuvertes(tab2);

    }
    if(action=='M')
    {
        if(tab1[coord1][coord2]==-1)
        {
         gotoxy(50+coord1*4 +2,3+coord2*2 +1);printf("M");//placer la lettre M dans la cellule correspondante
         minesRestantes=minesRestantes-1;
         gotoxy(8,6);printf("MINES RESTANTES:%d.0",minesRestantes);
        }
        else
        {
            perdu=1;
        }
    }
    //gotoxy(75,20);printf("%d",nombreDeCaseOuverte);
    if(nombreDeCaseOuverte==(64-nombreDeMines))
    {
        gagne=1;
    }
    }while(!perdu && !gagne);//la boucle continue tant qu'on a pas perdu ou gagné
    if(perdu)
    {
        gotoxy(50,22);
        printf("Dommage, Vous avez perdu\n");
    }
    if(gagne)
    {
        gotoxy(50,22);
        printf("Felicitations, Vous remportez la partie\n");
    }
    do{
            gotoxy(50,23);
    printf("Commencer une nouvelle partie ?(1 pour OUI/0 pour NON)");
    scanf("%d",&choix);}while(choix!=1 &&  choix!=0);//controler la saisie

    }while(choix==1);//la partie recommence tant que le choix est 1
   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}
