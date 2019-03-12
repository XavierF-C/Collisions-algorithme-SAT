#ifndef RESOURCES
#define RESOURCES

#include <math.h>

#include "glslStrings.hpp"

#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

namespace resources
{
	// Fonctions utilitaires
	template<typename Type>
	Type abs( const Type &value )
	{
		return value < (Type)( 0 ) ? -value : value;
	}

	template<typename Type>
	void swap( Type &A , Type &B )
	{
		Type C = A;
		A = B;
		B = C;
	}
	
	template<typename Type>
	Type getMinimum( const Type &a , const Type &b )
	{
		return a < b ? a : b;
	}

	template<typename Type>
	Type getMaximum( const Type &a , const Type &b )
	{
		return a > b ? a : b;
	}
	
	// Facilite l'utilisation des librairies
	class GlfwAndGlewManager
	{
	private:
		GLFWwindow* m_window;
		bool m_mustExit;
		
		bool m_isFullScreen;
		
		int m_windowWidth;
		int m_currentWindowWidth;
		int m_windowHeight;
		int m_currentWindowHeight;
		
		GlfwAndGlewManager()
		{}
		
		void destroyWindow()
		{
			glfwDestroyWindow( m_window );
		}
		
		void createWindowFullScreen()
		{
			const GLFWvidmode * mode;
			mode = (GLFWvidmode *)glfwGetVideoMode( glfwGetPrimaryMonitor() );
			
			m_currentWindowWidth = mode->width;
			m_currentWindowHeight = mode->height;
			
			m_window = glfwCreateWindow( m_currentWindowWidth , m_currentWindowHeight , "OpenGL" , glfwGetPrimaryMonitor() , NULL );
			
			glfwMakeContextCurrent( m_window );
		}
		
		void createWindowNormal()
		{
			limitWidth( m_windowWidth );
			limitHeight( m_windowHeight );
			
			m_window = glfwCreateWindow( m_windowWidth , m_windowHeight , "OpenGL" , NULL , NULL );
			
			m_currentWindowWidth = m_windowWidth;
			m_currentWindowHeight = m_windowHeight;
			
			centerWindow();
			
			glfwMakeContextCurrent( m_window );
		}
		
		void centerWindow()
		{
			const GLFWvidmode * mode;
			mode = (GLFWvidmode *)glfwGetVideoMode( glfwGetPrimaryMonitor() );
			
			int leftSpace = ( mode->width - m_currentWindowWidth ) / 2;
			int upSpace = ( mode->height - m_currentWindowHeight ) / 2;
			
			glfwSetWindowPos( m_window , leftSpace , upSpace );
		}
		
		void limitWidth( int &width )
		{
			const GLFWvidmode * mode;
			mode = (GLFWvidmode *)glfwGetVideoMode( glfwGetPrimaryMonitor() );
			
			if( width > mode->width )
				width = mode->width;
		}
		
		void limitHeight( int &height )
		{
			const GLFWvidmode * mode;
			mode = (GLFWvidmode *)glfwGetVideoMode( glfwGetPrimaryMonitor() );
			
			if( height > mode->height )
				height = mode->height;
		}
		
	public:
		GlfwAndGlewManager( const int &widthStart , const int &heightStart , const bool &setFullScreen )
		{
			m_mustExit = false;
			
			m_isFullScreen = setFullScreen;
			
			m_windowWidth = widthStart;
			m_windowHeight = heightStart;
			
			initializeGlfwAndGlew();
		}
		
		~GlfwAndGlewManager()
		{
			glfwTerminate();
		}
		
