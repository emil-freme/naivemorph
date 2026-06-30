#include <iostream>
#define NAIVE_MORPH_IMPLEMENTATION
#include  "naivemorph.hpp" 

namespace mm = Naive::Morph;

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


    Naive::Img img = mm::readImg(width, height);

    Naive::SElem se(3,3);
    se[0,0] = -1;
    se[0,1] = -1;
    se[0,2] = -1;
    se[1,0] = -1;
    se[1,1] =  0;
    se[1,2] = -1;
    se[2,0] = -1;
    se[2,1] = -1;
    se[2,2] = -1;

    std::cout << "\n";
    mm::printSE(se);
    std::cout << "\n";
    // Img r = mm::contrastAndBrightnessAdjust(img, a, b);
    Naive::SElem r = mm::dist0(img, se);
    mm::printSE(r);

    // std::cout << "\n";
    // r = mm::tophat0(img, se);
    // mm::printImg(r);
    //
    // std::cout << "\n";
    // r = mm::blackhat(img, se);
    // mm::printImg(r);

    return 0;
}
