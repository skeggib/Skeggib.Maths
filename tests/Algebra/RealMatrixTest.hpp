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
    void test_getValue();
	void test_setValue();
	void test_equals();
	void test_assign();
	void test_setLine();
	void test_fromArray();
    void test_plus_equal();
    void test_minus_equal();
    void test_multiply_equal();
    void test_multiply_matrix();
    void test_transpose();
    void test_determinant();
    void test_substraction();
    void test_product();
};

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib
