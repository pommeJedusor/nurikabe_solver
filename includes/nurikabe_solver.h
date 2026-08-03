#ifndef NURIKABE_SOLVER_H
# define NURIKABE_SOLVER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 1024
# define DEQUEUE_SIZE 1024
# define WATER 1

typedef struct s_pos
{
	int	x;
	int	y;
	int	cost;
}	t_pos;

typedef struct s_island
{
	int		id;
	int		current_size;
	int		target_size;
	t_pos	pos;
}	t_island;

typedef struct s_dequeue
{
	int		front_i;
	int		back_i;
	t_pos	queue[DEQUEUE_SIZE];
}	t_dequeue;

char		*get_file_content(char *file_name);
char		**split_lines(char *str);
char		**free_lines(char **strs);

t_island	*get_islands(char **lines);
void		print_islands(t_island *islands);

int			**free_grid(int **grid);
int			**get_empty_grid(int size);
int			**clone_grid(int **grid);
void		print_grid(int **grid);

void		initialise_grid(int **grid, t_island *islands);
int			get_islands_length(t_island *array);

void		island_borders_rule(int **grid, t_island *islands);
void		no_water_square_rule(int **grid);

int			count_bits(int number);
int			get_trailing_zeros(int number);

void		initialise_dequeue(t_dequeue *dequeue);
int			is_empty(t_dequeue dequeue);
int			is_full(t_dequeue dequeue);
t_pos		pop_front(t_dequeue *dequeue);
int			push_back(t_dequeue *dequeue, t_pos pos);

#endif
