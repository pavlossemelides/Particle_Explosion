/*
 * Screen.cpp
 *
 *  Created on: Jul 20, 2021
 *      Author: pavlo
 */

#include "Screen.h"
#include <cstring>
#include <iostream>
using namespace std;

namespace caveofprogramming {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_buffer2(NULL) {

}

bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		return false;
	}

	m_window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC); //flag to ensure renderer is in sync with screen refresh rate.
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT); //The thing our renderer is going to render. This is where we provide pixel information.
	// Second argument specifies use of 8 bits (or 1 byte) for each color (RGB) for each pixel(lookup SDL_PIXELFORMAT_RGBA8888 for more info on how pixels are colored.); 8 bits we can use 2^8 shades of each color.

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer); //incase renderer was created but texture couldn't.
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //32 bit integer type. Related to use of 32 bits (4x8) to color each pixel.
	//new keyword allocates memory to create an array of 32-bit integers.
	// buffer is array to keep all information for pixels.
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));	//USEFUL FUNCTION: allows you to set memory with a particular value; here with zeroes (i.e. black color).
	//set each byte in buffer to 255 or whatever.
	//could input 0xFF (hexadecimal convention signified by 0x) instead of 255.
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}

void Screen::boxBlur() {
	// Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer.
	Uint32 *temp = m_buffer;
	m_buffer = m_buffer2;
	m_buffer2 = temp; // not sure why we need these 3 lines and buffer2; maybe future use.

	for(int y = 0; y < SCREEN_HEIGHT; y++){
		for(int x=0; x < SCREEN_WIDTH; x++){


			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for(int row=-1; row <= 1; row++){
				for(int col=-1; col <= 1; col++){
					int currentX = x + col;
					int currentY = y + row;

					if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) { // make sure pixel is inside screen.
						Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX]; //Given pixel coords in x,y; go find it in buffer array (in index form) and retrieve color.

						Uint8 red = color >> 24; //8-bit int ensures we only get info we need. Only need the 8 bits at trail end of color, after necessary bit-shifting has taken place.
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						// So for each pixel chosen by x,y outer loop, we loop around neighboring pixels (and chosen pixel itself) and retrieve their colors.
						// We then add up the constituent colors from all 9 pixels, as seen below.
						// After doing so, for each constituent color, we average the addition from the 9 pixels and assign the resulting color palette to the central/chosen pixel (x,y loop).
						//In computer graphics this is called BOX BLUR.

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;

			setPixel(x, y, red, green, blue);
		}
	}
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) { //check if drawn pixels are off the screen since numbering begins from 0!
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer[(y * SCREEN_WIDTH) + x] = color;// y * SCREEN_WIDTH is row selector and x is column selector.
	//the above expression tranforms x,y coords into buffer index.
}

void Screen::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32)); //copying pixels (texture) to our buffer.
	SDL_RenderClear(m_renderer); //clear renderer.
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); //passing buffer to renderer.
	SDL_RenderPresent(m_renderer); //present renderer to the window/screen.
}

bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) { //SDL_PollEvent fills in event object if event takes place.
		//SDL_PollEvent returns true as long as there is an event waiting
		//to be processed.  So keeps looping as long as there are events in queue.
		if (event.type == SDL_QUIT) {
			return false; //if I press X on window-->SDL_QUIT and quit while loop.
		}
	}
	return true;
}

void Screen::close() {
	delete[] m_buffer; //deallocate;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window); //Destroy object window which is type Window.
	SDL_Quit(); //clean up any resources that SDL is using.
}

}
