#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "graphemat.h"
#include "liregraphe.h"

typedef GrapheMat Graphe;


int menu ()
{
    printf ("\n\nGRAPHES avec matrices\n\n");

    printf ("0 - Fin du programme\n");
    printf ("1 - Création à partir d'un fichier\n");
    printf ("2 - Liste des sommets et des arcs\n");
    printf ("3 - Plus proche voisin \n");

    printf ("\n");
    printf ("Votre choix ? ");
    int cod;
    scanf ("%d", &cod);
    getchar();
    printf ("\n");
    return cod;
}

int nbville(Graphe* g)
{
    return g->n;
}


int nbtraget = 0;
bool sommetDansTraget(int* traget, int s)
{
    for(int i = 0; i < nbtraget; i++)
    {
        if(traget[i] == s)
            return true;
    }
    return false;
}
int* creerTrajet(Graphe* g, int premier)
{
    int * traget = (int *) malloc(sizeof(int) * g->n);

    if(g->n > premier)
    {
        traget[0] = premier;
    }
    else
        printf("Depassement de capacité");

    return traget;
}

void ajouter(int* traget, int s)
{
    traget[++nbtraget] = s;
}
void afficherTraget(Graphe* graphe, int* traget)
{
    printf("Traget plusProcheVoisin : ");
    for(int i = 0; i < nbtraget; i++)
    {
        printf ("%s ", graphe->nomS[traget[i]]) ;
    }
}

int plusProcheVoisin (GrapheMat* graphe, int s, int * target)
{
    int posmin = -1;
    if (graphe->n == 0)
    {
        printf ("Le graphe est vide\n");
    }
    else
    {
        int minc = 1000000;
        int nMax = graphe->nMax;
        for (int j=0; j<graphe->n; j++)
        {
            if (graphe->element [s*nMax+j] == vrai)
            {
                if (graphe->value)
                {
                    if(graphe->valeur [s*nMax+j] < minc && !sommetDansTraget(target, j))
                    {
                        minc = graphe->valeur [s*nMax+j];
                        posmin = j;
                    }
                }
            }
        }
    }
    return posmin;
}

int randomVille(int max)
{
    return rand() % max;
}

int main ()
{
    srand(time(0));
    Graphe* graphe;
    booleen fini = faux;
    while (!fini)
    {
        switch ( menu() )
        {
        case 0:
            fini = vrai;
            break;
        case 1:    // création à partir d'un fichier
        {
            printf ("Nom du fichier contenant le graphe <graphe.txt> ");
            char nomFe [50] = "graphe.txt";
            FILE* fe = fopen (nomFe, "r");
            if (fe == NULL)
            {
                perror (nomFe);
            }
            else
            {
                graphe = lireGraphe (fe, 20); // 20 sommets maximum
                fclose (fe);
            }
            break;
        }

        case 2:
            ecrireGraphe (graphe);
            break;
        case 3:
            int rv = randomVille(graphe->n);
            printf("random ville = %d\n", rv);
            int* traget = creerTrajet(graphe, rv);
            int s = rv;
            while(nbtraget < graphe->n)
            {
                s = plusProcheVoisin(graphe, s, traget);
                ajouter(traget, s);
            }
            afficherTraget(graphe, traget);
            break;
        }
        if (!fini)
        {
            printf ("\n\nTaper Return pour continuer\n");
            getchar();
        }
    }

    return 0;
}
