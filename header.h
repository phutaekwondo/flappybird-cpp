#include<SDL_image.h>
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<cmath>
#include<cstring>
#include<string>
#include<sstream>

class myTexture{
private:
	SDL_Texture* texture;
	int width, height;
    SDL_Renderer* windowRenderer;
public:
	myTexture( SDL_Renderer* renderer = NULL );
	~myTexture();

	void loadImage(char* path);
    void loadImage( char* path, int w, int h );
	void free();
	void render(int x=0, int y=0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flipping = SDL_FLIP_NONE );
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setAlphaMod( Uint8 alpha );
	int  getW();
	int  getH();
	void setRenderer( SDL_Renderer* ren );
};
class game{
private:
	SDL_Renderer* renderer;
	myTexture ground;
	myTexture sky;
	unsigned width, height;
	unsigned int speed;
	unsigned int point;
	int groundStartX ;
	//add more
public:
	game( SDL_Renderer* ren = NULL, unsigned int spe = 10, unsigned int wi = 500, unsigned int hi = 700,  char*groundp="img/ground.jpg", char* skyp="img/sky.jpg");
	void runThings();
	void render();
};

//class bird
class elip{
private:
	SDL_Renderer* renderer;
	int x,y,w,h;
	int angle;
public:
	static constexpr const double PI = 3.141592653596;
	elip( SDL_Renderer* ren, int inx = 0, int iny = 0, int inw = 0, int inh = 0 );
	void draw();
	bool isCollision( SDL_Rect rect );
	void setX( int inx );
	void setY( int iny );
	void setW( int inw );
	void setH( int inh );
	void setAngle( int inangle );
	void set( int inx , int iny, int inw, int inh, int inangle );
};

bool init();
void close();