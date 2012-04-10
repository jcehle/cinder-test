#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"
#include "ParticleController.h"
#include "cinder/Perlin.h"


#define RESOLUTION 5


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
    void mouseUp ( MouseEvent event );
	void update();
	void draw();
    
    Perlin perlin;
    
    Surface mColorSurface;
    gl::Texture mColorTexture;
    
    Channel32f mChannel;
    gl::Texture mTexture;
    
    Vec2i mMouseLoc;
    Vec2f mMouseLastPos;
    Vec2f mMouseVel;
    
    ParticleController mParticleController;
    
    bool mDrawParticles;
    bool mDrawImage;
    bool mIsPressed;
    
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

void chapter3App::mouseDown(MouseEvent event)
{
    mIsPressed = true;
}

void chapter3App::mouseUp(MouseEvent event)
{
    mIsPressed = false;
}


void chapter3App::mouseMove(MouseEvent event)
{

    mMouseLoc = event.getPos(); 
    mMouseVel = mMouseLoc - mMouseLastPos;
    mMouseLastPos = (Vec2f)mMouseLoc;
    //console() << "mouse vel: " << mMouseVel << std::endl;
}

void chapter3App::mouseDrag(MouseEvent event)
{
    mouseMove(event);
}

Surface setupColorSurface()
{
    Surface surf( loadImage( loadResource( "color_800x600.png")));
    return surf;
}

Area getSurfaceArea( const Surface surf)
{
    Area a(0, 0, surf.getWidth(), surf.getHeight()); 
    return a;
}

Surface::Iter getSurfaceIter( Surface *surf, Area area)
{
    Surface::Iter i = surf->getIter(area);
    return i;
}
 
void chapter3App::setup()
{
    setFrameRate( 60.0f );
    perlin = Perlin();
    
    Url url( "http://libcinder.org/media/tutorial/paris.jpg" );
    mChannel = Channel32f ( loadImage ( loadUrl( url )));
    mTexture = mChannel;
    
    mColorSurface = setupColorSurface();
    mColorTexture = gl::Texture( mColorSurface );
    mParticleController.setSampleSurface( mColorSurface );

    mMouseLoc = Vec2i( 0, 0 );
    
    mDrawParticles = true;
    mDrawImage = false;
    mIsPressed = false;
}


void chapter3App::update()
{
    if (! mChannel ) return;
    
    if( mIsPressed )
        mParticleController.addParticles( 5, mMouseLoc, mMouseVel );
    
    mParticleController.update(perlin, mChannel, mMouseLoc );
}

void chapter3App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
        
    if(mDrawImage)
    {
        mColorTexture.enableAndBind();
        gl::draw( mColorTexture, getWindowBounds());
    }
    
    if ( mDrawParticles )
    {
        glDisable(GL_TEXTURE_2D);
        mParticleController.draw();
    }
}


CINDER_APP_BASIC( chapter3App, RendererGl )
