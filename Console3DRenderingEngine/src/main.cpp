//This is a 3D Rendering Engine in Windows console created totaly from scratch using only Windows apis to write directly
//to the Console Character buffer. Fist of all I must apolagize for my bad english. I have commented on almost every peice
//of code I wrote here. But there might be some comments that are totaly grammeticaly wrong and doesn't make any sense.
//I'm so sorry for that.
//The idea of creating a 3D rendering engine on Windows Console is not originaly a my idea. A youtuber named javidx9 has
//already created this and done a whole series about it. You can find the first episode of that series from here https://www.youtube.com/watch?v=ih20l3pJoeU
//I got the idea from that video and Yes some of the code I've written here is from javidx9's video. If you want an in-depth
//tutorial of creating Console3D Engine go check out that video

// TODO : Implement Triangle Clipping

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

//Windows Include
#define NOMINMAX
#include <Windows.h>

//Custom Maths Library
#include "Math/Math.h"

//Standard Includes
#include <chrono>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

//Scraped from msdn https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-tvtt/261ddfb0-ce10-4380-9b7a-4b50f482b8ec
enum KEY_CODE {
	LBUTTON = 0x01,
	RBUTTON = 0x02,
	CANCEL = 0x03,
	BACK = 0x08,
	TAB = 0x09,
	CLEAR = 0x0C,
	RETURN = 0x0D,
	SHIFT = 0x10,
	CTRL = 0x11,
	MENU = 0x12,
	PAUSE = 0x13,
	CAPITAL = 0x14,
	ESC = 0x1B,
	SPACE = 0x20,
	PRIOR = 0x21,
	NEXT = 0x22,
	END = 0x23,
	HOME = 0x24,
	LEFT = 0x25,
	UP = 0x26,
	RIGHT = 0x27,
	DOWN = 0x28,
	SELECT = 0x29,
	PRINT = 0x2A,
	EXECUTE = 0x2B,
	SNAPSHOT = 0x2C,
	INSERT = 0x2D,
	DEL = 0x2E,
	HELP = 0x2F,
	NUM0 = 0x30,
	NUM1 = 0x31,
	NUM2 = 0x32,
	NUM3 = 0x33,
	NUM4 = 0x34,
	NUM5 = 0x35,
	NUM6 = 0x36,
	NUM7 = 0x37,
	NUM8 = 0x38,
	NUM9 = 0x39,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	LWIN = 0x5B,
	RWIN = 0x5C,
	APPS = 0x5D,
	SLEEP = 0x5F,
	NUMPAD0 = 0x60,
	NUMPAD1 = 0x61,
	NUMPAD2 = 0x62,
	NUMPAD3 = 0x63,
	NUMPAD4 = 0x64,
	NUMPAD5 = 0x65,
	NUMPAD6 = 0x66,
	NUMPAD7 = 0x67,
	NUMPAD8 = 0x68,
	NUMPAD9 = 0x69,
	MULTIPLY = 0x6A,
	ADD = 0x6B,
	SEPARATOR = 0x6C,
	SUBTRACT = 0x6D,
	DEC = 0x6E,
	DIVIDE = 0x6F,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	F13 = 0x7C,
	F14 = 0x7D,
	F15 = 0x7E,
	F16 = 0x7F,
	F17 = 0x80,
	F18 = 0x81,
	F19 = 0x82,
	F20 = 0x83,
	F21 = 0x84,
	F22 = 0x85,
	F23 = 0x86,
	F24 = 0x87,
	NUMLOCK = 0x90,
	SCROLL = 0x91,
	LSHIFT = 0xA0,
	RSHIFT = 0xA1,
	LCTRL = 0xA2,
	RCTRL = 0xA3,
	LMENU = 0xA4,
	RMENU = 0xA5,
};

enum COLOUR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, // Thanks MS :-/
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};

//CHAR_INFO Buffer that holds the screen buffer. When we done writing to the buffer we can use WriteConsoleOutput() function to copy the data of this buffer to actual console screen buffer
CHAR_INFO* pBackBuffer = nullptr;


//Console size configurations
constexpr int nScreenWidth = 150; //Console Window Width in Character cells
constexpr int nScreenHeight = 120; //Console Window Height in Character cells
constexpr unsigned short nFontWidth = 4; //Console Character Width in Screen pixels
constexpr unsigned short nFontHeight = 4; //Console Character Height in Screen Pixels

//Handle to the console output buffer
HANDLE hConsole = nullptr;

//Declaration of the three main finctions. Implementations are below the main function

//This runs once after the application starts
bool OnStart();

//This runs every frame.
bool OnUpdate(float dt);

//This runs after the user requested to exit. Use this to clean up.
void OnDestroy();


