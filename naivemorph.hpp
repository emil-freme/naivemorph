
#ifndef NAIVE_MORPH_INCLUDE_H
#define NAIVE_MORPH_INCLUDE_H

#include <cmath>
#include <cstdint>
#include <vector>

namespace Naive {

using buint = uint8_t;
using Img_data = std::vector<buint>;
using SE_data = std::vector<int>;

class Img {
public:
  buint width;
  buint height;
  Img_data data;

  Img(buint w, buint h);

  buint &operator[](size_t i, size_t j);
  buint operator[](size_t i, size_t j) const;
  Img operator-(
      const Img &a) const; // Verificar se precisa ser para os mesmos tamanhos
  Img operator+(const Img &a) const;
};

class SElem {
public:
  buint width;
  buint height;
  SE_data data;

  SElem(buint w, buint h);

  /**
   * @brief Realiza a reflexão espacial (rotaciona 180 graus) do elemento
   * estruturante.
   * * Operação matemática fundamental para garantir a corretude geométrica da
   * dilatação quando o elemento estruturante não é simétrico.
   * * @return Uma nova instância de SElem contendo a máscara refletida.
   */
  SElem reflect() const;

  int &operator[](size_t i, size_t j);
  int operator[](size_t i, size_t j) const;
};

namespace Metrics {
float euclidean();

// city block
float manhattan();

// chessboard
float chebyshev();
} // namespace Metrics

namespace Morph {

/**
 * @brief Lê os dados de uma imagem a partir do fluxo de entrada padrão.
 * * Espera receber a largura, altura e a sequência de valores contíguos de
 * pixels.
 * * @note Atualmente acoplado rigidamente ao std::cin.
 * @return Uma nova instância preenchida da estrutura Img.
 */
Img readImg(buint w, buint h);

SElem readElem(buint w, buint h);

Img contrastAndBrightnessAdjust(const Img &in, float a, buint b);

Img subsampling(const Img &in, buint f);

// Uniform Quantization
Img posterize(const Img &in, buint b);

Img translate(const Img &in, int dx, int dy);

Img rotate(const Img &in, int e);

// TODO: Interpolação
Img scale(const Img &in, float sx, float sy);

Img shear(const Img &in, float sx, float sy);

Img warpAffine(const Img &in, float a, float b, float tx, float c, float d,
               float ty);

// Definir parametros
Img perspective_transform();

// Add Saturação constante
Img addm(const Img &in, float a);

/**
 * @brief Realiza o Blending (combinação linear) entre duas imagens.
 * Combina duas imagens utilizando um fator de transparência alfa
 * (ponderação).
 * @param in1 Primeira imagem de entrada.
 * @param in2 Segunda imagem de entrada.
 * @param alpha Fator de ponderação no intervalo [0.0, 1.0].
 * @return Nova imagem resultante da interpolação linear dos pixels.
 */
Img blend(const Img &in1, const Img &in2, float alpha);

/**
 * @brief Realiza a operação lógica/aritmética de negação (Inversão de Cores).
 * * Subtrai o valor de cada pixel do valor máximo permitido (255 -
 * pixel).
 * * @param in Imagem de entrada.
 * @return Nova imagem contendo o negativo fotográfico da entrada.
 */
Img neg(const Img &in);
Img bnot(const Img &in);

Img equalize(const Img &in, int b);
Img hist(const Img &in, int b);

// Bitwise and
Img band(const Img &in, const Img &mask);

Img blur0(const Img &in, int n);

Img lapacian0();

Img sobel0();

Img median0();

Img usm0();

// Usar Limiarização de Otsu
Img threshold(const Img &in);
// Limiarização binária
Img threshold(const Img &in, int l);

/**
 * @brief Executa a Dilatação Matemática Binária (Vizinhança Plana).
 * * Expande as regiões claras da imagem. Procura pelo valor máximo
 * na vizinhança delimitada pelo elemento estruturante refletido
 * espacialmente.
 * * @param in Imagem de entrada.
 * @param se Elemento estruturante definindo a vizinhança.
 * @return Imagem dilatada resultante.
 */
Img dil0(const Img &in, const SElem &se);

/**
 * @brief Executa a Dilatação em Tons de Cinza (Morfologia Ponderada).
 * * Considera os valores internos do elemento estruturante como
 * pesos aditivos adicionados à vizinhança antes do cálculo do valor
 * máximo local.
 * * @param in Imagem em tons de cinza de entrada.
 * @param se Elemento estruturante não-plano (ponderado).
 * @return Imagem resultante da dilatação em tons de cinza.
 */
Img dil1(const Img &in, const SElem &se);

/**
 * @brief Executa a Erosão Matemática Binária (Vizinhança Plana).
 * * Reduz as regiões claras da imagem. Procura pelo valor mínimo na
 * vizinhança delimitada pelo elemento estruturante.
 * * @param in Imagem de entrada.
 * @param se Elemento estruturante definindo a vizinhança.
 * @return Imagem erodida resultante.
 */
Img ero0(const Img &in, const SElem &se);

/**
 * @brief Executa a Erosão em Tons de Cinza (Morfologia Ponderada).
 * * Considera os valores internos do elemento estruturante como
 * pesos subtrativos subtraídos da vizinhança antes do cálculo do
 * valor mínimo local.
 * * @param in Imagem em tons de cinza de entrada.
 * @param se Elemento estruturante não-plano (ponderado).
 * @return Imagem resultante da erosão em tons de cinza.
 */
Img ero1(const Img &in, const SElem &se);

/**
 * @brief Aplica a operação morfológica de Abertura.
 * * Consiste em uma erosão seguida por uma dilatação utilizando o
 * mesmo elemento estruturante. É ideal para remover ruídos claros
 * pequenos e suavizar contornos externos.
 * * @param in Imagem de entrada.
 * @param se Elemento estruturante.
 * @return Imagem processada pela abertura.
 */
Img open0(const Img &in, const SElem &se);

/**
 * @brief Aplica a operação morfológica de Fechamento.
 * * Consiste em uma dilatação seguida por uma erosão utilizando o
 * mesmo elemento estruturante. É utilizada para preencher pequenos
 * buracos escuros e conectar regiões próximas.
 * * @param in Imagem de entrada.
 * @param se Elemento estruturante.
 * @return Imagem processada pelo fechamento.
 */
Img close0(const Img &in, const SElem &se);

Img grad0(const Img &in, const SElem &se);

Img tophat0(const Img &in, const SElem &se);

Img blackhat(const Img &in, const SElem &se);

Img dist0(const Img &in, const SElem &se);

void printImg(Img &img);
void printSE(SElem &se);

}; // namespace Morph

} // namespace Naive

