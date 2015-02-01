/* Serial line terminal program
 * characters can be displayed as in hex, decimal and ascii 
 * characters can be seperated by space, tab, newline or 'nothing'
 * local echo can be switched on or off
 *

 * by Albrecht Schmidt, Lancaster University - Oct 2001
 * http://www.comp.lancs.ac.uk/~albrecht 
 * Albrecht@comp.lancs.ac.uk
 * based on an example from Robert Mashlan - 
 *                    see http://r2m.com/~rmashlan/
 */

//#include "stdafx.h"
#define STRICT
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global vars - to aviod parameter passing over thread
// I am lazy I know ...
char exename[1024];
char logname[1024];
int DisplayMode, separator, echo, log;



void help() {
  printf("%s port [speed] [DisplayMode] [Separator] [Echo] [logfilename]\n", exename);
  printf("        port ::= com1 | com2 | com3 | com4 | com5 | com6\n");
  printf("        speed::= 300 | 4800 | 9600 | 19200 | 38400 | 57600 | 115200 | 230400\n");
  printf("                                     ^^^^^\n");
  printf("        DisplayMode::= ascii | hex | decimal\n");
  printf("                       ^^^^^\n");
  printf("        Separator::= empty | space | newline | tab\n");
  printf("                     ^^^^^\n");
  printf("        Echo::= no | yes\n");
  printf("                ^^\n");
  printf("        logfilename::= <anyname> (if not provided no log is written)\n\n");
  printf("Example: %s com1 115200 hex space no log.txt\n", exename);
  printf("    open the terminal on port com1 with 115200 bit/s, print hex code of\n"); 
  printf("    incoming characters, seperate them by space, no local echo, log to log.txt\n");
  printf("Example: %s com2 19200 decimal tab yes\n", exename);
  printf("    open the terminal on port com2 with 19200 bit/s, print decimal code\n"); 
  printf("    of incoming characters, seperate them by tabs, do local echo, no logfile\n");
}


void PrintError( LPCSTR str)
{
   LPVOID lpMessageBuffer;
   int error = GetLastError();
   FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
      (LPTSTR) &lpMessageBuffer,
      0,
      NULL
   );
   printf("%s: (%d) %s\n\n",str,error,lpMessageBuffer);
   help();
   LocalFree( lpMessageBuffer );
}


DWORD CALLBACK ConInThread( HANDLE h )
{
   // starts a user input thread using the console
   //
   // takes console characters and sends them to the com port


   OVERLAPPED ov;
   HANDLE hconn = GetStdHandle(STD_INPUT_HANDLE);
   BOOL quit = FALSE;

   ZeroMemory(&ov,sizeof(ov));
   ov.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
   if(ov.hEvent == INVALID_HANDLE_VALUE) {
      PrintError("E001_CreateEvent failed");
      SetCommMask(h,0);
      return 0;
   }

   char kb;
   INPUT_RECORD b1;

   SetConsoleMode(hconn,0);
   printf("press Esc or Ctrl+C to terminate\n");
    
   do {
      char buf[10];
	  DWORD read = 0;

      SetConsoleMode(hconn,0);
   
      // wait for user to type something
      WaitForSingleObject(hconn,INFINITE);

      // read the console buffer
	  if(!ReadConsoleInput(hconn,&b1,1,&read)) {
         PrintError("E002_ReadConsoleInput failed...");
         quit  = TRUE;
      }
	  
	  kb=b1.Event.KeyEvent.uChar.AsciiChar;
	  //printf("read=%i, b1.keyevent: 0x%x ", read, kb);
      buf[0] = kb;
	  
      
	  if(read) {
         DWORD write=1;
         // check for Esc
		 // for debug purpose to find out the key value ...
		 // printf("Val 0x%x\n", kb);
			 
		 // terminate when Esc pressed
         if( buf[0] == 0x1b ||       // ESC
				// buf[0] == 0x11 ||       // Ctrl + Q
				// buf[0] == 0x18 ||       // Ctrl + X
				buf[0] == 0x3 ) {      // Ctrl + C
               quit = TRUE;
		       break;
         } else {
				 if (buf[0] != 0x0  && b1.Event.KeyEvent.bKeyDown) {
					// send it to the com port
					if( !WriteFile(h,buf,write,&write,&ov) ) {
						if(GetLastError() == ERROR_IO_PENDING) {
							if( !GetOverlappedResult(h,&ov,&write,TRUE) ) {
								PrintError("E003_GetOverlappedResult failed");
								quit = TRUE;
							}
						}
						// make the local output - echo is global var ...
						if (echo == 1) printf("%c", (unsigned char)buf[0]);
					} else {
						PrintError("E004_WriteFile failed");
						quit = TRUE;
					}
				} 
         }
      }

   } while(!quit);

   // tell terminal thread to quit
   if (!SetCommMask(h,0)) {
	   printf("SetCommMask-GetLastError: %i\n", GetLastError());
   }
   return 0;
}


