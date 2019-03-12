#include <iostream>

#include <cstdlib>
#include <time.h>


#include "../include/glslStrings.hpp"
#include "../include/resources.hpp"

#include "../include/tickAndFps.hpp"

#define GLEW_STATIC
#include "../include/glew.h"
#include "../include/glfw3.h"

using namespace resources;

// Générer un nombre aléatoire
float upTo( const float &value )
{
	return value * (float)( rand() % 101 ) / 100.0f;
}

int main( int argc , char **argv )
{
	// Crér les objets utilitaires
	GlfwAndGlewManager *gagm = new GlfwAndGlewManager( 1400 , 780 , false );
	
	KeyboardManager *kbm = new KeyboardManager();
	
	Camera<float> *cam = new Camera<float>( 0.0f , 0.0f , 160.0f , 90.0f );
	
	GraphicsManager<float> *gpm = new GraphicsManager<float>;
	
	MapManager<float> *mm = new MapManager<float>( 2000 , 100 );
	
	srand( time( NULL ) );
	
	// Créer les objets rebondissants
	for( int n = 0 ; n < 20 ; ++n )
	{
		float size = ( 0.1f + upTo( 0.4f ) ) * 10.0f;
		mm->getMovingArray()[ mm->getCurrentMaxMovingObjects( true ) ] = new resources::Rectangle<float>( -70.0f + (float)( rand() % 141 ) , 36.0f - (float)( rand() % 7 ) , size , size );
		mm->getMovingArray()[ n ]->getForce()->add( -5.0f + upTo( 25.0f ) , -5.0f + upTo( 25.0f ) );
		mm->getMovingArray()[ n ]->getColor()->setAll( 0.1f + upTo( 0.8f ) , 0.1f + upTo( 0.8f ) , 0.1f + upTo( 0.8f ) , 1.0f );
	}
	
	// Créer le décor
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Rectangle<float>( -82.0f , 0.0f , 5.0f , 99.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Rectangle<float>( 82.0f , 0.0f , 5.0f , 99.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Rectangle<float>( 0.0f , -47.0f , 159.0f , 5.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Rectangle<float>( 0.0f , 47.0f , 159.0f , 5.0f );
	
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Triangle<float>( 20.0f , 20.0f , 60.0f , 5.0f , 35.0f , 10.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Triangle<float>( 20.0f , 20.0f , 60.0f , 5.0f , 35.0f , 10.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Triangle<float>( 70.0f , -2.0f , 15.0f , -15.0f , 55.0f , -15.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Triangle<float>( -65.0f , 20.0f , -40.0f , 5.0f , -60.0f , -5.0f );
	mm->getStaticArray()[ mm->getCurrentMaxStaticObjects( true ) ] = new resources::Triangle<float>( -30.0f , 15.0f ,  0.0f , 12.0f , -40.0f , -10.0f );
	
	mm->setStaticColorAll( 0.5f , 0.0f , 1.0f , 1.0f );
	
	
	// Permet de contrôler la fréquence de rafraîchissement de la logique et de l'affichage
	TickAndFps *taf = new TickAndFps( 60 , 5 );
	
	taf->initializeNextTick();
	taf->initializeNextDisplay();
	taf->setFpsMax( 60 );
	
	int count = 0;
	int countMax = taf->get_TICKS_PER_SECONDS() * 6000;
	
	
	
	GLfloat color[] = { 0.1f , 0.1f , 0.1f , 1.0f };
	
	
	
	while( !glfwWindowShouldClose( gagm->getWindow() ) )
	{
		taf->updateLoopBegin();
		
		while( taf->getFrameIsStarted() )
		{
			if( count >= countMax || glfwGetKey( gagm->getWindow() , GLFW_KEY_ESCAPE ) == GLFW_PRESS )
			{
				taf->setGameIsRunning( false );
				glfwSetWindowShouldClose( gagm->getWindow() , GL_TRUE );
			}
			
			++count;
			
			kbm->updateState( gagm->getWindow() );
			
			// Entrer/sortir du mode plein écran
			if( kbm->isKeyPressed( GLFW_KEY_F11 ) )
			{
				gagm->inverseWindowStatus();
				gpm->generateVaoAndVbo();
			}
			
			// Permet de zoomer
			static const float amount = 1.25f;
			
			if( kbm->isKeyPressed( GLFW_KEY_DOWN ) )
			{
				cam->setWidth( cam->getWidth() * amount );
				cam->setHeight( cam->getHeight() * amount );
			}
			else if( kbm->isKeyPressed( GLFW_KEY_UP ) )
			{
				cam->setWidth( cam->getWidth() / amount );
				cam->setHeight( cam->getHeight() / amount );
			}
			
			// Déplacer la caméra
			if( kbm->isKeyDown( GLFW_KEY_A ) )
				cam->addX( cam->getHeight() * -0.5f / taf->get_TICKS_PER_SECONDS() );
			
			if( kbm->isKeyDown( GLFW_KEY_D ) )
				cam->addX( cam->getHeight() * 0.5f / taf->get_TICKS_PER_SECONDS() );
			
			if( kbm->isKeyDown( GLFW_KEY_W ) )
				cam->addY( cam->getHeight() * 0.5f / taf->get_TICKS_PER_SECONDS() );
			
			if( kbm->isKeyDown( GLFW_KEY_S ) )
				cam->addY( cam->getHeight() * -0.5f / taf->get_TICKS_PER_SECONDS() );
			
			gpm->reset();
			
			mm->DisplaceAllMovingObject( taf->get_TICKS_PER_SECONDS() );
			mm->addGravity( taf->get_TICKS_PER_SECONDS() , 50.0f );
			
			gpm->addPolygons( mm->getMovingArray() , mm->getCurrentMaxMovingObjects( false ) , cam );
			gpm->addPolygons( mm->getStaticArray() , mm->getCurrentMaxStaticObjects( false ) , cam );
			
			
			taf->updateNextTick();
		}
		
		// Afficher à l'écran
		if( taf->getDisplayIsStarted() )
		{
			static const GLfloat backColor[] = { 0.0f , 0.0f , 0.0f , 1.0f };
			
			for( int n = 0 ; n < 3 ; ++n )
			{
				color[ n ] += -0.02f + upTo( 0.04f );
				
				if( color[ n ] < 0.0f )
					color[ n ] = 0.0f;
				
				if( color[ n ] > 0.15f )
					color[ n ] = 0.15f;
			}
			
			mm->setStaticColorAll( color[ 0 ] * 6.0f , color[ 1 ] * 6.0f , color[ 2 ] * 6.0f , 1.0f );
			
			glClearBufferfv( GL_COLOR , 0 , backColor );
			
			glUseProgram( gpm->getProgram() );
			
			
			gpm->drawAllLines();
			
			
			glfwSwapBuffers( gagm->getWindow() );
			glfwPollEvents();
			
			
			taf->updateNextDisplay();
		}
		
		taf->autoSleep();
	}
	
	
	delete mm;
	
	delete taf;
	delete gpm;
	delete cam;
	delete kbm;
	delete gagm;
	
	return 0;
}

