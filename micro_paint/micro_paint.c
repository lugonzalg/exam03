#include "micro_paint.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int	ft_fill_brd(t_brd *brd)
{	
	int	i;
	brd->size = fscanf(brd->file, "%d %d %c\n", &brd->width, &brd->height, &brd->bck);
	if (brd->size != 3 || brd->width < 1 || brd->width > 300 || brd->height < 1 || brd->height > 300)
		return (1);
	brd->brd = (char **)calloc(sizeof(char *), brd->height + 1);
	if (!brd->brd)
		return (1);
	i = -1;
	while (++i < brd->height)
	{
		brd->brd[i] = (char *)calloc(sizeof(char), brd->width + 1);
		memset(brd->brd[i], brd->bck, brd->width);
	}
	return (0);
}

static void	ft_fill_shape(t_brd *brd, t_shape s)
{
	float	y;
	float	x;

	y = -1;
	while (++y < brd->height)
	{
		x = -1;
		while (++x < brd->width)
		{
			if (x >= s.x && x <= s.xbr && y >= s.y && y <= s.ybr)
			{
				if (s.type == 'R')
					brd->brd[(int)y][(int)x] = s.bck;
				else if (s.type == 'r' && (((s.x - x < 1.0 && s.x - x > -1.0)
					|| (s.xbr - x < 1.0 && s.xbr - x > -1.0)
					|| (s.y - y < 1.0 && s.y - y > -1.0) || (s.ybr - y < 1.0 && s.ybr - y > -1.0))))
					brd->brd[(int)y][(int)x] = s.bck;
			}	
		}
	}
}

static int	ft_get_shape(t_brd *brd)
{
	t_shape s;

	memset(&s, 0, sizeof(t_shape));
	while (brd->size != -1)
	{
		brd->size = fscanf(brd->file, "%c %f %f %f %f %c\n", &s.type, &s.x, &s.y, &s.width, &s.height, &s.bck);
		if (brd->size == -1)
			break ;
		else if (brd->size != 6 || (s.type != 'R' && s.type != 'r') || s.width <= 0.0 || s.height <= 0.0)
			return (1);
		s.xbr = s.x + s.width;
		s.ybr = s.y + s.height;
		ft_fill_shape(brd, s);
	}
	return (0);
}
static void	ft_print_brd(t_brd *brd)
{
	int	i;

	i = -1;
	while (brd->brd[++i])
	{
		write(1, brd->brd[i], brd->width);
		write(1, "\n", 1);
	}
}

static void	ft_free_d2(t_brd *brd)
{
	int	i;

	i = -1;
	while (brd->brd[++i])
		free(brd->brd[i]);
	free(brd->brd);
}

int	main(int argc, char *argv[])
{
	t_brd	brd;

	memset(&brd, 0, sizeof(t_brd));
	if (argc != 2)
	{
		write(1, "Error: argument\n", sizeof("Error: argument"));
		return (1);
	}
	brd.file = fopen(argv[1], "r");
	if (!brd.file || ft_fill_brd(&brd) || ft_get_shape(&brd))
	{
		write(1, "Error: Operation file corrupted\n", sizeof("Error: Operation file corrupted"));
		ft_free_d2(&brd);
		fclose(brd.file);
		return (1);
	}
	ft_print_brd(&brd);
	ft_free_d2(&brd);
	fclose(brd.file);
	return (0);
}
