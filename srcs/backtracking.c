#include <limits.h>
#include "nurikabe_solver.h"

int	is_solved(unsigned long long ***grid, int bitset_size)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (count_bitset_bits(grid[y][x], bitset_size) != 1)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

t_pos	get_optimal_pos_to_change(unsigned long long ***grid, t_island *islands)
{
	t_pos	pos;
	t_pos	best_pos;
	int		best_pos_possibilities;
	int		bit_count;
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	(void)islands;
	best_pos.x = -1;
	best_pos.y = -1;
	best_pos_possibilities = INT_MAX;
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x])
		{
			bit_count = count_bitset_bits(grid[pos.y][pos.x], bitset_size);
			if (bit_count > 1 && bit_count < best_pos_possibilities)
			{
				best_pos_possibilities = bit_count;
				best_pos = pos;
			}
			pos.x++;
		}
		pos.y++;
	}
	return (best_pos);
}

void	free_clones(unsigned long long ***grid, t_island *islands)
{
	free_grid(grid);
	free(islands);
}

//returns 1 if found a solution
int	backtracking(unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue dequeue)
{
	unsigned long long	***grid_clone;
	unsigned long long	cache_bitmap[MAX_BITSET_SIZE];
	t_island			*islands_clone;
	t_pos				pos;
	int					i;
	int					j;
	int					bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	grid_clone = clone_grid(grid, bitset_size);
	if (grid_clone == 0)
		return (0);
	islands_clone = clone_islands(islands);
	if (islands_clone == 0)
	{
		free_clones(grid_clone, islands_clone);
		return (0);
	}
	//printf("test\n");
	//print_solution(grid_clone, islands_clone);
	//printf("\n");
	deduction_solve(grid_clone, islands_clone, cache_grid, &dequeue);
	//print_solution(grid_clone, islands_clone);
	if (!is_valid((const unsigned long long ***)grid_clone, islands_clone, cache_grid, &dequeue))
	{
		//printf("not valid\n");
		//printf("\n");
		//printf("\n");
		free_clones(grid_clone, islands_clone);
		return (0);
	}
	//printf("\n");
	//printf("\n");
	if (is_solved(grid_clone, bitset_size))
	{
		print_solution(grid_clone, islands_clone);
		//printf("solution found\n");
		//printf("\n");
		free_clones(grid_clone, islands_clone);
		return (1);
	}
	pos = get_optimal_pos_to_change(grid_clone, islands_clone);
	copy_bitset(cache_bitmap, grid_clone[pos.y][pos.x], bitset_size);
	j = bitset_size - 1;
	while (j >= 0 && pos.x != -1)
	{
		i = 63;
		while (i >= 0)
		{
			if (cache_bitmap[j] & (1ULL << i))
			{
				copy_bitset(grid_clone[pos.y][pos.x], EMPTY_BITSET, bitset_size);
				grid_clone[pos.y][pos.x][j] = 1ULL << i;
				if (backtracking(grid_clone, islands_clone, cache_grid, dequeue))
				{
					free_clones(grid_clone, islands_clone);
					return (1);
				}
			}
			i--;
		}
		j--;
	}
	free_clones(grid_clone, islands_clone);
	return (0);
}
