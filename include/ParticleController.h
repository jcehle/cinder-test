#ifndef chapter3_ParticleController_h
#define chapter3_ParticleController_h

#include "cinder/Channel.h"
#include "Particle.h"
#include <list>

class ParticleController
{
  public:
    ParticleController();
    ParticleController( int res);
    void update( const ci::Channel32f &channel, const ci::Vec2i &mouseLoc);
    void draw();
    void addParticle( int xRes, int yRes, int res);
    void addParticles (int amt);
    void addParticles (int amt, ci::Vec2f pos);
    void removeParticles (int amt);
    
    std::list<Particle> mParticles;
    
    int mXRes, mYRes;
    
};


#endif
