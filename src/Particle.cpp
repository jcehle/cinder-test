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

Particle::Particle( Vec2f loc)
{
    mLoc = loc;
    mDir = Rand::randVec2f();
    mDirToCursor = Vec2f::zero();
    mVel = Rand::randVec2f()*2;
    mVelDecay = Rand::randFloat(0.9f, 0.99f);
    mRadius = 2.0f;
    mScale = 3.0f;
    mColor = Color( 1.0f, 1.0f, 1.0f);
    
    mIsDead = false;
    mAge = 0;
    mLifeSpan = Rand::randInt(50, 150);
}

Particle::Particle ( Vec2f loc, Vec2f vel, ColorA col = ColorA(1.0f, 1.0f, 1.0f) )
{
    mLoc = loc;
    mVel = vel;
    
    mDir = Rand::randVec2f();
    mDirToCursor = Vec2f::zero();
    mVelDecay = Rand::randFloat(0.9f, 0.99f);
    mRadius = 2.0f;
    mScale = 3.0f;
    mColor = col;
    
    mIsDead = false;
    mAge = 0;
    mLifeSpan = Rand::randInt(50, 150);
}

void Particle::update (const Vec2i &mouseLoc)
{
    mAge++;
    mLoc += mVel;
    mVel *= mVelDecay;
    
    float agePer = 1.0f - ( mAge / (float)mLifeSpan );
    mRadius = 3.0f * agePer;
    
    
    if(mAge > mLifeSpan)
        mIsDead = true;
}

void Particle::update ( const Channel32f &channel, const Vec2i &mouseLoc)
{
    mAge++;
    mLoc += mVel;
    mVel *= mVelDecay;
    
    float agePer = 1.0f - ( mAge / (float)mLifeSpan );
    mRadius = 3.0f * agePer;
    
    
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
    

    gl::color(mColor);
    gl::drawSolidCircle(mLoc + mDirToCursor, mRadius);
    
    
    
    
}