#ifndef FLAGS_H
#define FLAGS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct Flags
{
  // https://www.tutorialspoint.com/cprogramming/c_structures.htm
  // Bit Fields
  char **envip;
  char *dir;
  unsigned int all : 1;  // -a OR --all
  unsigned int bytes : 1; // -b OR --bytes
  unsigned int blockSize : 1; // -B OR --block-size=SIZE
  unsigned short blockSizeValue : 16; // 16 bits tamanho maximo em bytes
  unsigned int countLinks : 1;  // -l OR --count-links
  unsigned int dereference : 1; // -L OR --dereference 
  unsigned int separateDirs : 1; // -S OR --separate-dirs
  unsigned int maxDepth : 1; // --max-depth=N   N=0 só lê dir atual, n=1 lê 1 subdir
  int maxDepthValue;
}flags;

void initFlags(flags *flags, char *envp[]);

int setFlags(flags *flags, int argc, char const *argv[]);

// http://www.cplusplus.com/reference/cstring/strstr/
// http://www.cplusplus.com/reference/cstring/strcmp/
// Returns 0 if okay, 1 otherwise
int fillFlagsStruct(flags *flags, int argc, char const *argv[]);

void printFlags(flags *flags);

#endif /*FLAGS_H*/
