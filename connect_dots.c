/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_dots.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:30:09 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/08 19:06:13 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
void ft_draw_line(float x1, float y1, float x2, float y2, void *mlx, void *win);

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

	i = 0;
	init_x = x;
	init_y = y;
	nbr = 0;
	ret = read(fd, buf, 8999);
	buf[ret] = '\0';
	if ((pdt = ft_strsplit(buf, '\n')) == 0)
		return (0);
	while (pdt[i])
	{
		j = 0;
		while (pdt[i][j])
		{
			while(pdt[i][j] && pdt[i][j] == ' ')
				j++;
			nbr = ft_getnbr(pdt[i], j);
			while (pdt[i][j] && pdt[i][j] != ' ')
				j++;
			while (pdt[i][j] && pdt[i][j] == ' ')
				j++;
			next_nbr = ft_getnbr(pdt[i], j);
			ft_draw_line(round(x), round(y - nbr),
			round(x + (sqrt(dist) / 2)), ((round(y + (sqrt(dist) / 2)) - next_nbr)), mlx, win);
			printf("y1: ");
			printf("%f\n", round(y - nbr));
			printf("y2: ");
			printf("%f\n", round(y + (sqrt(dist)/2) - next_nbr));

			x = round(x + (sqrt(dist) / 2));
			y = round(y + (sqrt(dist) / 2));
		}
		i++;
		x = init_x - ((sqrt(dist) / 2) * i);
		y = init_y + ((sqrt(dist) / 2) * i);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int fd;
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "line_test");
	fd = open(argv[1], O_RDONLY);
	connect_dots(fd, 1000, 300, 300, mlx, win);
	mlx_loop(mlx);
	return (0);
}
