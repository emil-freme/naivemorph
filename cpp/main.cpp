#include <iostream>
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
    
    short f; 
    std::cin >> f;


    Bare::Img img = mm::readImg(width, height);
    // Img r = mm::contrastAndBrightnessAdjust(img, a, b);
    Bare::Img r = mm::posterize(img, f);
    mm::printImg(r);


    return 0;
}
