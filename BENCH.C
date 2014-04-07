/*
 * this sample source will give you several benchmark results. -SW
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "des3.h"

#define BUFSIZE 4096
#define ROUNDS  4096

static char Usage[] = "bench [-]{d|e}[1|3]";

int main(int argc, char **argv)
{
  register unsigned char *b, *buf, c;
  register int i, j ,mode, what;
  register time_t t, t1;

  if(argc == 2) {
    switch (c = *argv[1] == '-' ? *++argv[1] : *argv[1]) {
      case 'e': case 'E': what = 0; break;
      case 'd': case 'D': what = 1; break;
      default : fprintf(stderr,"bench : illegal option %c \n",c);
   	   	fprintf(stderr,"Usage : %s \n",Usage);
   	   	return 1;
    }
    switch(*++argv[1]) {
      case '1': mode = 1; break;
      case '3': mode = 3; break;
      default : mode = 1;
    }
  } else {
    fprintf(stderr,"Usage : %s \n",Usage);
    return 1;
  }
  if ((buf = (unsigned char *) malloc(BUFSIZE)) == NULL) {
    fprintf(stderr,"Error: Cannot alloc memory !\n");
    return 1;
  }
  if (mode == 1) {    /* single DES */
    if (what == 0) {   /* encrypt */
      t = time(NULL);
      for (j = 0; j < ROUNDS; j++)
      for (b=buf, i = BUFSIZE; i > 0; i -=8 , b += 8) ecbencode(b,b);
      t1 = time(NULL) - t;
      printf("%ld seconds for encrypting 16 MB of memory using single DES\n", t1);
      return 0;
    } else {   /* decrypt */
      t = time(NULL);
      for (j = 0; j < ROUNDS; j++)
      for (b=buf, i = BUFSIZE; i > 0; i -=8 , b += 8) ecbdecode(b,b);
      t1 = time(NULL) - t;
      printf("%ld seconds for decrypting 16 MB of memory using single DES\n", t1);
      return 0;
    }
  } else {  /* triple DES */
    if (what == 0) {   /* encrypt */
      t = time(NULL);
      for (j = 0; j < ROUNDS; j++)
      for (b=buf, i = BUFSIZE; i > 0; i -=8 , b += 8) ecb3encode(b,b);
      t1 = time(NULL) - t;
      printf("%ld seconds for encrypting 16 MB of memory using triple DES\n", t1);
      return 0;
    } else {   /* decrypt */
      t = time(NULL);
      for (j = 0; j < ROUNDS; j++)
      for (b=buf, i = BUFSIZE; i > 0; i -=8 , b += 8) ecb3decode(b,b);
      t1 = time(NULL) - t;
      printf("%ld seconds for decrypting 16 MB of memory using triple DES\n", t1);
      return 0;
    }
  }
}
