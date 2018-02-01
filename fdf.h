/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 00:50:31 by dhorvill          #+#    #+#             */
/*   Updated: 2018/02/01 20:32:58 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
#define FT_FDF_H

typedef struct	s_misc
{
	void		*mlx;
	void		*win;
	int			a;
	int			b;
	int			c;
	int			d;
	float		e;
	float		n;
	float		p;
	int			fd;
	int			distx;
	int 		disty;
	char		*str;
	int			xrot;
	int			yrot;
	int			roti;
	int			roto;
}				t_misc;

int ft_draw_line2(int x0, int y0, int x1, int y1, void *mlx, void *win);
int ft_draw_line3(int x0, int y0, int x1, int y1, void*mlx, void *win);
int exitt(int keycode, t_misc *s);
t_misc find_initial_coord(t_misc *s);
int	connect_dots(int yrot, int xrot, int new_num, int fd, int distx, int disty, float x, float y, void *mlx, void *win);
int nbw(char *s, char c);
char *ft_exchange(char *buf, char a, char *str);
int ft_getnbr(char *str, int i);

#endif
