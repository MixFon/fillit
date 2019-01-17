/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:41:15 by eskeleto          #+#    #+#             */
/*   Updated: 2019/01/17 15:36:58 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct		s_tetr
{
	int				tetr_x[4];
	int				tetr_y[4];
	struct s_tetr	*next;
	char			ch;
}					t_tetr;

# define BUFF_SIZE 32

t_tetr				*ft_get_list(int fd);
char				*ft_concat_str(char *str1, char *str2);
int					ft_is_valid_chars(char *str);
int					ft_is_valid_contact(char *str);
char				**ft_write_tetrimino(char *str, int len);
char				*ft_read_file(int fd);
int					ft_is_valid_lines(char *str, int *len);
int					ft_check_tetrimino(char **stetr);
t_tetr				*ft_coords_list(int len, char **stetr);

int					ft_numberlst(t_tetr *lst);
void				ft_putboard(char **board);
void				ft_delboard(char **board);
int					ft_startsizeboard(t_tetr *lst);
char				**ft_creatboard(size_t n);
int					ft_recrunlst(char **board, t_tetr *lst);

void				ft_putfinalboard(t_tetr *one);

#endif
