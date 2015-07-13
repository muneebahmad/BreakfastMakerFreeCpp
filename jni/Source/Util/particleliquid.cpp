/*
 * particleliquid.cpp
 *
 *  Created on: 26-Jun-2015
 *      Author: muneebahmad
 */

#include "particle.h"

ParticleLiquid::ParticleLiquid() : wyQuadParticleSystem(1000) {
	setDuration(-1.0f);
	setParticleGravity(0.0f, 70.0f);
	setDirectionAngleVariance(-90.0f, 7.0f);
	setSpeedVariance(130.0f, 30.0f);
	setRadialAccelerationVariance(0.0f, 1.0f);
	setTangentialAccelerationVariance(0.0f, 1.0f);
	setLifeVariance(1.5, 0.0f);
	setStartSizeVariance(5.0f, 6.0f);
	setEndSizeVariance(5.0f, 6.0f);
	setEmissionRate(getMaxParticles() / getLife());
	setStartColorVariance(0.9f, 0.9f, 0.9f, 1.0f, 0.0f, 0.0f, 0.10, 0.0f);
	setEndColorVariance(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	setTexture(wyTexture2D::make("art/snow.png"));
	setBlendAdditive(false);
	setAutoRemoveOnFinish(true);
}

ParticleLiquid::~ParticleLiquid() {

}

ParticleLiquid* ParticleLiquid::make() {
	return new ParticleLiquid();
}
