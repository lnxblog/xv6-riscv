#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char **argv)
{
  if(argc != 2)
  {
    printf("Error: Requires one argument\n");
    exit(1);
  }
    int secs = (int)argv[1][0]-'0';
  if(sleep(secs)!=0)
  return 1;



  return 0;


}