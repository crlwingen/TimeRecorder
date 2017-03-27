/*============================================================================*
* Title       : Time Recorder
* Description : Time Recorder using C.
* Filename    : Time Recorder(Gensaya - Modified).c
* Version     : v1.0
* Author      : Gensaya, Carl Jerwin F.
* Yr&Sec&Uni  : BSCS 1-1N PUP Main
* Subject     : Programming 2
*============================================================================*/

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

/*=============================INITIALIZATION=================================*/
char strIdInput[20], chrLogMode[5], chrChoice, strCompName[50],
	 chrYear[10], chrMonth[10], chrDay[10], chrHr[10], chrMin[10], chrSec[10],
	 chrTxtName[30], DateTxtName[30], strTemp[30], strLogFormat[30];
	 
int intLogMode, intCtr, intFlag, intIdLength, intChoice;
struct tm *info;
FILE *FileRecTxt, *FileConfig;
/*============================================================================*/

/*===============================PROTOTYPING==================================*/
void fnConfigChecker();						// MODIFIED: Added config.ini file.
void fnDelLine();
void fnCoorXY(short x, short y);
void fnLoading();
void fnTimeChecker();			
void fnId_Input();					
void fnLogMode();							// MODIFIED: Bases the logformat to the config.ini file.
/*============================================================================*/

/*============================================================================*
     *  Function   : main
     *  Params     : None 
     *  Returns    : Void
     *  Description: Main function of the program.
*=============================================================================*/
int main() {
	
	fnId_Input();
	return 0;
} // End of int main() 

/*============================================================================*
     *  Function   : fnConfigChecker
     *  Params     : None 
     *  Returns    : Void
     *  Description: Checks the config file content.
*=============================================================================*/
void fnConfigChecker() {
	
	FileConfig = fopen("config.ini", "r");
	system("mode 95, 40");
	
	if( ! FileConfig ) {
		
		FileConfig = fopen("config.ini", "w");
		fnCoorXY(15, 5); printf("The config.ini is not present. Default settings activated!");
		intIdLength = 13;
		strcpy(strCompName, "??COMPANY");
		strcpy(strLogFormat, "[date][logmode][id]");
		fprintf(FileConfig, "CompanyName=%s\nIdLength=%i\nLogFormat=%s", strCompName, intIdLength, strLogFormat);
	} else {

		fscanf(FileConfig, "%[^=]= %s\n%[^=]= %i %[^=]= %s", strTemp, strCompName, strTemp, &intIdLength, strTemp, strLogFormat);
		
	}
	
	fclose(FileConfig);
	
} // End of void fnConfigChecker()

/*============================================================================*
     *  Function   : fnId_Input
     *  Params     : None 
     *  Returns    : Void
     *  Description: Handles the ID input of the user.
*=============================================================================*/
void fnId_Input() {
	
	fnConfigChecker();
	system("cls");
	fnTimeChecker();
	intFlag = 1;
	
	while( 1 ) {

		fnCoorXY(25, 3); printf("=======================================");
		fnCoorXY(31, 5); printf("%s", strCompName);
		fnCoorXY(25, 8); printf("=======================================");
		
		for( intCtr = 0; intCtr < intIdLength; intCtr++ ) {
			fnCoorXY(39 + intCtr, 15); printf("-");
		} 
		
		fnCoorXY(3, 14); printf("\tEnter %i char ID Code\t:      ", intIdLength);
		scanf("%s", &strIdInput);
		
		if( strlen(strIdInput) == intIdLength ) {
			for( intCtr = 0; intCtr < intIdLength; intCtr++ ) {
				strIdInput[intCtr] = toupper(strIdInput[intCtr]);
			}
			Sleep(500);
			fnCoorXY(60, 14); printf("| Status: Okay!");
			fnLogMode();
		} else {
			fnCoorXY(60, 14); printf("| Status: Error!");
			getch();
			fnId_Input();
		}
	}
} // End of void fnId_Input()

/*============================================================================*
     *  Function   : fnTimeChecker
     *  Params     : None 
     *  Returns    : Void
     *  Description: Checks current system time.
*=============================================================================*/
void fnTimeChecker() {
   time_t rawtime;
   char buffer[80];

   time( &rawtime );
   info = localtime( &rawtime );

   strftime(chrHr,    10, "%H", info);
   strftime(chrMin,   10, "%M", info);
   strftime(DateTxtName, 30, "%Y%m%d", info);

} // End of void fnTimeChecker()

