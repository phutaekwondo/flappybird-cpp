#include"header.h"

game::game( SDL_Renderer* ren, unsigned int spe, unsigned int wi, unsigned int hi, char* groundp, char* skyp ){
    renderer = ren;
    ground.setRenderer( ren );
    sky.setRenderer( ren );
    over.setRenderer( ren );

    //load sound
    wing = Mix_LoadWAV( "sound/wing.wav" );
    pointUp = Mix_LoadWAV( "sound/point.wav" );
    hit  = Mix_LoadWAV( "sound/hit.wav"  );

    ground.loadImage(groundp);
    sky.loadImage(skyp);
    over.loadImage( "img/over.png");
    setBirdToStartPos( ren, hi );

    unsigned int border = 70;
    pip.loadTexture( ren );
    pip.setHiLo( border, hi - ground.getH() - border - pip.getSpace() );

    point = 0 ;
    groundStartX = 0;

    speed = spe;
    width = wi;
    height = hi;

    running = true;
    std::fill_n(state, 4, false);
    setWaiting();
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
    
    // render pipes
    pip.render();

    //render bird
    _bird.render();

    //render ground
    filled = groundStartX;

    //repeat render like sky
    while ( filled < int(width) ){
        ground.render( filled , height - ground.getH() );
        filled += ground.getW();
    }

    // render point
    std::string pstr = std::to_string( point );
    char *pch = new char[ pstr.length() ];
    strcpy( pch, pstr.c_str() ); 
    myTexture ptex( renderer );
    ptex.loadText( pch, pointFont, white );
    ptex.render( ( width - ptex.getW() )/2, 50 );


    //render "game over" if game is end
    if ( state[ end ] ){
        over.render( ( width - over.getW() )/2, ( height - over.getH() )/2 - 100 );
    }
}
SDL_Rect game::getGroundRect(){
    SDL_Rect res = { 0, height - ground.getH(), ground.getW(), ground.getH() };
    return res;
}
void game::update(){
    // run things 
    if ( running ){
        runThings();
    }
    // bird jump or falling 
    _bird.fall();

    //pipe update
    pip.update( speed, width );

    //update point 
    int up  = pip.upPoint( _bird.getElip() );
    point += up;

    render(); 

    if ( up > 0 ){
        Mix_PlayChannel( -1, pointUp , 0);
    } 

    // check collision 
    if ( state[ started ] && pip.isCollision( _bird.getElip() ) ) {
        _bird.jump();
        Mix_PlayChannel( -1, hit, 0 );
        setCollision();
    }

    if ( _bird.isCollision( getGroundRect() ) ){
        setEnd();
    }
}
void game::setBirdToStartPos( SDL_Renderer* ren, int hi ){
    if ( ren == NULL ) ren = renderer;
    if ( hi < 0 ) hi = height;
    _bird.set( ren, 90,(hi - ground.getH())/2-40 );
    _bird.setFalling( false );
}
void game::setWaiting(){
    std::fill_n( state, 4, false );
    state[ waiting ] = true;

    point = 0;

    running = true;

    pip.setBorning( false );
    pip.setFresh();
    
    _bird.setFalling( false );
    setBirdToStartPos();
}
void game::setStarted(){
    std::fill_n( state, 4, false );
    state[ started ] = true;

    running = true;

    pip.setBorning( true );

    _bird.setFalling( true );
}
void game::setCollision(){
    std::fill_n( state, 4, false );
    state[ collision ] = true;

    pip.setBorning( false );

    running = false;

    _bird.setFalling( true );
}
void game::setEnd(){
    std::fill_n( state, 4, false );
    state[ end ] = true;

    running = false;

    pip.setBorning( false );

    _bird.setFalling( false );
}
void game::handleEvent( SDL_Event event ){
    if ( event.type == SDL_KEYDOWN ){
        if ( event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP ){
            if ( state[ waiting ] ){
                setStarted();
            }
            if ( state[ started ] ){
                _bird.jump();
                Mix_PlayChannel( -1, wing, 0 );
            }
            if ( state[ end ] ){
                setWaiting();
            }
        }
    }
}


