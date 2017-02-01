#include "RealMatrixTest.hpp"

namespace Skeggib {
namespace Maths {
namespace Algebra {

RealMatrixTest::RealMatrixTest() {
    TEST_ADD(RealMatrixTest::test_sizeConstructor);
    TEST_ADD(RealMatrixTest::test_sizeValueConstructor);
    TEST_ADD(RealMatrixTest::test_get);
    TEST_ADD(RealMatrixTest::test_set);
    TEST_ADD(RealMatrixTest::test_fromArray);
    TEST_ADD(RealMatrixTest::test_transpose);
    TEST_ADD(RealMatrixTest::test_determinant);
    TEST_ADD(RealMatrixTest::test_setLine);
    TEST_ADD(RealMatrixTest::test_productMatrix);
    TEST_ADD(RealMatrixTest::test_substraction);
    TEST_ADD(RealMatrixTest::test_equals);
    TEST_ADD(RealMatrixTest::test_plus);
    TEST_ADD(RealMatrixTest::test_minus);
    TEST_ADD(RealMatrixTest::test_multiplyScalar);
    TEST_ADD(RealMatrixTest::test_multiplyMatrix);
    TEST_ADD(RealMatrixTest::test_assign);
}

void RealMatrixTest::test_sizeConstructor() {
    TEST_THROWS_MSG(RealMatrix m1(0, 0),
            std::invalid_argument,
            "Creating a 0x0 matrix should throw an invalid_argument \
exception");
    TEST_THROWS_ANYTHING_MSG(RealMatrix m2(-1, 2),
            "Creating a matrix with negative size should throw an \
invalid_argument exception");
    TEST_THROWS_ANYTHING_MSG(RealMatrix m3(2, -1),
            "Creating a matrix with negative size should throw an \
invalid_argument exception");
    
    RealMatrix m4(10, 6);
    TEST_ASSERT_EQUALS(6, m4.width());
    TEST_ASSERT_EQUALS(10, m4.height());
}

void RealMatrixTest::test_sizeValueConstructor() {
    double value = 4;
    RealMatrix m(3, 6, value);

    TEST_ASSERT(m.height() == 3);
    TEST_ASSERT(m.width() == 6);

    for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 6; j++) {
         TEST_ASSERT(m.get(i, j) == value);
       }
    }
}

void RealMatrixTest::test_get() {
    RealMatrix m(10, 10, 0);
    TEST_THROWS(m.get(10, 10), std::out_of_range);
    TEST_THROWS(m.get(0, 10), std::out_of_range);
    TEST_THROWS(m.get(10, 0), std::out_of_range);
}

void RealMatrixTest::test_set() {
    RealMatrix m(10, 10, 0);
    m.set(2, 3, 40);
    m.set(5, 3, -3);
    TEST_ASSERT_EQUALS(40, m.get(2, 3));
    TEST_ASSERT_EQUALS(-3, m.get(5, 3));    
    TEST_THROWS(m.set(10, 10, 6), std::out_of_range);
    TEST_THROWS(m.set(0, 10, 6), std::out_of_range);
    TEST_THROWS(m.set(10, 0, 6), std::out_of_range);
}

void RealMatrixTest::test_fromArray() {
    RealMatrix m(2, 2);
    double array[4] = {
       1, 2,
       3, 4
    };
    m.fromArray(array);

    TEST_ASSERT_EQUALS(1, m.get(0, 0))
    TEST_ASSERT_EQUALS(2, m.get(0, 1))
    TEST_ASSERT_EQUALS(3, m.get(1, 0))
    TEST_ASSERT_EQUALS(4, m.get(1, 1))
}

void RealMatrixTest::test_transpose() {
    RealMatrix m(3, 2);
    double m_array[6] = {
        1, 2,
        3, 4,
        5, 6
    };
    m.fromArray(m_array);

    m.transpose();
    
    RealMatrix expected(2, 3);
    double expected_array[6] = {
        1, 3, 5,
        2, 4, 6
    };
    expected.fromArray(expected_array);

    TEST_ASSERT_EQUALS(expected, m);
}

void RealMatrixTest::test_determinant() {
    RealMatrix m(3, 3);
    double m_array[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    m.fromArray(m_array);
}

void RealMatrixTest::test_setLine() {
    RealMatrix m(2, 2);

    double l1[2] = {1, 2};
    double l2[2] = {3, 4};
    double l3[2] = {5, 6};

    m.setLine(0, l1);
    m.setLine(1, l2);

    TEST_ASSERT_EQUALS(1, m.get(0, 0));
    TEST_ASSERT_EQUALS(2, m.get(0, 1));
    TEST_ASSERT_EQUALS(3, m.get(1, 0));
    TEST_ASSERT_EQUALS(4, m.get(1, 1));

    m.setLine(1, l3);

    TEST_ASSERT_EQUALS(1, m.get(0, 0));
    TEST_ASSERT_EQUALS(2, m.get(0, 1));
    TEST_ASSERT_EQUALS(5, m.get(1, 0));
    TEST_ASSERT_EQUALS(6, m.get(1, 1));
}

void RealMatrixTest::test_productMatrix() {
    RealMatrix a(2, 3);
    double array_a[9] = {
        1, 2, 3,
        4, 5, 6
    };
    a.fromArray(array_a);

    RealMatrix b(3, 3);
    double array_b[9] = {
        6, 0, 1,
        4, 3, 8,
        9, 8, 2
    };
    b.fromArray(array_b);

    RealMatrix expected(2, 3);
    double array_expected[9] = {
        41, 30, 23,
        98, 63, 56
    };
    expected.fromArray(array_expected);

    RealMatrix result(2, 3);

    RealMatrix::product(a, b, result);

    TEST_ASSERT_EQUALS(expected, result);
}

void RealMatrixTest::test_substraction() {
    RealMatrix a(2, 3);
    double array_a[9] = {
        1, 2, 3,
        4, 5, 6
    };
    a.fromArray(array_a);

    RealMatrix b(2, 3);
    double array_b[9] = {
        6, 0, 1,
        4, 3, 8
    };
    b.fromArray(array_b);

    RealMatrix expected(2, 3);
    double array_expected[9] = {
        -5, 2, 2,
        0, 2, -2
    };
    expected.fromArray(array_expected);

    RealMatrix result(2, 3);

    RealMatrix::substraction(a, b, result);

    TEST_ASSERT_EQUALS(expected, result);
}

void RealMatrixTest::test_equals() {
    RealMatrix m1(10, 10, 0);
    m1.set(2, 2, 3);

    RealMatrix m2(10, 10, 0);
    m2.set(2, 2, 3);

    RealMatrix m3(10, 10, 0);
    m3.set(3, 2, 3);

    RealMatrix m4(10, 5, 0);

    TEST_ASSERT(m1 == m2);
    TEST_ASSERT(m1 != m3);
    TEST_ASSERT(m1 != m4);
}

void RealMatrixTest::test_plus() {
    RealMatrix a(3, 3);
    double array_a[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    a.fromArray(array_a);

    RealMatrix b(3, 3);
    double array_b[9] = {
        6, 0, 1,
        4, 3, 8,
        9, 8, 2
    };
    b.fromArray(array_b);

    RealMatrix expected(3, 3);
    double array_expected[9] = {
        7,  2,  4,
        8,  8,  14,
        16, 16, 11
    };
    expected.fromArray(array_expected);

    a += b;
    TEST_ASSERT_EQUALS(expected, a);

    RealMatrix c(3, 2);
    TEST_THROWS(a += c, std::length_error);
}

void RealMatrixTest::test_minus() {
    RealMatrix a(3, 3);
    double array_a[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    a.fromArray(array_a);

    RealMatrix b(3, 3);
    double array_b[9] = {
        6, 0, 1,
        4, 3, 8,
        9, 8, 2
    };
    b.fromArray(array_b);

    RealMatrix expected(3, 3);
    double array_expected[9] = {
        -5, 2, 2,
        0, 2, -2,
        -2, 0, 7
    };
    expected.fromArray(array_expected);

    a -= b;
    TEST_ASSERT_EQUALS(expected, a);

    RealMatrix c(3, 2);
    TEST_THROWS(a -= c, std::length_error);
}

void RealMatrixTest::test_multiplyScalar() {
    RealMatrix a(3, 3);
    double array_a[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    a.fromArray(array_a);

    double scalar = 2;

    RealMatrix expected(3, 3);
    double array_expected[9] = {
        2, 4, 6,
        8, 10, 12,
        14, 16, 18
    };
    expected.fromArray(array_expected);

    a *= scalar;
    TEST_ASSERT_EQUALS(expected, a);
}

void RealMatrixTest::test_multiplyMatrix() {
    RealMatrix a(2, 3);
    double array_a[9] = {
        1, 2, 3,
        4, 5, 6
    };
    a.fromArray(array_a);

    RealMatrix b(3, 3);
    double array_b[9] = {
        6, 0, 1,
        4, 3, 8,
        9, 8, 2
    };
    b.fromArray(array_b);

    RealMatrix expected(2, 3);
    double array_expected[9] = {
        41, 30, 23,
        98, 63, 56
    };
    expected.fromArray(array_expected);

    RealMatrix result(2, 3);

    result = a * b;

    TEST_ASSERT_EQUALS(expected, result);
    
    TEST_THROWS(b * a, std::length_error);
}

void RealMatrixTest::test_assign() {
    RealMatrix m1(3, 3);
    double a1[9] = {
       1, 4, 7,
       2, 5, 8,
       3, 6, 9
    };
    m1.fromArray(a1);

    RealMatrix m2(3, 3);

    m2 = m1;

    TEST_ASSERT_EQUALS(m1, m2);

    RealMatrix m3(2, 3);

    TEST_THROWS_MSG(m3 = m1, std::length_error,
            "Assigning matrix with different sizes should throw a \
length_error");
}

} // namespace Algebra
} // namespace Maths
} // namespace Skeggib
