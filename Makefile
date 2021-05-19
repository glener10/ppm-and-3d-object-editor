#VAR para nome do projeto

#Flags
FLAGS = -c -lGL -lGLU -lglut

#Compilador
CC=g++

#Caminhos
SRC = ./src
BIN = ./bin
HEADERS = ./include
OBJ = ./obj/Debug
APPS = ./app

all: glut.o image_aux.o image_base.o image_functions.o read_obj.o main.o executavel		#define qual funcoes ira chamar ao chamar o comando make ou make all

executavel:		#A partir dos .obj cria o executavel
	g++ $(OBJ)/*.o -lGL -lGLU -lglut -o $(BIN)/output

main.o:	#Cria os .obj
	g++ $(FLAGS) $(SRC)/main.cpp -I $(HEADERS) -o $(OBJ)/main.o

read_obj.o:
	g++ $(FLAGS) $(SRC)/read_obj.cpp -I $(HEADERS) -o $(OBJ)/read_obj.o

glut.o:
	g++ $(FLAGS) $(SRC)/glut.cpp -I $(HEADERS) -o $(OBJ)/glut.o



image_aux.o:
	g++ $(FLAGS) $(SRC)/image_aux.cpp -I $(HEADERS) -o $(OBJ)/image_aux.o

image_base.o:
	g++ $(FLAGS) $(SRC)/image_base.cpp -I $(HEADERS) -o $(OBJ)/image_base.o

image_functions.o:
	g++ $(FLAGS) $(SRC)/image_functions.cpp -I $(HEADERS) -o $(OBJ)/image_functions.o



run:		#Executa o app
	cd bin && ./output
	


clean:
	rm $(OBJ)/*.o $(BIN)/output
