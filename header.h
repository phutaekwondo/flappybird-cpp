#include<SDL_image.h>
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<cmath>
#include<cstring>
#include<string>
#include<sstream>
#include<vector>


class myTexture{
private:
	SDL_Texture* texture;
	int width, height;
    SDL_Renderer* windowRenderer;
public:
	myTexture( SDL_Renderer* renderer = NULL, char* path = NULL );
	~myTexture();

	void loadImage(char* path);
    void loadImage( char* path, int w, int h );
	void loadText( char* text, TTF_Font* font, SDL_Color color );
	void free();
	void render(int x=0, int y=0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flipping = SDL_FLIP_NONE );
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setAlphaMod( Uint8 alpha );
	int  getW();
	int  getH();
	void setRenderer( SDL_Renderer* ren );
};

//class bird
class elip{
private:
	SDL_Renderer* renderer;
	int x,y,w,h;
	int angle;
public:
	static constexpr const double PI = 3.141592653596;
	elip( SDL_Renderer* ren=NULL, int inx = 0, int iny = 0, int inw = 0, int inh = 0 );
	void draw();

	bool isInside( int a, int b );
	bool isCollision( SDL_Rect rect );
	bool isCollisionLine( int x1, int y1, int x2, int y2 );

	void setX( int inx );
	void setY( int iny );
	void setW( int inw );
	void setH( int inh );
	void setAngle( int inangle );
	void set( int inx , int iny, int inw, int inh, int inangle );
	void setRenderer( SDL_Renderer* ren );

	int getX();
};
class bird{
private:
	SDL_Renderer* renderer;
	myTexture texture;
	SDL_Rect local;
	int angle;
	elip cover;
	bool isFalling;
	int jumpspeed, fallingspeed;
public:
	static const int gravity = 1;
	bird( SDL_Renderer* ren=NULL, int x=0, int y=0, int spe=1, char* path="img/birdscaled.png" );
	bool isCollision( SDL_Rect rect );
	void render();

	void jump();
	void fall();

	void drawCover();
	void updateCover();

	void setY( int y );
	void setFalling( bool fal );
	void set(SDL_Renderer* ren=NULL, int x=0, int y=0, int spe=1, char* path="img/birdscaled.png" );

	elip getElip();
};

//class pipe
//global texture, use this for all pipe object
class pipe{
	myTexture* texturePointer;
	int startX, space, gatePos ;
public:
	pipe( myTexture* tex = NULL );
	void render();
	void set( int x, int pos, int spa = -1 );
	void setTexture( myTexture* tex );

	bool isCollision( elip eli );	
	int getW();
	int getSpace();
};
class pipe_list{
private:	
	pipe pip;
	int startX, step, startXfromBird ;
	std::vector<int> gatePos;
	int hi,lo;

	bool borning;
public:
	pipe_list( char* path = NULL, int w = 500, int ste = 100 );
	void loadTexture( SDL_Renderer* ren, char* path = "img/pipe.png");
	void render();

	void setHiLo( int h, int l );
	void setBorning( bool in );
	void setFresh( int w = 500 );

	void born();
	void update( int spe, int w = 500 );
	
	bool isCollision( elip eli );
	int upPoint( elip eli );

	int getSpace();
};

class game{
private:
	SDL_Renderer* renderer;

	pipe_list pip;
	bird _bird;
	myTexture ground;
	myTexture sky;

	int groundStartX ;
	unsigned width, height;
	unsigned int speed;
	unsigned int point;

	bool running ;
	enum gameState{
		waiting,
		started,
		collision,
		end,
		total
	};
	bool state[4];
	//add more
public:	
	TTF_Font* pointFont = TTF_OpenFont( "font/point.ttf", 50 );
	SDL_Color white = {255,255,255};
	void setBirdToStartPos( SDL_Renderer* ren = NULL, int hi = -1);
	void setWaiting();
	void setStarted();
	void setCollision();
	void setEnd();

	game( SDL_Renderer* ren = NULL, unsigned int spe = 10, unsigned int wi = 500, unsigned int hi = 700,  char*groundp="img/ground.jpg", char* skyp="img/sky.jpg");
	void runThings();
	void render();
	void update();

	SDL_Rect getGroundRect();

	void handleEvent( SDL_Event event );
};

bool init();
void close();