int main() {
	//Get the handle to the current console
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the cuurent screen buffer size according to the given screen sizes
	SetConsoleScreenBufferSize(hConsole, { nScreenWidth, nScreenHeight });

	// Change the font information of the current console. Set the font size to given font width and height
	CONSOLE_FONT_INFOEX cfiex;
	cfiex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfiex.nFont = 0;
	cfiex.dwFontSize.X = (SHORT)nFontWidth;
	cfiex.dwFontSize.Y = (SHORT)nFontHeight;
	cfiex.FontFamily = FF_DONTCARE;
	cfiex.FontWeight = FW_NORMAL;
	wcscpy_s(cfiex.FaceName, L"Consolas");

	SetCurrentConsoleFontEx(hConsole, FALSE, &cfiex);

	// Change the size of the current console window according to the given screen sizes and font sizes
	// I realy don't know why we have to substract 1 from both width and height of the screen size. But this is the only way it seem to be working.
	// If I set it to just screen width and height it won't work.
	SMALL_RECT rectConsoleSize = { 0, 0, (SHORT)(nScreenWidth - 1), (SHORT)(nScreenHeight - 1) }; 
	SetConsoleWindowInfo(hConsole, TRUE, &rectConsoleSize);

	//Allocate memory for back buffer
	pBackBuffer = new CHAR_INFO[nScreenWidth * nScreenHeight];

	//Set the backbuffer to 0
	memset(pBackBuffer, 0, sizeof(CHAR_INFO) * nScreenWidth * nScreenHeight);

	std::chrono::steady_clock::time_point tp1 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point tp2 = std::chrono::steady_clock::now();

	//Our OnStart() function
	if (!OnStart()) {
		goto APPLICATION_EXIT;
	}

	//Our main game loop
	while (true) {

		//Handle Timing
		//Calculating the time for a frame
		tp2 = std::chrono::steady_clock::now();
		std::chrono::duration<float> EalapsedTime = tp2 - tp1;
		tp1 = tp2;
		float dt = EalapsedTime.count();
		
		if (!OnUpdate(dt)) {
			goto APPLICATION_EXIT;
		}

		//Present our back buffer to the screen
		SMALL_RECT rectWriteRegion = { 0, 0, (SHORT)(nScreenWidth - 1), (SHORT)(nScreenHeight - 1) }; // We need to write to the whole screen. Again I don't know why we have to substract 1 from size
		WriteConsoleOutput(hConsole, pBackBuffer, { nScreenWidth, nScreenHeight }, { 0,0 }, &rectWriteRegion);
	
		wchar_t sWindowTitle[256];
		swprintf_s(sWindowTitle, 256, L"Console 3D Rendering Engine | FPS: %3.2f", 1.0f / dt);
		SetConsoleTitle(sWindowTitle);
	}


APPLICATION_EXIT:

	//Cleanup
	OnDestroy();

	//Delete backbuffer before exiting
	if (pBackBuffer) delete[] pBackBuffer;

	return 0;
}

//Some utility functions

//Utility function to set character on screen on given coordinate
void SetPixel(Math::Vector2i Coordinate, WCHAR UnicodeCharacter = PIXEL_TYPE::PIXEL_SOLID, WORD Attributes = COLOUR::FG_WHITE) {
	if (Coordinate.x >= 0 && Coordinate.x < nScreenWidth && Coordinate.y >= 0 && Coordinate.y < nScreenHeight) {
		pBackBuffer[Coordinate.x + Coordinate.y * nScreenWidth].Char.UnicodeChar = UnicodeCharacter;
		pBackBuffer[Coordinate.x + Coordinate.y * nScreenWidth].Attributes = Attributes;
	}
}

void SetPixel(int x, int y, WCHAR UnicodeCharacter = PIXEL_TYPE::PIXEL_SOLID, WORD Attributes = COLOUR::FG_WHITE) {
	if (x >= 0 && x < nScreenWidth && y >= 0 && y < nScreenHeight) {
		pBackBuffer[x + y * nScreenWidth].Char.UnicodeChar = UnicodeCharacter;
		pBackBuffer[x + y * nScreenWidth].Attributes = Attributes;
	}
}

