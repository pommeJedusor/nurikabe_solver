#ifndef NURIKABE_SOLVER_H
# define NURIKABE_SOLVER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define BUFFER_SIZE 1024
# define DEQUEUE_SIZE 1024
# define MAX_BITSET_SIZE 128

static const unsigned long long EMPTY_BITSET[MAX_BITSET_SIZE] = {0};
static const unsigned long long UNINITIALISED_BITSET[MAX_BITSET_SIZE] = {
    [0 ... MAX_BITSET_SIZE-1] = ULLONG_MAX
};
static const unsigned long long WATER[MAX_BITSET_SIZE] = {1};

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
void		get_full_bitmap_for_islands(int nb_islands, unsigned long long *bitmap);
int			get_islands_length(t_island *array);
t_island	*clone_islands(t_island *array);

unsigned long long	***free_grid(unsigned long long ***grid);
unsigned long long	***get_empty_grid(int size, int bitset_size);
unsigned long long	***clone_grid(unsigned long long ***grid, int bitset_size);
void				print_grid(unsigned long long ***grid, t_island *islands);
void				print_solution(unsigned long long ***grid, t_island *islands);

void		initialise_grid(unsigned long long ***grid, t_island *islands);

void		island_borders_rule(unsigned long long ***grid, t_island *islands);
void		no_water_square_rule(unsigned long long ***grid, int bitset_size);
void		deduction_solve(unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue);

int			count_bits(int number);
int			get_trailing_zeros(int number);

void		copy_bitset(unsigned long long *dest, const unsigned long long *src, int size);
int			count_bitset_bits(const unsigned long long *bitset, int bitset_size);
int			get_bitset_size_from_islands(t_island *islands);
int			cmp_bitsets(const unsigned long long *a, const unsigned long long *b, int size);
int			get_bitset_trailing_zeros(const unsigned long long *bitset, int bitset_size);
void		bitset_or(unsigned long long *dest, const unsigned long long *src, int size);
void		bitset_and(unsigned long long *dest, const unsigned long long *src, int size);

void		initialise_dequeue(t_dequeue *dequeue);
int			is_empty(t_dequeue *dequeue);
int			is_full(t_dequeue *dequeue);
t_pos		pop_front(t_dequeue *dequeue);
int			push_back(t_dequeue *dequeue, t_pos pos);

void		bfs(unsigned long long ***grid, t_island island, unsigned long long ***cache_grid, t_dequeue *dequeue, int bitset_size);
void		use_bfs_to_limit_islands(unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue);
void		init_cache_grid(unsigned long long ***grid, unsigned long long ***cache_grid, int bitset_size);
void		empty_cache_grid(const unsigned long long ***grid, unsigned long long ***cache_grid, int bitset_size);

void		extend_islands(unsigned long long ***grid, unsigned long long ***cache_grid, t_dequeue *dequeue, t_island *islands);
int			count_water(unsigned long long ***grid, int bitset_size);

void		backtracking(unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue dequeue);

int			is_valid(const unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue);

#endif
