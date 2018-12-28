/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:47:16 by widraugr          #+#    #+#             */
/*   Updated: 2018/12/28 13:39:32 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str_cop;

	i = 0;
	while (s1[i])
		i++;
	if (!(str_cop = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		str_cop[i] = s1[i];
		i++;
	}
	str_cop[i] = '\0';
	return (str_cop);
}