//Draw a line
void DrawLine(Math::Vector2i point1, Math::Vector2i point2, WCHAR UnicodeCharacter = PIXEL_TYPE::PIXEL_SOLID, WORD Attributes = COLOUR::FG_WHITE) {
	if (point1.x == point2.x && point1.y == point2.y) {
		SetPixel(point1, UnicodeCharacter, Attributes);
	}
	else if (point1.x == point2.x) {
		if (point1.y > point2.y) std::swap(point1.y, point2.y);
		for (int y = point1.y; y <= point2.y; y++) SetPixel(point1.x, y, UnicodeCharacter, Attributes);
	}
	else if (point1.y == point2.y) {
		if (point1.x > point2.x) std::swap(point1.x, point2.x);
		for (int x = point1.x; x <= point2.x; x++) SetPixel(x, point1.y, UnicodeCharacter, Attributes);
	}
	else {
		if (point1.x > point2.x) {
			//std::swap(point1.x, point2.x);
			//std::swap(point1.y, point2.y);
			std::swap(point1, point2);
		}

		//int nDx = point2.x - point1.x;
		//int nDy = point2.y - point1.y;

		Math::Vector2i vec2iDelta = point2 - point1;

		if (vec2iDelta.y > 0) {
			int nPrevY = point1.y;

			for (int x = 0; x <= vec2iDelta.x; x++) {
				float fY = (float)x / (float)vec2iDelta.x;
				int y = (int)(fY * vec2iDelta.y) + point1.y;
				SetPixel(point1.x + x, y, UnicodeCharacter, Attributes);

				if (y > (nPrevY + 1)) {
					int _nDy = y - (nPrevY + 1);
					for (int _y = 0; _y <= _nDy; _y++) {
						float _fX = (float)_y / (float)_nDy;
						int _x = (int)(_fX);
						SetPixel(point1.x + x + _x, _y + (nPrevY + 1), UnicodeCharacter, Attributes);
					}
				}

				nPrevY = y;
			}
		}
		else {
			int nPrevY = point1.y;

			for (int x = 0; x <= vec2iDelta.x; x++) {
				float fY = (float)x / (float)vec2iDelta.x;
				int y = (int)(fY * vec2iDelta.y) + point1.y;
				SetPixel(point1.x + x, y, UnicodeCharacter, Attributes);

				if (y < (nPrevY - 1)) {
					int _nDy = (nPrevY - 1) - y;
					for (int _y = 0; _y <= _nDy; _y++) {
						float _fX = (float)_y / (float)_nDy;
						int _x = (int)(_fX);
						SetPixel(point1.x + x - _x, y + _y, UnicodeCharacter, Attributes
);
					}
				}

				nPrevY = y;
			}
		}

	}
}

//Draw a Triangle
void DrawTriangle(Math::Vector2i point1, Math::Vector2i point2, Math::Vector2i point3, WCHAR UnicodeCharacter = PIXEL_TYPE::PIXEL_SOLID, WORD Attributes = COLOUR::FG_WHITE) {
	DrawLine(point1, point2, UnicodeCharacter, Attributes);
	DrawLine(point2, point3, UnicodeCharacter, Attributes);
	DrawLine(point3, point1, UnicodeCharacter, Attributes);
}

//Clear the screen to a certain character
void ClearScreen(WCHAR UnicodeCharacter = PIXEL_TYPE::PIXEL_SOLID, WORD Attributes = COLOUR::FG_BLACK) {
	for (std::size_t i = 0; i < nScreenWidth * nScreenHeight; i++) {
		pBackBuffer[i].Attributes = Attributes;
		pBackBuffer[i].Char.UnicodeChar = UnicodeCharacter;
	}
}


//Classify the pixel based on the t value (t must be normalized)
CHAR_INFO ClassifyPixel(const float& t) {
	CHAR_INFO c;

	int nt = (int)(t * 13.0f);

	switch (nt) {
	case  0: c.Attributes = BG_BLACK		| FG_BLACK;		c.Char.UnicodeChar = PIXEL_SOLID;			break;
		  
	case  1: c.Attributes = BG_BLACK		| FG_DARK_GREY; c.Char.UnicodeChar = PIXEL_QUARTER;			break;
	case  2: c.Attributes = BG_BLACK		| FG_DARK_GREY; c.Char.UnicodeChar = PIXEL_HALF;			break;
	case  3: c.Attributes = BG_BLACK		| FG_DARK_GREY; c.Char.UnicodeChar = PIXEL_THREEQUARTERS;	break;
	case  4: c.Attributes = BG_BLACK		| FG_DARK_GREY; c.Char.UnicodeChar = PIXEL_SOLID;			break;
		  
		  
		  
	case  5: c.Attributes = BG_DARK_GREY	| FG_GREY;		c.Char.UnicodeChar = PIXEL_QUARTER;			break;
	case  6: c.Attributes = BG_DARK_GREY	| FG_GREY;		c.Char.UnicodeChar = PIXEL_HALF;			break;
	case  7: c.Attributes = BG_DARK_GREY	| FG_GREY;		c.Char.UnicodeChar = PIXEL_THREEQUARTERS;	break;
	case  8: c.Attributes = BG_DARK_GREY	| FG_GREY;		c.Char.UnicodeChar = PIXEL_SOLID;			break;


	case  9: c.Attributes = BG_GREY		| FG_WHITE;			c.Char.UnicodeChar = PIXEL_QUARTER;			break;
	case 10: c.Attributes = BG_GREY		| FG_WHITE;			c.Char.UnicodeChar = PIXEL_HALF;			break;
	case 11: c.Attributes = BG_GREY		| FG_WHITE;			c.Char.UnicodeChar = PIXEL_THREEQUARTERS;	break;
	case 12: c.Attributes = BG_GREY		| FG_WHITE;			c.Char.UnicodeChar = PIXEL_SOLID;			break;
	default:
		c.Attributes = BG_GREY | FG_WHITE;			c.Char.UnicodeChar = PIXEL_SOLID;			break;
	}

	return c;
}

// A struct that holds the position and rotation of a object
struct Transform {
	Math::Vector3 position; // This is relative to the object space
	Math::Vector3 rotation;	
	// rotation.x rotation around the x axis of the object in radians
	// rotation.y rotation around the y axis of the object in radians
	// rotation.z rotation around the z axis of the object in radians
};

