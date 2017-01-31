#pragma once

#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include <sstream>

#define EPSILON 0.000000001 // TODO move

namespace Skeggib {
namespace Maths {
namespace Algebra {

/**
 * @brief Matrix
 * 
 * @tparam T Type of the elements of the matrix, T must support basic 
 * arithmetic operations (+, -, *) and comparison operators (==, !=, ...)
 */
template <typename T>
class Matrix {

private:

    unsigned int _height;
    unsigned int _width;
    unsigned int _elements_count;

    T* _values;
    T _null_element;
    T _neutral_element;

    /**
     * @brief Allocate memory
     * 
     * @param height
     * @param width
     * 
     * @throws invalid_argument If height or width is negative or equal to 0
     */
    void allocate(int height, int width);

public:

    Matrix(int      height,
           int      width,
           const T& null_element,
           const T& neutral_element);
    
    Matrix(int      height,
           int      width,
           const T& zero_value,
           const T& neutral_element,
           const T& default_value);
    
    Matrix(const Matrix& matrix);

    virtual ~Matrix();

    const T& get(unsigned int i, unsigned int j) const;
          T& get(unsigned int i, unsigned int j);

    void set(unsigned int i, unsigned int j, const T& value);

    void fromArray(T array[]);

    unsigned int height() const;
    unsigned int width() const;

    Matrix<T> transpose() const;

    T determinant();

    void setLine(unsigned int i, T array[]);
    void swapLines(unsigned int index1, unsigned int index2);
    void multiplyLine(unsigned int index, float scalar);
    void addLine(unsigned int index1, unsigned int index2, float x);

    static void product(const Matrix<T>& a,
                        const Matrix<T>& b,
                        Matrix<T>& result);

    static void product(double k,
                        const Matrix<T>& a,
                        Matrix<T>& result);
    
    static void substraction(const Matrix<T>& a,
                             const Matrix<T>& b,
                             Matrix<T>& result);

    bool operator==(const Matrix<T>& other) const;
    bool operator!=(const Matrix<T>& other) const;

    const Matrix<T> operator+(const Matrix<T>& rhs) const;
    const Matrix<T> operator-(const Matrix<T>& rhs) const;
    const Matrix<T> operator*(const Matrix<T>& rhs) const;
    const Matrix<T> operator*(const T& scalar) const;

    Matrix<T>& operator+=(const Matrix<T>& rhs);
    Matrix<T>& operator-=(const Matrix<T>& rhs);
    Matrix<T>& operator*=(const Matrix<T>& rhs);
    Matrix<T>& operator*=(const T& scalar);

    Matrix<T>& operator=(const Matrix<T>& matrix);

}; // class Matrix

template <class T>
std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix);

template <class T>
const Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix);

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib