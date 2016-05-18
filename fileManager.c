#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../struct.h"

int COM_change_extension(path src, const char *ext) // Modifie l'extension du chemin de fichier passé en paramètre
{
    if(src!=NULL && ext!=NULL)
    {
        char *c1, *c2;
        c1=src;
        while((c2=strchr(c1+1, '.'))!=NULL)
            c1=c2;
        strcpy(c1+1, ext);
        return 0;
    }
    return 1;
}

zone *COM_readMap(path fp)
{
    if(fp!=NULL)
    {
        FILE *f=fopen(fp, "r");
        if(f!=NULL)
        {

        }
    }
    return NULL;
}

void Write_File_Bin(char *dst, zone *src, int w, int h)
{
    printf("All in\n");
    if(dst!=NULL && src!=NULL)
    {
        printf("All\n");
        int **t=src->m;
        if(t!=NULL)
        {
            printf("In\n");
            FILE *f=fopen(dst, "wb");
            if(f!=NULL)
            {
                printf("Gonna be alright\n");
                int i;
                int k[2]={h, w};
                fwrite(k, sizeof(int), 2, f);
                for(i=0; i<src->h; i++)
                    fwrite(t[i], sizeof(int), src->w, f);
                fclose(f);
            }
        }
    }
    printf("passed away\n");
}

void _COM_readFile_ASC(char *src, map *m, unsigned int x, unsigned int y, unsigned int w, unsigned int h) // a et b seront déterminés par l'appel à une sous-fonction à l'avenir
{
    if(src!=NULL && /*t!=NULL &&*/ m!=NULL)
    {
        if(m->z==NULL)
            m->z=(zone*)malloc(sizeof(zone));
        zone *z=m->z;
            // Lecture du fichier
        FILE *f;
        f=fopen(src, "r"); // Ouverture en mode lecture

        if(f!=NULL)
        {
/**/            printf("\n\n");
            unsigned int a, b;
            fscanf(f, "ncols          %i\n", &a); m->w=a;
            fscanf(f, "nrows          %i\n", &b); m->h=b;
            int tampon;
            fscanf(f, "xllcorner      %i\n", &tampon);
            fscanf(f, "yllcorner      %i\n", &tampon);
            fscanf(f, "cellsize       %i\n", &(m->pas));
            fscanf(f, "NODATA_value   %i\n", &(m->NODATA));
            z->x=x;
            z->y=y;
            m->WATERLEVEL=0;
            if(w+x<a)
                z->w=w;
            else
                z->w=a-x;
            if(h+y<b)
                z->h=h;
            else
                z->h=b-y;

            unsigned int toscan=1000; // Nombre de valeurs à scanner à la fois
            unsigned int scanned; // Nombre de valeurs scannées par fread()
            int flag; // permet de savoir si la case courante a vu sa valeur modifiée pour utilisation ou non
            z->m=malloc(b*sizeof(int*)); // Allocation des pointeurs de ligne, devra être fait pendant le parcours plus tard
            unsigned int i;
            for(i=0;i<b;i++) // Allocation des tableaux de ligne
                z->m[i]=calloc(a, sizeof(int));
            char *c=(char*)malloc((toscan+1)*sizeof(char)); // Chaîne stockant les valeurs lues dans le fichier
            int col=0, ligne=0, neg=0; // Position dans le tableau (col et ligne), valeur courante négative ou non
            printf("Start scan\n");
            while((scanned=fread(c, sizeof(char), toscan, f))>0) // tant que fread stocke des valeurs dans c
            {
                c[scanned]='\0'; // On ajoute un caractère de fin de chaîne (utile seulement pour l'affichage)
                for(i=0;i<scanned;i++) // On parcourt la chaîne obtenue
                {
                    if(c[i]<='9' && c[i]>='0') // Si on est sur le chiffre d'un nombre, on ajoute à la valeur courante
                    {
                        if(flag==0)
                            flag=1;
                        z->m[ligne][col] = (z->m[ligne][col]*10) + (c[i]-'0');
                    }
                    else if(c[i]=='-') // Si on est sur un signe moins, on stocke l'information en mémoire
                    {
                        neg=1;
                    }
                    else // Si on est sur autre chose, on passe à la valeur suivante
                    {
                        if(flag)
                        {
                            if(neg) // Si la valeur doit être négative, on la multiplie par -1 pour qu'elle le soit effectivement
                            {
                                z->m[ligne][col]*=-1;
                                neg=0;
                            }
                            col++; // On change de colonne
                            ligne+=((unsigned int)col)/a; // Si on est en bout de ligne, on change de ligne
                            col%=a;
                            flag=0;
                        }
                    }
                }
            }
            fclose(f); // Une fois la lecture finie, on ferme le fichier
            free(c);
            printf("End scan\n\n");
        }
    }
}

/*!
 *	\fn int COM_change_extension(path, const char*)
 *	\brief Remplace l'extension du chemin d'accès passé en paramètre.
 *	\param src Chemin d'accès à modifier.
 *	\param ext Extension à mettre.
 *	\return Echec/Réussite du calcul.
*/
/*!
 *	\fn zone *COM_readMap(path)
 *	\brief Charge une carte en mémoire.
 *	\param path Chemin d'accès de la carte.
 *	\return Données de la carte.
*/