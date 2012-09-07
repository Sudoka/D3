UNAME := $(shell uname)

# on linux try "g++"
COMPILER = clang++

# on linux try "-std=gnu++0x"
CPP11_FLAGS = -std=c++11 -stdlib=libc++

ifeq ($(UNAME), Darwin)
LIBS = -lpng -framework OpenGL -framework GLUT
endif
ifeq ($(UNAME), Linux)
LIBS = -lpng -lGL -lglut
endif

BINDIR = bin

seminar:
	@echo "Compiling example..."
	@mkdir -p $(BINDIR)
	@${COMPILER} /main.cpp ${LIBS} ${CPP11_FLAGS} -o ${BINDIR}/d3

	@echo "Successfully completed!"
	@echo "To try, execute: make run"

run:
	@printf "Executing: ./${BINDIR}/d3\n\n"
	@./${BINDIR}/d3
	@echo

clean:
	@printf "Cleaning all"
	@rm -Rf ${BINDIR}
	@echo