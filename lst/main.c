/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:48:13 by widraugr          #+#    #+#             */
/*   Updated: 2019/01/09 16:38:52 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "unistd.h"
#include "stdlib.h"

/*
** Печатает лист все листы
*/

static void	ft_putlst(t_tetr *lst)
{
	t_tetr *iter;

	iter = lst;
	while (iter)
	{
		write(1, &iter->ch, 1);
		iter = iter->next;
	}
	write(1, "\n", 1);
}

/*
** Ищет лист соответствующий симаволу и возвращает его
*/

static t_tetr	*ft_searchlst(t_tetr *lst, char ch)
{
	t_tetr	*iter;

	iter = lst;
	while (iter && iter->ch != ch)
		iter = iter->next;
	return (iter);
}

/*
** Меняет содержимое листов местами
*/

static void	ft_swapvallst(t_tetr *lsta, t_tetr *lstb)
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
		lstb->tetr_x[i] = lsta->tetr_x[i];
		lsta->tetr_x[i] = temp;
		temp = lsta->tetr_y[i];
		lstb->tetr_y[i] = lsta->tetr_y[i];
		lsta->tetr_y[i] = temp;
		i++;
	}
}

/*
** Меняет местами два элемента листа местами
*/

static void	ft_swaplst(t_tetr *lst, char a, char b)
{
	t_tetr	*lsta;
	t_tetr	*lstb;

	lsta = ft_searchlst(lst, a);
	lstb = ft_searchlst(lst, b);
	ft_swapvallst(lsta, lstb);	
}

/*
** Меняет местами два элемента листа местами
*/

static void	ft_allvarlst(t_tetr *lst, int l, int r)
{
	int	i;

	if (l == r)
		ft_putlst(lst);
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

int		main(void)
{
	t_tetr		*one; 
	t_tetr		*two;
	t_tetr		*three;
	t_tetr		*four;
	//t_tetr		*iter;

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
	three->next = four;
	four->next = NULL;
	/*ft_swaplst(one, 'A', 'A');
	ft_putlst(one);
	ft_swaplst(one, 'C', 'D');
	ft_putlst(one);
	*/
	ft_allvarlst(one, 0, 3);
	return (0);
}
