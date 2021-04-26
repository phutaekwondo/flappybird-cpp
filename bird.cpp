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
// void rotateline( int Ix, int Iy, int value, bool vertical, int angle, double &a, double &b ){
//     int nx, ny;
//     if ( vertical ){
//         rotate( Ix, Iy, value, 0, angle, nx, ny );
//         a = sin( (90 - angle) * elip::PI / 180 );
//     }
//     else {
//         rotate( Ix, Iy, 0, value, angle, nx, ny );
//         a = sin( angle * elip::PI / 180 );
//     }

//     b = double(ny) - a*double(nx);
// }
// int equaltion( double a, double b, double c, int &x1, int &x2 ){
//     double delta = b*b - 4*a*c;
//     if ( delta < 0 ) return 0 ;
//     if ( delta == 0 ){
//         x1 = x2 = int( -b/(2*a) );
//         return 1;
//     }
//     //delta > 0
//     x1 = int( (-b - sqrt(delta) ) / ( 2*a ) );
//     x2 = int( (-b + sqrt(delta) ) / ( 2*a ) );
//     return 2;
// }
bool cut( double Ix, double Iy, double R, double x1, double y1, double x2, double y2 ){
    double a, b, c;
    a = - ( y2 - y1 );
    b = ( x2 - x1 );
    c = -( a*x1 + b*y1 );

    // if not cut
    double dis = ( a*Ix + b*Iy + c ) / sqrt( a*a + b*b );
    if ( dis < 0 ) dis = -dis;
    if ( dis > R ) return false;

    // if one in
    double dis1 = distance( Ix, Iy, x1, y1 );
    double dis2 = distance( Ix, Iy, x2, y2 );
    if ( dis1 <= R || dis2 <= R ) return true;

    //2 out
    double px,py;
    if ( a == 0 ){
        px = Ix;
        py = -c / b;
    }
    else if ( b == 0 ){
        px = -c / a;
        py = Iy;
    }
    else{
        py = ( c - a*a/b*Iy + a*Ix ) / ( 0.0 - ( a*a/b + b ) );
        px = ( -b*py -c )/a;
    }

    x1 = x1 - px;
    y1 = y1 - py;
    x2 = x2 - px;
    y2 = y2 - py;

    if ( x1*x2 + y1*y2 < 0.0 ) return true;

    return false;
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
bool elip::isCollisionLine( int x1, int y1, int x2, int y2 ){
    //rotate 2 points
    rotate( x, y, x1, y1, -angle, x1, y1 );
    rotate( x, y, x2, y2, -angle, x2, y2 );

    // horizontal shrinking
    double Ix = double(x)   * double(h) / double(w) ;
    double Iy = double(y);  
    double sx1 = double(x1) * double(h) / double(w) ;
    double sx2 = double(x2) * double(h) / double(w) ;
    double sy1 = double( y1 );
    double sy2 = double( y2 );

    // //draw the circle
    // for (int i = int(Ix) - w/2; i <= int(Ix)+w/2 ; i++ ){
    //     for ( int j = int(Iy) - h/2; j <= int(Iy)+h/2; j++ ){
    //         if ( distance(  Ix, Iy, double(i), double(j)) <= double(h/2) ){
    //             SDL_RenderDrawPoint( renderer,i,j);
    //         }
    //     }
    // }
    // // draw line after shrinking
    // SDL_RenderDrawLine( renderer, int(sx1), int(sy1), int(sx2), int(sy2) );

    return cut( Ix, Iy, double(h/2), sx1, sy1, sx2, sy2 );
}
bool elip::isCollision( SDL_Rect rect ){
    // int runx, runy;
    // // with vertical edge 
    // int leftx = rect.x;
    // int rightx = rect.x + rect.w;
    // runy = rect.y;
    // for ( ;runy <= rect.y + rect.h; runy++ )
    //     if ( isInside( leftx, runy ) || isInside( rightx, runy ) ) return true;

    // // with horizontal
    // int topy = rect.y, boty = rect.y + rect.h;
    // //bug here
    // for( ; leftx<= rightx; leftx++ )
    //     if ( isInside( leftx, topy ) || isInside( leftx, boty ) ){ 
    //         return true;
    //     }
    
    // return false;

    //new method
    
    //parameter of the line 
    // with ver-edge
    // int lo = rect.y, hi = rect.y + rect.h;
    // if ( isCollisionLine( rect.x, hi, lo, true ) || isCollisionLine( rect.x+rect.w, hi, lo, true ))
    //     return true;
    
    // //with hor-edge
    // lo = rect.x; hi = lo + rect.w;
    // if ( isCollisionLine( rect.y, hi, lo, false ) || isCollisionLine( rect.y+rect.h, hi, lo, false ))
    //     return true;

    // return false;

    // another method 
    int x1,y1,x2,y2;
    // for above edge
    x1 = rect.x;            y1 = rect.y; 
    x2 = rect.x + rect.w;   y2 = rect.y;
    if ( isCollisionLine( x1, y1, x2, y2 ) ) return true;
    
    // for left edge
    x2 = rect.x;            y2 = rect.y + rect.h ;
    if ( isCollisionLine( x1, y1, x2, y2 ) ) return true;

    // for below edge
    x1 = rect.x + rect.w ;  y1 = rect.y + rect.h; 
    if ( isCollisionLine( x1, y1, x2, y2 ) ) return true;

    // for right edge
    x2 = rect.x + rect.w;   y2 = rect.y;
    if ( isCollisionLine( x1, y1, x2, y2 ) ) return true;
    
    // no one 
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

    angle = 0;

    cover.setRenderer( ren );
    cover.set( local.x + (local.w/2), local.y+(local.h/2), local.w, local.h, 0);

    isFalling = false;
    jumpspeed = spe;
    fallingspeed = 0;
}
void bird::render(){
    texture.render(local.x, local.y , NULL, angle );
}
void bird::jump(){
    // if the bird is not falling then don't jump
    if ( !isFalling ) return;

    // rotate the bird up when flap
    int updateAngle = -30;
    angle = updateAngle; 
    cover.setAngle( updateAngle );

    // flap up
    fallingspeed = -12;
}
void bird::drawCover(){
    cover.draw();
}
void bird::updateCover(){
    cover.set( local.x + (local.w/2), local.y+(local.h/2), local.w, local.h, angle );
}
void bird::setY( int y ){
    local.y = y;
    updateCover();
}
void bird::fall(){
    // check if bird is not falling then don't "fall"
    if ( !isFalling ) return;

    fallingspeed += bird::gravity;
    // below line is make falling speed limimted 
    int maxfallspeed = 8;
    if ( fallingspeed > maxfallspeed ) fallingspeed = maxfallspeed;
    setY( local.y + fallingspeed );

    // update angle if the bird when falling
    // make game more fancy
    if ( fallingspeed > 0 )
    {
        angle += 2;
        if ( angle > 30 ) angle = 30;
        updateCover();
    }
}
void bird::setFalling( bool fal ){
    isFalling = fal;
}
bool bird::isCollision( SDL_Rect rect ){
    return cover.isCollision( rect );
}
void bird::set( SDL_Renderer* ren, int x, int y, int spe, char* path ){
    renderer = ren;

    texture.setRenderer( ren );
    texture.loadImage( path );

    local = { x, y, texture.getW(), texture.getH() };

    angle = 0;

    cover.setRenderer( ren );
    cover.set( local.x + (local.w/2), local.y+(local.h/2), local.w, local.h, 0);

    isFalling = false;
    jumpspeed = spe;
    fallingspeed = 0;
}
elip bird::getElip(){
    return cover;
}

