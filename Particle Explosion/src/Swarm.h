/*
 * Swarm.h
 *
 *  Created on: Jul 20, 2021
 *      Author: pavlo
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace caveofprogramming {

class Swarm {
public:
	const static int NPARTICLES = 5000;
private:
	Particle * m_pParticles;// Object-pointer.  Once we set it we dont want to change it so make it const. see line 25.
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();

	const Particle * const getParticles() { return m_pParticles;} // pointer to a particle
	// that's const.
	void update(int elapsed);
};



} /* namespace caveofprogramming */

#endif /* SWARM_H_ */
