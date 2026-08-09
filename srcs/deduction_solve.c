#include "nurikabe_solver.h"

void	island_borders_rule(unsigned long long ***grid, t_island *islands)
{
	int					x;
	int					y;
	int					islands_id;
	int					bitset_size;
	unsigned long long	border[MAX_BITSET_SIZE];

	bitset_size = get_bitset_size_from_islands(islands);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (count_bitset_bits(grid[y][x], bitset_size) != 1 || cmp_bitsets(grid[y][x], WATER, bitset_size) == 0)
			{
				x++;
				continue ;
			}
			copy_bitset(border, WATER, bitset_size);
			bitset_or(border, grid[y][x], bitset_size);
			islands_id = get_bitset_trailing_zeros(grid[y][x], bitset_size);
			if (islands[islands_id].current_size == islands[islands_id].target_size)
				copy_bitset(border, WATER, bitset_size);
			if (y != 0 && cmp_bitsets(grid[y - 1][x], grid[y][x], bitset_size) != 0)
				bitset_and(grid[y - 1][x], border, bitset_size);
			if (x != 0 && cmp_bitsets(grid[y][x - 1], grid[y][x], bitset_size) != 0)
				bitset_and(grid[y][x - 1], border, bitset_size);
			if (grid[y + 1] && cmp_bitsets(grid[y + 1][x], grid[y][x], bitset_size) != 0)
				bitset_and(grid[y + 1][x], border, bitset_size);
			if (grid[y][x + 1] && cmp_bitsets(grid[y][x + 1], grid[y][x], bitset_size) != 0)
				bitset_and(grid[y][x + 1], border, bitset_size);
			x++;
		}
		y++;
	}
}

void	no_water_square_rule(unsigned long long ***grid, int bitset_size)
{
	int		x;
	int		y;
	int		water_counter;
	t_pos	no_water_pos;

	y = 0;
	while (grid[y] && grid[y + 1])
	{
		x = 0;
		while (grid[y][x] && grid[y][x + 1])
		{
			no_water_pos.x = -1;
			water_counter = 0;
			if (cmp_bitsets(grid[y][x], WATER, bitset_size) == 0)
				water_counter++;
			else
			{
				no_water_pos.x = x;
				no_water_pos.y = y;
			}
			if (cmp_bitsets(grid[y + 1][x], WATER, bitset_size) == 0)
				water_counter++;
			else
			{
				no_water_pos.x = x;
				no_water_pos.y = y + 1;
			}
			if (cmp_bitsets(grid[y][x + 1], WATER, bitset_size) == 0)
				water_counter++;
			else
			{
				no_water_pos.x = x + 1;
				no_water_pos.y = y;
			}
			if (cmp_bitsets(grid[y + 1][x + 1], WATER, bitset_size) == 0)
				water_counter++;
			else
			{
				no_water_pos.x = x + 1;
				no_water_pos.y = y + 1;
			}
			if (water_counter == 3 && no_water_pos.x != -1)
				grid[no_water_pos.y][no_water_pos.x][0] &= grid[no_water_pos.y][no_water_pos.x][0] ^ 1;
			x++;
		}
		y++;
	}
}

int	get_grid_hash(unsigned long long ***grid, int bitset_size)
{
	int	sum;
	int	x;
	int	y;

	sum = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			sum += count_bitset_bits(grid[y][x], bitset_size);
			x++;
		}
		y++;
	}
	return (sum);
}

int	get_islands_hash(t_island *islands)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	while (islands[i].id != -1)
	{
		sum += islands[i].current_size;
		i++;
	}
	return (sum);
}

void	deduction_solve(unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue)
{
	int	prev_grid_hash;
	int	grid_hash;
	int	prev_islands_hash;
	int	islands_hash;
	int	bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	prev_grid_hash = -1;
	prev_islands_hash = -1;
	grid_hash = get_grid_hash(grid, bitset_size);
	islands_hash = get_islands_hash(islands);
	//printf("before\n");
	//print_solution(grid, islands);
	//printf("\n");
	while (prev_grid_hash != grid_hash || prev_islands_hash != islands_hash)
	{
		(void)cache_grid;
		(void)dequeue;
		island_borders_rule(grid, islands);
		//print_solution(grid, islands);
		//printf("\n");
		//printf("\n");
		no_water_square_rule(grid, bitset_size);
		use_bfs_to_limit_islands(grid, islands, cache_grid, dequeue);
		islands[0].current_size = count_water(grid, bitset_size);
		extend_islands(grid, cache_grid, dequeue, islands);
		prev_grid_hash = grid_hash;
		grid_hash = get_grid_hash(grid, bitset_size);
		prev_islands_hash = islands_hash;
		islands_hash = get_islands_hash(islands);
	}
}
