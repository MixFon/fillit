/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:22:57 by widraugr          #+#    #+#             */
/*   Updated: 2019/01/14 16:36:04 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_last_ver/libft.h"
#include "fillit.h"

/*
** Создание новой чистой доски, размерностью nxn.
*/

static char		**ft_creatboard(size_t n)
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

static void		ft_putboard(char **board)
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

static void		ft_delboard(char **board)
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
** Подсчет колличества элементов скиска, для подстановки в факториал и
** нахождение всех вариантов перебора.
*/

static int	ft_numberlst(t_tetr *lst)
{
	t_tetr	*iter;
	int		num;

	if (!lst)
		return (0);
	num = 0;
	iter = lst;
	while (iter)
	{
		num++;
		iter = iter->next;
	}
	return (num);
}

/*
** Вычислкние стартового размера доски
*/

static int	ft_startsizeboard(t_tetr *lst)
{
	int	len;
	int numberlst;

	len = 4;
	numberlst = ft_numberlst(lst);
	while ((len * len) < (numberlst * 4))
		len++;
	return (len);
}

/*
** Проверяет, может ли на данное место вставить тетримино
*/

static int		ft_checktrak(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int		i;
	int		sum;

	sum = ft_strlen(*board);
	i = 0;
	if (!tetr)
		return (0);
	while (i < 4)
	{
		if (start_y + tetr->tetr_y[i] >= sum || start_x + tetr->tetr_x[i] >= sum)
			return (0);
		if (board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] != '.')
			return (0);
		i++;
	}
	return (1);
}

/*
** Заполняет доку тeтримино (буквами)
** Печатал каждый раз символ который заполнял
*/

static void		ft_infilltetr(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] = tetr->ch;
		i++;
		//ft_putboard(board);
		//ft_putstr("\n");
	}
}

/*
** Удаляет с доски тетрамино.
*/

static void		ft_deltetr(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] = '.';
		i++;
		//ft_putboard(board);
		//ft_putstr("\n");
	}
}

/*
** Рекурсивный перебор всех вариантов располохения тетрамино на доске
*/

static int	ft_recrunlst(char **board, t_tetr *lst)
{
	t_tetr	*first;
	int		i;
	int		j;
	int		n;

	i = 0;
	n = ft_strlen(*board);
	if (!lst)
		return (1);
	//ft_putchar(lst->ch);
	//ft_putstr("\n");
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (ft_checktrak(board, j, i, lst))
			{
				ft_infilltetr(board, j, i, lst);
				//ft_putboard(board);
				//ft_putstr("\n");
				if (ft_recrunlst(board, lst->next))
					return (1);
				ft_deltetr(board, j, i, lst);
			}
			j++;
		}
		i++;
	}
	//ft_putboard(board);
	//ft_putstr("\n");
	//ft_putstr("bab\n");
	return (0);
}

int		main(void)
{
	t_tetr		*one; 
	t_tetr		*two;
	t_tetr		*three;
	t_tetr		*four;
	t_tetr		*five;
	t_tetr		*six;

	one = (t_tetr *)malloc(sizeof(t_tetr));
	two	= (t_tetr *)malloc(sizeof(t_tetr));
	three = (t_tetr *)malloc(sizeof(t_tetr));
	four = (t_tetr *)malloc(sizeof(t_tetr));
	five = (t_tetr *)malloc(sizeof(t_tetr));
	six = (t_tetr *)malloc(sizeof(t_tetr));
	one->ch = 'A';
	one->tetr_x[0] = 0;
	one->tetr_x[1] = 1;
	one->tetr_x[2] = 0;
	one->tetr_x[3] = 0;

	one->tetr_y[0] = 0;
	one->tetr_y[1] = 1;
	one->tetr_y[2] = 1;
	one->tetr_y[3] = 2;
	
	two->ch = 'B';
	two->tetr_x[0] = 0;
	two->tetr_x[1] = 0;
	two->tetr_x[2] = 0;
	two->tetr_x[3] = 0;

	two->tetr_y[0] = 0;
	two->tetr_y[1] = 1;
	two->tetr_y[2] = 2;
	two->tetr_y[3] = 3;

	three->ch = 'C';
	three->tetr_x[0] = 0;
	three->tetr_x[1] = 1;
	three->tetr_x[2] = 0;
	three->tetr_x[3] = 1;

	three->tetr_y[0] = 0;
	three->tetr_y[1] = 0;
	three->tetr_y[2] = 1;
	three->tetr_y[3] = 1;

	four->ch = 'D';
	four->tetr_x[0] = 0;
	four->tetr_x[1] = 1;
	four->tetr_x[2] = 0;
	four->tetr_x[3] = 1;

	four->tetr_y[0] = 0;
	four->tetr_y[1] = 0;
	four->tetr_y[2] = 1;
	four->tetr_y[3] = 1;

	five->ch = 'E';
	five->tetr_x[0] = 0;
	five->tetr_x[1] = 1;
	five->tetr_x[2] = 0;
	five->tetr_x[3] = 0;

	five->tetr_y[0] = 0;
	five->tetr_y[1] = 1;
	five->tetr_y[2] = 1;
	five->tetr_y[3] = 2;
	
	six->ch = 'F';
	six->tetr_x[0] = 0;
	six->tetr_x[1] = 1;
	six->tetr_x[2] = 0;
	six->tetr_x[3] = 0;

	six->tetr_y[0] = 0;
	six->tetr_y[1] = 1;
	six->tetr_y[2] = 1;
	six->tetr_y[3] = 2;

	one->next = two;
	two->next = three;
	three->next = four;
	four->next = five;
	five->next = six;
	six->next = NULL;

	char	**board;
	int sum = ft_startsizeboard(one);

	board = ft_creatboard(sum);
	while (!ft_recrunlst(board, one))
	{
		ft_delboard(board);
		board = ft_creatboard(++sum);
	}
	ft_putboard(board);
	return (0);
}
