#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argparse.h"

//TODO: flagGet* functions don't use strcmp which could be #$%^#@@
//
Flag flags[255];
int totalFlags = 0;

Flag initFlag(FlagType t, char *lstr, char *sstr) {
  Flag f = {0};
  f.type = t;
  f.lname = lstr;
  f.sname = sstr;

  return f;
}
// 255 flags on the command line is good for now

// user space
void createFlag(FlagType t, char *lstr, char *sstr) {
  flags[totalFlags] = initFlag(t, lstr, sstr);
  totalFlags++;
}

// TODO: return options as pointer so failing can be NULL???
char *flagGetString(char *c) {
  for (int f = 0; f < totalFlags; f++) {
    if (strcmp(flags[f].lname, c) == 0 || *c == *flags[f].sname && flags[f].type == String) {
      return flags[f].value.str;
    }
  }
  return NULL;
}
int flagGetInt(char *c) {
  for (int f = 0; f < totalFlags; f++) {
    if (strcmp(flags[f].lname, c) == 0 || *c == *flags[f].sname && flags[f].type == Int) {
      return flags[f].value.i;
    }
  }
  return 0;
}
float flagGetFloat(char *c) {
  // TODO: What error value to return ???
  for (int f = 0; f < totalFlags; f++) {
    if (strcmp(flags[f].lname, c) == 0 || *c == *flags[f].sname && flags[f].type == Float) {
      return flags[f].value.f;
    }
  }
  return 0;
}

int flagGetOption(char *c) {
  for (int f = 0; f < totalFlags; f++) {
    if (strcmp(c, flags[f].lname) == 0 || *c == *flags[f].sname && flags[f].type == Option) {
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
    if (strncmp("--",c,2) == 0) {
      c += 2;
      for (int i = 0; i < totalFlags; i++) {
        //printf("comp: %d %s %s\n", strcmp(flags[i].lname,c), c, flags[i].lname);
        if (strcmp(flags[i].lname, c) == 0 && flags[i].type == Option) {
          flags[i].value.bool = 1;
        }
        if (strcmp(flags[i].lname,c) == 0 && flags[i].type == String) {
          ++f;
          flags[i].value.str = strdup(argv[f]);
        }
        if (strcmp(flags[i].lname,c) == 0 && flags[i].type == Int) {
          ++f;
          sscanf(argv[f], "%d", &(flags[i].value.i));
        }
        if (strcmp(flags[i].lname, c) == 0 && flags[i].type == Float) {
          ++f;
          sscanf(argv[f], "%f", &(flags[i].value.f));
        }
      }
    } else if (*"-" == *c) {
      //char *c = argv[f];
      c++;
      for (int i = 0; i < totalFlags; i++) {
        if (*(flags[i].sname) == *c && flags[i].type == Option) {
          flags[i].value.bool = 1;
        }
        if (*(flags[i].sname) == *c && flags[i].type == String) {
          f++;
          flags[i].value.str = strdup(argv[f]);
        }
        if (*(flags[i].sname) == *c && flags[i].type == Int) {
          f++;
          sscanf(argv[f], "%d", &(flags[i].value.i));
        }
        if (*(flags[i].sname) == *c && flags[i].type == Float) {
          f++;
          sscanf(argv[f], "%f", &(flags[i].value.f));
        }
      }
    } else {
      printf("Flag (%s) not found!!!!\n", c);
    }
  }
return ret;
}
