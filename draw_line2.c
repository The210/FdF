/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:25:58 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/31 21:23:47 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "fdf.h"
#include <fcntl.h>

void	clearstuff(void *mlx, void *win)
{
	int x;
	int y;

	x = 0;
	while(x < 1700)
	{
		y = 0;
		while(y < 1400)
		{
			mlx_pixel_put(mlx, win, x, y, 0);
			y++;
		}
		x++;
	}
}

int	exitt(int keycode, t_misc *s)
{
	printf("%i\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
	{
		s->d += 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->mlx, s->win);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 126)
	{
		s->p += 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->mlx, s->win);
		connect_dots(s->p, s->fd, s->d,s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 125)
	{
		s->p -= 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->mlx, s->win);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 124)
	{
		s->n += 50;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->mlx, s->win);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	return (0);
}

int ft_draw_line2(int x0, int y0, int x1, int y1, void *mlx, void *win)
{
	float dx;
	int sx;
	float dy;
	int sy;
	float m;
	float b;

	if (x0 == x1 && y0 == y1)
	{
		mlx_pixel_put(mlx, win, x0, y0, 0x00FFFFFF);
		return (0);
	}
	dx = x1 - x0;
	dy = y1 - y0;
	sx = (dx < 0) ? -1 : 1;
	sy = (dy < 0) ? -1 : 1;

	if (fabsf(dy) < fabsf(dx))
	{
		m = dy / dx;
		b = y0 - m * x0;
		while (x0 != x1)
		{
			mlx_pixel_put(mlx, win, x0, round(m * x0 + b), 0x00FFFFFF);
			x0 += sx;
		}
	}
	else
	{
		m = dx / dy;
		b = x0 - m * y0;
		while (y0 != y1)
		{
			mlx_pixel_put(mlx, win, round(m * y0 +b), y0, 0x00FFFFFF);
			y0 += sy;
		}
	}
	mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
	return (0);
}

/*int	main(void)
  {
  void *mlx;
  void *win;

  mlx = mlx_init();
  win = mlx_new_window(mlx, 1000, 1000, "draw_line2");
  draw_line2(mlx, win, 50, 50, 34, 89);
  mlx_loop(mlx);
  return (0);
  }*/
