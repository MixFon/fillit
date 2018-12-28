/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:22:57 by widraugr          #+#    #+#             */
/*   Updated: 2018/12/28 16:53:45 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_last_ver/libft.h"

/*
** Создание новой чистой доски.
*/

static char	**ft_creatboard(size_t n)
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
		board[i] = (char *)ft_memset(board[i], '.', n);
		board[i][n] = '\0';
		i++;
	}
	board[i] = NULL;
	return (board);
}

/*
** Вывод доски в консоль
*/

static void	ft_putboard(char **board)
{
	while (*board)
	{
		ft_putstr(*board);
		ft_putstr("\n");
		board++;
	}
}

/*
** Удаление доски.
** Нужна проверка на утечки, возможны утечки в цикле.
*/

static void	ft_delboard(char **board)
{
	while (*board)
	{
		ft_strdel(board);
		board++;
	}
	//free(board);
	board = NULL;
}

/*
** Помещаем тетрино на доску. Тетрино пока что задаю явно.
**	#.
**	##
**	#.
*/

static int	ft_infillboard(char **board, int start_x, int start_y)
{
	int		tetr_x[4] = {0, 1, 0, 0};
	int		tetr_y[4] = {0, 1, 1, 2};
	int		i;

	i = 0;
	while (i < 4)
	{
		board[start_y + tetr_y[i]][start_x + tetr_x[i]] = '#';
		i++;
	}
	return (1);
}

int			main(void)
{
	char	**board;
	int		num;

	num = 4;
	board = ft_creatboard(num);
	ft_infillboard(board, 1, 1);
	ft_putboard(board);
	ft_delboard(board);
	return (0);
}
