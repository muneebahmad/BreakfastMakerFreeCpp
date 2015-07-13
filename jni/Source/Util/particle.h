/*
 * particle.h
 *
 *  Created on: 26-Jun-2015
 *      Author: muneebahmad
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <WiEngine.h>

class ParticleLiquid : public wyQuadParticleSystem {
private:

public:
	ParticleLiquid();
	~ParticleLiquid();
	static ParticleLiquid* make();
}; /** end class ParticleLiquid */

class ParticleSun : public wyQuadParticleSystem {
public:
	ParticleSun();
	~ParticleSun();
	static ParticleSun* make();
};/** end class ParticleSun */

#endif /* PARTICLE_H_ */
