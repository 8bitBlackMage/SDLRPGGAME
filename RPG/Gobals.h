#pragma once
//defines consts for game 

namespace Globals {
	const int Width = 640;
	const int Height = 480;
	const int TScale = 32;
	const int FPS = 60;
}
struct vector2 {

	int x,  y;
	vector2(): x(0),y(0){}
	vector2(int x, int y) :x(x), y(y) {}
};

struct vector2f {

	float x, y;
	vector2f() : x(0), y(0) {}
	vector2f(float x, float y) :x(x), y(y) {}
};


