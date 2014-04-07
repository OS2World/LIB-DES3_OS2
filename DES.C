/*
 * this sample source will give you an idea on how to
 * call up the various library functions. -SW
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "des3.h"

#define BUFSIZE 16384

static char Usage[] = "des [-]{d|e}[3] infile outfile key";

int main(int argc, char **argv)
{
  register unsigned char *b, *buf, c;
  static unsigned char key[8], key3[24];
  register int i, what, mode, bytes;
  static int last = 0;
  register time_t t, t1;
  FILE *ih, *oh;
  if(argc == 5) {
    switch (c = *argv[1] == '-' ? *++argv[1] : *argv[1]) {
      case 'e': case 'E': what = 0; break;
      case 'd': case 'D': what = 1; break;
      default : fprintf(stderr,"des : illegal option %c \n",c);
   	   	fprintf(stderr,"Usage : %s \n",Usage);
   	   	return 1;
    }
    switch(*++argv[1]) {
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
  ih =  fopen(argv[2],"rb");
  oh = fopen(argv[3],"wb");
  if (ih == NULL || oh == NULL) {
    perror(ih ? argv[3]:argv[2]);
    return 1;
  }
  if (mode == 1) {
    memset(key,0,8);
    bytes = strlen(argv[4]);
    memcpy(key,argv[4],bytes > 7 ? 8:bytes);
    desinit(key);
  } else {
    memset(key3,0,24);
    bytes = strlen(argv[4]);
    memcpy(key3,argv[4],bytes > 23 ? 24:bytes);
    des3init(key3);
  }
  t = time(NULL);
  while ((i = fread(buf,1,BUFSIZE,ih)) != 0) {
    for (b=buf, bytes=i; i > 0; i -= 8 , b += 8) {
      if (!what) {
        if (i < 8) {
          bytes += 8-i;
          last = i;
        }
        if (mode == 1) ecbencode(b,b); else ecb3encode(b,b);
      } else {
        if (i > 7) {
          if (mode == 1) ecbdecode(b,b); else ecb3decode(b,b);
        } else bytes -= (9 - (b[0] & 0xff));
      }
    }
    if (!what) {
      if (fwrite(buf, 1, bytes, oh) != (size_t) bytes) {
        fprintf(stderr,"Error in write !\n");
        return 1;
      }
    } else {
      if (fwrite(buf, 1, bytes, oh) != (size_t) bytes) {
        fprintf(stderr,"Error in write !\n");
        return 1;
      }
    }
  }
  if (!what) fputc(last ? last : last + 8,oh);
  t1 = time(NULL) - t;
  printf("%scrypted bytes per second using %s DES: %ld\n", what ? "De":"En",
          mode == 1 ? "single" : "triple" , ftell(ih)/(t1 ? t1 : 1));
  fclose(ih);
  fclose(oh);
  return 0;
}
