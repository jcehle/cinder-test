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
}



void Particle::update ( const Channel32f &channel, const Vec2i &mouseLoc)
{
    mCursorPos = mouseLoc;
    mDirToCursor = mouseLoc - mLoc;
    
    float time = app::getElapsedSeconds() * 4.0f;
    float dist = mDirToCursor.length() * 0.05f;
    float sinOffset = sin( dist - time ) * 100.0f;
    
    mDirToCursor.safeNormalize();
    
    Vec2f newLoc = mLoc + mDirToCursor * sinOffset;
    newLoc.x = constrain( newLoc.x, 0.0f, channel.getWidth() - 1.0f );
    newLoc.y = constrain( newLoc.y, 0.0f, channel.getHeight() - 1.0f);
    
    
    
    float gray = channel.getValue( newLoc );
    mColor = Color( gray, gray, gray );
    mRadius = mScale;

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
    
    gl::color(mColor);
    Rectf rect ( mLoc.x, mLoc.y, mLoc.x + mRadius, mLoc.y + mRadius );
    gl::drawSolidRect(rect);
    
    //gl::drawSolidCircle(mLoc + mDirToCursor * 0.2f, mRadius);
    
    
    
    
}