#include "Time.hpp"
using namespace std;

Time::Time() {
	Startime = 0;
	hour = minute = second = 0;
}

void Time::free() {
	TimeInScreen.free();
}

string twodigits(int a) {
	string s = to_string(a);
	if (s.length() == 1) {
		s = '0' + s;
	}
	return s;
}

bool Time::loadtime(SDL_Renderer* gRenderer, TTF_Font* gFont) {
	TimeInScreen.free();
	SDL_Color color = { 255, 255, 255 };
	string s = twodigits(hour) + ':' + twodigits(minute) + ':' + twodigits(second);
	return TimeInScreen.loadFromRenderedText(s, color, gFont, gRenderer);
}

void Time::render(int x, int y, SDL_Renderer* gRenderer) {
	TimeInScreen.render(x - TimeInScreen.getWidth() / 2, y - TimeInScreen.getHeight() / 2, gRenderer);
}

void Time::ResetTimer() {
	Startime = SDL_GetTicks();
	hour = 0;
	minute = 0;
	second = 0;
}

void Time::transfer() {
	int t = SDL_GetTicks() - Startime;
	t /= 1000;
	hour = t / 3600;
	minute = (t % 3600) / 60;
	second = t % 60;
}