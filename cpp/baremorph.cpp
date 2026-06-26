#include <iostream>
#include <cassert>
#include <algorithm>
#include "baremorph.hpp"

namespace Bare{

    Img::Img(buint w, buint h){

        width = w;
        height = h; 
        data = Img_data(w*h, 0);
    }

    buint& Img::operator[](size_t i, size_t j){
        
        return data[i * width + j];
    }

    buint Img::operator[](size_t i, size_t j) const {

        return data[i * width + j];
    }


    Img Morph::readImg(buint w, buint h){

        Img img(w, h);
        int pixel; 
        for(size_t i = 0; i < h; i++){
            for(size_t j = 0; j < w; j++){
                std::cin >> pixel;
                
                img[i, j] = pixel;
            }
        }
        return img;
    }

    Img Morph::contrastAndBrightnessAdjust(const Img &in, float a, buint b){

        Img out(in.width, in.height);
        for(size_t i = 0; i < (in.width * in.height); i++){
            int pixel = a * in.data[i] + b;
            out.data[i] = std::clamp(pixel, 0, 255);
        }
        return out;
    }

    Img Morph::subsampling(const Img &in, buint f){

        Img out(in.width / f, in.height / f);

        for(size_t i = 0; i < out.height; i++){
            for(size_t j = 0; j < out.width; j++){
                out[i, j] = in[i*f, j*f];
            }
        }
        return out;
    }

    Img Morph::posterize(const Img &in, buint b){

        Img out(in.width, in.height);
        int step = 256 / (1 << b); //pow (2, b)
        for(int i = 0; i < in.width * in.height; i++){
            out.data[i] = in.data[i]/step;
        }
        return out;
    }


    void Morph::printImg(Img &img){

        for(size_t i = 0; i < img.height; i++){
            for(size_t j = 0; j < img.width; j++){
                std::cout << +img[i, j] << " ";
            }
            std::cout << "\n";
        }
    }


}
