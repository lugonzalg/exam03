#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

#include <stdio.h>

typedef struct	s_brd
{
	int		width;
	int		height;
	char	bck;
	char	**brd;
	FILE	*file;
	int		size;
}	t_brd;

typedef struct	s_shape
{
	char	bck;
	char	type;
	float	x;
	float	y;
	float	xbr;
	float	ybr;
	float	width;
	float	height;
}	t_shape;

#endif
