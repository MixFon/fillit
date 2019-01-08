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
#include "fillit.h"


/*
** Создание новой чистой доски, размерностью nxn.
*/

static char		**ft_creatboard(size_t n)
{
	char	**boa;
	size_t	i;

	i = 0;
	if (!(boa = (char **)malloc(sizeof(char *) * (n + 9))))
		return (NULL);
	while (i < n)
	{
		if (!(boa[i] = (char *)malloc(sizeof(char) * (n + 1))))
			return (NULL);
		boa[i] = (char *)ft_memset(boa[i], '.', n);
		boa[i][n] = '\0';
		i++;
	}
	boa[i] = NULL;
	return (boa);
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
** Проверяет, может ли на данное место вставить тетримино 
*/

static int		ft_checktrak(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int		i;
	int		sum;

	sum = ft_strlen(*board);
	i = 0;
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
** Заполняет доку тeтримино 
*/

static void		ft_infilltetr(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] = tetr->ch;
		i++;
		ft_putboard(board);
		ft_putstr("\n");
	}
}

/*
** Подсчитывает площадь квадрата. 
*/

static void		ft_calkarea(char **board)
{
	int area; 

	area = 0;
	area = ft_strlen(*board);
	area *= area;
}


/*
**  Проходимся по всей доске и пытаемся вписать Тетримино.
**	Тетримино пока что задаю явно.
**	#.
**	##
**	#.
*/

static int		ft_infillboard(char **board, t_tetr *tetr)
{
	int		j;
	int		i;
	int		sum;

	sum = ft_strlen(*board);
	j = 0;
	i = 0;
	while (i <= sum)
	{
		j = 0;
		while (j <= sum)
		{
			if (ft_checktrak(board, j, i, tetr))
			{
				ft_infilltetr(board, j, i, tetr);	
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
** Рекуксивная функция для пребора всех возможных комбинаций листов списка.
** 
*/

/*
** Функция меняющая два сосдних элементов списка местами
*/

static t_tetr	*ft_swichlst(t_tetr *tetr)
{
	t_tetr *second;
	t_tetr *first;

	first = tetr;
	second = tetr->next;
	first->next = tetr->next->next;
	second->next = first;
	return (second);
}

/*
** Функция перебираюая возможные варианты и выподит информация в консоль
*/

static void		ft_allvar(char **board, t_tetr *tetr)
{
	int		num;
	int		i;
	t_tetr	*iter;
	t_tetr	*first;

	num = 4;
	i = 1;
	first = tetr;
	iter = tetr;
	while (i < 6)
	{
		ft_putnbr(i);
		ft_putstr("l\n");
		while (iter) 
		{
			if (!ft_infillboard(board, iter))
			{
				ft_delboard(board);
				board = ft_creatboard(++num);
				iter = tetr;
				ft_infillboard(board, iter);
			}
			iter = iter->next;
		}
		if (i%2 != 0)
		{
			iter = ft_swichlst(first);
			first = iter;
		} 
		else
		{
			iter = ft_swichlst(first->next);
			first = iter;
		} 
		num = 4;
		ft_delboard(board);
		board = ft_creatboard(num);
		i++;
	}
}

int				main(void)
{
	char		**board;
	int			num;
	t_tetr		*one; 
	t_tetr		*two;
	t_tetr		*three;
	t_tetr		*four;
	t_tetr		*iter;

	num = 4;
	one = (t_tetr *)malloc(sizeof(t_tetr));
	two	= (t_tetr *)malloc(sizeof(t_tetr));
	three = (t_tetr *)malloc(sizeof(t_tetr));
	four = (t_tetr *)malloc(sizeof(t_tetr));
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

	one->next = two;
	two->next = three;
	three->next = NULL;
	//four->next = NULL;

	board = ft_creatboard(num);
	ft_allvar(board, one);
	//ft_putnbr(ft_infillboard(board, 0, 0, one));
	//ft_putnbr(ft_infillboard(board, 0, 0, two));
	//ft_putnbr(ft_infillboard(board, 0, 0, three));
	//ft_putnbr(ft_infillboard(board, 0, 0, three));
	ft_putboard(board);
	ft_delboard(board);
	return (0);
}
