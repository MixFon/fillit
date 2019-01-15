/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:03:38 by eskeleto          #+#    #+#             */
/*   Updated: 2019/01/11 14:48:01 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_delmas(char **mas)
{
	while (*mas)
	{
		ft_strdel(mas);
		mas++;
	}
	mas = NULL;
}

static void	ft_dellist(t_tetr **alst)
{
	t_tetr	*list;
	t_tetr	*nextlist;

	if (alst == NULL)
		return;
	list = *alst;
	while (list != NULL)
	{
		nextlist = list->next;
		free(list);
		list = nextlist;
	}
	*alst = NULL;
}

t_tetr	*ft_get_list(int fd)
{
	char	*strfile;
	char	**stetr;
	int		len;
	t_tetr	*list;

	len = 0;
	strfile = ft_read_file(fd);
	if (!ft_is_valid_lines(strfile, &len) || len > 26)
	{
		ft_putendl("error");
		exit(-1);
	}
	stetr = ft_write_tetrimino(strfile, len);
    free(strfile);
	if (!ft_check_tetrimino(stetr))
	{
		ft_putendl("error");
		exit(-1);
	}
	list = ft_coords_list(len, stetr);
    ft_delmas(stetr);
	free(stetr);
	return (list);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_tetr	*one;

	if (argc != 2)
	{
		ft_putendl("usage ./fillit file");
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("error");
		return (-1);
	}
	one = ft_get_list(fd);
	ft_putfinalboard(one);
	//Здесь часть твоего кода - видимо надо создать для него отдельную функцию
	/*char	**board;
	int sum = ft_startsizeboard(one);

	board = ft_creatboard(sum);
	while (!ft_recrunlst(board, one))
	{
		ft_delboard(board);
		board = ft_creatboard(++sum);
	}
	ft_putboard(board);
	*/

	ft_dellist(&one);
	if (close(fd) == -1)
	{
		ft_putendl("error");
		return (-1);
	}
	return (0);
}
