/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:25:58 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/31 22:24:12 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "fdf.h"
#include <fcntl.h>

int	clearstuff(int new_num, int fd, int dist, float x, float y, void *mlx, void *win)
{
	char buf[15000];
	char **pdt;
	int ret;
	int i;
	int j;
	float init_x;
	float init_y;
	float nbr;
	float next_nbr;
	int calcul;
	int calcul2;
	int calcul3;
	int k;
	int kl;
	int nbpl;
	int counter;
	char **str;
	char *strr;

	i = 0;
	kl = 0;
	init_x = x;
	init_y = y;
	nbr = 0;
	counter = 0;
	ret = read(fd, buf, 14999);
	buf[ret] = '\0';
	if ((pdt = ft_strsplit(buf, '\n')) == 0)
		return (0);
	while (pdt[i])
	{
		j = 0;
		while (pdt[i][j + 2])
		{
			while(pdt[i][j + 2] && pdt[i][j] == ' ')
				j++;
			nbr = ft_getnbr(pdt[i], j) * new_num;
			while (pdt[i][j + 2] && pdt[i][j] != ' ')
				j++;
			while (pdt[i][j + 2] && pdt[i][j] == ' ')
				j++;
			next_nbr = ft_getnbr(pdt[i], j) * new_num;
			calcul = y - (nbr * (round(dist / 3)));
			calcul2 = round(x + dist);
			calcul3 = round(y + dist - (next_nbr * (round(dist / 3))));
			ft_draw_line3(x, calcul,
					calcul2, calcul3, mlx, win);
			x = round(x + (dist));
			y = round(y + (dist));
		}
		i++;
		x = init_x - (dist * i);
		y = init_y + (dist * i);
	}
	x = init_x;
	y = init_y;
	while(pdt[kl])
		kl++;
	strr = ft_exchange(buf, '\n', strr);
	str = ft_strsplit(strr, ' ');
	nbpl = nbw(pdt[0], ' ');
	while (counter < nbpl)
	{
		i = 0;
		while (i < nbpl * kl - nbpl)
		{
			while (i % nbpl != counter)
				i++;
			nbr = ft_getnbr(str[i], 0) * new_num;
			i++;
			while (i % nbpl != counter)
				i++;
			next_nbr = ft_getnbr(str[i], 0) * new_num;
			ft_draw_line3(x, round(y - (nbr * round(dist / 3))), round(x - dist), round(y + dist - (next_nbr * (round (dist / 3)))), mlx, win);
			x = round (x - (dist));
			y = round (y + (dist));
		}
		counter++;
		x = init_x + (dist * counter);
		y = init_y + (dist * counter);
	}
	x = init_x;
	y = init_y;
	return (0);
}

int	exitt(int keycode, t_misc *s)
{
	printf("%i\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->d += 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 126)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->p += 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d,s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 125)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->p -= 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 124)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->n += 50;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 123)
	{
		close(s->fd);
		s->fd= open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);	
		s->n -= 50;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 7)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->d -= 1;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 13)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->e -= 50;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		connect_dots(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
	}
	if (keycode == 1)
	{
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
		clearstuff(s->p, s->fd, s->d, s->n, s->e, s->mlx, s->win);
		s->e += 50;
		close(s->fd);
		s->fd = open(s->str, O_RDONLY);
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

int ft_draw_line3(int x0, int y0, int x1, int y1, void *mlx, void *win)
{
	float dx;
	int sx;
	float dy;
	int sy;
	float m;
	float b;

	if (x0 == x1 && y0 == y1)
	{
		mlx_pixel_put(mlx, win, x0, y0, 0);
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
			mlx_pixel_put(mlx, win, x0, round(m * x0 + b), 0);
			x0 += sx;
		}
	}
	else
	{
		m = dx / dy;
		b = x0 - m * y0;
		while (y0 != y1)
		{
			mlx_pixel_put(mlx, win, round(m * y0 +b), y0, 0);
			y0 += sy;
		}
	}
	mlx_pixel_put(mlx, win, x1, y1, 0);
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
