/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_dots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:30:09 by dhorvill          #+#    #+#             */
/*   Updated: 2018/02/01 21:10:15 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "fdf.h"

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

int	nbw(char *s, char c)
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

t_misc determine_dist(int fd, t_misc *s)
{
	char buf[9000];
	int ret;
	char **pdt;

	s->a = 0;
	s->b = 0;
	s->d = 0;
	ret = read(fd, buf, 8999);
	buf[ret] = '\0';
	if ((pdt = ft_strsplit(buf, '\n')) == 0)
		return (*s);
	s->b = nbw(pdt[s->a], ' ');
	while (pdt[s->a])
		s->a++;
	s->d = (round(10000 / (s->b * s->a)) + 5);
	return (*s);
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

int connect_dots(int yrot, int xrot, int new_num, int fd, int distx, int disty, float x, float y, void *mlx, void *win)
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
			nbr = ft_getnbr(pdt[i], j) * new_num / 5;
			while (pdt[i][j + 2] && pdt[i][j] != ' ')
				j++;
			while (pdt[i][j + 2] && pdt[i][j] == ' ')
				j++;
			next_nbr = ft_getnbr(pdt[i], j) * new_num / 5;
			calcul = y - (nbr * round(disty / 3)) - (yrot * nbr);
			calcul2 = round(x + distx - (xrot * next_nbr));
			calcul3 = round(y - (yrot * next_nbr) + disty - (next_nbr * (round(disty / 3))));
			ft_draw_line2(x - (xrot * nbr), calcul,
					calcul2, calcul3, mlx, win);
			x = round(x + (distx));
			y = round(y + (disty));
		}
		i++;
		x = init_x - (distx * i);
		y = init_y + (disty * i);
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
			nbr = ft_getnbr(str[i], 0) * new_num / 5;
			i++;
			while (i % nbpl != counter)
				i++;
			next_nbr = ft_getnbr(str[i], 0) * new_num / 5;
			ft_draw_line2(x - (xrot * nbr), y - (nbr * round(disty / 3)) - (yrot * nbr), round(x - distx - (xrot * next_nbr)), round(y - (yrot * next_nbr) + disty - (next_nbr * (round (disty / 3)))), mlx, win);
			x = round (x - (distx));
			y = round (y + (disty));
		}
		counter++;
		x = init_x + (distx * counter);
		y = init_y + (disty * counter);
	}
	x = init_x;
	y = init_y;
	return (0);
}

t_misc	find_initial_coord(t_misc *s)
{
	s->e = 500;
	s->n = 1230;
	s->e = s->e - ((s->a / 2) * s->d);
	s->n = s->n - ((s->b / 2) * s->d);
	return (*s);
}

int	main(int argc, char **argv)
{
	int fd;
	void *param;
	t_misc s;

	s.p = 1;
	s.roti = 0;
	s.roto = 0;
	s.xrot = 0;
	s.yrot = 0;
	s.str = argv[1];
	s.d = 0;
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, 2000, 2000, "line_test");
	fd = open(argv[1], O_RDONLY);
	if (s.d == 0)
		s = determine_dist(fd, &s);
	s.distx = s.d;
	s.disty = s.d;
	close(fd);
	fd = open(argv[1], O_RDONLY);
	s = find_initial_coord(&s);
	printf("%f, %f\n", s.n, s.e);
	s.fd = fd;
	connect_dots(s.yrot, s.xrot, s.p, fd, s.distx, s.disty, s.n, s.e, s.mlx, s.win);
	mlx_key_hook(s.win, exitt, (void *)&s);
	mlx_loop(s.mlx);
	return (0);
}
