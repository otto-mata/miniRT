#include "parser.h"

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
	char	buff[8192];

	if (!line)
		return (0); /* no data */
	i = 0;
	trim(buff, line);
	len = strlen(buff);
	while (i < len && i < ID_MAX_LEN && isalpha(buff[i]))
	{
		if (!isalpha(buff[i]))
			return (i); /* No identifier */
		i++;
	}
	identifier_size = (int)i;
	if (!isspace(line[i]))
		return (i); /* Identifier too long */
	return (-1);
}

void	stack_split(char dest[][256], char *s, int *count, char *sep)
{
	size_t	len;
	size_t	i;
	int		wc;

	i = 0;
	wc = 0;
	len = strlen(s);
	while (i < len)
	{
		if (strchr(sep, s[i]))
		{
			i++;
			continue ;
		}
		if (i == 0 || strchr(sep, s[i - 1]))
			wc++;
		i++;
	}
	*count = 0;
	i = 0;
	while (*count < wc)
	{
		while (i < len && strchr(sep, s[i]))
			i++;
		strncpy(dest[*count], s + i, strcspn(s + i, sep));
		dest[*count][strcspn(s + i, sep) + 2] = 0;
		i += strlen(dest[*count]);
		(*count)++;
	}
}

static int	validate_param(char *raw, t_metatype mt)
{
	char	arr[16][256];
	int		used;

	memset(arr, 0, sizeof(arr));
	if (mt.sep)
	{
		if (!strchr(raw, mt.sep))
			return (printf("Invalid parameter "
				"(no separator when one expected)\n"));
		used = 0;
		stack_split(arr, raw, &used, &mt.sep);
		if (used != mt.n)
			return (printf("Invalid parameter (incorrect number of values, "
				"expected%d, got %d)\n", mt.n, used));
		for (int i = 0; i < used; i++)
			if (atod(arr[i]) > mt.hi || atod(arr[i]) < mt.lo)
				return (printf("Invalid parameter (OOB value, should %.1f >= %.1f >= %.1f)\n", mt.hi, atod(arr[i]), mt.lo));
	}
	else
	{
		// printf("%s\n", raw);
		if (atod(raw) > mt.hi || atod(raw) < mt.lo)
			return (printf("Invalid parameter (OOB value, should %.1f >= %.1f >= %.1f)\n", mt.hi, atod(raw), mt.lo));
	}
	return (0);
}
static int	validate_line(char *line, t_declaration rule)
{
	char	arr[16][256];
	int		used;

	used = 0;
	memset(arr, 0, sizeof(arr));
	stack_split(arr, line, &used, WHITESPACE);
	if (used - 1 != rule.nparm)
		printf("%s: invalid number of arguments (expected %d, got %d)\n",
			rule.id, rule.nparm, used - 1);
	for (int i = 1; i <= rule.nparm; i++)
	{
		validate_param((char *)arr[i], rule.parm_types[i - 1]);
	}
	return (1);
}

void	parse_line(char *line, t_declaration *rx)
{
	char	*identifier;
	size_t	i;
	size_t	line_length;
	int		check;

	if (!line || strspn(line, WHITESPACE) == strlen(line))
		return ;
	i = 0;
	line_length = strlen(line);
	check = cat_check(line);
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
	check = 0;
	for (i = 0; i < 16 && !check; i++)
		if (strcmp(identifier, rx[i].id) == 0)
			check = validate_line(line, rx[i]);
	if (!check)
		printf("%s is not a recognized identifier\n", identifier);
	free(identifier);
}

int	main(int argc, char **argv)
{
	char			*ext;
	char			*line;
	int				fd;
	t_declaration	declarations[16];

	if (argc != 2)
		return (usage(argv[0]));
	ext = strstr(argv[1], ".rt");
	if (!ext || strlen(ext) != 3)
		return (usage(argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (dprintf(2, "Invalid file '%s'.\n", argv[1]));
	line = (char *)1;
	get_config(declarations);
	while (line)
	{
		line = gnl(fd);
		parse_line(line, declarations);
		free(line);
	}
	return (0);
}
