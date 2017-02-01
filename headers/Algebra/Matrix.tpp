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

	_values = (T*)std::malloc(_elements_count * sizeof(T));
}

template <class T>
Matrix<T>::Matrix(int height, int width) {
	allocate(height, width);
}

template <class T>
Matrix<T>::Matrix(int height, int width, const T& default_value) {
	allocate(height, width);

    T* ptr = _values;
    for (int i = 0; i < _elements_count; i++) {
        *ptr = default_value;
        ptr++;
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    allocate(matrix._height, matrix._width);

    T* pThis = _values;
    T* pOther = matrix._values;
    for (int i = 0; i < _elements_count; i++) {
        *pThis = *pOther;
        pThis++;
        pOther++;
    }
}

template <class T>
Matrix<T>::~Matrix() {
    if (_values)
        std::free(_values);
}

template <class T>
const T& Matrix<T>::get(unsigned int i, unsigned int j) const {
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
    T* pThis = _values + _width * i;
    T* pArray = array;
	for (int j = 0; j < _width; j++) {
		*pThis = *pArray;
        pThis++;
        pArray++;
	}
}

template <class T>
void Matrix<T>::fromArray(T array[]) {
    T* pThis = _values;
    T* pArray = array;
	for (int i = 0; i < _elements_count; i++) {
		*pThis = *pArray;
        pThis++;
        pArray++;
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
void Matrix<T>::transpose() {
    T* copy = (T*)std::malloc(_elements_count * sizeof(T));
    std::memcpy(copy, _values, _elements_count * sizeof(T));

    int buffer = _height;
    _height = _width;
    _width = buffer;

    T* pThis = _values;
    T* pCopy = copy;
    for (int i = 0; i < _height; i++) {
        pCopy = copy + i;
        for (int j = 0; j < _width; j++) {
            *pThis = *pCopy;
            pThis++;
            pCopy += _height;
        }
    }

    free(copy);
}

template <class T>
T Matrix<T>::determinant() {
    throw std::logic_error("Not implemented");
}

template <class T>
void Matrix<T>::swapLines(unsigned int index1, unsigned int index2) {
    if (index1 >= _height || index2 >= _height)
        throw std::out_of_range("");

    T* buffer;
    T* p1 = _values + index1 * _width;
    T* p2 = _values + index2 * _width;
    for (int i = 0; i < _width; i++) {
        *buffer = *p1;
        *p1 = *p2;
        *p2 = *buffer;
        p1++;
        p2++;
    }
}

template <class T>
void Matrix<T>::multiplyLine(unsigned int index, float scalar) {
    if (scalar == neutralElement())
        return;
    T* ptr = _values;
    for (int i = 0; i < _width; i++) {
        *ptr *= scalar;
        ptr++;
    }
}

template <class T>
void Matrix<T>::addLine(unsigned int index1, unsigned int index2, float x) {
    if (x == nullElement())
        return;
    if (index1 == index2)
        throw std::invalid_argument("Cannot add a line to itself");

    T* l1 = _values + index1 * _width;
    T* l2 = _values + index2 * _width;
    for (int i = 0; i < _width; i++) {
        *l1 += *l2 * x;
        l1++;
        l2++;
    }
}

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
        return false;
    if (_width != other._width)
        return false;

    T* pThis = _values;
    T* pOther = other._values;
    for (int i = 0; i < _elements_count; i++) {
        if (std::fabs(*pThis - *pOther) > EPSILON)
            return false;
        pThis++;
        pOther++;
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
        throw std::length_error("Addition require two matrices with the same \
dimensions");

    T* pThis = _values;
    T* pRhs = rhs._values;
    for (int i = 0; i < _elements_count; i++) {
        *pThis += *pRhs;
        pThis++;
        pRhs++;
    }

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
    if (_width != rhs._width || _height != rhs._height)
        throw std::length_error("substraction require two matrices with the \
same dimensions");

    T* pThis = _values;
    T* pRhs = rhs._values;
    for (int i = 0; i < _elements_count; i++) {
        *pThis -= *pRhs;
        pThis++;
        pRhs++;
    }

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
    if (scalar == neutralElement())
        return *this;

    T* ptr = _values;
    for (int i = 0; i < _elements_count; i++) {
        *ptr *= scalar;
        ptr++;
    }

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
    if (_width != rhs._height)
        throw std::length_error("Incompatible dimensions for product");

    T* copy = (T*)std::malloc(_elements_count * sizeof(T));
    std::memcpy(copy, _values, _elements_count * sizeof(T));

    free(_values);
    allocate(_height, rhs._width);

    T* pThis = _values;
    T* pCopy = copy;
    T* pRhs = rhs._values;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            pCopy = copy + rhs._height * i;
            pRhs = rhs._values + j;
            *pThis = nullElement();
            for (int k = 0; k < rhs._height; k++) {
                *pThis += *pCopy * *pRhs;
                pCopy++;
                pRhs += _width;
            }
            pThis++;
        }
    }

    free(copy);

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (other._width != _width || other._height != _height)
        throw std::length_error("Cannot assign matrix with different size");
    
    T* pThis = _values;
    T* pOther = other._values;
    for (int i = 0; i < _elements_count; i++) {
        *pThis = *pOther;
        pThis++;
        pOther++;
    }

    return *this;
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
