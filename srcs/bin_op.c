int	get_trailing_zeros(int number)
{
	int	i;

	i = 0;
	while ((number & (1 << i)) == 0)
		i++;
	return (i);
}

int	count_bits(int number)
{
	int	counter;

	counter = 0;
	while (number)
	{
		number &= number - 1;
		counter++;
	}
	return (counter);
}
