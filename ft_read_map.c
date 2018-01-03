/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:27:56 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/03 17:52:35 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	ft_get_length(char *map)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 1;
	while (map[i] && map[i] != '\n')
	{
		while (map[i] == ' ')
		{
			flag = 1;
			i++;
		}
		while (map[i] && map[i] != ' ' && map[i] != '\n')
		{
			j = j + flag;
			i++;
			flag = 0;
		}
	}
	return (j);
}

int ft_get_height(char *map)
{
	int i;
	char **pdt;

	if ((pdt = ft_strsplit(map, '\n')) == 0)
		return (0);
	i = 0;
	while (pdt[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int fd;
	int ret;
	int height;
	int length;
	char buf[5000];

	fd = open(argv[1], O_RDONLY);
	ret = read(fd, buf, 4999);
	buf[ret] = '\0';
	height = ft_get_height(buf);
	length = ft_get_length(buf);
	return (0);
}
