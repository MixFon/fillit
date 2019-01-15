/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:07:47 by eskeleto          #+#    #+#             */
/*   Updated: 2019/01/14 11:27:45 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetr		*ft_coords_tetrimino(char *stetr)
{
	t_tetr	*tetr;
	int		count;
	int		i;
	int		start;

	i = 0;
	while (stetr[i] != '#')
		i++;
	start = i;
	tetr = (t_tetr *)malloc(sizeof(t_tetr));
	tetr->tetr_x[0] = 0;
	tetr->tetr_y[0] = 0;
	count = 1;
	while (count < 4)
	{
		i++;
		if (stetr[i] == '#')
		{
			tetr->tetr_x[count] = (i % 5) - (start % 5);
			tetr->tetr_y[count] = (i / 5) - (start / 5);
			count++;
		}
	}
	return (tetr);
}

t_tetr		*ft_coords_list(int len, char **stetr)
{
	t_tetr	*list;
	t_tetr	*last;
	t_tetr	*new;
	int		i;

	list = ft_coords_tetrimino(stetr[0]);
	list->ch = 'A';
	list->next = NULL;
	last = list;
	i = 1;
	while (i < len)
	{
		new = ft_coords_tetrimino(stetr[i]);
		new->ch = (char)(i + 'A');
		new->next = NULL;
		last->next = new;
		last = new;
		i++;
	}
	return (list);
}
