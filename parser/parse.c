#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#define WHITESPACE " \r\v\f\n\t"
#define ID_MAX_LEN 2

char	*gnl(int fd)
{
	static char	buffer[65536] = {0};
	ssize_t		rd_n;
	char		*ret;
	size_t		spn;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	while (1)
	{
		rd_n = read(fd, buffer, 65536);
		if (strchr(buffer, '\n') || rd_n <= 0)
			break ;
	}
	if (rd_n == 0 && !strlen(buffer))
		return (0);
	spn = strcspn(buffer, "\n");
	ret = strndup(buffer, spn + 1);
	memmove(buffer, &buffer[spn + 1], 65536 - spn + 1);
	return (ret);
}

int	usage(char *name)
{
	dprintf(2, "Usage: %s <*.rt file>\n", name);
	return (EXIT_FAILURE);
}

int	cat_check(char *line)
{
	size_t	i;
	size_t	len;
	int		identifier_size;

	if (!line)
		return (0); /* no data */
	i = 0;
	len = strlen(line);
	while(i < len && isspace(line[i]))
		i++;
	if (!isalpha(line[i]))
		return (i); /* No identifier */
	while(i < ID_MAX_LEN && isalpha(line[i]))
		i++;
	identifier_size = (int)i;
	if (!isspace(line[i]))
		return (i); /* Identifier too long */
	return (-1);
}

void parse_line(char *line)
{
	char	*identifier;
	size_t	i;
	size_t	line_length;
	int		check;

	if (!line || strspn(line, WHITESPACE) == strlen(line))
		return ;
	i = 0;
	line_length = strlen(line);
	check =cat_check(line); 
	if (check != -1)
	{
		dprintf(2, "Error on line:\n");
		dprintf(2, "\t%s", line);
		if (!strchr(line, '\n'))
			dprintf(2, "\n");
		dprintf(2, "At character %d.\n", check);
		return ;
	}
	while (isspace(line[i]))
		i++;
	identifier = strndup(&line[i], strcspn(&line[i], WHITESPACE));
	free(identifier);
}

int main(int argc, char **argv)
{
	char	*ext;
	char 	*line;
	int		fd;

	if (argc != 2)
		return (usage(argv[0]));
	ext = strstr(argv[1], ".rt");
	if (!ext || strlen(ext) != 3)
		return (usage(argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (dprintf(2, "Invalid file '%s'.\n", argv[1]));
	line = (char *)1;
	while (line)
	{
		line = gnl(fd);
		parse_line(line);
		free(line);
	}
	return (0);
}
