#include "../../headers/Algebra/Matrix.hpp"

namespace Skeggib {
namespace Maths {
namespace Algebra {

template <class T>
void Matrix<T>::allocate(int height, int width) {
    if (height <= 0 || width <= 0)
        throw std::invalid_argument("Invalid matrix size");

	_height = height;
	_width = width;
    _elements_count = _height * _width;

	_values = (T*)std::malloc(_height * _width * sizeof(T));
}

template <class T>
Matrix<T>::Matrix(int height, int width, const T& null_element, const T& neutral_element) {
	allocate(height, width);

    _null_element = null_element;
    _neutral_element = neutral_element;
}

template <class T>
Matrix<T>::Matrix(int height, int width, const T& null_element, const T& neutral_element, const T& default_value) {
	allocate(height, width);

    _null_element = null_element;
    _neutral_element = neutral_element;

    T* ptr = _values;
    for (int i = 0; i < _elements_count; i++) {
        *ptr = default_value;
        ptr++;
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    allocate(matrix._height, matrix._width);

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            _values[i*_width+j] = matrix._values[i*_width+j];
        }
    }
}

template <class T>
Matrix<T>::~Matrix() {
    if (_values)
        std::free(_values);
}

/* --- Methodes --- */

template <class T>
const T& Matrix<T>::get(unsigned int i, unsigned int j) const {
	if (i > _height-1 || j > _width-1)
		throw std::out_of_range("");

	return _values[i*_width+j];
}

template <class T>
T& Matrix<T>::get(unsigned int i, unsigned int j) {
    if (i > _height-1 || j > _width-1)
        throw std::out_of_range("");

    return _values[i*_width+j];
}

template <class T>
void Matrix<T>::set(unsigned int i, unsigned int j, const T& value) {
	if (i > _height-1 || j > _width-1)
		throw std::out_of_range("");

	_values[i*_width+j] = value;
}

template <class T>
void Matrix<T>::setLine(unsigned int i, T array[]) {
	for (int j = 0; j < _width; j++) {
		get(i, j) = array[j];
	}
}

template <class T>
void Matrix<T>::fromArray(T array[]) {
	int i = 0;
	int j = 0;
	int pos = 0;

	for (i = 0; i < _height; i++) {
		for (j = 0; j < _width; j++) {
			pos = i*_width+j;
			get(i, j) = array[pos];
		}
	}
}

template <class T>
unsigned int Matrix<T>::height() const {
	return _height;
}

template <class T>
unsigned int Matrix<T>::width() const {
	return _width;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> t_matrix(_width, _height, _null_element);
    for (int i = 0; i < _height; i++)
        for (int j = 0; j < _width; j++)
            t_matrix.get(j, i) = get(i, j);
    return t_matrix;
}

template <class T>
T Matrix<T>::determinant() {
    throw std::logic_error("Not implemented");
}

template <class T>
void Matrix<T>::swapLines(unsigned int index1, unsigned int index2) {
    T buffer;
    int i;

    for (i = 0; i < _width; i++) {
        buffer = _values[index1*_width+i];
        _values[index1*_width+i] = _values[index2*_width+i];
        _values[index2*_width+i] = buffer;
    }
}

template <class T>
void Matrix<T>::multiplyLine(unsigned int index, float scalar) {
    if (scalar == 0.0)
        return;
    for (int i = 0; i < _width; i++)
        _values[index*_width+i] *= scalar;
}

template <class T>
void Matrix<T>::addLine(unsigned int index1, unsigned int index2, float x) {
    if (x == 0.0)
        return;
    if (index1 == index2)
        throw std::invalid_argument("");

    for (int i = 0; i < _width; i++)
        _values[index1*_width+i] += _values[index2*_width+i] * x;
}

/* --- Operators --- */

template <class T>
void Matrix<T>::product(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& result) {
    if (a._width != b._height)
        throw std::length_error("A.width must be equal to B.height");
    if (result._height != a._height)
        throw std::length_error("Result.height must be equal to A.height");
    if (result._width != b._width)
        throw std::length_error("Result.width must be equal to B.width");

    T* a_ptr = a._values;
    T* b_ptr = b._values;
    T* r_ptr = result._values;

    int i, j, k;
    for (i = 0; i < result._height; i++) {
        for (j = 0; j < result._width; j++) {

            a_ptr = a._values + a._width * i;
            b_ptr = b._values + j;

            *r_ptr = 0;
            for (k = 0; k < a._width; k++) {
                *r_ptr += *a_ptr * *b_ptr;

                a_ptr++;
                b_ptr += b._width;
            }

            r_ptr++;
        }
    }
}

template <class T>
void Matrix<T>::product(double k, const Matrix<T>& a, Matrix<T>& result) {
    if (result._height != a._height)
        throw std::length_error("Result.height must be equal to A.height");
    if (result._width != a._width)
        throw std::length_error("Result.width must be equal to A.width");

    T* a_ptr = a._values;
    T* r_ptr = result._values;

    for (int i = 0; i < a._width * a._height; i++) {
        *r_ptr = *a_ptr * k;

        r_ptr++;
        a_ptr++;
    }
}

template <class T>
void Matrix<T>::substraction(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& result) { // TODO unit tests
    if (a._width != b._width)
        throw std::length_error("A.width must be equal to B.width");
    if (a._height != b._height)
        throw std::length_error("A.height must be equal to B.height");
    if (result._width != a._width)
        throw std::length_error("Result.width must be equal to A.width");
    if (result._height != a._height)
        throw std::length_error("Result.height must be equal to A.height");

    T* a_ptr = a._values;
    T* b_ptr = b._values;
    T* r_ptr = result._values;

    for (int i = 0; i < a._height * a._width; i++) {
        *r_ptr = *a_ptr - *b_ptr;
        a_ptr++;
        b_ptr++;
        r_ptr++;
    }
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
	if (_height != other._height)
        throw std::length_error("");
    if (_width != other._width)
        throw std::length_error("");

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (std::fabs(get(i, j) - other.get(i, j)) > EPSILON)
                return false;
        }
    }

