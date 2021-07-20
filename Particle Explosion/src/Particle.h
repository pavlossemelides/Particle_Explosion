/*
 * Particle.h
 *
 *  Created on: Jul 20, 2021
 *      Author: pavlo
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace caveofprogramming {

struct Particle {// by default in a class, member vars are private, whereas in struct they are public.
	double m_x;
	double m_y;
private:
	double m_speed;
	double m_direction; //switching to polar coordinate system.

public:
	Particle();
	virtual ~Particle();
	void update(int interval);
private:
	void init();
};

} /* namespace caveofprogramming */

#endif /* PARTICLE_H_ */
