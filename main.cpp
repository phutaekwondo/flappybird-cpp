#include"header.h"

// global variable
const int WIDTH  = 500 ;
const int HEIGHT = 700 ;
const int FPS    = 60 ;
SDL_Window* gwindow = NULL;
SDL_Renderer* gwindowRenderer = NULL;

// double distance( double x, double y, double a, double b );
// void drawElip( int x, int y, int w, int h );

int main( int argc, char* argv[] ){
    if ( ! init() ){
        std::cout<<"init fail !\n";
        return 0;
    }
    //handle fps
    Uint32 perF = 1000/FPS;

    //test game class
    game test( gwindowRenderer, 5 );
    bird chim( gwindowRenderer, 100,100 );

    SDL_Rect ground = test.getGroundRect();


    // quit event handle
    bool quit = false;
    SDL_Event event;   
    while ( !quit ){
        //handle FPS 
        Uint32 start = SDL_GetTicks();

        //handle event
        while ( SDL_PollEvent( &event ) != 0 ){
            if ( event.type == SDL_QUIT ) quit = true;
            else if ( event.type == SDL_KEYDOWN ){
                if ( event.key.keysym.sym == SDLK_UP ) {
                    chim.setFalling( true );
                    chim.jump();
                }
            }
        }
        //handle keystate
        // const Uint8* keyboardstate = SDL_GetKeyboardState( NULL );
        // if ( keyboardstate[ SDL_SCANCODE_UP] )     roundy --;
        // if ( keyboardstate[ SDL_SCANCODE_DOWN ] )  roundy ++;
        // if ( keyboardstate[ SDL_SCANCODE_LEFT ] )  roundx --;
        // if ( keyboardstate[ SDL_SCANCODE_RIGHT ] ) roundx ++;


        // set renderer draw color to black 
        SDL_SetRenderDrawColor( gwindowRenderer, 0,0,0,255 );
        // clear renderer
        SDL_RenderClear( gwindowRenderer );

        test.runThings();
        test.render();
        if ( chim.isCollision( ground ) ) chim.setFalling( false );
        chim.fall();
        chim.render();
        chim.drawCover();



        //update the screen
        SDL_RenderPresent( gwindowRenderer );

        //handle FPS
        Uint32 end = SDL_GetTicks();
        if ( end - start < perF ) SDL_Delay( perF - (end-start) );
    }
    close();
    return 0;
}



// init Fuction
bool init(){
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
        std::cout<<"init SDL fail !\n";
        return false;
    }
    //init ttf lib
    if ( TTF_Init() < 0 ){
        std::cout<<"init SDL_ttf fail!\n";
        return false;
    }

    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
    int initted = IMG_Init( flags );
    if( ( initted&flags ) != flags ) {
        std::cout<<"init SDL_ image fail !\n";
        return false;
    }

    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
	    std::cout<<"SDL Mixer library init FAIL!!\n";
	    return false;
	}

    gwindow = SDL_CreateWindow( "flappy bird", SDL_WINDOWPOS_UNDEFINED ,SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0 );
    if ( gwindow == NULL ){
        std::cout<<"create gwindow fail!\n";
        return false;
    } 

    gwindowRenderer = SDL_CreateRenderer( gwindow, -1, SDL_RENDERER_ACCELERATED );
    if ( gwindowRenderer == NULL ) {
        std::cout<<"create renderer fail!\n";
        return false;
    }

    return true;
}
void close(){
    SDL_DestroyRenderer( gwindowRenderer );
    gwindowRenderer = NULL;
    SDL_DestroyWindow( gwindow );
    gwindow = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

// THIS PART IS DEFINE DRAW ELIP FUCNTION
// THIS PART'S PURPOSE IS VISION THE ELIP ROUND THE BIRD
// THAT ELIP WILL BE USED FOR COLLISION DETECTION
// double distance( double x, double y, double a, double b ){
//     return sqrt( pow(x-a,2) + pow(y-b,2) );
// }
// void drawElip( int x, int y, int w, int h ){
//     //set color to white
//     SDL_SetRenderDrawColor( gwindowRenderer, 255, 255 ,255 , 100 );
//     double a,b,c;
//     a = double( w )/2;
//     b = double( h )/2;
//     c = sqrt( a*a - b*b );

//     int startx = x-w/2, starty = y-h/2;
//     for ( int i = x - w/2; i <= x + w/2 ; i++ ){
//         for( int j = y - h/2; j <= y + h/2; j++ ){
//             double dis = distance( i,j,double(x)-c,y ) + distance( i,j,double(x) + c,y );
//             if (dis<=a*2 && dis>= a*2-5){
//                 SDL_RenderDrawPoint( gwindowRenderer, i,j );
//             }
//         }
//     }
// }
