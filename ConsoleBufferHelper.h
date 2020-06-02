#pragma once
#include <windows.h> 
#include <stdio.h>
#include <iostream>
class ConsoleBufferHelper
{
public:
	ConsoleBufferHelper();
	~ConsoleBufferHelper();
	bool update();
	bool clear();
private:
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hStdout, hNewScreenBuffer;
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO* chiBuffer;
	COORD coordBufSize;
	COORD coordBufCoord;
	BOOL fSuccess;

	int numOfRows = 1;
	int numOfCols = 1;
	int bufferSize = 1;
	bool getBuffer();
	bool setBuffer();
	bool loadScreenVariables();
	bool initCharInfoBuffer();
	bool writeOutput();
	void cls(HANDLE hConsole);
};

ConsoleBufferHelper::ConsoleBufferHelper()
{
	std::cout << "ConsoleBufferHelper()" << std::endl;
	//getBuffer();
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);
}

ConsoleBufferHelper::~ConsoleBufferHelper()
{
}

inline bool ConsoleBufferHelper::getBuffer()
{
//	std::cout << "getBuffer()" << std::endl;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get a handle to the STDOUT screen buffer to copy from and 
	// create a new screen buffer to copy to. 
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		return 0;
	}

	loadScreenVariables();


	return true;
}

inline bool ConsoleBufferHelper::setBuffer()
{
//	std::cout << "setBuffer()" << std::endl;

	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL 
	if (hStdout == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return false;
	}
	// Make the new screen buffer the active screen buffer. 

	if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return false;
	}

	// Set the source rectangle. 

	srctReadRect.Top = 0;    // top left: row 0, col 0 
	srctReadRect.Left = 0;
	srctReadRect.Bottom = numOfRows; // bottom. right:
	srctReadRect.Right = numOfCols;

	// The temporary buffer size is numOfRows rows x numOfCols columns. 

	coordBufSize.Y = numOfRows;
	coordBufSize.X = numOfCols;

	// The top left destination cell of the temporary buffer is 
	// row 0, col 0. 

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	// Copy the block from the screen buffer to the temp. buffer. 

	fSuccess = ReadConsoleOutput(
		hStdout,        // screen buffer to read from 
		chiBuffer,      // buffer to copy into 
		coordBufSize,   // col-row size of chiBuffer 
		coordBufCoord,  // top left dest. cell in chiBuffer 
		&srctReadRect); // screen buffer source rectangle 
	if (!fSuccess)
	{
		printf("ReadConsoleOutput failed - (%d)\n", GetLastError());
		return false;
	}

	// Set the destination rectangle. 

	srctWriteRect.Top = 0;    // top lt: row 0, col 0 
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = numOfRows; // bot. rt:
	srctWriteRect.Right = numOfCols;

	return true;
}

inline bool ConsoleBufferHelper::loadScreenVariables()
{
//	std::cout << "loadScreenVariables()" << std::endl;
	// Get the current screen buffer size and window position. 
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		return false;
	}
	if (numOfCols != csbiInfo.srWindow.Right || numOfRows != csbiInfo.srWindow.Bottom) {
		numOfCols = csbiInfo.srWindow.Right + 1;
		numOfRows = csbiInfo.srWindow.Bottom + 1;
		bufferSize = numOfRows * numOfCols;
	//	std::cout << "loadScreenVariables New Cols: " << numOfCols << " Rows: " << numOfRows << " BufferSize: : " << bufferSize << std::endl;
		initCharInfoBuffer();
		return true;
	}
	else {

	//	std::cout << "loadScreenVariables Old Cols: " << numOfCols << " Rows: " << numOfRows << " BufferSize: : " << bufferSize << std::endl;
		return true;
	}
	return false;
}

inline bool ConsoleBufferHelper::initCharInfoBuffer()
{
//	std::cout << "initCharInfoBuffer()" << std::endl;

	if (bufferSize > 1) {
		if (chiBuffer == nullptr) {
			chiBuffer = new CHAR_INFO[bufferSize];
			clear();
		}
		else {
			delete[] chiBuffer;
			chiBuffer = new CHAR_INFO[bufferSize];
			clear();
		}
		return true;
	}
	return false;
}

inline bool ConsoleBufferHelper::update()
{
//	std::cout << "update()" << std::endl;
	getBuffer();
	for (int i = 0; i < bufferSize; i++) {
		chiBuffer[i].Char.AsciiChar = '5';
	}
	for (int k = 0; k < 15; k++) {
		chiBuffer[k].Char.AsciiChar = (char)'|';
	}
	setBuffer();
	writeOutput();
	Sleep(5000);
	loadScreenVariables();

	return true;
}


inline bool ConsoleBufferHelper::clear()
{
//	std::cout << "clear()" << std::endl;
	if (bufferSize > 1) {
		for (int i = 0; i < bufferSize; i++) {
			chiBuffer[i].Char.AsciiChar = '*';
		}
		return true;
	}
	return false;
}
inline bool ConsoleBufferHelper::writeOutput()
{
//	std::cout << "writeOutput()" << std::endl;
	fSuccess = WriteConsoleOutput(
		hNewScreenBuffer, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);  // dest. screen buffer rectangle 
	if (!fSuccess)
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
		return false;
	}
	return true;
}

inline void ConsoleBufferHelper::cls(HANDLE hConsole)
{
		COORD coordScreen = { 0, 0 };    // home for the cursor 
		//DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;

		// Get the number of character cells in the current buffer. 

		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			return;
		}

		dwConSize = csbi.srWindow.Right * csbi.srWindow.Bottom;
		bufferSize = dwConSize;
		initCharInfoBuffer();
		// Fill the entire screen with blanks.

		//if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
		//	(TCHAR)'#',     // Character to write to the buffer
		//	dwConSize,       // Number of cells to write 
		//	coordScreen,     // Coordinates of first cell 
		//	&cCharsWritten))// Receive number of characters written
		//{
		//	return;
		//}

		//// Get the current text attribute.

		//if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		//{
		//	return;
		//}

		//// Set the buffer's attributes accordingly.

		//if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
		//	csbi.wAttributes, // Character attributes to use
		//	dwConSize,        // Number of cells to set attribute 
		//	coordScreen,      // Coordinates of first cell 
		//	&cCharsWritten)) // Receive number of characters written
		//{
		//	return;
		//}

		// Put the cursor at its home coordinates.
		hNewScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ |           // read/write access 
			GENERIC_WRITE,
			FILE_SHARE_READ |
			FILE_SHARE_WRITE,        // shared 
			NULL,                    // default security attributes 
			CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
			NULL);                   // reserved; must be NULL 
		if (hConsole == INVALID_HANDLE_VALUE ||
			hNewScreenBuffer == INVALID_HANDLE_VALUE)
		{
			printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
			//return 1;
		}

		// Make the new screen buffer the active screen buffer. 

		if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
		{
			printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
			//return 1;
		}
		SetConsoleCursorPosition(hConsole, coordScreen);
		srctWriteRect.Top = 0;    // top lt: row 0, col 0 
		srctWriteRect.Left = 0;
		srctWriteRect.Bottom = 45; // bot. rt:
		srctWriteRect.Right = 23;
		WriteConsoleOutput(
			hConsole,
			chiBuffer,
			coordScreen,
			coordScreen,
			&srctWriteRect
		);
		Sleep(5000);
		if (!SetConsoleActiveScreenBuffer(hConsole))
		{
			printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
			//return 1;
		}
}
