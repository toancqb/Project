#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef __WIN32__
  #include <windows.h>
#endif

#include "struct.h"
#include "Files/fileManager.h"
#include "algorythms.h"

cell *List_BuildCell(int x, int y)
{
  cell *c=malloc(sizeof(cell));
  if(c!=NULL) // Si l'allocation a réussi
  {
    c->x=x;
    c->y=y;
    c->n=NULL;
  }
  return c;
}

list *List_Init(list *l)
{
  printf("List init\n");
  if(l==NULL)
    l=malloc(sizeof(list));
  if(l!=NULL) // Si l'allocation a réussi
    l->f=NULL;
  return l;
}

void List_Add(list *l, cell *c)
{
  if(l!=NULL && c!=NULL)
  {
    c->n=l->f;
    l->f=c;
  }
  else{
    printf("Can't add cell\n");
    exit(-3);
  }
}

int List_Pop(list *l, int *x, int *y)
{
  if(l!=NULL && x!=NULL && y!=NULL)
  {
    cell *c=l->f;
    if(c!=NULL)
    {
      *x=c->x;
      *y=c->y;
      l->f=c->n;
      free(c);
      return 1;
    }
  }
  printf("Couldn't load\n");
  return 0;
}

void print_Area(map m)
{
  int i, j;
  for(i=0; i<m.z->h; i++)
  {
    for(j=0; j<m.z->w; j++)
    {
      printf("%d ", m.z->m[i][j]);
    }
    printf("\n");
  }
}

int _Calc_Area(map m, unsigned int wl, list *l)
{
  printf("Start Area\n");
  zone *z = m.z;

  if(wl>0 && z!=NULL && l!=NULL)
  {
    m.WATERLEVEL-=(m.WATERLEVEL-wl!=m.NODATA)?wl:wl+1;
      
    int i, j, x2, y2;
    int **t=z->m;
    int x=-2, y=-2;
    bool mask[z->h][z->w];
    for(i=0; i<z->h; i++)
      for(j=0; j<z->w; j++)
        mask[i][j]=false;
    while(List_Pop(l, &x, &y)) // On récupère un point considéré comme étant submergé
    {
      // Vérification des points adjacents
      for(i=0; i<4; i++)  // Test dans les 4 directions (droite-gauche-bas-haut)
      {
        x2=x+(i==0)-(i==1);
        y2=y+(i==2)-(i==3);
        if(x2<z->w && x2>0 && y2<z->h && y2>0)
          if(!mask[x2][y2] && t[x2][y2]>m.WATERLEVEL && t[x2][y2]<=wl && t[x2][y2]!=m.NODATA) // Le point au-dessus est submergé
          {
            mask[x2][y2]=true;
            List_Add(l, List_BuildCell(x2, y2));
            t[x2][y2] = (t[x2][y2]!=0)?m.WATERLEVEL:0;
          }
      }
    }
    printf("End Area\n");
//    printf("w=%i\th=%i\n", z->w, z->h);
      // Tout ce qui est avant le return devra sauter
    for(i=0; i<z->h; i++)
      for(j=0; j<z->w; j++)
        if(t[i][j]>0)
          t[i][j]=(t[i][j]<wl)?1:t[i][j]-wl;
//    printf("C'est fini");
    printf("\n[%d:%d]\n", m.w, m.h);
    return 0;
  }
  return -1;
}

int _Calc_Area_Basic(map m, unsigned int wl)
{
  if(m.z!=NULL && wl>0)
  {
    int i, j;
    m.WATERLEVEL=-1;
    for(i=0; i<m.z->h; i++)
    {
      for(j=0; j<m.z->w; j++)
      {
        if(m.z->m[i][j]!=m.NODATA && m.z->m[i][j]!=0)
        {
          m.z->m[i][j]=(m.z->m[i][j])<=wl?m.WATERLEVEL:m.z->m[i][j]-wl;
        }
      }
    }
  }
  return 0;
}

map *Calc_Map(char *src, int wl, list* l, int mode, map *m)
{
  printf("Start Calc\n");
  if(src!=NULL)
  {
    if(m==NULL)
      m=calloc(1, sizeof(map));
    if(m!=NULL)
    {
      _COM_readFile_ASC(src, m, 0, 0, 99999, 99999);
      if(l==NULL)
      {
        l=List_Init(NULL);
        List_Add(l, List_BuildCell(50, 50)); // Cellule par défaut pour les tests, à supprimer
      }
      switch(mode)
      {
        case 1:
          _Calc_Area(*m, wl, l);
          break;
        default:
          _Calc_Area_Basic(*m, wl);
          break;
      }
    }
    return m;
  }
  else
    printf("No proper src file received\n");
  printf("End Calc\n");
  return NULL;
}
