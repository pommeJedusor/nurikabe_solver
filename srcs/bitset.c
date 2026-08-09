#include "nurikabe_solver.h"

int	cmp_bitsets(const unsigned long long *a, const unsigned long long *b, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (a[i] < b[i])
			return (-1);
		else if (a[i] > b[i])
			return (1);
		i++;
	}
	return (0);
}

void	bitset_and(unsigned long long *dest, const unsigned long long *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] &= src[i];
		i++;
	}
}

void	bitset_or(unsigned long long *dest, const unsigned long long *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] |= src[i];
		i++;
	}
}

void	copy_bitset(unsigned long long *dest, const unsigned long long *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

int	count_bitset_bits(const unsigned long long *bitset, int bitset_size)
{
	int	i;
	unsigned long long	cache;
	int	counter;

	counter = 0;
	i = 0;
	while (i < bitset_size)
	{
		cache = bitset[i];
		while (cache)
		{
			cache &= cache - 1;
			counter++;
		}
		i++;
	}
	return (counter);
}

int	get_bitset_size_from_nb_islands(int nb_islands)
{
	return ((nb_islands + 1) / 64 + 1);
}

int	get_bitset_size_from_islands(t_island *islands)
{
	return (get_bitset_size_from_nb_islands(get_islands_length(islands)));
}

int	get_bitset_trailing_zeros(const unsigned long long *bitset, int bitset_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < bitset_size)
	{
		j = 0;
		while (bitset[i] && (bitset[i] & (1ULL << j)) == 0)
			j++;
		if (bitset[i])
			return (j);
		i++;
	}
	return (-1);
}