#endif // NAIVE_MORPH_INCLUDE_H

#ifdef NAIVE_MORPH_IMPLEMENTATION

#include <algorithm>
#include <cassert>
#include <iostream>

namespace Naive {

Img::Img(buint w, buint h) {

  width = w;
  height = h;
  data = Img_data(w * h, 0);
}

buint &Img::operator[](size_t i, size_t j) { return data[i * width + j]; }

buint Img::operator[](size_t i, size_t j) const { return data[i * width + j]; }

Img Img::operator-(const Img &a) const {
  assert(height == a.height && width == a.width &&
         "Imagens devem ser de mesmo tamanho");

  Img out(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Solucionar problema de overflow e underflor
      int px = (*this)[i, j] - a[i, j];
      px = px < 255 ? px : 255;
      out[i, j] = px > 0 ? px : 0;
    }
  }
  return out;
}

Img Img::operator+(const Img &a) const {
  assert(height == a.height && width == a.width &&
         "Imagens devem ser de mesmo tamanho");

  Img out(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Solucionar problema de overflow e underflor
      int px = (*this)[i, j] + a[i, j];
      px = px < 255 ? px : 255;
      out[i, j] = px > 0 ? px : 0;
    }
  }
  return out;
}

SElem::SElem(buint w, buint h) {

  width = w;
  height = h;
  data = SE_data(w * h, 0);
}

SElem SElem::reflect() const {
  SElem reflected(width, height);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {

      int ri = height - 1 - i;
      int rj = width - 1 - j;

      reflected[ri, rj] = (*this)[i, j];
    }
  }
  return reflected;
}

int &SElem::operator[](size_t i, size_t j) { return data[i * width + j]; }

int SElem::operator[](size_t i, size_t j) const { return data[i * width + j]; }

Img Morph::readImg(buint w, buint h) {

  Img img(w, h);
  int pixel;
  for (size_t i = 0; i < h; i++) {
    for (size_t j = 0; j < w; j++) {
      std::cin >> pixel;

      img[i, j] = pixel;
    }
  }
  return img;
}

Img Morph::readElem(buint w, buint h) {

  Img img(w, h);
  int pixel;
  for (size_t i = 0; i < h; i++) {
    for (size_t j = 0; j < w; j++) {
      std::cin >> pixel;

      img[i, j] = pixel;
    }
  }
  return img;
}

Img Morph::contrastAndBrightnessAdjust(const Img &in, float a, buint b) {

  Img out(in.width, in.height);
  for (size_t i = 0; i < (in.width * in.height); i++) {
    int pixel = a * in.data[i] + b;
    out.data[i] = std::clamp(pixel, 0, 255);
  }
  return out;
}

