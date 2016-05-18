#ifndef ALGORYTHMS_INCLUDED
#define ALGORYTHMS_INCLUDED


typedef struct cell
{
  int x, y;
  struct cell *n;
}cell;

typedef struct list{cell *f;}list;

map *Calc_Map(char*, int wl, list*, int mode, map*);

#endif