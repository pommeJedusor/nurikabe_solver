#ifndef NURIKABE_SOLVER_H
# define NURIKABE_SOLVER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 1024

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_island
{
	int		id;
	int		current_size;
	int		target_size;
	t_pos	pos;
}	t_island;

char	*get_file_content(char *file_name);
char	**split_lines(char *str);
char	**free_lines(char **strs);

t_island	*get_islands(char **lines);
void		print_islands(t_island *islands);

int		**free_grid(int **grid);
int		**get_empty_grid(int size);
int		**clone_grid(int **grid);
void	print_grid(int **grid);

#endif
