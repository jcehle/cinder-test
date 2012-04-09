#ifndef chapter3_Particle_h
#define chapter3_Particle_h

#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"

#include <vector>


class Particle {
  
  public:
    Particle();
    Particle( ci::Vec2f loc);
    Particle( ci::Vec2f loc, ci::Vec2f vel, ci::ColorA);
    
    
    void update( const ci::Vec2i &mouseLoc);
    void update( const ci::Channel32f &channel, const ci::Vec2i &mouseLoc);
    
    void draw();
    
    ci::Vec2f mLoc;
    ci::Vec2f mLocPer;
    ci::Vec2f mDir;
    ci::Vec2f mDirToCursor;
    ci::Vec2f mCursorPos;
    
    ci::Vec2f mVel;
    float mVelDecay;
    
    int mAge;
    int mLifeSpan;
    bool mIsDead;
    
    
    float mRadius;
    float mScale;
    ci::Color mColor;
    
    
};



#endif
