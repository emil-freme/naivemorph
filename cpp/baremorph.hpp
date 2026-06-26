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

            void printImg(Img &img);
    
    };

}
