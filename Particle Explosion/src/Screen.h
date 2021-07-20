/*
 * Screen.h
 *
 *  Created on: Jul 20, 2021
 *      Author: pavlo
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace caveofprogramming {

class Screen {
public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;
	Uint32 *m_buffer2;

public:
	Screen();
	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 blue, Uint8 green); // unsigned 8-bit int, AKA unsigned char.
	bool processEvents();
	void close();
	void boxBlur();

};
}


#endif /* SCREEN_H_ */