// A struct that holds the information about a vertex of a mesh
struct Vertex {
	Math::Vector3 position;
};

// A struct that holds the information about a mesh
struct Mesh {

	Mesh() {};
	Mesh(std::string filename, Transform transform) : transform(transform) {
		LoadFromOBJFile(filename);
		CalculateNormals();
	}

	Mesh(std::string filename, Math::Vector3 position, Math::Vector3 rotation) {
		transform.position = position;
		transform.rotation = rotation;
		LoadFromOBJFile(filename);
		CalculateNormals();
	}

	Transform transform; // this holds the position and rotation of the mesh in world space
	std::vector<Vertex> vertices; // holds the vertices
	std::vector<unsigned short> indices; // holds the indices of triangles
	std::vector<Math::Vector3> normals;

	//a helper function to load a obj file
	bool LoadFromOBJFile(std::string filename) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			return false;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::vector<std::string> words(std::istream_iterator<std::string>{iss},
				std::istream_iterator<std::string>());
			if (words[0] == "v") {
				vertices.push_back({Math::Vector3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3])) });
			}
			if (words[0] == "f") {
				indices.push_back(std::stoi(words[1]) - 1);
				indices.push_back(std::stoi(words[2]) - 1);
				indices.push_back(std::stoi(words[3]) - 1);
			}

		}

		return true;
	}

	//Calculate the normals of the each triangle of the mesh
	void CalculateNormals() {
		for (std::size_t i = 0; i < indices.size(); i += 3) {
			const Vertex& v0 = vertices[indices[i]];
			const Vertex& v1 = vertices[indices[i + 1]];
			const Vertex& v2 = vertices[indices[i + 2]];

			const Math::Vector3 line1 = v1.position - v0.position;
			const Math::Vector3 line2 = v2.position - v0.position;

			Math::Vector3 normal = Math::Vec3CrossProduct(line1, line2);
			normal.Normalize();
			normals.push_back(normal);
		}
	}
};

//A Struct that holds the information about the camera
struct Camera {
	Transform transform;
	float fCameraMovingSpeed = 2.0f;
	float fCameraRotatingSpeed = 5.0f;
};

//A struct that holds the directional light data
struct DirectionalLight {
	Math::Vector3 rotation;
};

std::unordered_map<int /*object_id*/, std::pair< std::string /*Filename / Filepath*/, Transform /*position and rotation data*/>> ObjFiles = {
		{0, { "Models/Box.obj" ,	{Math::Vector3(0.0f, 0.0f, 4.0f), Math::Vector3(0.0f, 0.0f, 0.0f)} }},
		{1, { "Models/Monkey.obj" , {Math::Vector3(3.0f, 0.0f, 5.0f), Math::Vector3(0.0f, 0.0f, 0.0f)} }},
		//{2, { "Models/human_female.obj", {Math::Vector3(-4.0f, 0.0f, 5.0f), Math::Vector3(0.0f, 0.0f, 0.0f)}}},
	//{0, { "Models/fantacy_tree_house.obj" ,	{Math::Vector3(0.0f, 0.0f, 20.0f), Math::Vector3(0.0f, 0.0f, 0.0f)} }},
};
std::unordered_map<int /*object_id*/, Mesh /*Actual mesh*/> GameObjects;

//Our projection matrix
Math::Mat4x4 ProjectionMatrix;

//Our main camera
Camera mainCamera;

//Our Directional Light
//For the time being this engine still only support one Directional Light. In future I plan on Adding support for multiple light sources and multiple light sources types (such as Point Light, Directional Light, Spot Light, etc.)
// TODO : Add support for multiple light sources
// TODO : Add support for multiple light source types
DirectionalLight directoinalLight;

//Pointer to the depth buffer where we store the information about depth values of every pixel / character cell
float* pfDepthBuffer = nullptr;

//Clear DepthBuffer
void ClearDepthBuffer(float* _pfDepthBuffer) {
	memset(_pfDepthBuffer, 0, sizeof(float) * nScreenWidth * nScreenHeight);
}

