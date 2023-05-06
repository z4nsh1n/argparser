#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  String,
  Int,
  //Float,
  Option,
} FlagType;

typedef union Value{
   int bool;
   float f;
   int i;
   char *str;
} Value; 

typedef struct {
  char *lname;
  char *sname;
  char *start;
  char *end;
  FlagType type;
  Value value;

} Flag;

Flag initFlag(FlagType t, char *lstr, char *sstr) {
  Flag f = {0};
  f.type = t;
  f.lname = lstr;
  f.sname = sstr;

  return f;
}
// 255 flags on the command line is good for now
Flag flags[255];
int totalFlags = 0;

// user space
void createFlag(FlagType t, char *lstr, char *sstr) {
  flags[totalFlags] = initFlag(t, lstr, sstr);
  totalFlags++;
}

char *flagGetString(char *c){
    for (int f=0; f<totalFlags; f++) {
        if (*c == *flags[f].sname && flags[f].type == String) {
            return flags[f].value.str;
        }
    }
    return NULL;
}

int flagGetOption(char *c) {
    for (int f=0; f<totalFlags; f++) {
        if (strcmp(c,flags[f].sname) && flags[f].type == Option) {
            return flags[f].value.bool;
        }
    }
    return 0;
}

int parseFlags(int argc, char **argv) {
  // Skip progname TODO: save it somewhere
  int ret = 1;
  argc--;
  argv++;
  // No flags
  if (totalFlags == 0) {
      return 0;
  }

  for (int f = 0; f < argc; f++) {
      char *c = argv[f];
      if (*"-" == *c){  //strcmp(c, "-")) {
          c++;
          for (int i=0; i<totalFlags; i++) {
              if (*(flags[i].sname) == *c && flags[i].type == Option) {
                flags[i].value.bool = 1;
              }
              if (*(flags[i].sname) == *c && flags[i].type == String){
                f++;
                char *k = strdup(argv[f]);
                flags[i].value.str = strdup(argv[f]);
              } 
            
          }
      }
  }

  return ret;
}
int main(int argc, char *argv[]) {
  char **p = argv;
  char *a;

  // No flags always true
  //assert(parseFlags(argc, argv) == 1);

  // check for invalid flag
  //createFlag(Option, "invalid", 'i');
  //assert(parseFlags(argc, argv) == 0);
  createFlag(Option, "verbose", "v");
  createFlag(String, "file", "f");

  if (parseFlags(argc, argv)){
      int verbose = flagGetOption("v");
      int verbose2 = flagGetOption("q");
      char *file = flagGetString("f");

      printf("flag contains: %d\n", verbose);
      printf("flag contains: %d\n", verbose2);
      printf("flag contains: %s\n", file);
  }
  return EXIT_SUCCESS;
}
