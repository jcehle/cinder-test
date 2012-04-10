#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Perlin.h"


using namespace ci;
using namespace ci::app;
using std::list;

ParticleController::ParticleController()
{
}

ParticleController::ParticleController ( int res)
{
    mXRes = app::getWindowWidth() / res;
    mYRes = app::getWindowHeight() / res;
    
    console() << "xres: " << mXRes << std::endl;
    
    int pCount = 0;
    for (int y = 0; y<mYRes; y++) 
    {
        for (int x = 0; x < mXRes; x++)
        {
            addParticle(x, y, res);
            pCount++;
        }
    }
    console() << "total particles: " << pCount << std::endl;
}

void ParticleController::setSampleSurface(const ci::Surface &surf)
{
    sampleSurface = surf;
}

void ParticleController::update( const Vec2i &mouseLoc)
{
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); )
    {
        if(p->mIsDead)
        {
            p = mParticles.erase( p );
        }
        else
        {
            p->update( mouseLoc);   
            ++p;
        }
    } 
}


void ParticleController::update(const Perlin &perlin, const Channel32f &channel, const Vec2i &mouseLoc)
{
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); )
    {
        if(p->mIsDead)
        {
            p = mParticles.erase( p );
        }
        else
        {
            p->update(perlin, channel, mouseLoc);   
            ++p;
        }
    }
}

void ParticleController::draw()
{
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p)
    {
        p->draw();
    }
}

void ParticleController::addParticle(int xi, int yi, int res)
{
    float x = ( xi + 0.5f) * (float)res;
    float y = ( yi + 0.5f) * (float)res;
    mParticles.push_back( Particle( Vec2f(x, y)));
}

void ParticleController::addParticles( int amt)
{
    for (int i=0; i<amt; i++ )
    {
        float x = Rand::randFloat( app::getWindowWidth() );
        float y = Rand::randFloat( app::getWindowHeight() );
        mParticles.push_back( Particle (Vec2f( x, y )));
    }
}

void ParticleController::addParticles(int amt, const Vec2f &pos)
{
    for (int i=0; i<amt; i++) {
       // float x = pos.x + Rand::randInt( 10 );
       // float y = pos.y + Rand::randInt( 10 );
       // mParticles.push_back( Particle( Vec2f( x,y )));
        
        //more clever
        Vec2f rand = Rand::randVec2f() * 10.0f;
        mParticles.push_back(Particle ( rand + pos ));
    }
}

void ParticleController::addParticles(int amt, const Vec2f &pos, const Vec2f &mouseVel)
{
    for (int i=0; i<amt; i++)
    {
        Vec2f rand = Rand::randVec2f() * 10.0f;
        Vec2f particlePosition = pos + rand;
        float velDamp = Rand::randFloat(0.1f, 0.5f);
        ColorA pColor = sampleSurface.getPixel(particlePosition);
        mParticles.push_back( Particle(particlePosition, mouseVel * velDamp, pColor));
    }
}


void ParticleController::removeParticles(int amt)
{
    for ( int i=0; i<amt; i++ )
    {
        mParticles.pop_back();
    }
}

