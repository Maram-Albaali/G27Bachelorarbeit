#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#include "LogitechWrapper.h"

#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <time.h>
#include <ctime>
#include <string>
#include <chrono>





using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_BTN_INIT 1
#define ID_BTN_CLOSE 2

LogitechWrapper obj;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) 
{
	MSG  msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"LogiMQTT";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&wc);
	
	// Main windows
	CreateWindowW(wc.lpszClassName, L"LogiMQTT", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 150, 150, 250, 200, 0, 0, hInstance, 0);
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg) 
	{
	case WM_CREATE:
		// Button 1
		CreateWindowW(L"BUTTON", L"Init", WS_VISIBLE | WS_CHILD, 20, 50, 80, 25, hwnd, (HMENU)ID_BTN_INIT, NULL, NULL);
		//Button 2
		CreateWindowW(L"BUTTON", L"Close", WS_VISIBLE | WS_CHILD, 120, 50, 80, 25, hwnd, (HMENU)ID_BTN_CLOSE, NULL, NULL);
		break;

	case WM_COMMAND:
		// was passiet wenn BUTTON_1 geclickt wird 
		if (LOWORD(wParam) == ID_BTN_INIT) 
		{
			// Logitech Init usw.
			bool result = obj.establishConnection();
			/* read x from wheel
			DIJOYSTATE2* vars = obj.getWheelVariables();
			double x = vars->lX;
			*/
			

			//Windo with Connection informations         
			if (result)
			{
				MessageBox(hwnd, L"Connected", L"InitButton", MB_OK);  
				
				//openFile
				std::ofstream logFileDynamics;
				std::string newLine;
				std::string line;
				std::ifstream fileMSAvoid("steeringWheelDaten.txt");
				char bufferTime[80];
				std::string strTime(bufferTime);

				// to get Time
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);

				// Time vars rechnen
				int timer = ((int)(now->tm_sec * 1000)); //[s] *1000
				int year = now->tm_year + 1900;
				int month = now->tm_mon + 1;

				//to read wheel vars 
				DIJOYSTATE2* vars = obj.getWheelVariables();

				double speed = vars->lY;
				double Break = vars->lRz;
				double clutch = vars->rglSlider[1];
				double wheelAngle = vars->lX;

				//open file and write
				logFileDynamics.open("steeringWheelDaten.txt");
				logFileDynamics
					<< "Time: Year; Mon; Day; Hour; Min; Sec; Millisec;"
					<< "Speed ;"
					<< "Break ;"
					<< "Clutch ;"
					<< "WheelAngle ;"
					<< std::endl;


				//unsigned int x = 3000;
				//while (true) {

				fileMSAvoid >> newLine; //read the header line of the text file
				line = newLine;

				logFileDynamics

					<< year << ';' << month << ';' << now->tm_mday << ';' << now->tm_hour << ';' << now->tm_min << ';' << now->tm_sec << ';' << timer << ';'
					<< speed << ';'
					<< Break << ';'
					<< clutch << ';'
					<< wheelAngle << ';'
					<< std::endl;

				//std::this_thread::sleep_for(std::chrono::milliseconds(x));

			//}
				logFileDynamics.close();
				/*
				DIJOYSTATE2* vars = obj.getWheelVariables();

				double x = vars->lY;

				std::string myString = "x = ";
				myString += std::to_string(x);

				LPWSTR ws = new wchar_t[x];
				copy(myString.begin(), myString.end(), ws);
				ws[myString.size()] = 0; // zero at the end

				MessageBox(hwnd, ws, L"x", MB_OK);*/ 
			}

		}


		
	
		// was passiet wenn BUTTON_2 geclickt wird 
		if (LOWORD(wParam) == ID_BTN_CLOSE) 
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			//MessageBox(hwnd, L"Close Pressed", L"Message - Close", MB_OKCANCEL);	
		}
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}


	return DefWindowProcW(hwnd, msg, wParam, lParam);
}