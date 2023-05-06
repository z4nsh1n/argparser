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
  createFlag(Option, "verbose", "v");
  createFlag(String, "file", "f");
  createFlag(Int, "integer", "i");
  createFlag(Float, "nfloat", "n");

  if (parseFlags(argc, argv)){
      int verbose = flagGetOption("v");
      int verbose2 = flagGetOption("q");
      char *file = flagGetString("f");
      int integer = flagGetInt("i");
      float fl = flagGetFloat("n");

      printf("flag -v contains: %d\n", verbose);
      printf("flag -q contains: %d\n", verbose2);
      printf("flag -f contains: %s\n", file);
      printf("flag -i contains: %d\n", integer);
      printf("flag -n contains: %f\n", fl);
  }
  return EXIT_SUCCESS;
}
