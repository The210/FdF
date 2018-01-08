/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:47:51 by dhorvill          #+#    #+#             */
/*   Updated: 2018/01/03 15:54:36 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_get_nbr(char *nbr)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (nbr[++i])
		j = j * 10 + (nbr[i] - '0');
	return (j);
}

int	main(int argc, char **argv)
{
	printf("%i\n", ft_get_nbr(argv[1]));
	return (0);
}
