/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:54:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/01/09 16:38:54 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLiT_H
#define FILLiT_H

typedef struct			s_tetr
{
	int					tetr_x[4];
	int					tetr_y[4];
	struct s_tetr		*next;
	char				ch;
}						t_tetr;

#endif
