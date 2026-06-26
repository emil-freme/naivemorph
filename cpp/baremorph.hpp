#include <cmath>
#include <cstdint>
#include <vector>

namespace Bare{

    using buint = uint8_t;
    using Img_data =  std::vector<buint>;

    class Img{
        public:
        buint width; 
        buint height; 
        Img_data data;

        Img(buint w, buint h);

        buint& operator[](size_t i, size_t j);
        buint operator[](size_t i, size_t j) const;
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
            Img dil0();

            Img dil1();

            Img ero0();
            Img ero1();

            Img open0();

            Img close0();

            Img tophat0();

            Img blackhat();



            void printImg(Img &img);
    
    };

}
