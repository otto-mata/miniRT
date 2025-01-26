#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define WHITESPACE " \r\v\f\n\t"

typedef struct s_metatype		t_metatype;
typedef struct s_declaration	t_declaration;

struct							s_metatype
{
	char						*name;
	char						*ptype;
	int							n;
	double						hi;
	double						lo;
};

struct							s_declaration
{
	char						*id;
	int							nparm;
	t_metatype					parm_types[255];
};

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

static int	skip_line(char *s)
{
	int	i;

	i = 0;
	while (isspace(s[i]))
		i++;
	if (i == strlen(s))
		return (1);
	if (s[i] == '#')
		return (1);
	return (0);
}

void parse_metatype(char *name, int fd)
{
	char *line;
	t_metatype	t;

	t.name = name;
	while (!strchr(line,'}')) 

}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("rt_conf.oml", O_RDONLY);
	if (fd < 0)
		return (1);
	line = (char *)1;
	while (line)
	{
		line = gnl(fd);
		if (!line)
			break ;
		if (skip_line(line))
			continue ;
		printf("%s", line);
		free(line);
	}
}
