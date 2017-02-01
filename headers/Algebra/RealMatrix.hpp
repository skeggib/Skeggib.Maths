#pragma once

#include "../../headers/Algebra/Matrix.hpp"


namespace Skeggib {
namespace Maths {
namespace Algebra {

class RealMatrix : public Matrix<double> {

protected:

    virtual const double nullElement() const;
    virtual const double neutralElement() const;

public:

	RealMatrix(int rows, int columns);
    RealMatrix(int rows, int columns, double preset);

    const RealMatrix operator+(const RealMatrix& rhs) const;
    const RealMatrix operator-(const RealMatrix& rhs) const;
    const RealMatrix operator*(const RealMatrix& rhs) const;
    const RealMatrix operator*(const double& scalar) const;

    RealMatrix& operator+=(const RealMatrix& rhs);
    RealMatrix& operator-=(const RealMatrix& rhs);
    RealMatrix& operator*=(const RealMatrix& rhs);
    RealMatrix& operator*=(const double& scalar);

    RealMatrix& operator=(const RealMatrix& matrix);

}; // class RealMatrix

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib