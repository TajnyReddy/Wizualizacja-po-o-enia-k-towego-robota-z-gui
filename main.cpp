#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <fstream>
#include <string>
#include <cmath>
#include <math.h>

#define MAX_LOADSTRING 100
#define TMR_1 1
#define TIME 0.04
#define M_PI 3.14159265358979323846

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR textSaved[6];
TCHAR text[50] = { 'W', 'r','o','n', 'g',' ', 'd', 'a','t', 'a', ' ','p', 'r', 'o','v','i', 'd','e','d','!' };
INT value;

// buttons
HWND hwndButton;
HWND TextBox;

// sent data
int col = 0;
std::vector<Point> data1;
std::vector<Point> data2;
std::vector<Point> data3;
std::vector<Point> YZ;
std::vector<Point> XZ;
std::vector<Point> XY;

RECT drawArea1 = { 10, 5, 250, 100 };
RECT drawArea2 = { 10,135,250,230 };
RECT drawArea3 = { 10,280,250,500 };

RECT drawArea4 = { 650, 5, 900, 105 };
RECT drawArea5 = { 650, 135, 900, 235 };
RECT drawArea6 = { 650, 280, 900, 600 };

int displacement = 0;
int multiplier = 1;
float divider = 1;
int File = 1;
int buf;
int displacementing = 0;
int displacementing2 = 0;
int velocity = 1;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);
//vectors
//vectors
std::vector<std::string> roll1;
std::vector<std::string> roll2;
std::vector<std::string> roll3;
std::vector<std::string> pitch1;
std::vector<std::string> pitch2;
std::vector<std::string> pitch3;
std::vector<std::string> yaw1;
std::vector<std::string> yaw2;
std::vector<std::string> yaw3;
void MyOnPaint1(HDC hdc, std::vector<std::string> vector)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));
	Pen pen3(Color(0, 0, 0));

	for (int i = 1; i < vector.size() - displacementing; i++) {
		graphics.DrawLine(&pen2, data1[i - 1].X - displacement, data1[i - 1].Y + 50, data1[i].X - displacement, data1[i].Y + 50);
	}
}

void obramowka(HDC hdc) {
	Graphics graphics(hdc);
	Pen pen3(Color(0, 0, 0));
	graphics.DrawRectangle(&pen3, 9, 1, 241, 115);
	graphics.DrawRectangle(&pen3, 9, 131, 241, 115);
	graphics.DrawRectangle(&pen3, 9, 270, 241, 235);
}
void MyOnPaint2(HDC hdc, std::vector<std::string> vector)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));

	for (int i = 1; i < vector.size() - displacementing; i++)
		graphics.DrawLine(&pen2, data2[i - 1].X - displacement, data2[i - 1].Y + 180, data2[i].X - displacement, data2[i].Y + 180);

}
void MyOnPaint3(HDC hdc, std::vector<std::string> vector)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));
	Pen pen3(Color(0, 0, 0));


	for (int i = 1; i < vector.size() - displacementing; i++)
		graphics.DrawLine(&pen2, data3[i - 1].X - displacement, data3[i - 1].Y + 310, data3[i].X - displacement, data3[i].Y + 310);

}
void MyOnPaint4(HDC hdc, std::vector<std::string> vector)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));
	Pen pen3(Color(0, 0, 0));


	for (int i = 1; i < (vector.size() - displacementing2); i++)
		graphics.DrawLine(&pen2, YZ[i - 1].X + 775 - displacement, YZ[i - 1].Y + 55, YZ[i].X + 775 - displacement, YZ[i].Y + 55);
	graphics.DrawLine(&pen3, 650, 55, 900, 55);
	graphics.DrawLine(&pen3, 775, 5, 775, 155);
}
void MyOnPaint5(HDC hdc, std::vector<std::string> vector)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));
	Pen pen3(Color(0, 0, 0));


	for (int i = 1; i < (vector.size() - displacementing2) / 2; i++)
		graphics.DrawLine(&pen2, XZ[i - 1].X + 775 - displacement, XZ[i - 1].Y + 185, XZ[i].X + 775 - displacement, XZ[i].Y + 185);
	graphics.DrawLine(&pen3, 650, 185, 900, 185);
	graphics.DrawLine(&pen3, 775, 135, 775, 235);
}
void MyOnPaint6(HDC hdc, std::vector<std::string> vector)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));
	Pen pen3(Color(0, 0, 0));


	for (int i = 1; i < (vector.size() - displacementing2) / 2; i++)
		graphics.DrawLine(&pen2, XY[i - 1].X + 775 - displacement, XY[i - 1].Y + 400, XY[i].X + 775 - displacement, XY[i].Y + 400);
	graphics.DrawLine(&pen3, 650, 400, 900, 400);
	graphics.DrawLine(&pen3, 775, 280, 775, 505);
}