//Rasterize the triangle 
void RasterizeTriangle(Math::Vector3 p0, 
	Math::Vector3 p1, Math::Vector3 p2,  
	float* _pfDepthBuffer , 
	WCHAR UnicodeCharacter = PIXEL_TYPE::PIXEL_SOLID, 
	WORD Attributes = COLOUR::FG_WHITE) {

	//Sort the points according to the y values of points
	if (p0.y > p1.y) { std::swap(p0, p1); }
	if (p0.y > p2.y) { std::swap(p0, p2); }
	if (p1.y > p2.y) { std::swap(p1, p2); }
	//Now p0 is the point with the lowest y coordinate
	//p2 is the point with the highest y coordinate

	//x and y must be in integers. But for depth calculations we need z in form of floating points
	Math::Vector2i xy_values_of_p0((int)p0.x, (int)p0.y); float z_value_of_p0 = p0.z;
	Math::Vector2i xy_values_of_p1((int)p1.x, (int)p1.y); float z_value_of_p1 = p1.z;
	Math::Vector2i xy_values_of_p2((int)p2.x, (int)p2.y); float z_value_of_p2 = p2.z;

	Math::Vector2i delta_xy_of_p0p2_line = xy_values_of_p2 - xy_values_of_p0; float delta_z_value_of_p0p2_line = z_value_of_p2 - z_value_of_p0;
	Math::Vector2i delta_xy_of_p0p1_line = xy_values_of_p1 - xy_values_of_p0; float delta_z_value_of_p0p1_line = z_value_of_p1 - z_value_of_p0;

	//Draw the first half of the triangle
	if (delta_xy_of_p0p1_line.y) {
		for (int _y = 0; _y < delta_xy_of_p0p1_line.y; _y++) {
			//Get the two x values of the two lines from the _y value

			//Get the x value of p0p2 line (Relative to p0)
			Math::Vector2i xy_values_of_current_point_on_p0p2_line;
			xy_values_of_current_point_on_p0p2_line.y = _y;
			xy_values_of_current_point_on_p0p2_line.x = (int)((float)xy_values_of_current_point_on_p0p2_line.y / (float)delta_xy_of_p0p2_line.y * (float)delta_xy_of_p0p2_line.x);


			//Get the z value of (x_value_of_p0p2_line, _y) point of the line. (Relative to p0)
			float z_value_of_the_current_point_on_p0p2_line = ((float)xy_values_of_current_point_on_p0p2_line.Magnitude() / (float)delta_xy_of_p0p2_line.Magnitude()) * delta_z_value_of_p0p2_line;

			//Get the x value of p0p1 line (Relative to p0)
			Math::Vector2i xy_values_of_current_point_on_p0p1_line;
			xy_values_of_current_point_on_p0p1_line.y = _y;
			xy_values_of_current_point_on_p0p1_line.x = (int)((float)xy_values_of_current_point_on_p0p1_line.y / (float)delta_xy_of_p0p1_line.y * (float)delta_xy_of_p0p1_line.x);


			//Get the z value of (x_value_of_p0p1_line, _y) point of the line. (Relative to p0)
			float z_value_of_the_current_point_on_p0p1_line = ((float)xy_values_of_current_point_on_p0p1_line.Magnitude() / (float)delta_xy_of_p0p1_line.Magnitude()) * delta_z_value_of_p0p1_line;

			//sort the values according to the x values
			if (xy_values_of_current_point_on_p0p1_line.x > xy_values_of_current_point_on_p0p2_line.x) {
				std::swap(xy_values_of_current_point_on_p0p1_line, xy_values_of_current_point_on_p0p2_line);
				std::swap(z_value_of_the_current_point_on_p0p1_line, z_value_of_the_current_point_on_p0p2_line);
			}

			for (int _x = xy_values_of_current_point_on_p0p1_line.x; _x < xy_values_of_current_point_on_p0p2_line.x; _x++) {
				// Z value of the current pixel relative to the p0
				float z_value_of_the_current_pixel = (float)(_x - xy_values_of_current_point_on_p0p1_line.x) / (float)(xy_values_of_current_point_on_p0p2_line.x - xy_values_of_current_point_on_p0p1_line.x) * (z_value_of_the_current_point_on_p0p2_line - z_value_of_the_current_point_on_p0p1_line) + z_value_of_the_current_point_on_p0p1_line;

				//real x
				int x = _x + xy_values_of_p0.x;
				int y = _y + xy_values_of_p0.y;
				float z = z_value_of_the_current_pixel + z_value_of_p0;

				//Finaly draw the pixel if the depth value of that pixel higher than the depth value already there
				if (x >= 0 && x < nScreenWidth && y >= 0 && y < nScreenHeight) {
					if (z > _pfDepthBuffer[x + y * nScreenWidth]) {
						SetPixel(x, y, UnicodeCharacter, Attributes);
						_pfDepthBuffer[x + y * nScreenWidth] = z;
					}
				}

			}
		}
	}
	
	Math::Vector2i delta_xy_of_p1p2_line = xy_values_of_p2 - xy_values_of_p1; float delta_z_value_of_p1p2_line = z_value_of_p2 - z_value_of_p1;

	//Draw the next half of the triangle
	if (delta_xy_of_p1p2_line.y) {
		for (int _y = 0; _y <= delta_xy_of_p1p2_line.y; _y++) {
			//Just like above
			//Get the two x values of the two lines from the _y value

			//Get the x value of p0p2 line (Relative to p0)
			Math::Vector2i xy_values_of_current_point_on_p0p2_line;
			xy_values_of_current_point_on_p0p2_line.y = _y + delta_xy_of_p0p1_line.y;
			xy_values_of_current_point_on_p0p2_line.x = (int)((float)xy_values_of_current_point_on_p0p2_line.y / (float)delta_xy_of_p0p2_line.y * (float)delta_xy_of_p0p2_line.x);

			//Get the z value of (x_value_of_p0p2_line, _y) point of the line. (Relative to p1)
			float z_value_of_the_current_point_on_p0p2_line = ((float)xy_values_of_current_point_on_p0p2_line.Magnitude() / (float)delta_xy_of_p0p2_line.Magnitude()) * delta_z_value_of_p0p2_line - delta_z_value_of_p0p1_line;

			//Make the x value of p0p2 line relative to p1
			xy_values_of_current_point_on_p0p2_line.x -= delta_xy_of_p0p1_line.x;

			//Get the x value of p1p2 line (Relative to p1)
			Math::Vector2i xy_values_of_current_point_on_p1p2_line;
			xy_values_of_current_point_on_p1p2_line.y = _y;
			xy_values_of_current_point_on_p1p2_line.x = (int)((float)xy_values_of_current_point_on_p1p2_line.y / (float)delta_xy_of_p1p2_line.y * (float)delta_xy_of_p1p2_line.x);

			//Get the z value of (x_value_of_p0p1_line, _y) point of the line. (Relative to p1)
			float z_value_of_the_current_point_on_p1p2_line = ((float)xy_values_of_current_point_on_p1p2_line.Magnitude() / (float)delta_xy_of_p1p2_line.Magnitude()) * delta_z_value_of_p1p2_line;

			//sort the values according to the x values
			if (xy_values_of_current_point_on_p1p2_line.x > xy_values_of_current_point_on_p0p2_line.x) {
				std::swap(xy_values_of_current_point_on_p1p2_line, xy_values_of_current_point_on_p0p2_line);
				std::swap(z_value_of_the_current_point_on_p1p2_line, z_value_of_the_current_point_on_p0p2_line);
			}


			for (int _x = xy_values_of_current_point_on_p1p2_line.x; _x < xy_values_of_current_point_on_p0p2_line.x; _x++) {
				// Z value of the current pixel relative to the p0
				float z_value_of_the_current_pixel = (float)(_x - xy_values_of_current_point_on_p1p2_line.x) / (float)(xy_values_of_current_point_on_p0p2_line.x - xy_values_of_current_point_on_p1p2_line.x) * (z_value_of_the_current_point_on_p0p2_line - z_value_of_the_current_point_on_p1p2_line) + z_value_of_the_current_point_on_p1p2_line;

				//real x
				int x = _x + xy_values_of_p1.x;
				int y = _y + xy_values_of_p1.y;
				float z = z_value_of_the_current_pixel + z_value_of_p1;

				if (x >= 0 && x < nScreenWidth && y >= 0 && y < nScreenHeight) {
					if (z > _pfDepthBuffer[x + y * nScreenWidth]) {
						SetPixel(x, y, UnicodeCharacter, Attributes);
						_pfDepthBuffer[x + y * nScreenWidth] = z;
					}
				}

			}

		}
	}
}

