/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 18:59:48 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/01 21:37:23 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	exitt(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	float		x1;
	float		y1;
	float 	x2;
	float		y2;
	int		m;
	int		n;
	float	coeff;
	int		coeffint;
	int		increm;

	m = 1;
	n = 1;
	increm = 1;
	x1 = atoi(argv[1]);
	y1 = atoi(argv[2]);
	x2 = atoi(argv[3]);
	y2 = atoi(argv[4]);
	if (x2 - x1 == 0)
		coeff = 0;
	else
		coeff = ((y2 - y1) / (x2 - x1));
	if (coeff < 0)
		coeff *= -1;
	if (coeff == 0)
		coeffint = 0;
	else
		coeffint = 1 / coeff;
	if (coeffint == 0)
		coeffint = coeff;
	printf("%i\n", coeffint);
	printf("%f\n", coeff);
	if (x1 > x2)
		m = -1;
	if (y1 > y2)
		n = -1;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "line_test");
	if (coeff == 0 || coeffint == 0)
	{
		while (y1 != y2)
		{
			mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
			y1 += n;
		}
	}
	if (coeff > 1)
	{
		if (m == 1 && n == 1)
		{
			while (x1 < x2 ||  y1 < y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					x1 += m;
				else
				{
					y1 += n;
					increm = 0;
				}
				increm++;
			}
		}
		else if (m == 1 && n == -1)
		{
			while (x1 < x2 ||  y1 > y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					x1 += m;
				else
				{
					y1 += n;
					increm = 0;
				}
				increm++;
			}
		}
		else if (m == -1 && n == 1)
		{
			while (x1 > x2 ||  y1 < y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					x1 += m;
				else
				{
					y1 += n;
					increm = 0;
				}
				increm++;
			}
		}
		else
		{
			while (x1 > x2 ||  y1 > y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					x1 += m;
				else
				{
					y1 += n;
					increm = 0;
				}
				increm++;
			}
		}
	}
	else
	{
		if (m == 1 && n == 1)
		{
			while (x1 < x2 || y1 < y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					y1 += n;
				else
				{
					x1 += m;
					increm = 0;
				}
				increm++;
			}
		}
		else if (m == 1 && n == -1)
		{
			while (x1 < x2 || y1 > y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					y1 += n;
				else
				{
					x1 += m;
					increm = 0;
				}
				increm++;
			}
		}
		else if (m == -1 && n == -1)
		{
			while (x1 > x2 || y1 > y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					y1 += n;
				else
				{
					x1 += m;
					increm = 0;
				}
				increm++;
			}
		}
		else
		{
			while (x1 > x2 || y1 < y2)
			{
				mlx_pixel_put(mlx, win, x1, y1, 0x00FFFFFF);
				if (increm <= coeffint)
					y1 += n;
				else
				{
					x1 += m;
					increm = 0;
				}
				increm++;
			}
		}
	}

	mlx_key_hook(win , exitt, mlx);
	mlx_loop(mlx);
	return (0);
}