void repaintWindow1(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<std::string> vector)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint1(hdc, vector);
	EndPaint(hWnd, &ps);
}
void repaintWindow2(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<std::string> vector)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint2(hdc, vector);
	EndPaint(hWnd, &ps);
}
void repaintWindow3(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<std::string> vector)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint3(hdc, vector);
	EndPaint(hWnd, &ps);
}
void repaintWindow4(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<std::string> vector)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint4(hdc, vector);
	EndPaint(hWnd, &ps);
}
void repaintWindow5(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<std::string> vector)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint5(hdc, vector);
	EndPaint(hWnd, &ps);
}
void repaintWindow6(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, std::vector<std::string> vector)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint6(hdc, vector);
	EndPaint(hWnd, &ps);
}

void in_vector(std::fstream& File, std::vector<std::string>& roll1, std::vector<std::string>& pitch1, std::vector<std::string>& yaw1) {
	std::string line;
	std::string roll;
	std::string pitch;
	std::string yaw;
	while (getline(File, line)) {
		roll = line;
		pitch = line;
		yaw = line;
		roll1.push_back(roll.substr(0, 6));
		pitch1.push_back(pitch.substr(7, 6));
		yaw1.push_back(yaw.substr(14, 6));
	}
}
void load(std::vector<std::string>& roll1, std::vector<std::string>& pitch1, std::vector<std::string>& yaw1,
	std::vector<std::string>& roll2, std::vector<std::string>& pitch2, std::vector<std::string>& yaw2,
	std::vector<std::string>& roll3, std::vector<std::string>& pitch3, std::vector<std::string>& yaw3) {
	std::fstream RFB01;
	std::fstream RFA02;
	std::fstream PO01;
	RFB01.open("outputRobotForwardB01.log", std::ios::in);
	RFA02.open("outputRobotForwardA02.log", std::ios::in);
	PO01.open("outputPendulumOrt01.log", std::ios::in);
	in_vector(RFB01, roll1, pitch1, yaw1);
	in_vector(RFA02, roll2, pitch2, yaw2);
	in_vector(PO01, roll3, pitch3, yaw3);
	RFB01.close();
	RFA02.close();
	PO01.close();
}

