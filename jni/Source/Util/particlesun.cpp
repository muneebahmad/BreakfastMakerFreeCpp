/*
 * particlesun.cpp
 *
 *  Created on: 26-Jun-2015
 *      Author: muneebahmad
 */

#include "particle.h"

ParticleSun::ParticleSun() : wyQuadParticleSystem(350) {
	setBlendAdditive(true);
	setDuration(PARTICLE_DURATION_INFINITY);
	setDirectionAngleVariance(90, 360);
	setLifeVariance(1.0f, 0.5f);
	setSpeedVariance(20, 5);
	setStartSizeVariance(30.0f, 10.0f);
	setEmissionRate(getMaxParticles() / getLife());
	setStartColorVariance(0.76f, 0.25f, 0.12f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	setEndColorVariance(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	setTexture(wyTexture2D::make("art/fire.png"));
}

ParticleSun::~ParticleSun() {

}

ParticleSun* ParticleSun::make() {
	return new ParticleSun();
}


