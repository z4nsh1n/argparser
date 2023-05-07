#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argparse.h"

int main(int argc, char *argv[]) {

  // No flags always true
  assert(parseFlags(argc, argv) == 0);

  // check for invalid flag
  //createFlag(Option, "invalid", 'i');
  //assert(parseFlags(argc, argv) == 0);
  //
  //longnames can be start with a different letter
  createFlag(Option, "clear", "v");
  createFlag(String, "aname", "f");
  createFlag(Int, "zenumber", "i");
  createFlag(Float, "thefloat", "n");

  if (parseFlags(argc, argv)){
      //int verbose = flagGetOption("v");
      //int verbose2 = flagGetOption("q");
      //char *file = flagGetString("f");
      //int integer = flagGetInt("i");
      //float fl = flagGetFloat("n");

      int verbose = flagGetOption("clear");
      int verbose2 = flagGetOption("saldk");
      char *file = flagGetString("aname");
      int integer = flagGetInt("zenumber");
      float fl = flagGetFloat("thefloat");

      printf("flag -v (clear) contains: %d\n", verbose);
      printf("flag -q (should be false) contains: %d\n", verbose2);
      printf("flag -f (aname) contains: %s\n", file);
      printf("flag -i (zenumber) contains: %d\n", integer);
      printf("flag -n (thefloat) contains: %f\n", fl);
  }
  return EXIT_SUCCESS;
}
