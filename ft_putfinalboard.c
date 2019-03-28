/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:22:57 by widraugr          #+#    #+#             */
/*   Updated: 2019/01/17 12:24:23 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Delete board.
** Problem leaks in while??
*/

void		ft_delboard(char **board)
{
	while (*board)
	{
		ft_strdel(board);
		board++;
	}
	board = NULL;
}

/*
** Calculation of the starting size.
*/

int			ft_startsizeboard(t_tetr *lst)
{
	int	len;
	int	numberlst;

	len = 2;
	numberlst = ft_numberlst(lst);
	while ((len * len) < (numberlst * 4))
		len++;
	return (len);
}

/*
** Create new board size nxn
*/

char		**ft_creatboard(size_t n)
{
	char	**board;
	size_t	i;

	i = 0;
	if (!(board = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		if (!(board[i] = (char *)malloc(sizeof(char) * (n + 1))))
			return (NULL);
		board[i] = (char *)ft_memset((char *)board[i], '.', n);
		board[i][n] = '\0';
		i++;
	}
	board[i] = NULL;
	return (board);
}

/*
** Input board to console
*/

void		ft_putboard(char **board)
{
	while (*board)
	{
		ft_putstr(*board);
		ft_putstr("\n");
		board++;
	}
}

void		ft_putfinalboard(t_tetr *one)
{
	char	**board;
	int		sum;

	sum = ft_startsizeboard(one);
	board = ft_creatboard(sum);
	while (!ft_recrunlst(board, one))
	{
		ft_delboard(board);
		free(board);
		board = ft_creatboard(++sum);
	}
	ft_putboard(board);
	ft_delboard(board);
	free(board);
}
