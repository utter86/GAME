CC = g++
ODIR = ./obj/
CDIR = ./cpp/
SRCS = $(wildcard ./cpp/*.cpp)
DEPS = $(wildcard *.h)
OBJS = $(patsubst ./cpp/%.cpp,./obj/%.o,$(SRCS))
FLAGS = -ggdb -Wall -I ./h/
LIBS =  -lSDL2 -lSDL2_image

.PHONY: clean all

game: $(OBJS)
	$(CC) $(FLAGS) $(LIBS) $(OBJS) -o $@

$(ODIR)%.o: $(CDIR)%.cpp $(DEPS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f ./obj/*.o ./game 
