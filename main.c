/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:22:57 by widraugr          #+#    #+#             */
/*   Updated: 2019/01/10 15:44:22 by widraugr         ###   ########.fr       */
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
** Подсчитывает площадь квадрата. 
*/
/*
static void		ft_calkarea(char **board)
{
	int area; 

	area = 0;
	area = ft_strlen(*board);
	area *= area;
}
*/

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
** Печатает лист все листы использовал для тестов
*/

void	ft_putlst(t_tetr *lst)
{
	t_tetr *iter;

	iter = lst;
	while (iter)
	{
		ft_putchar(iter->ch);
		iter = iter->next;
	}
	ft_putstr("\n");
}

/*
** Ищет лист соответствующий симаволу и возвращает его
*/

t_tetr	*ft_searchlst(t_tetr *lst, char ch)
{
	t_tetr	*iter;

	iter = lst;
	while (iter && iter->ch != ch)
		iter = iter->next;
	return (iter);
}

/*
** Меняет содержимое листов местами.
** Возможно ли не перезаписывать поля листа, а менять указатели?
*/

void	ft_swapvallst(t_tetr *lsta, t_tetr *lstb)
{
	char	c;
	int		i;
	int		temp;

	i = 0;
	c = lsta->ch;
	lsta->ch = lstb->ch;
	lstb->ch = c;
	while (i < 4)
	{
		temp = lsta->tetr_x[i];
		lsta->tetr_x[i] = lstb->tetr_x[i];
		lstb->tetr_x[i] = temp;
		temp = lsta->tetr_y[i];
		lsta->tetr_y[i] = lstb->tetr_y[i];
		lstb->tetr_y[i] = temp;
		i++;
	}
}

/*
** Меняет местами два элемента листа
*/

void	ft_swaplst(t_tetr *lst, char a, char b)
{
	t_tetr	*lsta;
	t_tetr	*lstb;

	lsta = ft_searchlst(lst, a);
	lstb = ft_searchlst(lst, b);
	ft_swapvallst(lsta, lstb);	
}

/*
** Пробегает по списку тетримино и по очереди пытается заполнит тетримино
** на доску.
*/

static void	ft_runlst(char **board, t_tetr *lst)
{
	t_tetr	*iter;
	int		num;

	num = 4;
	iter = lst;
	while (iter)
	{
		if (!ft_infillboard(board, iter))
		{
			ft_delboard(board);
			board = ft_creatboard(++num);
			iter = lst;
			ft_infillboard(board, iter);
		}
		iter = iter->next;
	}
	ft_putboard(board);
	ft_putstr("\n");
	ft_delboard(board);
	//board = ft_creatboard(4);
}	

/*
** Подсчет колличества элементов скиска, для нахождение всех
** вариантов перебора.
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
** Высчитываем начальный размер доски.
*/

static int	ft_startsizeboard(t_tetr *lst)
{
	int	len;
	int	numlst;

	numlst = ft_numberlst(lst);
	len = 2;
	while (len * len < numlst * 4)
		len++;
	return (len);
}

/*
** Backtracing (Рекурися с возвратом) перебор всех вариантов.
*/

static void	ft_allvarlst(t_tetr *lst, int l, int r)
{
	int		i;
	static int		j = 0; //Убрать!
	char	**board;

	board = ft_creatboard(ft_startsizeboard(lst));
	if (l == r)
	{
		ft_putnbr(++j);	//Delete
		ft_putstr("\n");//Delete
		ft_runlst(board, lst);
	}
	else 
	{
		i = l;
		while (i <= r)
		{
			ft_swaplst(lst, 'A' + l, 'A' + i);
			ft_allvarlst(lst, l + 1, r);
			ft_swaplst(lst, 'A' + l, 'A' + i);
			i++;
		}
	}
}

/*
** Вычисление факториала, для нахождения колличества возможных вариантов
** Может и не понадобится 
*/

static int	ft_factorial(int nb)
{
	int i;
	int a;

	i = 1;
	a = 1;
	if (nb == 1)
		return (1);
	else	if (nb <= 0)
		return (0);
	else
		while (i <= nb)
		{
			a = i * a;
			i++;
		}
	return (a);
}


int		main(void)
{
	//char		**board;
	t_tetr		*one; 
	t_tetr		*two;
	t_tetr		*three;
	t_tetr		*four;
	t_tetr		*five;
	//t_tetr		*iter;

	one = (t_tetr *)malloc(sizeof(t_tetr));
	two	= (t_tetr *)malloc(sizeof(t_tetr));
	three = (t_tetr *)malloc(sizeof(t_tetr));
	four = (t_tetr *)malloc(sizeof(t_tetr));
	five = (t_tetr *)malloc(sizeof(t_tetr));
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
	one->next = two;
	two->next = three;
	three->next = four;
	four->next = five;
	five->next = NULL;
	/*ft_swaplst(one, 'A', 'A');
	ft_putlst(one);
	ft_swaplst(one, 'C', 'D');
	ft_putlst(one);
	*/
	ft_allvarlst(one, 0, ft_numberlst(one) - 1);
	return (0);
}

/*
int				main(void)
{
	char		**board;
	int			num;
	t_tetr		*one; 
	t_tetr		*two;
	t_tetr		*three;
	t_tetr		*four;
	//t_tetr		*iter;

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
*/
/*
** Функция меняющая два сосдних элементов списка местами
*/
/*
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
*/
/*
** Функция перебирает все возможные варианты и выподит доску в консоль
*/
/*
static void		ft_allvar(char **board, t_tetr *tetr)
{
	int		num;
	int		i;
	t_tetr	*iter;
	t_tetr	*first;

	num = 4;
	i = 1;
	first = tetr;
	iter = first;
	while (i < 5)
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
		}*/
		/*if (i%2 != 0)
		{
			iter = ft_swichlst(first);
			first = iter;
		} 
		else
		{
			iter = ft_swichlst(first->next);
			first = iter;
		}*/ 
		/*	iter = ft_swichlst(first);
			first = iter;
		num = 4;
		ft_delboard(board);
		board = ft_creatboard(num);
		i++;
	}
}
*/

