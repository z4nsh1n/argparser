
#ifndef __ARGPARSE_h
#define __ARGPARSE_H

typedef enum {
  String,
  Int,
  Float,
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


Flag initFlag(FlagType t, char *lstr, char *sstr);
void createFlag(FlagType t, char *lstr, char *sstr);
char *flagGetString(char *c);
int flagGetInt(char *c);
float flagGetFloat(char *c);
int flagGetOption(char *c);
int parseFlags(int argc, char **argv);

#endif