void Terminal( HANDLE h )
{
   HANDLE hconn = GetStdHandle(STD_OUTPUT_HANDLE);
   DWORD mask;
   DWORD id, i;
   OVERLAPPED ov;


   FILE *stream;
   if (log ==1) {
		stream = fopen( logname, "w" );
   }
   

   HANDLE hconin = CreateThread(NULL,0,ConInThread,h,0,&id);
   if( hconin == INVALID_HANDLE_VALUE ) {
      PrintError("E005_CreateThread failed");
      return;
   }
   CloseHandle(hconin);  // don't need this handle

   ZeroMemory(&ov,sizeof(ov));

   // create event for overlapped I/O
   ov.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
   if(ov.hEvent == INVALID_HANDLE_VALUE)
      PrintError("E006_CreateEvent failed");

   // wait for received characters
   if(!SetCommMask(h,EV_RXCHAR))
      PrintError("E007_SetCommMask failed");

   while( 1 ) {
      // get the event mask
      if( !WaitCommEvent(h,&mask,&ov) ) {
         DWORD e = GetLastError();
         if( e == ERROR_IO_PENDING ) {
            DWORD r;
            if( !GetOverlappedResult(h,&ov,&r,TRUE) ) {
               PrintError("E008_GetOverlappedResult failed");
               break;
            }
         } else {
            PrintError("E009_WaitCommEvent failed");
            break;
         }
      }

      // if no event, then UI thread terminated with SetCommMask(h,0)
      if( mask == 0 ) {
         break;
      }

      if( mask & EV_RXCHAR) {
         char buf[10];
         DWORD read;
         do {
            read = 0;
            if( !ReadFile(h,buf,sizeof(buf),&read,&ov) ) {
               if( GetLastError() == ERROR_IO_PENDING ) {
                  if( !GetOverlappedResult(h,&ov,&read,TRUE) ) {
                     PrintError("E010_GetOverlappedResult failed");
                     break;
                  }
               } else {
                  PrintError("E011_ReadFile failed");
                  break;
               }
            }
            if(read)
		 	  // WriteFile(hconn,buf,read,&read,NULL);
			  for (i=0; i<read; i++) {
				  if (DisplayMode==0) printf("0x%x", (unsigned char)buf[i]);
				  if (DisplayMode==1) printf("%c", (unsigned char)buf[i]);
				  if (DisplayMode==2) printf("%i", (unsigned char)buf[i]);
				  if (separator==0) printf(" ");
				  if (separator==1) printf("\n");
				  if (separator==2) printf("\t");
				  // separator==3 - do nothing!

				  if (log ==1) {
		  			  // print to the logfile
					  if (DisplayMode==0) fprintf(stream,"0x%x", (unsigned char)buf[i]);
					  if (DisplayMode==1) fprintf(stream,"%c", (unsigned char)buf[i]);
					  if (DisplayMode==2) fprintf(stream,"%i", (unsigned char)buf[i]);
					  if (separator==0) fprintf(stream," ");
					  if (separator==1) fprintf(stream,"\n");
					  if (separator==2) fprintf(stream,"\t");
					  // separator==3 - do nothing!
				  }
			  }
		 } while(read);
      }
      mask = 0;
   }
   CloseHandle(ov.hEvent);  // close the event
   if (log ==1) {
	 fclose( stream );
   }
  
  
 }

