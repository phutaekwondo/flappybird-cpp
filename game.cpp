#include"header.h"

game::game( SDL_Renderer* ren, unsigned int spe, unsigned int wi, unsigned int hi, char* groundp, char* skyp ){
    renderer = ren;
    ground.setRenderer( ren );
    sky.setRenderer( ren );

    ground.loadImage(groundp);
    sky.loadImage(skyp);
    point = 0 ;
    groundStartX = 0;
    speed = spe;
    width = wi;
    height = hi;
}
void game::runThings(){
    groundStartX -= speed;
    if ( groundStartX < -ground.getW() ){
        groundStartX += ground.getW() ;
    }
}
void game::render(){
    //render background sky
    int filled = 0;
    //repeat render background until filled the screen
    while ( filled < width ){
        sky.render(filled);
        filled += sky.getW();
    }

    //render ground
    filled = groundStartX;

    //repeat render like sky
    while ( filled < int(width) ){
        ground.render( filled , height - ground.getH() );
        filled += ground.getW();
    }
}
SDL_Rect game::getGroundRect(){
    SDL_Rect res = { 0, height - ground.getH(), ground.getW(), ground.getH() };
    return res;
}

