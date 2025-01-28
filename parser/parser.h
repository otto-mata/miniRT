#ifndef PARSER_H
# define PARSER_H
# include <ctype.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define WHITESPACE " \r\v\f\n\t"
# define ID_MAX_LEN 2
# define DEFAULT_LIMIT 10000000

typedef struct s_metatype		t_metatype;
typedef struct s_declaration	t_declaration;
typedef enum e_ptypes			t_ptypes;

enum							e_ptypes
{
	INT = 0,
	DOUBLE,
};

struct							s_metatype
{
	char						name[16];
	t_ptypes					ptype;
	int							n;
	double						hi;
	double						lo;
	char						sep;
};

struct							s_declaration
{
	char						id[8];
	int							nparm;
	t_metatype					parm_types[256];
};
int								get_config(t_declaration *dest);
char							*trim(char *d, char *s);
double							atod(char *nptr);
#endif
