#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

/**
 * @class Vector
 * @brief Implements 2D vectors that represent cartesian coordinates
*/
struct Vector{
  public:
    float _x, _y;

    /**
    * @brief Creates a new default vector
    */

    Vector();
    /**
    * @brief Creats a new vector based on one value
    */
    Vector(float _xy);
    /**
    * @brief Creates a new vector based on x and y values
    */
    Vector(float _x, float _y);
    /**
    * @brief Implements vector sum using operator overload
    */
    Vector operator+(const Vector& other) const;

    /**
    * @brief Implements vector subtraction using operator overload
    */
    Vector operator-(const Vector& other) const;
    /**
    * @brief Implements vector multiplication by scalar using operator overload
    */
    Vector operator*(float value) const; 
    /**
 * @brief Calcula o produto escalar entre dois vetores.
 * @param a O primeiro vetor.
 * @param b O segundo vetor.
 * @return O valor do produto escalar como um número de ponto flutuante.
*/
    static float dot(const Vector& a, const Vector& b);
    /**
 * @brief Calcula a distância entre dois pontos (representados como vetores).
 * @details Mede o comprimento do segmento de reta que conecta os dois pontos. A implementação
 * calcula o vetor diferença d = a - b e então retorna seu módulo,
 * que é a raiz quadrada do produto escalar de d por ele mesmo.
 * @param a O primeiro vetor.
 * @param b O segundo vetor.
 * @return A distância em linha reta entre os pontos a e b.
*/

    static float distance(const Vector& a, const Vector& b);
  /**
 * @brief Calcula a menor distância de um ponto a um segmento de reta.
 * @details Este método encontra o ponto em um segmento de reta (definido por a e b)
 * que está mais próximo do ponto p e retorna a distância entre eles. A lógica
 * consiste em projetar o vetor ap sobre o vetor ab e obter um triângulo retângulo.
 * @param p O ponto do qual se deseja calcular a distância.
 * @param a O ponto inicial do segmento de reta.
 * @param b O ponto final do segmento de reta.
 * @return A menor distância entre o ponto p e o segmento ab.
*/
    static float shortestDistancePointToSegment(const Vector& p, const Vector& a, const Vector& b);
};
#endif