bool OnStart() {

	//Alocate the memory for the pfDepthBuffer
	pfDepthBuffer = new float[nScreenWidth * nScreenHeight]; // Depth buffer must be the same size as our screen buffer
	//We must delete the pfDepthBuffer in our OnDestroy() function

	// Set up the projection matrix
	ProjectionMatrix = Math::Mat4MakeProjectionMatrix((float)nScreenWidth / (float)nScreenHeight, 90.0f, 0.05f, 1000.0f);

	//Set the position and the transformation of the main camera to zero vectors
	mainCamera.transform.position = Math::Vector3(0.0f, 2.0f, 0.0f);
	mainCamera.transform.rotation = Math::Vector3(0.0f, 0.0f, 0.0f);

	//Set the camera moving speed to 2.0 unit per second;
	mainCamera.fCameraMovingSpeed = 2.0f;

	//Set the camera rotating spped to 5.0 radian per second
	mainCamera.fCameraRotatingSpeed = 3.0f;

	//Set the directional light rotation to -45.0f deg around x axis, -45.0f deg around y axis and finaly -45.0f deg around z axis
	directoinalLight.rotation = Math::Vector3(
		Math::fDegToRadian( 45.0f),
		Math::fDegToRadian(-45.0f),
		Math::fDegToRadian( 0.0f)
	);

	//Load object models
	for (const std::pair<int, std::pair<std::string, Transform>>& obj : ObjFiles) {
		Mesh gameObject(obj.second.first, obj.second.second);
		GameObjects.insert({ obj.first, gameObject });
	}

	//Now the GameObject unordered map contains the meshes we specified in the ObjFiles map

	return true;
}