void inputData1(std::vector<std::string>& vector)
{
	float pomoc;
	for (int i = 0 + displacementing; i < vector.size(); i++) {
		pomoc = std::stof(vector[i]);
		data1.push_back(Point(i - displacementing, ((pomoc / 2) * (divider))));
	}
}
void inputData2(std::vector<std::string>& vector)
{
	float pomoc;
	for (int i = 0 + displacementing; i < vector.size(); i++) {
		pomoc = std::stof(vector[i]);
		data2.push_back(Point(i - displacementing, ((pomoc / 2) * divider)));
	}
}
void inputData3(std::vector<std::string>& vector)
{
	float pomoc;
	for (int i = 0 + displacementing; i < vector.size(); i++) {
		pomoc = std::stof(vector[i]);
		data3.push_back(Point(i - displacementing, ((pomoc / 2) * divider)));
	}
}
void przesun1(std::vector<std::string>& vector) {
	double Y=1;
	double Z=0;
	double Yp = 0;
	double Zp = 0;
	YZ.push_back(Point(Yp, Zp));
	Yp = (Y * cos(std::stof(vector[1])) - Z * sin(std::stof(vector[1]))) * velocity * 1 / 25;
	Zp =  (Y * sin(std::stof(vector[1])) + Z * cos(std::stof(vector[1]))) * velocity * 1 / 25;
	YZ.push_back(Point(Yp, Zp));
	for (int i = 2 + displacementing2; i < vector.size() ; i++) {
		Yp = Yp +(Y * cos(std::stof(vector[i])) - Z * sin(std::stof(vector[i]))) * velocity * i / 25;
		Zp = Zp + (Y * sin(std::stof(vector[i])) + Z * cos(std::stof(vector[i]))) * velocity * i / 25;
		YZ.push_back(Point(Yp, Zp*divider));
	}
}
void przesun2(std::vector<std::string>& vector) {
	double X = 1;
	double Z = 0;
	double Xp = 0;
	double Zp = 0;
	XZ.push_back(Point(Xp, Zp));
	Zp = (Z * cos(std::stof(vector[1])) - X * sin(std::stof(vector[1]))) * velocity * 1 / 25;
	Xp = (Z * sin(std::stof(vector[1])) + X * cos(std::stof(vector[1]))) * velocity * 1 / 25;
	XZ.push_back(Point(Xp, Zp));
	for (int i = 2 + displacementing2; i < vector.size(); i++) {
		Xp =Xp +  (Z * sin(std::stof(vector[i]))+X * cos(std::stof(vector[i]))) * velocity * i / 25;
		Zp =Zp+ (Z*cos(std::stof(vector[i])) - X*sin(std::stof(vector[i]))) * velocity * i / 25;
		XZ.push_back(Point(Xp, Zp * divider));
	}
}
void przesun3(std::vector<std::string>& vector) {
	double X = 1;
	double Y = 0;
	double Xp = 0;
	double Yp = 0;
	XY.push_back(Point(Xp, Yp));
	Xp = (X * velocity * 1 / 25 * cos(std::stof(vector[1])) - Y * sin(std::stof(vector[1]))) * velocity * 1 / 25;
	Yp = (X * sin(std::stof(vector[1])) + Y * cos(std::stof(vector[1]))) * velocity * 1 / 25;
	XY.push_back(Point(Xp, Yp));
	for (int i = 2 + displacementing2; i < vector.size(); i++) {
		Xp =Xp+ (X * cos(std::stof(vector[i])) - Y * sin(std::stof(vector[i])))* velocity * i / 25;
		Yp =Yp+ (X * sin(std::stof(vector[i])) + Y * cos(std::stof(vector[i]))) * velocity * i / 25;
		XY.push_back(Point(Xp, Yp * divider));
	}
}
int OnCreate1(HWND window, std::vector<std::string> vector)
{
	inputData1(vector);
	return 0;
}
int OnCreate2(HWND window, std::vector<std::string> vector)
{
	inputData2(vector);
	return 0;
}
int OnCreate3(HWND window, std::vector<std::string> vector)
{
	inputData3(vector);
	return 0;
}
int OnCreate4(HWND window, std::vector<std::string> vector)
{
	przesun1(vector);
	return 0;
}
int OnCreate5(HWND window, std::vector<std::string> vector)
{
	przesun2(vector);
	return 0;
}
int OnCreate6(HWND window, std::vector<std::string> vector)
{
	przesun3(vector);
	return 0;
}
void change(HWND hWnd) {
	std::string pomin;
	int check;
	for (int i = 0; i < 6; i++) {
		pomin += textSaved[i];
	}
	if (stoi(pomin) > data1.size() || stoi(pomin) > data2.size() || stoi(pomin) > data3.size())
		::MessageBox(hWnd, text, textSaved, MB_OK);
	else {
		displacementing = 0;
		::MessageBox(hWnd, textSaved, textSaved, MB_OK);
		displacementing = stoi(pomin);
	}
	if (displacementing < YZ.size() && displacementing < XZ.size() && displacementing < XY.size()) {
		displacementing2 = displacementing;
	}
	else ::MessageBox(hWnd, text, textSaved, MB_OK);
}

// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	load(roll1, pitch1, yaw1, roll2, pitch2, yaw2, roll3, pitch3, yaw3);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);


	// create button and store the handle                                                       

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Draw"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,  // the styles
		260, 20,                                  // the left and top co-ordinates-
		100, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	// create button and store the handle 
	TextBox = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 360, 390, 190, 30, hWnd, NULL, NULL, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("How much to skip"),
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		305, 350, 190, 30, hWnd, (HMENU)ID_RBUTTON13, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Confirm"),
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		260, 390, 100, 30, hWnd, (HMENU)ID_RBUTTON14, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer ON"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		260, 60, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer OFF"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		260, 100, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer x1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		260, 150, 100, 30, hWnd, (HMENU)ID_RBUTTON3, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer x2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		260, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON4, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer x4"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		260, 250, 100, 30, hWnd, (HMENU)ID_RBUTTON5, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Reset"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		260, 300, 110, 30, hWnd, (HMENU)ID_RBUTTON6, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Amplitude x 1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 60, 110, 30, hWnd, (HMENU)ID_RBUTTON7, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Amplitude x 2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 100, 110, 30, hWnd, (HMENU)ID_RBUTTON8, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Amplitude x 0.5"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 20, 110, 30, hWnd, (HMENU)ID_RBUTTON9, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("File 1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 200, 110, 30, hWnd, (HMENU)ID_RBUTTON10, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("File 2"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 250, 110, 30, hWnd, (HMENU)ID_RBUTTON11, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("File 3"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 300, 110, 30, hWnd, (HMENU)ID_RBUTTON12, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Amplitude x 10"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		390, 150, 110, 30, hWnd, (HMENU)ID_RBUTTON15, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Velocity 1"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		515, 20, 120, 30, hWnd, (HMENU)ID_RBUTTON16, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Velocity 100"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		515, 70, 120, 30, hWnd, (HMENU)ID_RBUTTON17, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Velocity 5"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
		515, 120, 120, 30, hWnd, (HMENU)ID_RBUTTON18, GetModuleHandle(NULL), NULL);

	OnCreate1(hWnd, roll1);
	OnCreate2(hWnd, pitch1);
	OnCreate3(hWnd, yaw1);
	OnCreate4(hWnd, roll1);
	OnCreate5(hWnd, pitch1);
	OnCreate6(hWnd, yaw1);


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			col++;
			if (col > 10)
				col = 0;
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
			repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
			repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
			repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			break;
		case ID_RBUTTON1:
			SetTimer(hWnd, TMR_1, 25, 0);
			break;
		case ID_RBUTTON2:
			KillTimer(hWnd, TMR_1);
			break;
		case ID_RBUTTON3:
			multiplier = 1;
			break;
		case ID_RBUTTON4:
			multiplier = 2;
			break;
		case ID_RBUTTON5:
			multiplier = 4;
			break;
		case ID_RBUTTON6:
			displacement = 0;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON7:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			divider = 1;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON8:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			divider = 2;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON9:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			divider = (0.5);
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON10:
			File = 1;
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			OnCreate1(hWnd, roll1);
			OnCreate2(hWnd, pitch1);
			OnCreate3(hWnd, yaw1);
			OnCreate4(hWnd, roll1);
			OnCreate5(hWnd, pitch1);
			OnCreate6(hWnd, yaw1);
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
			repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
			repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
			repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			break;
		case ID_RBUTTON11:
			File = 2;
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			OnCreate1(hWnd, roll2);
			OnCreate2(hWnd, pitch2);
			OnCreate3(hWnd, yaw2);
			OnCreate4(hWnd, roll2);
			OnCreate5(hWnd, pitch2);
			OnCreate6(hWnd, yaw2);
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
			repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
			repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
			repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			break;
		case ID_RBUTTON12:
			File = 3;
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			OnCreate1(hWnd, roll3);
			OnCreate2(hWnd, pitch3);
			OnCreate3(hWnd, yaw3);
			OnCreate4(hWnd, roll3);
			OnCreate5(hWnd, pitch3);
			OnCreate6(hWnd, yaw3);
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
			repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
			repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
			repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			break;
		case ID_RBUTTON14:
			GetWindowText(TextBox, textSaved, 6);
			change(hWnd);
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON15:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			divider = 10;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON16:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			velocity = 1;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON17:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			velocity = 100;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);;
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		case ID_RBUTTON18:
			data1.clear();
			data2.clear();
			data3.clear();
			YZ.clear();
			XZ.clear();
			XY.clear();
			velocity = 5;
			if (File == 1) {
				OnCreate1(hWnd, roll1);
				OnCreate2(hWnd, pitch1);
				OnCreate3(hWnd, yaw1);
				OnCreate4(hWnd, roll1);
				OnCreate5(hWnd, pitch1);
				OnCreate6(hWnd, yaw1);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll1);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch1);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw1);
			}
			if (File == 2) {
				OnCreate1(hWnd, roll2);
				OnCreate2(hWnd, pitch2);
				OnCreate3(hWnd, yaw2);
				OnCreate4(hWnd, roll2);
				OnCreate5(hWnd, pitch2);
				OnCreate6(hWnd, yaw2);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll2);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch2);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw2);
			}
			if (File == 3) {
				OnCreate1(hWnd, roll3);
				OnCreate2(hWnd, pitch3);
				OnCreate3(hWnd, yaw3);
				OnCreate4(hWnd, roll3);
				OnCreate5(hWnd, pitch3);
				OnCreate6(hWnd, yaw3);
				repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
				repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
				repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
				repaintWindow4(hWnd, hdc, ps, &drawArea4, roll3);
				repaintWindow5(hWnd, hdc, ps, &drawArea5, pitch3);
				repaintWindow6(hWnd, hdc, ps, &drawArea6, yaw3);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		obramowka(hdc);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			value++;
			break;
		}
		if ((displacement < data1.size() - 150) && (displacement < data3.size() - 150) && (displacement < data2.size() - 150)) {
			displacement += multiplier;
		}
		if (File == 1) {
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll1);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch1);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw1);
		}
		if (File == 2) {
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll2);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch2);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw2);
		}
		if (File == 3) {
			repaintWindow1(hWnd, hdc, ps, &drawArea1, roll3);
			repaintWindow2(hWnd, hdc, ps, &drawArea2, pitch3);
			repaintWindow3(hWnd, hdc, ps, &drawArea3, yaw3);
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
