#include <limits.h>
#include "nurikabe_solver.h"

int	is_solved(int **grid)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (count_bits(grid[y][x]) != 1)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

t_pos	get_optimal_pos_to_change(int **grid, t_island *islands)
{
	t_pos	pos;
	t_pos	best_pos;
	int		best_pos_possibilities;
	int		bit_count;

	(void)islands;
	best_pos.x = -1;
	best_pos.y = -1;
	best_pos_possibilities = INT_MAX;
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x] != -1)
		{
			bit_count = count_bits(grid[pos.y][pos.x]);
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

void	free_clones(int **grid, t_island *islands)
{
	free_grid(grid);
	free(islands);
}

void	backtracking(int **grid, t_island *islands, int **cache_grid, t_dequeue dequeue)
{
	int			**grid_clone;
	t_island	*islands_clone;
	t_pos		pos;
	int			i;
	int			cache_bitmap;

	grid_clone = clone_grid(grid);
	if (grid_clone == 0)
		return ;
	islands_clone = clone_islands(islands);
	if (islands_clone == 0)
	{
		free_clones(grid_clone, islands_clone);
		return ;
	}
	//printf("test\n");
	//print_solution(grid_clone, islands_clone);
	//printf("\n");
	deduction_solve(grid_clone, islands_clone, cache_grid, &dequeue);
	//print_solution(grid_clone, islands_clone);
	//printf("\n");
	//printf("\n");
	if (!is_valid(grid_clone, islands_clone, cache_grid, &dequeue))
	{
		free_clones(grid_clone, islands_clone);
		return ;
	}
	if (is_solved(grid_clone))
	{
		print_solution(grid_clone, islands_clone);
		//printf("solution found\n");
		//printf("\n");
		free_clones(grid_clone, islands_clone);
		return ;
	}
	pos = get_optimal_pos_to_change(grid_clone, islands_clone);
	i = 0;
	cache_bitmap = grid_clone[pos.y][pos.x];
	while (i < 32 && pos.x != -1)
	{
		if (cache_bitmap & (1 << i))
		{
			grid_clone[pos.y][pos.x] = 1 << i;
			backtracking(grid_clone, islands_clone, cache_grid, dequeue);
		}
		i++;
	}
	free_clones(grid_clone, islands_clone);
}
