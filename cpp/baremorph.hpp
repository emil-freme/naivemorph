
#ifndef BARE_MORPH_INCLUDE_H
#define BARE_MORPH_INCLUDE_H

#include <cmath>
#include <cstdint>
#include <vector>

namespace Bare{

    using buint = uint8_t;
    using Img_data =  std::vector<buint>;
    using SE_data = std::vector<int>;

    class Img{
        public:
        buint width; 
        buint height; 
        Img_data data;

        Img(buint w, buint h);

        buint& operator[](size_t i, size_t j);
        buint operator[](size_t i, size_t j) const;
    };

    class SElem{
        public:
        buint width; 
        buint height; 
        SE_data data;

        SElem(buint w, buint h);

        SElem reflect() const;

        int& operator[](size_t i, size_t j);
        int operator[](size_t i, size_t j) const;
    };

    namespace Metrics{
        float euclidean();

        //city block
        float manhattan();

        //chessboard
        float chebyshev();
    }

    namespace Morph{

            //mm.readImg() TODO: Better image data structure
            Img readImg(buint w, buint h);

            Img readElem(buint w, buint h);

            Img contrastAndBrightnessAdjust(const Img &in, float a, buint b);

            Img subsampling(const Img &in, buint f);

            //Uniform Quantization
            Img posterize(const Img &in, buint b);

            Img translate(const Img &in, int dx, int dy);

            Img rotate(const Img &in, int e);

            //TODO: Interpolação
            Img scale(const Img &in, float sx, float sy);

            Img shear(const Img &in, float sx, float sy);

            Img warpAffine(const Img &in, float a, float b, float tx, 
                          float c, float d, float ty);

            //Definir parametros
            Img perspective_transform();

            //Add Saturação constante
            Img addm(const Img &in, float a);

            Img blend(const Img &in1, const Img &in2, float alpha); 

            Img neg(const Img &in);
            Img bnot(const Img &in);

            Img equalize(const Img &in, int b);
            Img hist(const Img &in, int b);

            //Bitwise and
            Img band(const Img &in, const Img &mask);

            Img blur0(const Img &in, int n);

            Img lapacian0();

            Img sobel0();

            Img median0();

            Img usm0();

            //Usar Limiarização de Otsu
            Img threshold(const Img &in);
            //Limiarização binária
            Img threshold(const Img &in, int l);

            //Dilatação
            Img dil0(const Img &in, const  SElem &se);

            Img dil1(const Img &in, const  SElem &se);

            Img ero0(const Img &in, const  SElem &se);

            Img ero1(const Img &in, const  SElem &se);

            Img open0(const Img &in, const  SElem &se);

            Img close0(const Img &in, const  SElem &se);

            Img tophat0();

            Img blackhat();



            void printImg(Img &img);
            void printSE(SElem &se);
    
    };

}

#endif //BARE_MORPH_INCLUDE_H

#ifdef BARE_MORPH_IMPLEMENTATION

