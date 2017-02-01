#pragma once

#include "../../Skeggib.Cpptest/headers/cpptest-suite.h"
#include "../../Skeggib.Cpptest/headers/cpptest-assert.h"

#include "../../headers/Algebra/RealMatrix.hpp"


namespace Skeggib {
namespace Maths {
namespace Algebra {

class RealMatrixTest : public Test::Suite {

public:

	RealMatrixTest();

private:

	void test_sizeConstructor();
	void test_sizeValueConstructor();
    void test_get();
	void test_set();
    void test_getPtr();
    void test_fromArray();
    void test_transpose();
    void test_determinant(); // TODO
    void test_setLine();
    void test_swapLine(); // TODO
    void test_multiplyLine(); // TODO
    void test_addLine(); // TODO
    void test_productMatrix();
    void test_productScalar(); // TODO
    void test_substraction();
	void test_equals();
    void test_plus();
    void test_minus();
    void test_multiplyScalar();
    void test_multiplyMatrix();
    void test_assign();
};

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib
