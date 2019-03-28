/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_tetrimino.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:12:54 by eskeleto          #+#    #+#             */
/*   Updated: 2019/01/11 13:44:58 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_is_valid_chars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '.' && str[i] != '#' && str[i] != '\n')
			return (0);
		if (str[i] == '#')
			count++;
		i++;
	}
	if (count != 4)
		return (0);
	return (1);
}

static int	ft_count_contact(char *str, int pos)
{
	int	count;

	count = 0;
	if (pos / 5 != 0)
	{
		if (str[pos - 5] == '#')
			count++;
	}
	if (pos / 5 != 3)
	{
		if (str[pos + 5] == '#')
			count++;
	}
	if (pos % 5 != 0)
	{
		if (str[pos - 1] == '#')
			count++;
	}
	if (pos % 5 != 4)
	{
		if (str[pos + 1] == '#')
			count++;
	}
	return (count);
}

int			ft_is_valid_contact(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '#')
			count += ft_count_contact(str, i);
		i++;
	}
	if (count >= 5)
		return (1);
	return (0);
}
