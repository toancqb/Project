#ifndef STRUCTURES_DEPEND
#define STRUCTURES_DEPEND

#define FILETYPE_ASC 0b01
#define FILETYPE_XYZ 0b10
/*  // Input files
char *FILE_INPUT[]={"asc", "asf"}; // IGN format
int FILE_INPUTN=2;
  // Output files
char *FILE_OUTPUT[]={"fmd", "rmd", "rfmd"}; // Resized Formatted Map Data
int FILE_OUTPUTN=3;
  // Intermediate format
char *FILE_TEMP="ut"; // Undergoing treatment
int FILE_TEMPN=1;
*/
#define COM_WATERLEVEL -5000

typedef char path[260];

typedef struct zone
{
  unsigned int x, y;
  unsigned int w, h;
  int **m;
} zone;

typedef struct map
{
  unsigned int pas;
  zone *z;
  int w, h;
  int NODATA, WATERLEVEL;
  path src, dst;
} map;



#endif

