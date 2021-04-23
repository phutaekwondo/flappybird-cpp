#include"header.h"


myTexture::myTexture( SDL_Renderer* renderer ){
    texture = NULL;
    width   = 0;
    height  = 0;
    windowRenderer = renderer;
} 
myTexture::~myTexture(){
    free();
}
void myTexture::loadImage(char* path){
    SDL_Surface* loadSurface = NULL;
    loadSurface = IMG_Load(path);
    if ( loadSurface == NULL ){
	std::cout<<"Can not load "<<path<<std::endl;
	return;
    }	

    free();
    texture = SDL_CreateTextureFromSurface( windowRenderer, loadSurface );
    width   = loadSurface->w;
    height  = loadSurface->h;
    SDL_FreeSurface( loadSurface );
    loadSurface = NULL;
}
void myTexture::loadImage( char* path, int w, int h ){
    SDL_Surface* base = SDL_CreateRGBSurface( 0, w,h, 32, 0,0,0,0 );
    SDL_Surface* loadImage = IMG_Load( path );
    if ( loadImage == NULL ){
        std::cout<<"can not load "<<path<<std::endl;
        return;
    }
    free();
    if ( SDL_BlitScaled( loadImage, NULL, base, NULL ) ){
        std::cout<< "resize loaded image fail!\n";
        return;
    }
    texture = SDL_CreateTextureFromSurface( windowRenderer, base );
    width   = w;
    height  = h;
    SDL_FreeSurface( loadImage );
    SDL_FreeSurface( base );
    loadImage = NULL;
    base      = NULL;
}
void myTexture::free(){
    if ( texture != NULL ){
	SDL_DestroyTexture( texture );
	texture = NULL;
	width   = 0 ;
	height  = 0 ;
    }
}
void myTexture::render(int x, int y, SDL_Rect* clip , double angle , SDL_Point* center, SDL_RendererFlip flipping ){
    SDL_Rect des = { x, y, width, height };
    SDL_RenderCopyEx( windowRenderer, texture, clip, &des, angle, center, flipping );

}
void myTexture::setColor(Uint8 r, Uint8 g, Uint8 b){
	SDL_SetTextureColorMod( texture, r,g,b);
}
int myTexture::getW(){ return width; }
int myTexture::getH(){ return height; }
void myTexture::setAlphaMod( Uint8 alpha ){
    SDL_SetTextureAlphaMod( texture, alpha );
}
void myTexture::setRenderer( SDL_Renderer* ren ){
    windowRenderer = ren;
}
