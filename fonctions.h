 #ifndef AFFICHEGRILLE_H_INCLUDED
#define AFFICHEGRILLE_H_INCLUDED
#include <conio.h>
#include <windows.h>
void gotoxy(int x,int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    fflush(stdout);
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}
void clrscr()
{
  system("cls");
}

void afficheGrille(int x,int y,int cols,int lines)
{
    cols=cols*4;
    lines*=2;
    int i,j,n=0,t=0;
   for(i=2;i<cols;i=i+4)//pour mettre les indices en haut de chaque colonne de la grille
    {
        gotoxy(x+i,y-1);//y-1 pour se positionner à une ligne avant la grille et x+i pour se positionner à l'emplacement exact qui varie
        printf("%d",n);
        n=n+1;
    }
    for(i=1;i<lines;i=i+2)//pour mettre les indices à la gauche de chaque ligne de la grille
    {
        gotoxy(x-1,y+i);//x-1 pour se positionner à gauche de la grille puis y+i pour aller à l'emplacement précis qui varie
        printf("%d",t);
        t+=1;
    }
    gotoxy(x,y); //postion de l'angle supérieur gauche de la grille ┌
    printf("%c",218);
    gotoxy(x+cols,y);//postion de l'angle supérieur droit de la grille┐
    printf("%c",191);
    gotoxy(x,y+lines);//postion de l'angle inférieur gauche de la grille└
    printf("%c",192);
    gotoxy(x+cols,y+lines);//postion de l'angle inférieur droit de la grille┘
    printf("%c",217);
    for(i=4;i<cols;i=i+4)//pour tracer les deux grandes lignes horizontales de la grille
    {//avec les symboles ┬ et ┴ et ainsi délimiter les colonnes
        gotoxy(x+i,y);
        printf("%c",194);
        gotoxy(x+i,y+lines);
        printf("%c",193);
    }
    for(i=2;i<lines;i=i+2)//pour tracer les deux grandes lignes verticales de la grille
    {//avec les symboles ├ et ┤ et ainsi délimiter les lignes
        gotoxy(x,y+i);
        printf("%c",195);
        gotoxy(x+cols,y+i);
        printf("%c",180);
    }
    for(i=4;i<cols;i=i+4)//pour signifier le croisement entre ligne et colonne
    {//en plaçant le symbole ┼ et ainsi délimiter les cellules de la grille
        for(j=2;j<lines;j=j+2)
        {
            gotoxy(x+i,y+j);
            printf("%c",197);
        }
    }
    for(i=0;i<=lines;i=i+2)//pour fermer une partie des espaces vides de la
    {//grille de façon horizontale avec le symbole ─
        for(j=1;j<cols;j=j+2)
        {
            gotoxy(x+j,y+i);
            printf("%c",196);
        }

    }
    for(i=0;i<=lines;i=i+2)//pour fermer la seconde partie des espaces vides de la
    {//grille de façon horizontale avec le symbole ─
        for(j=2;j<cols;j=j+4)
        {
            gotoxy(x+j,y+i);
            printf("%c",196);
        }

    }
   /* for(i=4;i<cols;i=i+4)
    {
        for(j=2;j<lines;j=j+2)//
        {
            gotoxy(x+i,y+j);
            printf("%c",197);
        }
    }*/
    for(i=0;i<=cols;i=i+4)//pour fermer les espaces vides de la
    {//grille de façon verticale avec le symbole │
        for(j=1;j<=lines;j=j+2)
        {
           gotoxy(x+i,y+j);
           printf("%c",179);

        }
    }
}//FIN de la fonction afficheGrille
void initTableau(int tab[8][8])
{
    int i,j;
    for(i=0;i<8;i++)//Avec ce code , i est a 0 et j prend les valeurs de 0 à 7
    {//puis i passe à 1 et j prends tjrs les mêmes valeurs et on repete
        for(j=0;j<8;j++) //jusqu'à arriver a i=7 et j=7
        {
            tab[i][j]=0;//initialiser chaque cellule à la valeur 0
        }
    }
}// FIN DE initTableau
/*void afficher(int tab[8][8])
{
     int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%d",tab[i][j]);
        }
    }
}*/
void afficheMatrice(int tab[8][8],int x,int y,int coord1,int coord2)//prend en paramètre les emplacements x et y de notre grille de depart
{//Puis les coordonnées de la cellule à afficher
    int i,j,n=2,m=1;//n permet de faire des sauts dans les colonnes de la grille et m dans les lignes
    for(i=0;i<8;i++)//les deux boucles for permettent de parcourir toutes les cellules de la matrice
    {
        for(j=0;j<8;j++)
        {
           gotoxy(x+n,y+m);//cette ligne permet de se placer dans l'emplacement de la grille où on doit afficher la cellule à chaque passage de la boucle
           if(i==coord1 && j==coord2)//on verifie si i et j correspondent aux coordonnées de la cellule qu'on veut afficher
           {
               printf("%d",tab[i][j]);//si c'est le cas on affiche dans la grille la valeur qui se trouve dans cette cellule de la matrice
           }
           m+=2;
        }
        n+=4;//pour aller au milieu de la colonne suivante
        m=1;//on met m=1 pour revenir sur la première ligne
    }
}//Fin de afficheMatrice
void miner(int tab[8][8],int nombreMines)
{
    const int MAX = 7, MIN = 0;//nombre aléatoire maximum est 7 et mininum est 0
    srand(time(NULL));
    int i=0,n=0;
    do
    {
        int nbr = (rand() % (MAX - MIN + 1)) + MIN;//1er nombre aléatoire généré
        int nbr1 = (rand() % (MAX - MIN + 1)) + MIN;//2e nombre aléatoire généré
        if(tab[nbr][nbr1]==0)//vérifier on a pas encore placé de mines à cet emplacement
        {
            tab[nbr][nbr1]=-1;//si oui mettre à -1
            n=n+1;//pour compter le nombre de mines placés
        }
    }while(n<nombreMines);//répéter tant qu'on aura pas placer le nombre de mmines qu'il faut
    //la boucle a été fait pour éviter de placer une mine à un même emplacement plusieurs fois
    //car les deux nombres aléatoires peuvent être les mêmes
} //FIN DE LA FONCTION miner
void renseigner(int tab[8][8],int i,int j)
{
    if(tab[i][j]==0){//pour éviter de renseigner une cellule contenant une mine
    int x,y,n=0;
    for(x=i-1;x<=i+1;x++)//x va de i-1 pour dire la colonne avant la colonne
    {//de la cellule qu'on veut renseigner
        for(y=j-1;y<=j+1;y++)//y va de j-1 pour dire la ligne avant la ligne
        {//de la cellule qu'on veut renseigner
            if(x>=0 && y>=0 && x<8 && y<8)//vérifier si x et y sont bien comprises entre 0 et 7
            {
               if(tab[x][y]==-1)//si la valeur de d'une des cellules adjacentes est -1
               {
                   n=n+1;//compter une mine
               }
            }
        }
    }
    tab[i][j]=n;//mettre la valeur de n trouvé dans la celllule qu'on veut renseigner
    //n représente le nombre de mines autour
    }
}//FIN DE LA FONCTION renseigner
int afficheVoisin(int tab[8][8],int tab2[8][8],int posX,int posY,int i,int j)//permet d'afficher les cases adjacentes
{//d'une cellule tout en comptant le nombre dans les cases adjacentes
    int x,y,mineTrouve=0;
    for(x=i-1;x<=i+1;x++)
    {
        for(y=j-1;y<=j+1;y++)
        {
            if(x>=0 && y>=0 && x<8 && y<8)//le même principe que pour la fonction renseigner jusqu'ici
            {
                afficheMatrice(tab,posX,posY,x,y);//pour afficher une case adjacente
                tab2[x][y]=1;//marquer qu'une cellule a deja été ouverte en remplaçant sa valeur par 1
                if(tab[x][y]==-1)//si la cellule contient une mine
                {
                    mineTrouve=1;//pour indiquer qu'il y a une mine dans les cellules adjacentes
                }

            }
        }
    }
    return mineTrouve;

}//FIN DE LA FONCTION afficheVoisin
int nombreDeVoisins(int tab[8][8],int tab2[8][8],int i,int j)
{
    int x,y,nbVoisin=0;
    for(x=i-1;x<=i+1;x++)
    {
        for(y=j-1;y<=j+1;y++)
        {
            if(x>=0 && y>=0 && x<8 && y<8)//même principe que dans la fonction renseigner jusqu'ici
            {
                if(tab2[x][y]==0){//si la cellule n'a pas encore été ouverte ou affiché
                nbVoisin=nbVoisin+1;//compter le nombre de voisin
                }

            }
        }
    }
    nbVoisin=nbVoisin-1;//comme on compte aussi la cellule concernéé dans les cellules adjacentes
    return nbVoisin;

}//FIN DE LA FONCTION nombreDeVoisins
int nombreDeCasesOuvertes(int tab[8][8])
{
    int i,j,nbr=0;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(tab[i][j]==1)//si la cellule a deja été ouverte
            {
                nbr+=1;
            }
        }
    }
    return nbr;
}//FIN DE LA FONCTION nombreDeCasesOuvertes
#endif // AFFICHEGRILLE_H_INCLUDED