void wait4keypressed()
{
	  HANDLE hStdin; 
	  DWORD cNumRead, fdwMode, fdwSaveOldMode, i, quit; 
      INPUT_RECORD irInBuf[128]; 
 
      // Get the standard input handle. 
 
      hStdin = GetStdHandle(STD_INPUT_HANDLE); 
      if (hStdin == INVALID_HANDLE_VALUE) 
        printf("Problem:GetStdHandle"); 
 
      // Save the current input mode, to be restored on exit. 
      if (! GetConsoleMode(hStdin, &fdwSaveOldMode) ) 
        printf("Problem:GetConsoleMode"); 
 
       //Enable the window and mouse input events. 
 
      fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
      if (! SetConsoleMode(hStdin, fdwMode) ) 
        printf("Problem:SetConsoleMode"); 
 
      // Loop to read and handle the input events. 
	  quit = 1;

      while (quit) 
	  { 
        // Wait for the events. 
        if (! ReadConsoleInput( 
                hStdin,      // input buffer handle 
                irInBuf,     // buffer to read into 
                128,         // size of read buffer 
                &cNumRead) ) // number of records read 
            printf("\nProblem:ReadConsoleInput\n"); 
 
        // check if key pressed ...
        for (i = 0; i < cNumRead; i++) 
        {
			if (irInBuf[i].EventType == KEY_EVENT) quit=0;
        }
	  } 

	  // rest the console mode
	  SetConsoleMode(hStdin, fdwSaveOldMode);
}



int main( int argc, char **argv )
{

   // copy the name of the executable into a global variable
   strcpy(exename,argv[0]);

   if(argc>1) {
      // open port for overlapped I/O
      HANDLE h = CreateFile(argv[1],
                    GENERIC_READ|GENERIC_WRITE,
                    0,NULL,
                    OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

      if(h == INVALID_HANDLE_VALUE) {
         PrintError("E012_Failed to open port");
      } else {
         // set timeouts
         COMMTIMEOUTS cto = { 2, 1, 1, 0, 0 };
         DCB dcb;
         if(!SetCommTimeouts(h,&cto))
            PrintError("E013_SetCommTimeouts failed");

         // set DCB
         memset(&dcb,0,sizeof(dcb));
         dcb.DCBlength = sizeof(dcb);
         dcb.BaudRate = 19200;
         if(argc>2 && atoi(argv[2]) )
            dcb.BaudRate = atoi(argv[2]);
         DisplayMode = 1;
		 if(argc>3) {
			if (argv[3][0] == 'h') DisplayMode = 0;
			if (argv[3][0] == 'a') DisplayMode = 1;
			if (argv[3][0] == 'd') DisplayMode = 2;
		 }
         separator = 3;
		 if(argc>4) {
			if (argv[4][0] == 's') separator = 0;
			if (argv[4][0] == 'n') separator = 1;		 
			if (argv[4][0] == 't') separator = 2;		 
			if (argv[4][0] == 'e') separator = 3;		 
		 }
         echo = 0;
		 if(argc>5) {
			if (argv[5][0] == 'n') echo = 0;
			if (argv[5][0] == 'y') echo = 1;
		 }
		log = 0;
		 if(argc>6) {
			log =1;
			strcpy(logname, argv[6]);
		 }


         dcb.fBinary = 1;
		 dcb.fDtrControl = DTR_CONTROL_ENABLE;
		 dcb.fRtsControl = RTS_CONTROL_ENABLE;
		 // dcb.fOutxCtsFlow = 1;
  		 // dcb.fRtsControl = DTR_CONTROL_HANDSHAKE;

         dcb.Parity = NOPARITY;
         dcb.StopBits = ONESTOPBIT;
         dcb.ByteSize = 8;

         if(!SetCommState(h,&dcb))
            PrintError("E014_SetCommState failed");

		

         // start terminal
         Terminal(h);
	     CloseHandle(h);
	
      }
   } else {
	  printf("Commandline Serial Terminal - Version 1.1 by A. Schmidt, Oct 2001\n");
	  printf("Lancaster University - http://www.comp.lancs.ac.uk/~albrecht/\n\n");
	  help();
	  wait4keypressed();
	}
   return 0;
}


