// I use this file to define class elip method and class bird method
#include"header.h"

elip::elip( SDL_Renderer* ren, int inx , int iny , int inw , int inh  ){
    renderer = ren;
    x = inx;
    y = iny;
    w = inw;
    h = inh;
    angle = 0;
}
void elip::setX( int inx ){
    x = inx ;
}
void elip::setY( int iny ){
    y = iny ;
}
void elip::setW( int inw ){
    w = inw;
}
void elip::setH( int inh ){
    h = inh;
}
void elip::setAngle( int inangle ){
    angle = inangle;
}
void elip::set( int inx, int iny, int inw, int inh, int inangle ){
    x = inx;
    y = iny;
    w = inw;
    h = inh;
    angle = inangle;
}
double distance( double x, double y, double a, double b ){
    return sqrt( pow(x-a,2) + pow(y-b,2) );
}
void rotate( int x, int y, int a, int b, int angle, int &outx, int &outy ){
    double an = double(angle)*(elip::PI)/180.0;
    double vx = double(a-x);
    double vy = double(b-y);

    double rvx = cos(an)*vx - sin(an)*vy;
    double rvy = sin(an)*vx + cos(an)*vy;
    outx = x + int(rvx);
    outy = y + int(rvy);
}
void elip::draw(){
    //set color to white
    SDL_SetRenderDrawColor( renderer, 255, 255 ,255 , 100 );
    double a,b,c;
    a = double( w )/2;
    b = double( h )/2;
    c = sqrt( a*a - b*b );

    int startx = x-w/2, starty = y-h/2;
    for ( int i = x - w/2; i <= x + w/2 ; i++ ){
        for( int j = y - h/2; j <= y + h/2; j++ ){
            double dis = distance( i,j,double(x)-c,y ) + distance( i,j,double(x) + c,y );
            if (dis<=a*2 && dis>= a*2-5){
                if ( angle == 0 )
                    SDL_RenderDrawPoint( renderer, i,j );
                else{
                    int rx , ry;
                    rotate( x,y,i,j,angle,rx,ry );
                    SDL_RenderDrawPoint( renderer, rx, ry );
                }
            }
        }
    }
}
bool elip::isInside( int inx, int iny ){
    double a,b,c;
    a = double( w )/2;
    b = double( h )/2;
    c = sqrt( a*a - b*b );

    int rx,ry;
    rotate(x,y,inx,iny,-angle,rx,ry);
    double dis = distance( rx,ry,double( x )-c,y ) + distance( rx,ry,double( x )+c, y );
    return dis<=(a*2);
}
bool elip::isCollision( SDL_Rect rect ){
    int runx, runy;
    // with vertical edge 
    int leftx = rect.x;
    int rightx = rect.x + rect.w;
    runy = rect.y;
    for ( ;runy <= rect.y + rect.h; runy++ )
        if ( isInside( leftx, runy ) || isInside( rightx, runy ) ) return true;

    // with horizontal
    int topy = rect.y, boty = rect.y + rect.h;
    for( ; leftx<= rightx; leftx++ )
        if ( isInside( leftx, topy ) || isInside( leftx, boty ) ) return true;
    
    return false;
}
void elip::setRenderer( SDL_Renderer* ren ){
    renderer = ren;
}

bird::bird( SDL_Renderer* ren, int x, int y, int spe, char* path ){
    renderer = ren;
    texture.setRenderer( ren );
    texture.loadImage( path );
    local = { x, y, texture.getW(), texture.getH() };
    cover.set( local.x + (local.w/2), local.y+(local.h/2), local.w, local.h, 0);
    jumpspeed = spe;
    fallingspeed = 0;
}
void bird::render(){
    texture.render(local.x, local.y );
}