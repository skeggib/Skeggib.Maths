#include "../../headers/Algebra/RealMatrix.hpp"

namespace Skeggib {
namespace Maths {
namespace Algebra {

const double RealMatrix::nullElement() const {
	return 0;
}

const double RealMatrix::neutralElement() const {
	return 1;
}

RealMatrix::RealMatrix(int rows, int columns)
: Matrix(rows, columns) {

}

RealMatrix::RealMatrix(int rows, int columns, double preset)
: Matrix(rows, columns, preset) {
	
}

const RealMatrix RealMatrix::operator+(const RealMatrix& rhs) const {
    RealMatrix result = *this;
    result += rhs;
    return result;
}

const RealMatrix RealMatrix::operator-(const RealMatrix& rhs) const {
    RealMatrix result = *this;
    result -= rhs;
    return result;
}

const RealMatrix RealMatrix::operator*(const RealMatrix& rhs) const {
    RealMatrix result = *this;
    result *= rhs;
    return result;
}

const RealMatrix RealMatrix::operator*(const double& scalar) const {
    RealMatrix result = *this;
    result *= scalar;
    return result;
}

RealMatrix& RealMatrix::operator+=(const RealMatrix& rhs) {
    Matrix<double>::operator+=(rhs);
    return *this;
}

RealMatrix& RealMatrix::operator-=(const RealMatrix& rhs) {
    Matrix<double>::operator-=(rhs);
    return *this;
}

RealMatrix& RealMatrix::operator*=(const double& scalar) {
    Matrix<double>::operator*=(scalar);
    return *this;
}

RealMatrix& RealMatrix::operator*=(const RealMatrix& rhs) {
    Matrix<double>::operator*=(rhs);
    return *this;
}

RealMatrix& RealMatrix::operator=(const RealMatrix& other) {
    Matrix<double>::operator=(other);
    return *this;
}

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib