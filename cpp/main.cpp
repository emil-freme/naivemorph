#include <iostream>
#define BARE_MORPH_IMPLEMENTATION
#include  "baremorph.hpp" 

namespace mm = Bare::Morph;

int main(void){

    short width; 
    short height; 

    std::cin >> height;
    std::cin >> width;

    // float_t a;
    // short b; 
    // std::cin >> a >> b;
    
    // short f; 
    // std::cin >> f;


    Bare::Img img = mm::readImg(width, height);

    Bare::SElem se(3,3);
    se[0,1] = 1;
    se[1,0] = 1;
    se[1,1] = 1;
    se[1,2] = 1;
    se[2,1] = 1;

    std::cout << "\n";
    mm::printSE(se);
    std::cout << "\n";
    // Img r = mm::contrastAndBrightnessAdjust(img, a, b);
    Bare::Img r = mm::dil0(img, se);
    mm::printImg(r);


    return 0;
}
