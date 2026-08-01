#include <stdlib.h>

int	count_lines(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && (i == 0 || str[i - 1] == '\n'))
			counter++;
		i++;
	}
	return (counter);
}

char	**free_lines(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

char	*copy_until_new_line(char *str)
{
	int		i;
	int		size;
	char	*line;

	size = 0;
	while (str[size] && str[size] != '\n')
		size++;
	line = malloc(sizeof(char) * (size + 1));
	if (line == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**split_lines(char *str)
{
	char	**strs;
	int		nb_line;
	int		i;
	int		strs_i;

	nb_line = count_lines(str);
	strs = malloc(sizeof(char *) * (nb_line + 1));
	if (strs == 0)
		return (0);
	i = 0;
	strs_i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && (i == 0 || str[i - 1] == '\n'))
		{
			strs[strs_i] = copy_until_new_line(&str[i]);
			if (strs[strs_i] == 0)
				return (free_lines(strs));
			strs_i++;
		}
		i++;
	}
	strs[strs_i] = 0;
	return (strs);
}
