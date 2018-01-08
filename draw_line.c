/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 18:59:48 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/08 18:15:38 by dhorvill         ###   ########.fr       */
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

void ft_draw_line(float x1, float y1, float x2, float y2, void *mlx, void *win)
{
	int		m;
	int		n;
	float	coeff;
	int		coeffint;
	int		increm;

	m = 1;
	n = 1;
	increm = 1;
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
	if (x1 > x2)
		m = -1;
	if (y1 > y2)
		n = -1;
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
}
