/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_dots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:30:09 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/22 17:25:00 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "fdf.h"

void ft_draw_line(float x1, float y1, float x2, float y2, void *mlx, void *win);

char	*ft_exchange(char *buf, char a, char *str)
{
	int i;
	char *strr;

	if ((strr = (char*)malloc(sizeof(strr) * ft_strlen(buf))) == NULL)
		return (NULL);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == a)
			strr[i] = ' ';
		else
			strr[i] = buf[i];
		i++;
	}
	return (strr);
}

static int	nbw(char *s, char c)
{
	int i;
	int sym;
	int count;

	i = 0;
	sym = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			sym = 1;
			i++;
		}
		while (s[i] == c && s[i])
		{
			count += sym;
			sym = 0;
			i++;
		}
	}
	return (count + 1);
}

t_misc determine_dist(int fd, t_misc s)
{
	char buf[9000];
	int ret;
	char **pdt;

	s.a = 0;
	s.b = 0;
	s.d = 0;
	ret = read(fd, buf, 8999);
	buf[ret] = '\0';
	if ((pdt = ft_strsplit(buf, '\n')) == 0)
		return (s);
	s.b = nbw(pdt[s.a], ' ');
	while (pdt[s.a])
		s.a++;
	//s.d = (round(10000 / (s.b * s.a * 2)) + 5);
	s.d = 12;
	printf("%i\n", s.d);
	return (s);
}


int	ft_getnbr(char *str, int i)
{
	int j;
	int nbr;

	j = i;
	nbr = 0;
	while (str[j] && str[j] != ' ')
	{
		nbr = nbr * 10 + (str[j] - '0');
		j++;
	}
	return (nbr);
}

int connect_dots(int fd, int dist, float x, float y, void *mlx, void *win)
{
	char buf[9000];
	char **pdt;
	int ret;
	int i;
	int j;
	float init_x;
	float init_y;
	int nbr;
	int next_nbr;
	int calcul;
	int calcul2;
	int calcul3;
	int k;
	int kl;
	int nbpl;
	int counter;
	char **str;
	char *strr;

	printf("enters");
	i = 0;
	kl = 0;
	init_x = x;
	init_y = y;
	nbr = 0;
	counter = 0;
	ret = read(fd, buf, 8999);
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
			nbr = ft_getnbr(pdt[i], j);
			while (pdt[i][j + 2] && pdt[i][j] != ' ')
				j++;
			while (pdt[i][j + 2] && pdt[i][j] == ' ')
				j++;
			next_nbr = ft_getnbr(pdt[i], j);
			calcul = round(y - (nbr * (round(dist / 3))));
			calcul2 = round(x + dist);
			calcul3 = round(y + dist - (next_nbr * (round(dist / 3))));
			ft_draw_line(x, calcul,
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
			nbr = ft_getnbr(str[i], 0);
			i++;
			while (i % nbpl != counter)
				i++;
			next_nbr = ft_getnbr(str[i], 0);
			ft_draw_line(x, round(y - (nbr * round(dist / 3))), round(x - dist), round(y + dist - (next_nbr * (round (dist / 3)))), mlx, win);
			x = round (x - (dist));
			y = round (y + (dist));
		}
		counter++;
		x = init_x + (dist * counter);
		y = init_y + (dist * counter);
	}
	return (0);
}

t_misc	find_initial_coord(t_misc s)
{
	s.e = 500;
	s.n = 1200;
	s.e = s.e - ((s.a / 2) * s.d);
	s.n = s.n - ((s.b / 2) * s.d);
	return (s);
}

int	main(int argc, char **argv)
{
	int fd;
	void *mlx;
	void *win;
	t_misc s;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 2000, 2000, "line_test");
	fd = open(argv[1], O_RDONLY);
	s = determine_dist(fd, s);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	s = find_initial_coord(s);
	connect_dots(fd, s.d, s.n, s.e, mlx, win);
	mlx_loop(mlx);
	return (0);
}
