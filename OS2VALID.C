#define INCL_WIN
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include "des3.h"

MRESULT EXPENTRY ClientWndProc(HWND, ULONG, MPARAM, MPARAM);

CHAR szTitle[]  = "Certification of the DES Algorithm in OS2";
CHAR szClient[] = "OS2VALID";

/* size of standard DES block, in bits */
#define	BITSZ	(64)
/* size of standard DES block, in bytes */
#define	BLKSZ	(8)
/* how many standard DES blocks defined in ANSI X9.9 Appendix B */
#define	X99MX	(4)


int main(VOID)
{
  static ULONG flFrameFlags = FCF_AUTOICON | FCF_TASKLIST;

  HAB hab;
  HMQ hmq;
  HWND hwndFrame, hwndClient;
  QMSG qmsg;

  hab = WinInitialize(0);
  hmq = WinCreateMsgQueue(hab, 0);
                   
  WinRegisterClass(hab, szClient, ClientWndProc, CS_SIZEREDRAW, 0);
  
  hwndFrame = WinCreateStdWindow(HWND_DESKTOP, WS_VISIBLE, &flFrameFlags,
              (PSZ) szClient, NULL, 0L, NULLHANDLE, 0, &hwndClient);
  WinSendMsg(hwndFrame, WM_SETICON, (MPARAM)WinQuerySysPointer
             (HWND_DESKTOP, SPTR_APPICON, FALSE), NULL);
  while(WinGetMsg(hab, (PQMSG) &qmsg, (HWND)NULL, (ULONG) 0, (ULONG) 0)) 
    WinDispatchMsg(hab, &qmsg);
  WinDestroyWindow(hwndFrame);
  WinDestroyMsgQueue(hmq);
  WinTerminate(hab);
  return 0;
} 
  
MRESULT EXPENTRY ClientWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   INT i;
   /* for validation, keybits and patterns taken from ANSI X9.9 Appendix B */
   static UCHAR keybits[BLKSZ] = { 0xe6,0xa1,0x2f,0x07,0x9d,0x15,0xc4,0x37 };
   static UCHAR pattern[X99MX][BLKSZ] = {
       { 0x0a,0x20,0x20,0x20,0x54,0x4f,0x20,0x59 },
       { 0x51,0x44,0x2d,0x38,0x30,0x20,0x30,0x37 },
       { 0x54,0x4f,0x20,0x59,0x4f,0x55,0x52,0x20 },
       { 0x51,0x44,0x2d,0x38,0x30,0x20,0x30,0x37 }
   };
   static UCHAR results[X99MX][BLKSZ], clrtext[X99MX][BLKSZ], round[BITSZ], szBuf[512];
   switch(msg) {
     case WM_CREATE:
       desinit(keybits);
       for (i = 0; i < X99MX; i++) {
         ecbencode(pattern[i],results[i]);
         ecbdecode(results[i],clrtext[i]);
       }
       for (i = 0; i < X99MX; i++) {
         sprintf((CHAR *)round,"ECB %02x%02x%02x%02x%02x%02x%02x%02x -> %02x%02x%02x%02x%02x%02x%02x%02x \
-> %02x%02x%02x%02x%02x%02x%02x%02x\n",
         pattern[i][0], pattern[i][1], pattern[i][2], pattern[i][3],
      	 pattern[i][4], pattern[i][5], pattern[i][6], pattern[i][7],
      	 results[i][0], results[i][1], results[i][2], results[i][3],
      	 results[i][4], results[i][5], results[i][6], results[i][7],
      	 clrtext[i][0], clrtext[i][1], clrtext[i][2], clrtext[i][3],
      	 clrtext[i][4], clrtext[i][5], clrtext[i][6], clrtext[i][7]);
	 strcat((CHAR *)szBuf,(CHAR *) round);
       }
       WinMessageBox(HWND_DESKTOP,hwnd,(CHAR *)szBuf, szTitle, 0, MB_OK);
       WinPostMsg(hwnd, WM_QUIT, NULL, NULL);
       return 0;
   }
   return WinDefWindowProc(hwnd, msg, mp1, mp2);
}
       