#include <iostream>
#include <algorithm>

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

    SElem::SElem(buint w, buint h){

        width = w;
        height = h; 
        data = SE_data(w*h, 0);
    }

    SElem SElem::reflect() const {
        SElem reflected(width, height);

        for(size_t i = 0; i < height; i++){
            for(size_t j = 0; j < width; j++){
               
                int ri = height - 1 - i; 
                int rj = width - 1 - j; 

                reflected[ri, rj] = (*this)[i, j];

            }
        }
        return reflected;
    }

    int& SElem::operator[](size_t i, size_t j){
        
        return data[i * width + j];
    }

    int SElem::operator[](size_t i, size_t j) const {

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

    
    Img Morph::readElem(buint w, buint h){

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


    Img Morph::ero0(const Img &in, const  SElem &se){

        Img out(in.width, in.height);

        std::vector<uint8_t> neight(se.width * se.height, 0);
        for(size_t i = 0; i < in.height; i++){
            for(size_t j = 0; j < in.width; j++){

                //Deslisando o elemento estruturante
                for(size_t si = 0; si < se.height; si++){
                    for(size_t sj = 0; sj < se.width; sj++){
                        
                        //mapeamento para a imagem original
                        int ii = i + si-se.height/2;
                        int ij = j + sj-se.width/2;

                        if( se[si, sj] == 0 ||
                            ii < 0 || ii >= in.height ||
                            ij < 0 || ij >= in.width 
                            ){
                            neight[si * se.width + sj] = 255;
                            continue;
                        }

                        neight[si * se.width + sj] = in[ii, ij];

                    }
                }
                out[i, j] = std::ranges::min(neight);

            }
        }
        return out;
    }

    Img Morph::ero1(const Img &in, const  SElem &se){

        Img out(in.width, in.height);

        std::vector<int> neight(se.width * se.height, 0);
        for(size_t i = 0; i < in.height; i++){
            for(size_t j = 0; j < in.width; j++){

                //Deslisando o elemento estruturante
                for(size_t si = 0; si < se.height; si++){
                    for(size_t sj = 0; sj < se.width; sj++){
                        
                        //mapeamento para a imagem original
                        int ii = i + si-se.height/2;
                        int ij = j + sj-se.width/2;

                        if( ii < 0 || ii >= in.height ||
                            ij < 0 || ij >= in.width 
                            ){
                            neight[si * se.width + sj] = 255;
                            continue;
                        }

                        neight[si * se.width + sj] = in[ii, ij] - se[si, sj];

                    }
                }
                out[i, j] = std::ranges::min(neight);

            }
        }
        return out;
    }

    Img Morph::dil0(const Img &in, const  SElem &se){

        Img out(in.width, in.height);

        SElem rse = se.reflect();

        std::vector<uint8_t> neight(rse.width * rse.height, 0);
        for(size_t i = 0; i < in.height; i++){
            for(size_t j = 0; j < in.width; j++){

                //Deslisando o elemento estruturante
                for(size_t si = 0; si < rse.height; si++){
                    for(size_t sj = 0; sj < rse.width; sj++){
                
                        //mapeamento para a imagem original
                        int ii = i + si-rse.height/2;
                        int ij = j + sj-rse.width/2;

                        if( rse[si, sj] == 0 ||
                            ii < 0 || ii >= in.height ||
                            ij < 0 || ij >= in.width 
                            ){
                            //Aqui estou usando 0 por ele é minimo de uint8_t
                            //caso fosse outro tipo deveria ser o minimo do
                            //tipo.
                            neight[si * rse.width + sj] = 0;
                            continue;
                        }

                        neight[si * rse.width + sj] = in[ii, ij];

                    }
                }
                out[i, j] = std::ranges::max(neight);

            }
        }
        return out;
    }

    Img Morph::dil1(const Img &in, const  SElem &se){

        Img out(in.width, in.height);

        // SElem rse = se.reflect(); Com SE ponderado não se reflete;

        std::vector<int> neight(se.width * se.height, 0);
        for(size_t i = 0; i < in.height; i++){
            for(size_t j = 0; j < in.width; j++){

                //Deslisando o elemento estruturante
                for(size_t si = 0; si < se.height; si++){
                    for(size_t sj = 0; sj < se.width; sj++){
                
                        //mapeamento para a imagem original
                        int ii = i + si-se.height/2;
                        int ij = j + sj-se.width/2;

                        if( ii < 0 || ii >= in.height ||
                            ij < 0 || ij >= in.width 
                            ){
                            //Aqui estou usando 0 por ele é minimo de uint8_t
                            //caso fosse outro tipo deveria ser o minimo do
                            //tipo.
                            neight[si * se.width + sj] = 0;
                            continue;
                        }

                        neight[si * se.width + sj] = in[ii, ij] + se[si, sj];

                    }
                }
                out[i, j] = std::ranges::max(neight);

            }
        }
        return out;
    }


    Img Morph::open0(const Img &in, const  SElem &se){
        return Morph::dil0(Morph::ero0(in, se), se);
    }


    Img Morph::close0(const Img &in, const  SElem &se){
        return Morph::ero0(Morph::dil0(in,se), se);
    }

    void Morph::printImg(Img &img){

        for(size_t i = 0; i < img.height; i++){
            for(size_t j = 0; j < img.width; j++){
                std::cout << +img[i, j] << " ";
            }
            std::cout << "\n";
        }
    }

    void Morph::printSE(SElem &se){

        for(size_t i = 0; i < se.height; i++){
            for(size_t j = 0; j < se.width; j++){
                std::cout << +se[i, j] << " ";
            }
            std::cout << "\n";
        }
    }

}

#endif

