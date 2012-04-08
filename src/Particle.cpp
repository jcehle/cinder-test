#include "cinder/gl/gl.h"
#include "Particle.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/app/AppBasic.h"
#include <iostream>

using namespace ci;

Particle::Particle()
{
    
}

Particle::Particle( ci::Vec2f loc)
{
    mLoc = loc;
    mDir = Rand::randVec2f();
    mDirToCursor = Vec2f::zero();
    mVel = 0.0f;
    mRadius = 2.0f;
    mScale = 3.0f;
    mColor = Color( 1.0f, 1.0f, 1.0f);
    
    mIsDead = false;
    mAge = 0;
    mLifeSpan = 100;
}



void Particle::update ( const Channel32f &channel, const Vec2i &mouseLoc)
{
    mAge++;
    if(mAge > mLifeSpan)
        mIsDead = true;
}

void Particle::draw()
{
 //DRAWING VECOTR   
 //   gl::color ( Color( 1.0f, 1.0f, 1.0f )); 
 //   float arrowLength = 15.0f;
 //   Vec3f p1( mLoc, 0.0f );
 //   Vec3f p2 ( mLoc + mDirToCursor * arrowLength, 0.0f);
 //   float headLength = 6.0f;
 //   float headRadius = 3.0f;
 //   gl::drawVector(p1, p2, headLength, headRadius);
    

    
    gl::drawSolidCircle(mLoc + mDirToCursor, mRadius);
    
    
    
    
}