		void initializeGlfwAndGlew()
		{
			if( !glfwInit() )
				m_mustExit = true;
			
			glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR , 3 );
			glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR , 2 );
			glfwWindowHint( GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE );
			glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT , GL_TRUE );
			
			glfwWindowHint( GLFW_RESIZABLE , GL_FALSE );
			
			if( m_isFullScreen )
				createWindowFullScreen();
			else
				createWindowNormal();
			
			
			glewExperimental = GL_TRUE;
			glewInit();
		}
		
		void resizeWindow( const int &newWidth , const int &newHeight )
		{
			m_windowWidth = newWidth;
			m_windowHeight = newHeight;
			
			limitWidth( m_windowWidth );
			limitHeight( m_windowHeight );
			
			m_currentWindowWidth = m_windowWidth;
			m_currentWindowHeight = m_windowHeight;
						
			if( !m_isFullScreen )
			{
				glfwSetWindowSize( m_window , m_windowWidth , m_windowHeight );
				
				centerWindow();
			}
		}
		
		void inverseWindowStatus()
		{
			destroyWindow();
			
			if( m_isFullScreen )
			{
				m_isFullScreen = false;
				
				createWindowNormal();
			}
			else
			{
				m_isFullScreen = true;
				
				createWindowFullScreen();
			}
		}
		
		GLFWwindow* getWindow()
		{
			return m_window;
		}
		
		int getWindowWidth()
		{
			return m_currentWindowWidth;
		}
		
		int getWindowHeight()
		{
			return m_currentWindowHeight;
		}
		
	};
	
	// Permet l'utilisation du clavier
	class KeyboardManager
	{
	private:
		const static int MAX_KEY = 200;
		
		int *arrayKey;
		
		int currentSize;
		
		void addKeyToArray( const int &newKey )
		{
			++currentSize;
			
			arrayKey[ currentSize * 2 ] = newKey;
			arrayKey[ ( currentSize * 2 ) + 1 ] = KEY_UP;
		}
		
		void addLetters()
		{
			addKeyToArray( GLFW_KEY_A );
			addKeyToArray( GLFW_KEY_B );
			addKeyToArray( GLFW_KEY_C );
			addKeyToArray( GLFW_KEY_D );
			addKeyToArray( GLFW_KEY_E );
			addKeyToArray( GLFW_KEY_F );
			addKeyToArray( GLFW_KEY_G );
			addKeyToArray( GLFW_KEY_H );
			addKeyToArray( GLFW_KEY_I );
			addKeyToArray( GLFW_KEY_J );
			addKeyToArray( GLFW_KEY_K );
			addKeyToArray( GLFW_KEY_L );
			addKeyToArray( GLFW_KEY_M );
			addKeyToArray( GLFW_KEY_N );
			addKeyToArray( GLFW_KEY_O );
			addKeyToArray( GLFW_KEY_P );
			addKeyToArray( GLFW_KEY_Q );
			addKeyToArray( GLFW_KEY_R );
			addKeyToArray( GLFW_KEY_S );
			addKeyToArray( GLFW_KEY_T );
			addKeyToArray( GLFW_KEY_U );
			addKeyToArray( GLFW_KEY_V );
			addKeyToArray( GLFW_KEY_W );
			addKeyToArray( GLFW_KEY_X );
			addKeyToArray( GLFW_KEY_Y );
			addKeyToArray( GLFW_KEY_Z );
		}
		
		void addOthers()
		{
			addKeyToArray( GLFW_KEY_LEFT_SHIFT );
			addKeyToArray( GLFW_KEY_LEFT_CONTROL );
			addKeyToArray( GLFW_KEY_SPACE );
			addKeyToArray( GLFW_KEY_ENTER );
			addKeyToArray( GLFW_KEY_LEFT );
			addKeyToArray( GLFW_KEY_RIGHT );
			addKeyToArray( GLFW_KEY_UP );
			addKeyToArray( GLFW_KEY_DOWN );
			addKeyToArray( GLFW_KEY_F11 );
		}
		
		void addNumbers()
		{
			addKeyToArray( GLFW_KEY_0 );
			addKeyToArray( GLFW_KEY_1 );
			addKeyToArray( GLFW_KEY_2 );
			addKeyToArray( GLFW_KEY_3 );
			addKeyToArray( GLFW_KEY_4 );
			addKeyToArray( GLFW_KEY_5 );
			addKeyToArray( GLFW_KEY_6 );
			addKeyToArray( GLFW_KEY_7 );
			addKeyToArray( GLFW_KEY_8 );
			addKeyToArray( GLFW_KEY_9 );
		}
		
	public:
		const static int KEY_UP = 0;
		const static int KEY_RELEASED = 1;
		const static int KEY_DOWN = 2;
		const static int KEY_PRESSED = 3;
		
		KeyboardManager()
		{
			arrayKey = new int[ MAX_KEY * 2 ];
			
			for( int n = 0 ; n < MAX_KEY ; ++n )
			{
				arrayKey[ n * 2 ] = 0;
				arrayKey[ ( n * 2 ) + 1 ] = KEY_UP; 
			}
			
			currentSize = 0;
			
			addOthers();
			addLetters();
			addNumbers();
		}
		
		~KeyboardManager()
		{
			delete[] arrayKey;
		}
		
		void updateState( GLFWwindow *window )
		{
			for( int n = 0 ; n < currentSize ; ++n )
			{
				int previous = arrayKey[ ( n * 2 ) + 1 ];
				
				if( glfwGetKey( window , arrayKey[ n * 2 ] ) == GLFW_PRESS )
				{
					if( previous != KEY_DOWN && previous != KEY_PRESSED )
						arrayKey[ ( n * 2 ) + 1 ] = KEY_PRESSED;
					else
						arrayKey[ ( n * 2 ) + 1 ] = KEY_DOWN;
				}
				else
				{
					if( previous != KEY_UP && previous != KEY_RELEASED )
						arrayKey[ ( n * 2 ) + 1 ] = KEY_RELEASED;
					else
						arrayKey[ ( n * 2 ) + 1 ] = KEY_UP;
				}
			}
		}
		
		bool isKeyDown( const int &key )
		{
			for( int n = 0 ; n < currentSize ; ++n )
			{
				if( arrayKey[ n * 2 ] == key )
				{
					if( arrayKey[ ( n * 2 ) + 1 ] == KEY_DOWN || arrayKey[ ( n * 2 ) + 1 ] == KEY_PRESSED )
						return true;
					else
						return false;
				}
			}
			
			return false;
		}
		
		bool isKeyPressed( const int &key )
		{
			for( int n = 0 ; n < currentSize ; ++n )
			{
				if( arrayKey[ n * 2 ] == key )
				{
					if( arrayKey[ ( n * 2 ) + 1 ] == KEY_PRESSED )
						return true;
					else
						return false;
				}
			}
			
			return false;
		}
		
		bool isKeyUp( const int &key )
		{
			for( int n = 0 ; n < currentSize ; ++n )
			{
				if( arrayKey[ n * 2 ] == key )
				{
					if( arrayKey[ ( n * 2 ) + 1 ] == KEY_UP || arrayKey[ ( n * 2 ) + 1 ] == KEY_RELEASED )
						return true;
					else
						return false;
				}
			}
			
			return false;
		}
		
		bool isKeyReleased( const int &key )
		{
			for( int n = 0 ; n < currentSize ; ++n )
			{
				if( arrayKey[ n * 2 ] == key )
				{
					if( arrayKey[ ( n * 2 ) + 1 ] == KEY_RELEASED )
						return true;
					else
						return false;
				}
			}
			
			return false;
		}
		
		int getKeyState( const int &key )
		{
			for( int n = 0 ; n < currentSize ; ++n )
			{
				if( arrayKey[ n * 2 ] == key )
					return arrayKey[ ( n * 2 ) + 1 ];
			}
			
			return KEY_UP;
		}
		
	};
	
	// Conteneur RGBA
	class Color
	{
	private :
		float *m_red;
		float *m_green;
		float *m_blue;
		float *m_alpha;
		
	protected :
		void allocate()
		{
			m_red = new float( 1.0f );
			m_green = new float( 1.0f );
			m_blue = new float( 1.0f );
			m_alpha = new float( 1.0f );
		}
		
	public :
		Color()
		{
			allocate();
		}
		
		Color( const float &newRed , const float &newGreen , const float &newBlue , const float &newAlpha )
		{
			allocate();
			setAll( newRed , newGreen , newBlue , newAlpha );
		}
		
		~Color()
		{
			delete m_red;
			delete m_green;
			delete m_blue;
			delete m_alpha;
		}
		
		void setAll( const float &newRed , const float &newGreen , const float &newBlue , const float &newAlpha )
		{
			*m_red = newRed;
			*m_green = newGreen;
			*m_blue = newBlue;
			*m_alpha = newAlpha;
		}
		
		void setRed( const float &newRed )
		{
			*m_red = newRed;
		}
		
		void setGreen( const float &newGreen )
		{
			*m_green = newGreen;
		}
		
		void setBlue( const float &newBlue )
		{
			*m_blue = newBlue;
		}
		
		void setAlpha( const float &newAlpha )
		{
			*m_alpha = newAlpha;
		}
		
		float getRed()
		{
			return *m_red;
		}
		
		float getGreen()
		{
			return *m_green;
		}
		
		float getBlue()
		{
			return *m_blue;
		}
		
		float getAlpha()
		{
			return *m_alpha;
		}
		
	};
	
	template<typename Type>
	class Point
	{
	private :
		Type *m_x;
		Type *m_y;
	
	public :
		Point()
		{
			allocate();
		}
		
		Point( const Type &x , const Type &y )
		{
			allocate();
			*m_x = x;
			*m_y = y;
		}
		
		~Point()
		{
			delete m_x;
			delete m_y;
		}
		
		void allocate()
		{
			m_x = new Type( 0 );
			m_y = new Type( 0 );
		}
		
		void inverse()
		{
			*m_x = -*m_x;
			*m_y = -*m_y;
		}
		
		void multiply( const Type &value )
		{
			*m_x *= value;
			*m_y *= value;
		}
		
		void normalize()
		{
			Type distance = sqrt( ( (*m_x) * (*m_x) ) + ( (*m_y) * (*m_y) ) );
			
			if( distance > (Type)( 0 ) )
			{
				*m_x = *m_x / distance;
				*m_y = *m_y / distance;
			}
		}
		
		void set( const Type &x , const Type &y )
		{
			*m_x = x;
			*m_y = y;
		}
		
		void add( const Type &x , const Type &y )
		{
			*m_x += x;
			*m_y += y;
		}
		
		void setX( const Type &x )
		{
			*m_x = x;
		}
		
		void addX( const Type &x )
		{
			*m_x += x;
		}
		
		void subX( const Type &x )
		{
			*m_x -= x;
		}
		
		void setY( const Type &y )
		{
			*m_y = y;
		}
		
		void addY( const Type &y )
		{
			*m_y += y;
		}
		
		void subY( const Type &y )
		{
			*m_y -= y;
		}
		
		Type getLength()
		{
			return sqrt( ( (*m_x) * (*m_x) ) + ( (*m_y) * (*m_y) ) );
		}
		
		Type getX()
		{
			return *m_x;
		}
		
		Type getY()
		{
			return *m_y;
		}
		
	};
	
	// Interface pour les objets à afficher
	template<typename Type>
	class Displayable
	{
	public:
		virtual ~Displayable(){}
		
		virtual void displace( const Type &x , const Type &y ) = 0;
		
		virtual int getNumberPoint() = 0;
		virtual int getNumberEdge() = 0;
		
		virtual Point<Type>* getPosition() = 0;
		virtual Point<Type>* getForce() = 0;
		
		virtual Color* getColor() = 0;
		
		virtual Type getWidth() = 0;
		virtual Type getHeight() = 0;
		
		virtual void setParallelMultiplier( const Type &parallelMultiplier ) = 0;
		virtual void setPerpendicularMultiplier( const Type &perpendiculaMultiplier ) = 0;
		
		virtual Type getParallelMultiplier() = 0;
		virtual Type getPerpendicularMultiplier() = 0;
		
		virtual Point<Type>* getPointIndex( const int &index ) = 0;
		virtual Point<Type>* getEdgeIndex( const int &index ) = 0;
		
	};
	
	// Permet de relier des points pour créer une forme fermée
	template<typename Type>
	void createEdges( Point<Type> *points , const int &numberPoints , Point<Type> *edges , const int &numberEdges )
	{
		for( int n = 1 ; n < numberEdges ; ++n )
		{
			Type x = points[ n ].getX() - points[ n - 1 ].getX();
			Type y = points[ n - 1 ].getY() - points[ n ].getY();
			Type dis = sqrt( ( y * y ) + ( x * x ) );
			edges[ n - 1 ].set( y / dis , x / dis );
		}
		
		Type x = points[ numberPoints - 1 ].getX() - points[ 0 ].getX();
		Type y = points[ 0 ].getY() - points[ numberPoints - 1 ].getY();
		Type dis = sqrt( ( y * y ) + ( x * x ) );
		edges[ numberEdges - 1 ].set( y / dis , x / dis );
	}
	
	template<typename Type>
	class Rectangle : public Displayable<Type>
	{
	private:
		Point<Type> *m_points;
		Point<Type> *m_edges;
		Point<Type> *m_position;
		Point<Type> *m_force;
		
		Color *m_color;
		
		Type *m_width;
		Type *m_height;
		
		Type *m_parallelMultiplier;
		Type *m_perpendicularMultiplier;
		
	public:
		Rectangle()
		{
			allocate();
		}
		
		Rectangle( const Type &x , const Type &y , const Type &width , const Type &height )
		{
			allocate();
			
			initialize( x , y , width , height );
		}
		
		~Rectangle()
		{
			delete[] m_points;
			delete[] m_edges;
			delete m_position;
			delete m_force;
			
			delete m_color;
			
			delete m_width;
			delete m_height;
			
			delete m_parallelMultiplier;
			delete m_perpendicularMultiplier;
		}
		
		void allocate()
		{
			m_points = new Point<Type>[ 4 ];
			
			m_edges = new Point<Type>[ 2 ];
			
			m_position = new Point<Type>();
			
			m_force = new Point<Type>();
			
			m_color = new Color();
			
			m_width = new Type;
			m_height = new Type;
			
			m_parallelMultiplier = new Type( 1.0 );
			m_perpendicularMultiplier = new Type( 1.0 );
		}
		
		void initialize( const Type &x , const Type &y , const Type &width , const Type &height )
		{
			m_points[ 0 ].set( x + -width / (Type)( 2 ) , y + height / (Type)( 2 ) );
			m_points[ 1 ].set( x + -width / (Type)( 2 ) , y + -height / (Type)( 2 ) );
			m_points[ 2 ].set( x + width / (Type)( 2 ) , y + -height / (Type)( 2 ) );
			m_points[ 3 ].set( x + width / (Type)( 2 ) , y + height / (Type)( 2 ) );
			
			createEdges( m_points , 4 , m_edges , 2 );
			
			m_position->set( x , y );
			
			*m_width = width;
			*m_height = height;
		}
		
		virtual void displace( const Type &x , const Type &y )
		{
			m_position->add( x , y );
			
			for( int n = 0 ; n < 4 ; ++n )
				m_points[ n ].add( x , y );
		}
		
		virtual int getNumberPoint()
		{
			return 4;
		}
		
		virtual int getNumberEdge()
		{
			return 2;
		}
		
		virtual Point<Type>* getPosition()
		{
			return m_position;
		}
		
		virtual Point<Type>* getForce()
		{
			return m_force;
		}
		
		virtual Color* getColor()
		{
			return m_color;
		}
		
		virtual Type getWidth()
		{
			return *m_width;
		}
		
		virtual Type getHeight()
		{
			return *m_height;
		}
		
		virtual void setParallelMultiplier( const Type &parallelMultiplier )
		{
			*m_parallelMultiplier = parallelMultiplier;
		}
		
		virtual void setPerpendicularMultiplier( const Type &perpendicularMultiplier )
		{
			*m_perpendicularMultiplier = perpendicularMultiplier;
		}
		
		virtual Type getParallelMultiplier()
		{
			return *m_parallelMultiplier;
		}
		
		virtual Type getPerpendicularMultiplier()
		{
			return *m_perpendicularMultiplier;
		}
		
		virtual Point<Type>* getPointIndex( const int &index )
		{
			return &(m_points[ index ]);
		}
		
		virtual Point<Type>* getEdgeIndex( const int &index )
		{
			return &(m_edges[ index ]);
		}
	};
	
	template<typename Type>
	class Triangle : public Displayable<Type>
	{
	private:
		Point<Type> *m_points;
		Point<Type> *m_edges;
		Point<Type> *m_position;
		Point<Type> *m_force;
		
		Color *m_color;
		
		Type *m_width;
		Type *m_height;
		
		Type *m_parallelMultiplier;
		Type *m_perpendicularMultiplier;
		
	public:
		Triangle()
		{
			allocate();
		}
		
		Triangle( const Type &x1 , const Type &y1 , const Type &x2 , const Type &y2 , const Type &x3 , const Type &y3 )
		{
			allocate();
			
			initialize( x1 , y1 , x2 , y2 , x3 , y3 );
		}
		
		~Triangle()
		{
			delete[] m_points;
			delete[] m_edges;
			delete m_position;
			delete m_force;
			
			delete m_color;
			
			delete m_width;
			delete m_height;
			
			delete m_parallelMultiplier;
			delete m_perpendicularMultiplier;
		}
		
		void allocate()
		{
			m_points = new Point<Type>[ 3 ];
			
			m_edges = new Point<Type>[ 3 ];
			
			m_position = new Point<Type>();
			
			m_force = new Point<Type>();
			
			m_color = new Color();
			
			m_width = new Type;
			m_height = new Type;
			
			m_parallelMultiplier = new Type( 1.0 );
			m_perpendicularMultiplier = new Type( 1.0 );
		}
		
		void initialize( const Type &x1 , const Type &y1 , const Type &x2 , const Type &y2 , const Type &x3 , const Type &y3 )
		{
			m_points[ 0 ].set( x1 , y1 );
			m_points[ 1 ].set( x2 , y2 );
			m_points[ 2 ].set( x3 , y3 );
			
			createEdges( m_points , 3 , m_edges , 3 );
			
			centerPosition();
			
			*m_width = getMaximum( getMaximum( x1 , x2 ) , x3 ) - getMinimum( getMinimum( x1 , x2 ) , x3 );
			*m_height = getMaximum( getMaximum( y1 , y2 ) , y3 ) - getMinimum( getMinimum( y1 , y2 ) , y3 );
		}
		
		void centerPosition()
		{
			m_position->set( ( m_points[ 0 ].getX() + m_points[ 1 ].getX() + m_points[ 2 ].getX() ) / (Type)( 3 ) ,
				( m_points[ 0 ].getY() + m_points[ 1 ].getY() + m_points[ 2 ].getY() ) / (Type)( 3 ) );
		}
		
		virtual void displace( const Type &x , const Type &y )
		{
			m_position->add( x , y );
			
			for( int n = 0 ; n < 3 ; ++n )
				m_points[ n ].add( x , y );
		}
		
		virtual int getNumberPoint()
		{
			return 3;
		}
		
		virtual int getNumberEdge()
		{
			return 3;
		}
		
		virtual Point<Type>* getPosition()
		{
			return m_position;
		}
		
		virtual Point<Type>* getForce()
		{
			return m_force;
		}
		
		virtual Color* getColor()
		{
			return m_color;
		}
		
		virtual Type getWidth()
		{
			return *m_width;
		}
		
		virtual Type getHeight()
		{
			return *m_height;
		}
		
		virtual void setParallelMultiplier( const Type &parallelMultiplier )
		{
			*m_parallelMultiplier = parallelMultiplier;
		}
		
		virtual void setPerpendicularMultiplier( const Type &perpendicularMultiplier )
		{
			*m_perpendicularMultiplier = perpendicularMultiplier;
		}
		
		virtual Type getParallelMultiplier()
		{
			return *m_parallelMultiplier;
		}
		
		virtual Type getPerpendicularMultiplier()
		{
			return *m_perpendicularMultiplier;
		}
		
		virtual Point<Type>* getPointIndex( const int &index )
		{
			return &(m_points[ index ]);
		}
		
		virtual Point<Type>* getEdgeIndex( const int &index )
		{
			return &(m_edges[ index ]);
		}
		
	};
	
	template<typename Type>
	class Camera
	{
	private:
		Type x;
		Type y;
		
		Type width;
		Type height;
		
		Camera()
		{}
				
	public:
		Camera( const Type &xStart , const Type &yStart , const Type &widthStart , const Type &heightStart )
		{
			x = xStart;
			y = yStart;
			
			width = widthStart;
			height = heightStart;
		}
		
		void setX( const Type &newX )
		{
			x = newX;
		}
		
		void addX( const Type &newX )
		{
			x += newX;
		}
		
		void setY( const Type &newY )
		{
			y = newY;
		}
		
		void addY( const Type &newY )
		{
			y += newY;
		}
		
		void setWidth( const Type &newWidth )
		{
			width = newWidth;
		}
		
		void setHeight( const Type &newHeight )
		{
			height = newHeight;
		}
		
		Type getX()
		{
			return x;
		}
		
		Type getY()
		{
			return y;
		}
		
		Type getWidth()
		{
			return width;
		}
		
		Type getHeight()
		{
			return height;
		}
	};
	
	// Facilite l'utilisation de OpenGL
	template<typename Type>
	class GraphicsManager
	{
	private:
		const static int m_MAX_LINES = 9000;
		
		const static int m_MAX_VERTEX = m_MAX_LINES * 4 * sizeof(Type);
		const static int m_MAX_COLORS = m_MAX_LINES * 8 * sizeof(Type);
		
		Type *m_arrayVertex;
		Type *m_arrayColors;
		
		int m_currentMemoryVertex;
		int m_currentMemoryColor;
		
		GLuint m_program;
		GLuint *m_vao;
		GLuint *m_vbo;
		
	public:
		GraphicsManager()
		{
			m_vao = new GLuint;
			m_vbo = new GLuint[ 2 ];
			
			m_arrayVertex = new Type[ m_MAX_VERTEX ];
			m_arrayColors = new Type[ m_MAX_COLORS ];
			
			m_currentMemoryVertex = 0;
			m_currentMemoryColor = 0;
			
			initialize();
		}
		
		~GraphicsManager()
		{
			delete m_vao;
			delete[] m_vbo;
			
			delete[] m_arrayVertex;
			delete[] m_arrayColors;
		}
		
		void initialize()
		{
			generateVaoAndVbo();
		}
		
		void generateVaoAndVbo()
		{
			m_program = glCreateProgram();
			
			GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
			glShaderSource( fs , 1 , fragmentShaderStrings::fragSrcLine , NULL );
			glCompileShader( fs );
			
			GLuint vs = glCreateShader( GL_VERTEX_SHADER );
			glShaderSource( vs , 1 , vertexShaderStrings::vertSrcLine , NULL );
			glCompileShader( vs );
			
			glAttachShader( m_program , vs );
			glAttachShader( m_program , fs );
			
			glBindAttribLocation( m_program , 0 , "inPoint" );
			glBindAttribLocation( m_program , 1 , "inVertexColor" );
			
			glLinkProgram( m_program );
			
			glDeleteShader( vs );
			glDeleteShader( fs );
			
			
			
			glGenVertexArrays( 1 , m_vao );
			glBindVertexArray( m_vao[ 0 ] );
			
			glGenBuffers( 2 , m_vbo );
			
			glBindBuffer( GL_ARRAY_BUFFER , m_vbo[ 0 ] );
			glBufferData( GL_ARRAY_BUFFER , m_MAX_VERTEX , NULL , GL_DYNAMIC_DRAW );
			glVertexAttribPointer( (GLuint)0 , 2 , GL_FLOAT , GL_FALSE , 0 , 0 );
			glEnableVertexAttribArray( 0 );
			
			glBindBuffer( GL_ARRAY_BUFFER , m_vbo[ 1 ] );
			glBufferData( GL_ARRAY_BUFFER , m_MAX_COLORS , NULL , GL_DYNAMIC_DRAW );
			glVertexAttribPointer( (GLuint)1 , 4 , GL_FLOAT , GL_FALSE , 0 , 0 );
			glEnableVertexAttribArray( 1 );
		}
		
		void reset()
		{
			for( int n = 0 ; n < m_currentMemoryVertex ; ++n )
				m_arrayVertex[ n ] = (Type)(NULL);
				
			for( int n = 0 ; n < m_currentMemoryColor ; ++n )
				m_arrayColors[ n ] = (Type)(NULL);
			
			m_currentMemoryVertex = 0;
			m_currentMemoryColor = 0;
		}
		
		void addPolygons( Displayable<Type> **arrayPolygons , const int &numberPolygons , Camera<Type> *camera )
		{
			Type camX = camera->getX();
			Type camY = camera->getY();
			
			Type halfWidth = camera->getWidth() / (Type)( 2 );
			Type halfHeight = camera->getHeight() / (Type)( 2 );
			
			Type *arrayVertex = new Type[ 5 * 4 ];
			Type *arrayColor = new Type[ 5 * 8 ];
			
			for( int n = 0 ; n < numberPolygons ; ++n )
			{
				int numberPoint = arrayPolygons[ n ]->getNumberPoint();
				
				bool isInsideCamera = false;
				
				Type width = arrayPolygons[ n ]->getWidth();
				Type height = arrayPolygons[ n ]->getHeight();
				
				for( int i = 0 ; i < numberPoint && !isInsideCamera ; ++i )
				{
					if( ( -halfWidth - width <= arrayPolygons[ n ]->getPointIndex( i )->getX() - camX ) && ( arrayPolygons[ n ]->getPointIndex( i )->getX() - camX ) <= halfWidth + width && ( -halfHeight - height <= arrayPolygons[ n ]->getPointIndex( i )->getY() - camY ) && ( arrayPolygons[ n ]->getPointIndex( i )->getY() - camY ) <= halfHeight + height )
						isInsideCamera = true;
				}
				
				if( isInsideCamera )
				{
					for( int i = 0 ; i < numberPoint - 1 ; ++i )
					{
						arrayVertex[ ( i * 4 ) ] = ( arrayPolygons[ n ]->getPointIndex( i )->getX() - camX ) / halfWidth;
						arrayVertex[ ( i * 4 ) + 1 ] = ( arrayPolygons[ n ]->getPointIndex( i )->getY() - camY ) / halfHeight;
						arrayVertex[ ( i * 4 ) + 2 ] = ( arrayPolygons[ n ]->getPointIndex( i + 1 )->getX() - camX ) / halfWidth;
						arrayVertex[ ( i * 4 ) + 3 ] = ( arrayPolygons[ n ]->getPointIndex( i + 1 )->getY() - camY ) / halfHeight;
					}
					
					arrayVertex[ ( ( numberPoint - 1 ) * 4 ) ] = ( arrayPolygons[ n ]->getPointIndex( numberPoint - 1 )->getX() - camX ) / halfWidth;
					arrayVertex[ ( ( numberPoint - 1 ) * 4 ) + 1 ] = ( arrayPolygons[ n ]->getPointIndex( numberPoint - 1 )->getY() - camY ) / halfHeight;
					arrayVertex[ ( ( numberPoint - 1 ) * 4 ) + 2 ] = ( arrayPolygons[ n ]->getPointIndex( 0 )->getX() - camX ) / halfWidth;
					arrayVertex[ ( ( numberPoint - 1 ) * 4 ) + 3 ] = ( arrayPolygons[ n ]->getPointIndex( 0 )->getY() - camY ) / halfHeight;
					
					for( int i = 0 ; i < numberPoint * 2 ; ++i )
					{
						arrayColor[ ( i * 4 ) ] = arrayPolygons[ n ]->getColor()->getRed();
						arrayColor[ 1 + ( i * 4 ) ] = arrayPolygons[ n ]->getColor()->getGreen();
						arrayColor[ 2 + ( i * 4 ) ] = arrayPolygons[ n ]->getColor()->getBlue();
						arrayColor[ 3 + ( i * 4 ) ] = arrayPolygons[ n ]->getColor()->getAlpha();
					}
					
					for( int i = 0 ; i < numberPoint * 4 ; ++i )
					{
						m_arrayVertex[ m_currentMemoryVertex ] = arrayVertex[ i ];
						++m_currentMemoryVertex;
					}
					for( int i = 0 ; i < numberPoint * 8 ; ++i )
					{
						m_arrayColors[ m_currentMemoryColor ] = arrayColor[ i ];
						++m_currentMemoryColor;
					}
				}
			}
			
			delete[] arrayVertex;
			delete[] arrayColor;
		}
		
		void addLines( const int &vertexSize , Type *arrayVertex , const int &colorSize , Type *arrayColor )
		{
			glBindVertexArray( m_vao[ 0 ] );
			
			glBindBuffer( GL_ARRAY_BUFFER , m_vbo[ 0 ] );
			glBufferSubData( GL_ARRAY_BUFFER , m_currentMemoryVertex , vertexSize , arrayVertex );
			
			glBindBuffer( GL_ARRAY_BUFFER , m_vbo[ 1 ] );
			glBufferSubData( GL_ARRAY_BUFFER , m_currentMemoryColor , colorSize , arrayColor );
			
			m_currentMemoryVertex += vertexSize;
			m_currentMemoryColor += colorSize;
		}
		
		void drawAllLines()
		{
			glBindBuffer( GL_ARRAY_BUFFER , m_vbo[ 0 ] );
			glBufferData( GL_ARRAY_BUFFER , m_MAX_VERTEX , m_arrayVertex , GL_DYNAMIC_DRAW );
			
			
			glBindBuffer( GL_ARRAY_BUFFER , m_vbo[ 1 ] );
			glBufferData( GL_ARRAY_BUFFER , m_MAX_COLORS , m_arrayColors , GL_DYNAMIC_DRAW );
			
			
			glDrawArrays( GL_LINES , 0 , 2 * m_MAX_LINES );
		}
		
		GLuint getProgram()
		{
			return m_program;
		}
		
	};
	
	// Contiens les objets affichables
	template<typename Type>
	class MapManager
	{
	private:
		const int m_MAX_MOVING_OBJECTS;
		const int m_MAX_STATIC_OBJECTS;
		
		int m_currentMaxMovingObjects;
		int m_currentMaxStaticObjects;
		
		Displayable<Type> **m_movingArray;
		Displayable<Type> **m_staticArray;
		
	public:
		MapManager() :
			m_MAX_MOVING_OBJECTS( 10 ) , m_MAX_STATIC_OBJECTS( 50 ) 
		{
			allocate();
		}
		
		MapManager( const int &MAX_MOVING_OBJECTS , const int &MAX_STATIC_OBJECTS ) :
			m_MAX_MOVING_OBJECTS( MAX_MOVING_OBJECTS ) , m_MAX_STATIC_OBJECTS(  MAX_STATIC_OBJECTS ) 
		{
			allocate();
		}
		
		~MapManager()
		{
			for( int n = 0 ; n < m_MAX_MOVING_OBJECTS ; ++n )
				delete m_movingArray[ n ];
			
			delete[] m_movingArray;
			
			
			for( int n = 0 ; n < m_MAX_STATIC_OBJECTS ; ++n )
				delete m_staticArray[ n ];
			
			delete[] m_staticArray;
		}
		
		void allocate()
		{
			m_currentMaxMovingObjects = 0;
			m_currentMaxStaticObjects = 0;
			
			m_movingArray = new Displayable<Type>*[ m_MAX_MOVING_OBJECTS ];
			
			for( int n = 0 ; n < m_MAX_MOVING_OBJECTS ; ++n )
				m_movingArray[ n ] = NULL;
			
			
			m_staticArray = new Displayable<Type>*[ m_MAX_STATIC_OBJECTS ];
			
			for( int n = 0 ; n < m_MAX_STATIC_OBJECTS ; ++n )
				m_staticArray[ n ] = NULL;
		}
		
		void setMovingColorAll( const float &newRed , const float &newGreen , const float &newBlue , const float &newAlpha )
		{
			for( int n = 0 ; n < m_currentMaxMovingObjects ; ++n )
				m_movingArray[ n ]->getColor()->setAll( newRed , newGreen , newBlue , newAlpha );
		}
		
		void setStaticColorAll( const float &newRed , const float &newGreen , const float &newBlue , const float &newAlpha )
		{
			for( int n = 0 ; n < m_currentMaxStaticObjects ; ++n )
				m_staticArray[ n ]->getColor()->setAll( newRed , newGreen , newBlue , newAlpha );
		}
		
		void addGravity( const int &ticksPerSecond , const Type &intensity )
		{
			for( int n = 0 ; n < m_currentMaxMovingObjects ; ++n )
			{
				m_movingArray[ n ]->getForce()->addY( -intensity / ticksPerSecond );
			}
		}
		
		void DisplaceAllMovingObject( const int &ticksPerSecond )
		{
			Point<Type>* velocity = new Point<Type>( (Type)( 0 ) , (Type)( 0 ) );
			Point<Type>* reflexion = new Point<Type>( (Type)( 0 ) , (Type)( 0 ) );
			
			bool isCloser = false;
			Type multiplier;
			Type inverseM;
			static const int MAX_REFLEXION = 10;
			int reflected = 0;
			
			Point<Type>* arrayAxis = new Point<Type>[ 10 ];
			Type *arrayMinimum = new Type[ 10 ];
			Point<Type> *perpendicularDeplacement = new Point<Type>;
			Point<Type> *parallelDeplacement = new Point<Type>;
			
			
			for( int n = 0 ; n < m_currentMaxMovingObjects ; ++n )
			{
				bool collision = false;
				
				if( reflected == 0 )
					velocity->set( m_movingArray[ n ]->getForce()->getX() / ticksPerSecond , m_movingArray[ n ]->getForce()->getY() / ticksPerSecond );
				
				reflexion->set( (Type)( 0 ) , (Type)( 0 ) );
				
				multiplier = (Type)( 1 );
				inverseM = (Type)( 0 );
				
				for( int i = 0 ; i < m_currentMaxStaticObjects ; ++i )
				{
					if( abs( velocity->getX() ) + m_movingArray[ n ]->getWidth() + m_staticArray[ i ]->getWidth() >= abs( m_movingArray[ n ]->getPosition()->getX() - m_staticArray[ i ]->getPosition()->getX() ) &&
						abs( velocity->getY() ) + m_movingArray[ n ]->getHeight() + m_staticArray[ i ]->getHeight() >= abs( m_movingArray[ n ]->getPosition()->getY() - m_staticArray[ i ]->getPosition()->getY() ) )
					{
						isCloser = false;
						
						if( collide( m_movingArray[ n ] , m_staticArray[ i ] , velocity ,
							arrayAxis , arrayMinimum , perpendicularDeplacement , parallelDeplacement ,
								multiplier , inverseM , reflexion , isCloser ) )
							collision = true;
					}
				}
				
				if( collision )
				{
					m_movingArray[ n ]->displace( ( velocity->getX() * multiplier ) , ( velocity->getY() * multiplier ) );
					
					m_movingArray[ n ]->getForce()->set( reflexion->getX() * ticksPerSecond , reflexion->getY() * ticksPerSecond );
					
					if( reflected <= MAX_REFLEXION )
					{
						reflected += 1;
						
						velocity->set( reflexion->getX() * inverseM , reflexion->getY() * inverseM );
						
						n -= 1;
					}
					else
					{
						reflected = 0;
					}
				}
				else
				{
					reflected = 0;
					m_movingArray[ n ]->displace( velocity->getX() , velocity->getY() );
				}
			}
			
			delete[] arrayAxis;
			delete[] arrayMinimum;
			
			delete perpendicularDeplacement;
			delete parallelDeplacement;
			
			delete velocity;
			delete reflexion;
		}
		
		Displayable<Type>** getMovingArray()
		{
			return m_movingArray;
		}
		
		Displayable<Type>** getStaticArray()
		{
			return m_staticArray;
		}
		
		int getCurrentMaxMovingObjects( const bool &expand )
		{
			if( expand )
			{
				++m_currentMaxMovingObjects;
								
				return ( m_currentMaxMovingObjects - 1 );
			}
			
			return m_currentMaxMovingObjects;
		}
		
		int getCurrentMaxStaticObjects( const bool &expand )
		{
			if( expand )
			{
				++m_currentMaxStaticObjects;
								
				return ( m_currentMaxStaticObjects - 1 );
			}
			
			return m_currentMaxStaticObjects;
		}
		
	};
	
	template<typename Type>
	Type dotProduct( Point<Type> *pointA , Point<Type> *pointB )
	{
		return ( pointA->getX() * pointB->getX() ) + ( pointA->getY() * pointB->getY() );
	}
	
	template<typename Type>
	void generateMinAndMax( Type &min , Type &max , Displayable<Type>* polygon , const int &currentAxis , Point<Type>* arrayAxis )
	{
		min = dotProduct( polygon->getPointIndex( 0 ) , &(arrayAxis[ currentAxis ]) );
		max = min;
		
		for( int n = 1 ; n < polygon->getNumberPoint() ; ++n )
		{
			min = getMinimum( min , dotProduct( polygon->getPointIndex( n ) , &(arrayAxis[ currentAxis ]) ) );
			max = getMaximum( max , dotProduct( polygon->getPointIndex( n ) , &(arrayAxis[ currentAxis ]) ) );
		}
	}
	
	template<typename Type>
	bool collide( Displayable<Type>* polygonMoving , Displayable<Type>* polygonStatic , Point<Type>* velocity ,
		Point<Type>* arrayAxis , Type *arrayMinimum , Point<Type>* perpendicularDeplacement , Point<Type>* parallelDeplacement ,
		Type &previousMultiplier , Type &previousInverseM , Point<Type>* reflexion , bool &isCloser )
	{
		bool returnValue = true;
		
		Type biggestMinimum = (Type)( 1 );
		int chosenAxis = 0;
		
		const Type SMALL = (Type)( 0.001 );
		
		int numberEdgeM = polygonMoving->getNumberEdge();
		
		int numberEdgeS = polygonStatic->getNumberEdge();
		
		int numberAxis = numberEdgeM + numberEdgeS;
		
		
		for( int n = 0 ; n < numberEdgeM ; ++n )
			arrayAxis[ n ].set( polygonMoving->getEdgeIndex( n )->getX() , polygonMoving->getEdgeIndex( n )->getY() );
		
		for( int n = 0 ; n < numberEdgeS ; ++n )
			arrayAxis[ n + numberEdgeM ].set( polygonStatic->getEdgeIndex( n )->getX() , polygonStatic->getEdgeIndex( n )->getY() );
		
		
		for( int n = 0 ; n < numberAxis ; ++n )
			arrayMinimum[ n ] = (Type)( 1 );
		
		
		for( int n = 0 ; n < numberAxis && returnValue ; ++n )
		{
			Type minBegin , maxBegin , minEnd , maxEnd , minStatic , maxStatic;
			
			generateMinAndMax( minBegin , maxBegin , polygonMoving , n , arrayAxis );
			
			polygonMoving->displace( velocity->getX() , velocity->getY() );
			generateMinAndMax( minEnd , maxEnd , polygonMoving , n , arrayAxis );
			polygonMoving->displace( -velocity->getX() , -velocity->getY() );
			
			generateMinAndMax( minStatic , maxStatic , polygonStatic , n , arrayAxis );
			
			
			bool beginLeft = true;
			
			
			Type minimum , maximum;
			
			minimum = maxBegin;
			maximum = maxEnd;
			
			if( minimum > maximum )
			{
				beginLeft = false;
				swap( minimum , maximum );
			}
			
			Type movingSize = maxBegin - minBegin;
			
			
			Type movementLength = maximum - minimum;
			
			if( (Type)( 0 ) <= movementLength && movementLength <= SMALL )
				movementLength = SMALL;
			else if( -SMALL <= movementLength && movementLength <= (Type)( 0 ) )
				movementLength = -SMALL;
			
			
			Type maxStaticPlusMovingSize = maxStatic + movingSize;
			
			bool intervalIntersect = false;
			
			
			if( beginLeft )
			{
				if( minimum <= maxStaticPlusMovingSize && maximum >= minStatic )
				{
					intervalIntersect = true;
					
					arrayMinimum[ n ] = (Type)( 1 ) - ( ( SMALL + maximum - minStatic ) / movementLength );
				}
			}
			else
			{
				if( maximum >= minStatic && minimum <= maxStaticPlusMovingSize )
				{
					intervalIntersect = true;
					
					arrayMinimum[ n ] = (Type)( 1 ) - ( ( SMALL + maxStaticPlusMovingSize - minimum ) / movementLength );
				}
			}
			
			if( n <= 0 || arrayMinimum[ n ] > biggestMinimum )
			{
				biggestMinimum = arrayMinimum[ n ];
				
				chosenAxis = n;
			}
			
			if( !intervalIntersect )
				returnValue = false;
		}
		
		if( returnValue && biggestMinimum < previousMultiplier )
		{
			isCloser = true;
			
			previousInverseM = (Type)( 1 ) - biggestMinimum;
			
			if( biggestMinimum < (Type)( 0 ) )
				previousInverseM = (Type)( 1 );
			
			Type dotNorVel = dotProduct( &(arrayAxis[ chosenAxis ]) , velocity );
			
			perpendicularDeplacement->set( dotNorVel * arrayAxis[ chosenAxis ].getX() , dotNorVel * arrayAxis[ chosenAxis ].getY() );
			parallelDeplacement->set( velocity->getX() - perpendicularDeplacement->getX() , velocity->getY() - perpendicularDeplacement->getY() );
			
			previousMultiplier = biggestMinimum;
			
			perpendicularDeplacement->multiply( polygonMoving->getPerpendicularMultiplier() * polygonStatic->getPerpendicularMultiplier() );
			
			parallelDeplacement->multiply( polygonMoving->getParallelMultiplier() * polygonStatic->getParallelMultiplier() );
			
			reflexion->set( parallelDeplacement->getX() - perpendicularDeplacement->getX() ,
				parallelDeplacement->getY() - perpendicularDeplacement->getY() );
		}
		
		return returnValue;
	}
	
};

#endif

