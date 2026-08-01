#ifndef NURIKABE_SOLVER_H
# define NURIKABE_SOLVER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

char	*get_file_content(char *file_name);
char	**split_lines(char *str);
char	**free_lines(char **strs);

#endif
