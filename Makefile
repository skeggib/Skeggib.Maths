CC=g++
CFLAGS=-w -std=gnu++11 -MMD
LFLAGS=

# Windows
ifeq ($(OS),Windows_NT)

	LIB=libSkeggibMaths.a
	TEST=SkeggibMathsTests.exe

	LFLAGS+= -static-libgcc -static-libstdc++ -lmingw32

# Linux
else

	LIB=libSkeggibMaths.a
	TEST=SkeggibMathsTests

endif

# Objects ---------------------------------------------------------------------

O_LIB=\
	src/Algebra/RealMatrix.o\

O_TEST=\
	tests/tests.o\
	tests/Algebra/RealMatrixTest.o\

O_ALL=\
	$(O_LIB)\
	$(O_TEST)\

# Compilation -----------------------------------------------------------------

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp %.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

# Library ---------------------------------------------------------------------

all: $(LIB)

test: $(TEST)

runtest: test
	@./$(TEST)

$(LIB): $(O_LIB)
	ar rvs $@ $^

$(O_TEST): $(LIB)

$(TEST): $(O_TEST)
	$(CC) $^ -o $@ -L./Skeggib.Cpptest -lSkeggibCpptest -L. -lSkeggibMaths $(LFLAGS)

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