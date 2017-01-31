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
	Skeggib.Cpptest/src/collectoroutput.o\
	Skeggib.Cpptest/src/compileroutput.o\
	Skeggib.Cpptest/src/htmloutput.o\
	Skeggib.Cpptest/src/missing.o\
	Skeggib.Cpptest/src/source.o\
	Skeggib.Cpptest/src/suite.o\
	Skeggib.Cpptest/src/textoutput.o\
	Skeggib.Cpptest/src/time.o\
	Skeggib.Cpptest/src/utils.o\

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