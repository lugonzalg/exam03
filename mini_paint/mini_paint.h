#ifndef MINI_PAINT_H
#define MINI_PAINT_H

#include <stdio.h>

typedef struct	s_brd
{
	FILE	*file;
	char	**brd;
	int		width;
	int		height;
	char	bck;
	int		size;
}	t_brd;

typedef struct	s_shape
{
	float	x;
	float	y;
	float	r;
	char	bck;
	char	type;
}	t_shape;
#endif
