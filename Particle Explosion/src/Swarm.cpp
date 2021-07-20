/*
 * Swarm.cpp
 *
 *  Created on: Jul 20, 2021
 *      Author: pavlo
 */

#include "Swarm.h"

namespace caveofprogramming {

Swarm::Swarm(): lastTime(0) {
	// TODO Auto-generated constructor stub

	m_pParticles = new Particle[NPARTICLES]; // This will allocate memory and fill it with a
	// bunch of particle objects.

}

Swarm::~Swarm() {
	// TODO Auto-generated destructor stub

	delete [] m_pParticles;
}

void Swarm::update(int elapsed) {

	int interval = elapsed - lastTime; // to be used to proportion the particle "speed" based on
	// how quickly the PC can run the game loop.

	for (int i = 0; i < Swarm::NPARTICLES; i++){
		m_pParticles[i].update(interval); // See method particle::update() in Particle.cpp --> Updates particle position on screen.
	}

	lastTime = elapsed;
}

} /* namespace caveofprogramming */
