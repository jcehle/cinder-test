#include "cinder/gl/gl.h"
#include "Particle.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include <iostream>

using namespace ci;

Particle::Particle()
{
    
}

Particle::Particle( ci::Vec2f loc)
{
    mLoc = loc;
    mDir = Rand::randVec2f();
}



void Particle::update ( const ci::Channel32f &channel, const ci::Vec2i &mouseLoc)
{
    
}

void Particle::draw()
{
    gl::drawSolidCircle(mLoc, mRadius);
}