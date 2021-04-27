#include"header.h"

pipe::pipe( myTexture* tex ){
    texturePointer = tex;
    startX = 0;
    // this is space of gate
    // space of gate is distance from above pipe to below pipe
    space = 200;
    startX = 0;
    gatePos = 100;
}
void pipe::render(){
    //render above pipe 
    texturePointer->render( startX, gatePos - texturePointer->getH(), NULL, 180 );

    // render below pipe
    texturePointer->render( startX, gatePos + space );
}
void pipe::set( int x, int pos, int spa ){
    startX = x;
    gatePos = pos;
    if ( spa >= 0 )
        space = spa;
}
void pipe::setTexture( myTexture* tex ){
    texturePointer = tex;
}
bool pipe::isCollision( elip eli ){
    SDL_Rect above = { startX, gatePos - texturePointer->getH(), texturePointer->getW(), texturePointer->getH() };
    // check collision elip with above
    //bug here
    if ( eli.isCollision( above ) ) return true;

    //set #above is the bot pipe rect
    above.y = gatePos + space;
    if ( eli.isCollision( above ) ) return true;

    // elip is not collision with any pipe
    return false;
}
int pipe::getW(){
    return texturePointer->getW();
}
int pipe::getSpace(){
    return space;
}

// pipe list class
pipe_list::pipe_list( char* path, int w, int ste ){
    borning = false;
    int startTrail = 200;
    startX = w + startTrail ; 
    startXfromBird = w + startTrail ;
    //step is distance between two gate
    step = ste;
}
void pipe_list::loadTexture( SDL_Renderer* ren, char* path ){
    if ( ren == NULL || path == NULL ) return;
    myTexture* tex = new myTexture;
    tex->setRenderer( ren );
    tex->loadImage( path );
    pip.setTexture( tex );
}
void pipe_list::render(){
    int filled = startX;

    for( int i = 0; i < gatePos.size(); i++ ){
        pip.set( filled, gatePos[i] );
        pip.render();
        filled += pip.getW() + step;
    }
}
void pipe_list::setHiLo( int h, int l ){
    hi = h;
    lo = l;
}
void pipe_list::setBorning( bool in ){
    borning = in;
}
void pipe_list::born(){
    if ( !borning ) return;
    gatePos.push_back( (rand()%( lo - hi ) + hi ) );
}
void pipe_list::update( int spe, int w ){
    // if pipe is not borning, then do nothing 
    if ( !borning ) return;

    if ( startX + pip.getW() < 0 ){
        startX += pip.getW() + step;
        gatePos.erase( gatePos.begin() );
    }
    if ( startX + ( pip.getW() + step )*gatePos.size() <= w )
        born();
    
    // run pipes
    startX -= spe ;
    startXfromBird -= spe;
}
bool pipe_list::isCollision( elip eli ){
    int filled = startX;

    int size = gatePos.size();
    if ( size == 0 ) return false;

    for( int i = 0; i < size; i++ ){
        pip.set( filled, gatePos[i] );
        if ( pip.isCollision( eli ) ) return true;
        filled += pip.getW() + step;
    }

    return false;
}
int pipe_list::upPoint( elip eli ){
    if ( startXfromBird <= eli.getX() ){
        startXfromBird += pip.getW() + step;
        return 1;
    }
    return 0;
}
int pipe_list::getSpace(){
    return pip.getSpace();
}
void pipe_list::setFresh( int w ){
    gatePos.clear();

    int startTrail = 200;
    startX = w + startTrail ; 
    startXfromBird = w + startTrail ;
}

