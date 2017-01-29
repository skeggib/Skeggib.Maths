CC=g++

LIB_FLAGS=-w -std=gnu++11 -MMD
TEST_FLAGS=

# Windows
ifeq ($(OS),Windows_NT)

	LIB=libSkeggibMaths.a
	TEST=SkeggibMathsTests.exe

	TEST_FLAGS+= -static-libgcc -static-libstdc++ -lmingw32

# Linux
else

	LIB=libSkeggibMaths.a
	TEST=SkeggibMathsTests

	TEST_FLAGS+=

endif

# Objects ---------------------------------------------------------------------

O_LIB=\
    src/Algebra/Matrix.o\

O_CPPTEST=\
	cpptest/collectoroutput.o\
	cpptest/compileroutput.o\
	cpptest/htmloutput.o\
	cpptest/missing.o\
	cpptest/source.o\
	cpptest/suite.o\
	cpptest/textoutput.o\
	cpptest/time.o\
	cpptest/utils.o\

O_TEST=\
	tests/tests.o\
	tests/MatrixTests.o\

O_ALL=\
	$(O_LIB)\
	$(O_CPPTEST)\

# Compilation -----------------------------------------------------------------

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp %.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

# Library ---------------------------------------------------------------------

all: $(LIB)

$(LIB): $(O_LIB)
	ar rvs $@ $^

# Dependencies ----------------------------------------------------------------

D_ALL=$(O_ALL:%.o=%.d)
-include $(D_ALL)

# Cleaning --------------------------------------------------------------------

.PHONY: clean mrproper

clean:
	@rm -rf $(O_ALL)
	@rm -rf $(D_ALL)

mrproper: clean
	@rm -rf $(LIB)
	@rm -rf $(TEST)