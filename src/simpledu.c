#include "simpledu.h"

int main(int argc, char const *argv[], char *envp[])
{
  flags duflags; initRegister(); initFlags(&duflags, envp);
  regCommand(argc,argv);

  if (setFlags(&duflags, argc, argv))
    regExit(1);

  //printFlags(&duflags);

  boole = 0;
  if(listThings(duflags.dir,0, &duflags)<0){
    printf("Error listing\n");
    regExit(1);
  }

  regExit(0);
}
