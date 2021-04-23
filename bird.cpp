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



