#ifndef _MODULE_DES3_H_
#define _MODULE_DES3_H_
/*
 *             des3 - NBS Data Encryption Standard Library
 *
 *         Copyright (c) 1992 - 96 by SWS. All Rights Reserved.
 *       Stefan Wolf Software; Gartenstr 22; D-61449 Steinbach/Ts.
 *         FON/FAX: +49 (0) 6171 980483; BBS: +49 (0) 69 5075592
 *      Compu$erve: 100111,140; Internet: 100111.140@compuserve.com
 *
 *    Synopsis:	desinit(key)
 * Description: intializes all arrays and permutation tables for 
 *              single DES
 *       Input: key -  8 Byte DES key
 *      Output: 0 if OK; >0 if a (semi) weak was selected
 *
 *    Synopsis:	des3init(key)
 * Description: intializes all arrays and permutation tables for
 *              triple DES
 *       Input: key - 24 Byte DES key
 *      Output: 0 if OK; >0 if a (semi) weak was selected
 *
 *    Synopsis: ecbXcode(inblock,outblock)
 * Description: encrypts (X=en) or decrypts (X=de) 64-bit inblock to
 *              64-bit outblock using single DES in ECB mode
 *     	 Input: inblock  - pointer to 64-bit buffer of input data
 *              outblock - pointer to 64-bit buffer for output data
 *      Output: 0 if OK                                        
 *
 *    Synopsis: ecb3Xcode(inblock,outblock)
 * Description: encrypts (X=en) or decrypts (X=de) 64-bit inblock to
 *              64-bit outblock using triple DES (EDE) in ECB mode 
 *     	 Input: inblock  - pointer to 64-bit buffer of input data
 *              outblock - pointer to 64-bit buffer for output data
 *      Output: 0 if OK
 *
 *    Synopsis: cbcXcode(inblock,outblock,ivec)
 * Description: encrypts (X=en) or decrypts (X=de) 64-bit inblock to
 *              64-bit outblock using single DES in CBC mode
 *     	 Input: inblock  - pointer to 64-bit buffer of input data
 *              outblock - pointer to 64-bit buffer for output data
 *              ivec     - pointer to 64-bit initilization vector
 *      Output: 0 if OK
 *
 *    Synopsis: cbc3Xcode(inblock,outblock,ivec)
 * Description: encrypts (X=en) or decrypts (X=de) 64-bit inblock to
 *              64-bit outblock using triple DES (EDE) in CBC mode 
 *     	 Input: inblock  - pointer to 64-bit buffer of input data
 *              outblock - pointer to 64-bit buffer for output data
 *              ivec     - pointer to 64-bit initilization vector
 *      Output: 0 if OK
 *
 */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(WIN16) 
#define DECL int far pascal
#define UCHAR unsigned char far
#endif /* WIN16 */

#if defined(WIN32) || defined(OS2)
#define DECL int pascal
#define UCHAR unsigned char
#endif /* WIN32 */

#if !defined(WIN16) && !defined(WIN32) && !defined(OS2)
#define DECL int
#define UCHAR unsigned char
#endif /* !WIN16 && !WIN32 && !OS2 */

DECL desinit(UCHAR *key1);
DECL ecbencode(UCHAR *inblock, UCHAR *outblock);
DECL ecbdecode(UCHAR *inblock, UCHAR *outblock);
DECL cbcencode(UCHAR *inblock, UCHAR *outblock, UCHAR *ivec);
DECL cbcdecode(UCHAR *inblock, UCHAR *outblock, UCHAR *ivec);
DECL des3init(UCHAR *key3);
DECL ecb3encode(UCHAR *inblock, UCHAR *outblock);          
DECL ecb3decode(UCHAR *inblock, UCHAR *outblock);
DECL cbc3encode(UCHAR *inblock, UCHAR *outblock, UCHAR *ivec);
DECL cbc3decode(UCHAR *inblock, UCHAR *outblock, UCHAR *ivec);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _MODULE_DES3_H_ */
 