CXX = g++
CXXFLAGS = -I./
LDFLAGS = -l glfw -l GLEW -l GL -l GLU -l armadillo

# Incluimos las carpetas de los archivos que vamos a utilizar.
cppsrc = $(wildcard ./*.cpp) \ $(wildcard ./obj_reader/*.cpp) $(wildcard ./graphics/*.cpp)
obj = $(cppsrc:.cpp=.o)

main: $(obj)
		${CXX} $^ -o $@ ${LDFLAGS}