bool OnUpdate(float dt) {

	//Clear the screen to black before drawing anything
	ClearScreen(PIXEL_TYPE::PIXEL_SOLID ,COLOUR::FG_YELLOW);
	//Clear the depdth buffer alongside with the screen buffer
	ClearDepthBuffer(pfDepthBuffer);

	//Since we haven't implemented any proper way of gathering keyboard inputs I'm going to use Windows's GetAsyncKeyState() function to gather the keyboard input
	//GetAsyncKeyState() function takes a virtual key code as the argument and returns a short. According to the https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
	//the most significant bit of the returned short is set if the key is down. So for now that's all we need to know
	if (GetAsyncKeyState(KEY_CODE::W) & 0x8000) {
		//Move forward relative to the camera
		Math::Vector3 move_direction = Math::VEC3_Forward * Math::Mat3MakeRotationZXY(mainCamera.transform.rotation);
		mainCamera.transform.position += move_direction * mainCamera.fCameraMovingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::S) & 0x8000) {
		//Move backward relative to the camera
		Math::Vector3 move_direction = Math::VEC3_Forward * Math::Mat3MakeRotationZXY(mainCamera.transform.rotation);
		mainCamera.transform.position -= move_direction * mainCamera.fCameraMovingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::D) & 0x8000) {
		//Move Right relative to the camera
		Math::Vector3 move_direction = Math::VEC3_Right * Math::Mat3MakeRotationZXY(mainCamera.transform.rotation);
		mainCamera.transform.position += move_direction * mainCamera.fCameraMovingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::A) & 0x8000) {
		//Move Left relative to the camera
		Math::Vector3 move_direction = Math::VEC3_Right * Math::Mat3MakeRotationZXY(mainCamera.transform.rotation);
		mainCamera.transform.position -= move_direction * mainCamera.fCameraMovingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::Q) & 0x8000) {
		//move Up relative to the camera
		Math::Vector3 move_direction = Math::VEC3_Up * Math::Mat3MakeRotationZXY(mainCamera.transform.rotation);
		mainCamera.transform.position += move_direction * mainCamera.fCameraMovingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::E) & 0x8000) {
		//move Down relative to the camera
		Math::Vector3 move_direction = Math::VEC3_Up * Math::Mat3MakeRotationZXY(mainCamera.transform.rotation);
		mainCamera.transform.position -= move_direction * mainCamera.fCameraMovingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::L) & 0x8000) {
		//Rotate clockwise around y axis of the camera
		mainCamera.transform.rotation.y += mainCamera.fCameraRotatingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::J) & 0x8000) {
		//Rotate counter-clockwise around y axis of the camera
		mainCamera.transform.rotation.y -= mainCamera.fCameraRotatingSpeed * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::NUMPAD8) & 0x8000) {
		//Rotate clockwise around x axis of the directoinalLight
		directoinalLight.rotation.x -= 1.0f * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::NUMPAD2) & 0x8000) {
		//Rotate counter-clockwise around x axis of the directoinalLight
		directoinalLight.rotation.x += 1.0f * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::NUMPAD6) & 0x8000) {
		//Rotate clockwise around y axis of the directoinalLight
		directoinalLight.rotation.y += 1.0f * dt;
	}
	if (GetAsyncKeyState(KEY_CODE::NUMPAD4) & 0x8000) {
		//Rotate counter-clockwise around y axis of the directoinalLight
		directoinalLight.rotation.y -= 1.0f * dt;
	}

	//Rotate the cube around its x axis and z axis
	GameObjects[0].transform.rotation.x += 1.0f * dt;
	GameObjects[0].transform.rotation.z += 1.0f * dt;

	//Rendering routine
	//Loop through the elements of the GameObjects map
	for (const std::pair<int, Mesh>& GameObject : GameObjects) {
		//GameObject.second contains the actual mesh
		//GameObject.first conatains the id of that mesh. We don't need that id in this loop. But It is useful if we needed to make changes to the position or the rotation of that particuler object. We can simply get the mesh by using that id as the key from GameObjects map
		std::vector<Math::Vector4> vec4TransformedVertices;
		for (const Vertex& vertex : GameObject.second.vertices) {
			Math::Vector4 transformedVertex =
				Math::Vector4(vertex.position) * // vertex.position is in object space. Meaning, It's relative to the object's origin
				Math::Mat4MakeRotationZXY(GameObject.second.transform.rotation) * // We rotate the vertex.position according to the object's rotation information in object space
				Math::Mat4MakeTranslation(GameObject.second.transform.position) * // Convert the position from Object space to world space by adding the object position to the vertex position
				Math::Mat4MakeTranslationInv(mainCamera.transform.position) * 
				Math::Mat4MakeRotationZXYInv(mainCamera.transform.rotation) * // Get the position of the vertex in CamaraSpcae by translating and rotating the vertex by camera position and rotation
				ProjectionMatrix; // Finaly Multiply the position of the vertex so we can convert it to the screen spcae


			//This is just a quick fix alternative to clipping. Once triangle clipping algorithm implemented this check won't be neccesory 
			if (transformedVertex.w > 1.0f) {
				// Get the position of the vertex in normalized screen space by deviding the vector by its w component
				transformedVertex /= transformedVertex.w;
				// Finaly convert it to real screen cordinates
				transformedVertex.x = (transformedVertex.x * 0.5f + 0.5f) * (float)nScreenWidth;
				transformedVertex.y = (1.0f - (transformedVertex.y * 0.5f + 0.5f)) * (float)nScreenHeight;
			}
			// Push the final transformed vertex position to vec4TransformedVertices vector
			vec4TransformedVertices.push_back(transformedVertex);
		}

		for (std::size_t i = 0; i < GameObject.second.indices.size(); i += 3) {

			//Get the right points of the right triangle from vec4TransformedVertices
			Math::Vector4 p0_in_screen_space = vec4TransformedVertices[GameObject.second.indices[i]];
			Math::Vector4 p1_in_screen_space = vec4TransformedVertices[GameObject.second.indices[i + 1]];
			Math::Vector4 p2_in_screen_space = vec4TransformedVertices[GameObject.second.indices[i + 2]];

			//This is just a quick fix alternative to clipping. Once triangle clipping algorithm implemented this check won't be neccesory 
			// TODO : Implement a triangle clipping algorithm
			if (p0_in_screen_space.w == 1.0f && p1_in_screen_space.w == 1.0f && p2_in_screen_space.w == 1.0f) {

				//Get the normal of this particular triangle (in world space)
				Math::Vector3 normal = GameObject.second.normals[(int)(i / 3)];

				//Convert the normal from Object space to world space by rotating it by object's rotation
				normal = normal * Math::Mat3MakeRotationZXY(GameObject.second.transform.rotation);
				normal.Normalize();

				//Normal of the object relative to the main camera ( This is for testing purposes only )
				Math::Vector3 normal_relative_to_mainCamera = normal * Math::Mat3MakeRotationZXYInv(mainCamera.transform.rotation);

				//Get the vertex of the triangle relative to the camera (Vector4)
				Math::Vector4 vec4_vertex_of_the_triangle_rel_to_mainCamera = Math::Vector4(GameObject.second.vertices[GameObject.second.indices[i + 1]].position) * Math::Mat4MakeRotationZXY(GameObject.second.transform.rotation) * Math::Mat4MakeTranslation(GameObject.second.transform.position) * Math::Mat4MakeTranslationInv(mainCamera.transform.position) * Math::Mat4MakeRotationZXYInv(mainCamera.transform.rotation);

				//Turn the above vertex position to vector3 So we can apply this to Math::Vec3DotProduct() function below
				Math::Vector3 vertex_of_the_triangle_rel_to_mainCamera(
					vec4_vertex_of_the_triangle_rel_to_mainCamera.x,
					vec4_vertex_of_the_triangle_rel_to_mainCamera.y,
					vec4_vertex_of_the_triangle_rel_to_mainCamera.z
				);


				//Directional Light direction
				//We could pre calcultate this instead of recalculating this every frame
				//But this way it gets a more dynamic look. I mean if you modified the rotation of the directional light at runtime pre calculated results won't give you realtime results
				Math::Vector3 directional_light_direction = Math::VEC3_Forward * Math::Mat3MakeRotationZXY(directoinalLight.rotation);
				directional_light_direction.Normalize();

				//Since we are calculating the dot product of 2 normalized vectors dot product will be between -1 and 1. We have to normalize that before feeding it into the ClassifyPixel() function to determine the color of the pixel
				float dot_product_of_the_triangle_normal_and_light_direction = Math::Vec3DotProduct(normal, directional_light_direction);

				//Normalize the dot_product_of_the_triangle_normal_and_light_direction
				dot_product_of_the_triangle_normal_and_light_direction = dot_product_of_the_triangle_normal_and_light_direction * 0.5f + 0.5f;

				

				CHAR_INFO pixel_info = ClassifyPixel(dot_product_of_the_triangle_normal_and_light_direction);

				// Only draw the triangle if the dot product of the vertex_of_the_triangle_rel_to_mainCamera vector and normal_relative_to_mainCamera vector is equal or less than zero. \
				//This is for backface culling. If you want to know about why we do this. Google "How does backface culling work in computer graphics) 

				// TODO : Right now Getting the dot product of the vertex_of_the_triangle_rel_to_mainCamera and normal_relative_to_mainCamera to determine to cull a face or not doesn't work very well. 
				//So I have skipped the backface culling part for now. I may fix it later. Right now back face culling doesn't make any visual difernce because we already have implemented the depth buffer. 
				//It certenly gives a perfomance improvement so I will fix it. Until then no backface culling!

				//if (Math::Vec3DotProduct(vertex_of_the_triangle_rel_to_mainCamera, normal_relative_to_mainCamera) <= 0.0f) {
					//Finaly draw the driangle in wireframe mode using DrawTriangle() function
					//DrawTriangle( Math::Vector2i((int)p0_in_screen_space.x, (int)p0_in_screen_space.y), Math::Vector2i((int)p1_in_screen_space.x, (int)p1_in_screen_space.y), Math::Vector2i((int)p2_in_screen_space.x, (int)p2_in_screen_space.y) );

					//Finaly Rasterize the triangle
				RasterizeTriangle(
					Math::Vector3(p0_in_screen_space.x, p0_in_screen_space.y, 1.0f / p0_in_screen_space.z),
					Math::Vector3(p1_in_screen_space.x, p1_in_screen_space.y, 1.0f / p1_in_screen_space.z),
					Math::Vector3(p2_in_screen_space.x, p2_in_screen_space.y, 1.0f / p2_in_screen_space.z),
					pfDepthBuffer,
					pixel_info.Char.UnicodeChar,
					pixel_info.Attributes
				);
				//}
			}
		}
	}
	return true;
}

void OnDestroy() {
	//Delete the float array we created.
	if (pfDepthBuffer) delete[] pfDepthBuffer;
}
