/* 
 * TESTCBC.C - validates the DES in Cipher Block Chaining (CBC) mode     
 *
 *  In Cipher Block Chaining (CBC) mode the first plain text data block
 * is XORed with a block of pseudo-random data prior to being processed
 * through the DES. The resulting cipher text block is then XORed with
 * the next plain text data block to form the next input block to the 
 * DES, thus chaining together blocks of ciphertext.
 * The CBC mode produces the same cipher text whenever the same plain 
 * text encrypted using the same key and IV.
 */

#include <stdio.h>
#include <string.h>
#include "des3.h"

/* for validation keybits and patterns taken from FIPS PUB 81 Appendix C */
/* initialization vector = 1234567890abcdef */
static unsigned char ivec[8]   = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef };
/* cryptographic key = 0123456789abcdef */
static unsigned char key[8]    = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
/* plain text: "Now is the time for all ." */
static unsigned char plain[3][8] = {
   { 0x4e, 0x6f, 0x77, 0x20, 0x69, 0x73, 0x20, 0x74, },
   { 0x68, 0x65, 0x20, 0x74, 0x69, 0x6d, 0x65, 0x20, },
   { 0x66, 0x6f, 0x72, 0x20, 0x61, 0x6c, 0x6c, 0x20, },
};

int main(void)
{
  unsigned char results[3][8], clrtext[3][8], iv[8];
  int i;
  desinit(key);
  memcpy(iv,ivec,8);
  for (i = 0; i < 3; i++) {
    cbcencode(plain[i],results[i],iv);
    memcpy(iv,results[i],8);
  }
  for (i = 0; i < 3; i++)
  printf("CBC encrypt: %02x%02x%02x%02x%02x%02x%02x%02x -> %02x%02x%02x%02x%02x%02x%02x%02x \n",
    plain[i][0], plain[i][1], plain[i][2], plain[i][3], plain[i][4], plain[i][5],
    plain[i][6], plain[i][7], results[i][0], results[i][1], results[i][2],
    results[i][3], results[i][4], results[i][5], results[i][6], results[i][7]);
  memcpy(iv,ivec,8);
  for (i = 0; i < 3; i++) {
    cbcdecode(results[i],clrtext[i],iv);
    memcpy(iv,results[i],8);
  }
  for (i = 0; i < 3; i++)
  printf("CBC decrypt: %02x%02x%02x%02x%02x%02x%02x%02x -> %02x%02x%02x%02x%02x%02x%02x%02x \n",
    results[i][0], results[i][1], results[i][2], results[i][3], results[i][4], results[i][5], 
    results[i][6], results[i][7], clrtext[i][0], clrtext[i][1], clrtext[i][2], clrtext[i][3], 
    clrtext[i][4], clrtext[i][5], clrtext[i][6], clrtext[i][7]);
  return 0;
}
