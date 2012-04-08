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
    
}



void Particle::update ( const Channel32f &channel, const Vec2i &mouseLoc)
{
    mCursorPos = mouseLoc;
    mDirToCursor = mouseLoc - mLoc;
    mDirToCursor.safeNormalize();
    
    
    std::cout << "wtf: " << channel << std::endl;
   // mRadius = channel.getData( mLoc ) * mScale;
}

void Particle::draw()
{
    gl::color ( Color( 1.0f, 1.0f, 1.0f )); 
    float arrowLength = 15.0f;
    Vec3f p1( mLoc, 0.0f );
    Vec3f p2 ( mLoc + mDirToCursor * arrowLength, 0.0f);
    float headLength = 6.0f;
    float headRadius = 3.0f;
    gl::drawVector(p1, p2, headLength, headRadius);
    //gl::drawSolidCircle(mLoc, mRadius);

    //gl::drawLine(mLoc, mCursorPos);
    
}