#include "fillit.h"

/*
** Calculatest the namber of list.
*/

int	ft_numberlst(t_tetr *lst)
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
** Check insert tetramino in board.
*/

int		ft_checktrak(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int		i;
	int		sum;

	sum = ft_strlen(*board);
	i = 0;
	if (!tetr)
		return (0);
	while (i < 4)
	{
		if (start_y + tetr->tetr_y[i] >= sum || start_x + tetr->tetr_x[i] >= sum
			|| start_y + tetr->tetr_y[i] < 0 || start_x + tetr->tetr_x[i] < 0)
			return (0);
		if (board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] != '.')
			return (0);
		i++;
	}
	return (1);
}

/*
** Fills the board with tetraminos. (Characters)
*/

void		ft_infilltetr(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] = tetr->ch;
		i++;
	}
}

/*
** Removes tetraminos from the board.
*/

void		ft_deltetr(char **board, int start_x, int start_y, t_tetr *tetr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		board[start_y + tetr->tetr_y[i]][start_x + tetr->tetr_x[i]] = '.';
		i++;
	}
}

/*
** All combinations. (Backtraking).
*/

int	ft_recrunlst(char **board, t_tetr *lst)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	n = ft_strlen(*board);
	if (!lst)
		return (1);
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (ft_checktrak(board, j, i, lst))
			{
				ft_infilltetr(board, j, i, lst);
				if (ft_recrunlst(board, lst->next))
					return (1);
				ft_deltetr(board, j, i, lst);
			}
			j++;
		}
		i++;
	}
	return (0);
}
