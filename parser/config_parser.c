#include "parser.h"

static t_metatype	types[16] = {0};
static int			g_index = 0;

static void add_type(t_metatype mt)
{
	types[g_index] = mt;
	g_index++;
}

static char	*gnl(int fd)
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

static int	line_attr(char *attr_name, char *s)
{
	return (!strncmp(s, attr_name, strlen(attr_name)));
}

double	atod(char *nptr)
{
	double	res;
	double	sign;
	double	div_order;

	res = 0;
	sign = 1;
	div_order = 0;
	while (*nptr && isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign -= (*nptr++ == '-') * 2;
	while (*nptr && (isdigit(*nptr) || (*nptr == '.' && !div_order)))
	{
		div_order *= 10;
		if (*nptr == '.')
			div_order = 1;
		else
			res = (res * 10) + *nptr - '0';
		nptr++;
	}
	if (!div_order)
		div_order = 1;
	return ((res * sign) / div_order);
}

char	*trim(char *d, char *s)
{
	char	*ref;
	size_t	i;

	memset(d, 0, 8192);
	ref = s + strspn(s, WHITESPACE);
	i = strlen(ref);
	while (strchr(WHITESPACE, ref[i]) && i >= 0)
		i--;
	strncpy(d, ref, i + 1);
	d[i + 1] = 0;
	return (d);
}

static void	metatype_validation(t_metatype *mt)
{
	if (mt->n > 1 && !mt->sep)
		mt->sep = ',';
	if ((int)mt->hi == 0 && (int)mt->lo == 0)
	{
		mt->hi = DBL_MAX;
		mt->lo = -DBL_MAX;
	}
}

static int	get_parent_type(char *s)
{
	if (!strcmp(s, "double"))
		return (DOUBLE);
	return (INT);
}

static void	parse_metatype(char *name, int fd)
{
	char		*line;
	t_metatype	t;
	char		buff[8192];

	trim(buff, &name[1]);
	strcpy(t.name, buff);
	t.sep = 0;
	line = "gngngn";
	while (1)
	{
		line = gnl(fd);
		trim(buff, line);
		free(line);
		if (strchr(buff, '}'))
			break ;
		if (line_attr("type=", buff))
			t.ptype = get_parent_type(buff + strlen("type="));
		else if (line_attr("n=", buff))
			t.n = atoi(buff + strlen("n="));
		else if (line_attr("hi=", buff))
			t.hi = atod(buff + strlen("hi="));
		else if (line_attr("lo=", buff))
			t.lo = atod(buff + strlen("lo="));
		else if (line_attr("sep=", buff))
			t.sep = buff[strlen("sep=")];
	}
	metatype_validation(&t);
	add_type(t);
}

static void register_default_metatypes(void)
{
	t_metatype	t;

	strcpy(t.name,"double");
	t.sep = 0;
	t.ptype = DOUBLE;
	t.n = 1;
	t.hi = DBL_MAX;
	t.lo = DBL_MIN;
	add_type(t);
	strcpy(t.name,"int");
	t.sep = 0;
	t.ptype = INT;
	t.n = 1;
	t.hi = INT_MAX;
	t.lo = INT_MIN;
	add_type(t);
}


static void	set_param(t_declaration *ds, char *raw)
{
	size_t	len;
	size_t	i;
	int		j;
	int		k;
	char	typename[16];

	len = strlen(raw);
	j = 0;
	i = 0;
	while (i < len)
	{
		k = 0;
		strncpy(typename, raw + i, strcspn(raw + i, ","));
		typename[strcspn(raw + i, ",")] = 0;
		i += strlen(typename) + 1;
		while (k < g_index)
		{
			if (strcmp(types[k].name, typename) == 0)
				break;
			k++;
		}
		ds->parm_types[j] = types[k];
		j++;
	}
}

static	void	parse_datastructure(t_declaration *dec, int fd)
{
	char			*line;
	char			buff[8192];

	line = "gngngn";
	while (!strchr(line, '}'))
	{
		line = gnl(fd);
		trim(buff, line);
		free(line);
		if (strchr(buff, '}'))
			break ;
		if (line_attr("id=", buff))
			strcpy(dec->id, buff + strlen("id="));
		else if (line_attr("params=", buff))
			dec->nparm = atoi(buff + strlen("params="));
		else if (line_attr("params_type=", buff))
			set_param(dec, buff + strlen("params_type="));
	}
}

int get_config(t_declaration *dest)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("rt_conf.oml", O_RDONLY);
	if (fd < 0)
		return (1);
	line = (char *)1;
	register_default_metatypes();
	while (line)
	{
		line = gnl(fd);
		if (!line)
			break ;
		if (line[0] == '^')
			parse_metatype(line, fd);
		free(line);
	}
	close(fd);
	fd = open("rt_conf.oml", O_RDONLY);
	if (fd < 0)
		return (1);
	line = (char *)1;
	i = 0;
	while (line)
	{
		line = gnl(fd);
		if (!line)
			break ;
		if (line[0] == '%')
			parse_datastructure(&dest[i++], fd);
		free(line);
	}
	return (0);
}
