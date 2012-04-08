#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

#define RESOLUTION 20


using namespace ci;
using namespace ci::app;


class chapter3App : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
    void keyDown ( KeyEvent event );
   // void mouseMove ( MouseEvent event );
   // void mouseDrag ( MouseEvent event );
	void setup();
    void mouseMove ( MouseEvent event );
    void mouseDrag ( MouseEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Channel32f mChannel;
    gl::Texture mTexture;
    
    Vec2i mMouseLoc;
    
    ParticleController mParticleController;
    
    bool mDrawParticles;
    bool mDrawImage;
    
    
};

void chapter3App::prepareSettings(Settings *settings)
{
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f);
}

void chapter3App::keyDown( KeyEvent event )
{
    if (event.getChar() == '1' )
    {
        mDrawImage = !mDrawImage;
    }
    else if( event.getChar() == '2' )
    {
        mDrawParticles = !mDrawParticles;
    }
    else if( event.getCode() == KeyEvent::KEY_RIGHT )
    {
        console() << " well key r pushed too fecker " << std::endl;
        Color myColor( 1.0f, 0.5f, 0.25f);
        console() << " here is the col " << myColor << std::endl;
    }
}


void chapter3App::mouseMove(MouseEvent event)
{
    mMouseLoc = event.getPos(); 
}

void chapter3App::mouseDrag(MouseEvent event)
{
    mouseMove(event);
}



void chapter3App::setup()
{
    Url url( "http://libcinder.org/media/tutorial/paris.jpg" );
    mChannel = Channel32f ( loadImage ( loadUrl( url )));
    mTexture = mChannel;
    
    mParticleController = ParticleController( RESOLUTION );
    
    mMouseLoc = Vec2i( 0, 0 );
    
    mDrawParticles = true;
    mDrawImage = false;
    
}

void chapter3App::mouseDown( MouseEvent event )
{
}

void chapter3App::update()
{
    if (! mChannel ) return;
    
    mParticleController.update( mChannel, mMouseLoc );
}

void chapter3App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
        
    if(mDrawImage)
    {
        mTexture.enableAndBind();
        gl::draw( mTexture, getWindowBounds());
    }
    
    if ( mDrawParticles )
    {
        glDisable(GL_TEXTURE_2D);
        mParticleController.draw();
    }
}


CINDER_APP_BASIC( chapter3App, RendererGl )
