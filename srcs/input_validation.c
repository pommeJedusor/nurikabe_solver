int	is_input_valid(char *file_content)
{
	int	i;
	int	line_length;
	int	current_line_length;
	int	nb_lines;

	line_length = -1;
	nb_lines = 0;
	if (file_content[0] == '\0')
		return (0);
	current_line_length = 0;
	i = 0;
	while (i == 0 || file_content[i - 1])
	{
		if ((i != 0 && file_content[i - 1] != '\n' && file_content[i - 1] != '\0')
				&& (file_content[i] == '\n' || file_content[i] == '\0'))
		{
			if (line_length == -1)
				line_length = current_line_length;
			else if (line_length != current_line_length)
				return (0);
			nb_lines++;
			current_line_length = 0;
		}
		else if (file_content[i] != '\n' && file_content[i] != '\0')
			current_line_length++;
		i++;
	}
	return (line_length > 0 && nb_lines == line_length);
}