Img Morph::subsampling(const Img &in, buint f) {

  Img out(in.width / f, in.height / f);

  for (size_t i = 0; i < out.height; i++) {
    for (size_t j = 0; j < out.width; j++) {
      out[i, j] = in[i * f, j * f];
    }
  }
  return out;
}

Img Morph::posterize(const Img &in, buint b) {

  Img out(in.width, in.height);
  int step = 256 / (1 << b); // pow (2, b)
  for (int i = 0; i < in.width * in.height; i++) {
    out.data[i] = in.data[i] / step;
  }
  return out;
}

Img Morph::ero0(const Img &in, const SElem &se) {

  Img out(in.width, in.height);

  std::vector<uint8_t> neight(se.width * se.height, 0);
  for (size_t i = 0; i < in.height; i++) {
    for (size_t j = 0; j < in.width; j++) {

      // Deslisando o elemento estruturante
      for (size_t si = 0; si < se.height; si++) {
        for (size_t sj = 0; sj < se.width; sj++) {

          // mapeamento para a imagem original
          int ii = i + si - se.height / 2;
          int ij = j + sj - se.width / 2;

          if (se[si, sj] == 0 || ii < 0 || ii >= in.height || ij < 0 ||
              ij >= in.width) {
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

Img Morph::ero1(const Img &in, const SElem &se) {

  Img out(in.width, in.height);

  std::vector<int> neight(se.width * se.height, 0);
  for (size_t i = 0; i < in.height; i++) {
    for (size_t j = 0; j < in.width; j++) {

      // Deslisando o elemento estruturante
      for (size_t si = 0; si < se.height; si++) {
        for (size_t sj = 0; sj < se.width; sj++) {

          // mapeamento para a imagem original
          int ii = i + si - se.height / 2;
          int ij = j + sj - se.width / 2;

          if (ii < 0 || ii >= in.height || ij < 0 || ij >= in.width) {
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

Img Morph::dil0(const Img &in, const SElem &se) {

  Img out(in.width, in.height);

  SElem rse = se.reflect();

  std::vector<uint8_t> neight(rse.width * rse.height, 0);
  for (size_t i = 0; i < in.height; i++) {
    for (size_t j = 0; j < in.width; j++) {

      // Deslisando o elemento estruturante
      for (size_t si = 0; si < rse.height; si++) {
        for (size_t sj = 0; sj < rse.width; sj++) {

          // mapeamento para a imagem original
          int ii = i + si - rse.height / 2;
          int ij = j + sj - rse.width / 2;

          if (rse[si, sj] == 0 || ii < 0 || ii >= in.height || ij < 0 ||
              ij >= in.width) {
            // Aqui estou usando 0 por ele é minimo de uint8_t
            // caso fosse outro tipo deveria ser o minimo do
            // tipo.
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

Img Morph::dil1(const Img &in, const SElem &se) {

  Img out(in.width, in.height);

  // SElem rse = se.reflect(); Com SE ponderado não se reflete;

  std::vector<int> neight(se.width * se.height, 0);
  for (size_t i = 0; i < in.height; i++) {
    for (size_t j = 0; j < in.width; j++) {

      // Deslisando o elemento estruturante
      for (size_t si = 0; si < se.height; si++) {
        for (size_t sj = 0; sj < se.width; sj++) {

          // mapeamento para a imagem original
          int ii = i + si - se.height / 2;
          int ij = j + sj - se.width / 2;

          if (ii < 0 || ii >= in.height || ij < 0 || ij >= in.width) {
            // Aqui estou usando 0 por ele é minimo de uint8_t
            // caso fosse outro tipo deveria ser o minimo do
            // tipo.
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

Img Morph::open0(const Img &in, const SElem &se) {
  return Morph::dil0(Morph::ero0(in, se), se);
}

Img Morph::close0(const Img &in, const SElem &se) {
  return Morph::ero0(Morph::dil0(in, se), se);
}

Img Morph::grad0(const Img &in, const SElem &se) {
  return dil0(in, se) - ero0(in, se);
}

Img Morph::tophat0(const Img &in, const SElem &se) {
  return in - open0(in, se);
}

Img Morph::blackhat(const Img &in, const SElem &se) {
  return close0(in, se) - in;
}

void Morph::printImg(Img &img) {

  for (size_t i = 0; i < img.height; i++) {
    for (size_t j = 0; j < img.width; j++) {
      std::cout << +img[i, j] << " ";
    }
    std::cout << "\n";
  }
}

void Morph::printSE(SElem &se) {

  for (size_t i = 0; i < se.height; i++) {
    for (size_t j = 0; j < se.width; j++) {
      std::cout << +se[i, j] << " ";
    }
    std::cout << "\n";
  }
}

} // namespace Naive

#endif
