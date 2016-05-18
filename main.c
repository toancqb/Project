#include <limits.h>
#include <stdio.h>
#ifdef __WIN32__ // Gestion de realpath sous windows
#define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
#endif
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

#include "struct.h"
#include "Files/fileManager.h"
#include "algorythms.h"

int main(int argc, char **argv)
{
  if(argc>1)
  {
    //map *m=calloc(1, sizeof(map));
    //strcpy(m.src, argv[1]);
    //m.z=NULL;
    //COM_readFile_ASC(argv[1], m, 0, 0, 99999, 99999);
    float wl;
    int mode;

    if(argc>3)  		//mode = 1 : calc_area
      mode=atoi(argv[3]);	//mode = 2 : calc_area_marée
    else			//mode != 1 && !=2 : calc_basic
    {
      printf("No mode as parameter, defaults to 0");
      mode=0;
    }

    if(argc>2)
      wl=atof(argv[2]);
    else
    {
      printf("No waterlevel as parameter, defaults to 2");
      wl=2;
    }
    
    map *m=Calc_Map(argv[1], wl, NULL, mode, NULL);

    if(m!=NULL)
    {
      m->WATERLEVEL=-5000;
      Write_File_Bin("Test.fbd", m->z, m->w, m->h);
      system("./interface_graphique");
    }
    else
      printf("The calculation was alright, right ?");
  }
  else
    printf("Need a map as argument\n");
  return 0;
}