/*============================================================================*
     *  Function   : fnLogMode
     *  Params     : None 
     *  Returns    : Void
     *  Description: Checks user log mode.
*=============================================================================*/
void fnLogMode() {
	
	fnCoorXY(34, 6); printf("Welcome, %s.", strIdInput);
	fnCoorXY(3, 17); printf("\tEnter log mode\t\t:");
	fnCoorXY(39, 18); printf("-");
	fnCoorXY(5, 19); printf("\t  [1] In\n\t  [2] Out\n\t  [3] Back");
	fnCoorXY(39, 17); scanf("%s", &chrChoice);
	
	if( chrChoice == '1' || chrChoice == '2' ) {

		if( chrChoice == '1' )
			strcpy(chrLogMode, "in");
		else if( chrChoice == '2' )
			strcpy(chrLogMode, "out");
		
		if( chrChoice == '1' || chrChoice == '2' ) {
			sprintf(chrTxtName, "TR%s.txt", DateTxtName);
			FileRecTxt = fopen(chrTxtName, "a");
			fnLoading();
			fnCoorXY(21, 28); printf("STATUS: Your time has been recorded. Thank You!\n\n");
			
			if(strcmp(strLogFormat, "[date][logmode][id]") == 0)
				fprintf(FileRecTxt, "%s%s%s\n", DateTxtName, chrLogMode, strIdInput);
			else if(strcmp(strLogFormat, "[id][date][logmode]") == 0)
				fprintf(FileRecTxt, "%s%s%s\n", strIdInput, DateTxtName, chrLogMode);
			else if(strcmp(strLogFormat, "[id][logmode][date]") == 0)
				fprintf(FileRecTxt, "%s%s%s\n", strIdInput, chrLogMode, DateTxtName);
			else if(strcmp(strLogFormat, "[logmode][id][date]") == 0)		
				fprintf(FileRecTxt, "%s%s%s\n", chrLogMode, strIdInput, DateTxtName);
			else if(strcmp(strLogFormat, "[logmode][date][id]") == 0)
				fprintf(FileRecTxt, "%s%s%s\n", chrLogMode, strIdInput, DateTxtName);
			else
				fprintf(FileRecTxt, "%s%s%s\n", DateTxtName, strIdInput, chrLogMode);
	
		fclose(FileRecTxt);
		fnCoorXY(60, 34); printf("-----------------------");
		fnCoorXY(61, 36); printf("Next in line. Please.");
		fnCoorXY(60, 38); printf("-----------------------");
		Sleep(2000);
		fnId_Input();
		
		}
	} else if( chrChoice == '3' )
		fnId_Input();
		
	else {
		fnCoorXY(60, 17); printf("| Status: Error!");
		getch();
		fnCoorXY(0, 17); fnDelLine();
		fnLogMode();
	}
} // End of void fnLogMode()

/*============================================================================*
     *  Function   : fnCoorXY
     *  Params     : short x: X-coordinate of the cursor placement.
     				 short y: Y-coordinate of the cursor placement.
     *  Returns    : Void
     *  Description: Handles the cursor positioning on the console.
*=============================================================================*/
void fnCoorXY(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
} // End of void fnCoorXY(short x, short y)

/*============================================================================*
     *  Function   : fnDelLine
     *  Params     : None 
     *  Returns    : Void
     *  Description: Delete certain lines on the console.
*=============================================================================*/
void fnDelLine() {
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE),&info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;

    FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE),
      ' ', info.dwSize.X * info.dwCursorPosition.Y, coord, &written);
    fnCoorXY (info.dwCursorPosition.X + 1,
    info.dwCursorPosition.Y + 1);

} // End of void fnDelLine()

/*============================================================================*
     *  Function   : fnLoading
     *  Params     : None 
     *  Returns    : Void
     *  Description: Loading animation of the program.
*=============================================================================*/
void fnLoading() {
	
	fnCoorXY(30, 25); printf("[                         ]");
	for( intCtr = 1; intCtr < 26; intCtr++ ) {
		Sleep(40);
		fnCoorXY(30 + intCtr, 25);
		printf("=");
		
		if( intCtr * 4 == 100 ) {
			fnCoorXY(34, 27); printf("Recording Finished..\n");
			fnCoorXY(60, 17); printf("| Status: Okay!");
		}
	}
} // End of void fnLoading()