CFILES = main.c get_file_content.c split.c grid.c island.c initialise_grid.c deduction_solve.c dequeue.c bfs.c extend_islands.c backtracking.c is_position_valid.c bitset.c
CPATHS = $(addprefix ./srcs/, $(CFILES))
PROGRAM_NAME = ./nurikabe_solver
HEADERS = ./includes
CFLAGS = -Wall -Wextra -Werror

all: ./$(PROGRAM_NAME)

./$(PROGRAM_NAME): $(CPATHS)
	cc $(CFLAGS) -I $(HEADERS) $(CPATHS) -o $(PROGRAM_NAME) -O3

debug: $(CPATHS)
	cc $(CFLAGS) -I $(HEADERS) $(CPATHS) -o $(PROGRAM_NAME) -g

clean:

fclean: clean
	rm -f $(PROGRAM_NAME)

re: fclean all
