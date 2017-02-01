#include <memory>

#include "../Skeggib.Cpptest/headers/cpptest-suite.h"
#include "../Skeggib.Cpptest/headers/cpptest-textoutput.h"

#include "Algebra/RealMatrixTest.hpp"
using Skeggib::Maths::Algebra::RealMatrixTest;

bool runTests();

int main(int argc, char* argv[])
{
	bool result = runTests();

	if (result)
		return 0;
	return 1;
}

bool runTests() {
	Test::Suite ts;

	ts.add(std::unique_ptr<Test::Suite>(new RealMatrixTest));

	Test::TextOutput output(Test::TextOutput::Verbose);
	return ts.run(output);
}
