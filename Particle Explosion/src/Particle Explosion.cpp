//============================================================================
// Name        : Particle.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include <cstring>
#include <math.h>
#include "Screen.h"
#include <stdlib.h>
#include <ctime>
#include "Swarm.h"
#include "Particle.h"
using namespace std;
using namespace caveofprogramming;

int main(int argc, char *argv[]) {

	srand(time(NULL));

	Screen screen;

	if (screen.init() == false) {
		cout << "Error initializing SDL." << endl;
	}

	Swarm swarm;

	while (true) { //"game loop" to prevent window from opening and closing instantaneosly.

		// Update particles

		// Draw particles

		int elapsed = SDL_GetTicks(); // Returns the number of miliseconds since the program started.

		swarm.update(elapsed); // Swarm constructor creates object array of class Particle. swarm.update() then calls particle::update() method to update particle position.

		unsigned char green = (unsigned char) ((1 + sin(elapsed * 0.0001)) * 128); // a lot of miliseconds pass between iterations of the game loop,
		// so that returned value from sin each time differs kinda a lot from previous. To get
		// around this multiply 'elapsed' by a number <1 to make output smoother.
		// Use unsigned char cause even if function returned 256, char only goes up to 255.
		// C++ discards any decimal supplied to our char 'green' i.e. 233.566-->233.
		// But can double cast our function to make clear what we are doing.
		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.00023)) * 128);
		unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

		const Particle *const pParticles = swarm.getParticles(); // See swarm.h

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i]; //getting individual particles one by one.

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;
			int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2; // Change from height to width to create circular and not oval explosion pattern.

			screen.setPixel(x, y, green, red, blue);
		}

		screen.boxBlur();

		//Draw the screen
		screen.update(); // Uses SDL functions to generate new screen each time. buffer is key input here.
		// Have a look at these to understand use of texurer, renderer and buffer arrays.

		// Check for messages/events: if user provides any sort of input.
		if (screen.processEvents() == false) {
			break; //break applies to outer loop (i.e. game loop)!
		}

	}

	screen.close();

	return 0;
}