    return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
	return !operator==(other);
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
    if (_width != rhs._width || _height != rhs._height)
        throw std::length_error("");

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            get(i, j) += rhs.get(i, j);
        }
    }
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
    if (_width != rhs._width || _height != rhs._height)
        throw std::length_error("Cannot substract different size matrix");

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            get(i, j) -= rhs.get(i, j);
        }
    }
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar) {    
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            get(i, j) *= scalar;
        }
    }
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
    *this = *this * rhs; // TODO optimize
}

template <class T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    Matrix<T> result = *this;
    result += other;
    return result;
}

template <class T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    Matrix<T> result = *this;
    result -= other;
    return result;
}

template <class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (_width != other._height)
        throw std::length_error("A.width must be equal to B.height");

    Matrix<T> result(_height, other._width, _null_element, _null_element);

    for (int i = 0; i < result._height; i++) {
        for (int j = 0; j < result._width; j++) {
            for (int k = 0; k < _width; k++)
                result.get(i, j) += get(i, k) * other.get(k, j);
        }
    }

    return result;
}

template <class T>
const Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    Matrix<T> result = *this;
    result *= scalar;
    return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (other._width != _width || other._height != _height)
        throw std::length_error("Cannot assign matrix with different size");
    
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            _values[i*_width+j] = other._values[i*_width+j];
        }
    }
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.height(); i++) {
        if (i > 0)
            stream << std::endl;
        for (int j = 0; j < matrix.width(); j++) {
            stream << matrix.get(i, j) << "\t";
        }
    }
    return stream;
}

template <class T>
// TODO optimize
const Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix) {
    return matrix * scalar;
}

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib
