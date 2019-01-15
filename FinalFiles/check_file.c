/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 12:57:08 by eskeleto          #+#    #+#             */
/*   Updated: 2019/01/14 11:20:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char		**ft_write_tetrimino(char *str, int len)
{
	char	**tetriminos;
	int		i;
	int		count;
	int		j;

	if (!(tetriminos = (char **)malloc(sizeof(char *) * (len + 1))))
		return (0);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		j = 0;
		tetriminos[count] = (char *)malloc(sizeof(char) * 21);
		while (i % 21 != 20)
		{
			tetriminos[count][j++] = str[i++];
		}
		tetriminos[count][j] = '\0';
		if (str[i] != '\0')
			i++;
		count++;
	}
	tetriminos[count] = NULL;
	return (tetriminos);
}

char		*ft_read_file(int fd)
{
	char	*strfile;
	char	*buf;
	int		ret;

	strfile = (char*)malloc(sizeof(char));
	strfile[0] = '\0';
	buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		strfile = ft_concat_str(strfile, buf);
	}
	free(buf);
	return (strfile);
}

static int	ft_chars_in_line(char *str, int *i)
{
	int		chars_in_line;

	chars_in_line = 0;
	while (str[*i] != '\n')
	{
		if (str[*i] == '\0')
			return (0);
		chars_in_line++;
		(*i)++;
	}
	return (chars_in_line);
}

int			ft_is_valid_lines(char *str, int *len)
{
	int		lines;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		lines = 0;
		while (lines < 4)
		{
			if (ft_chars_in_line(str, &i) != 4)
				return (0);
			i++;
			lines++;
		}
		if (!(str[i] == '\0' ||
				(str[i] == '\n' && (str[i + 1] == '.' || str[i + 1] == '#'))))
			return (0);
		if (str[i] != '\0')
			i++;
		(*len)++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int			ft_check_tetrimino(char **stetr)
{
	int		i;

	i = 0;
	while (stetr[i] != NULL)
	{
		if (!ft_is_valid_chars(stetr[i]) || !ft_is_valid_contact(stetr[i]))
			return (0);
		i++;
	}
	return (1);
}
