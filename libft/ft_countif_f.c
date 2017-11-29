/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countif_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 13:27:12 by anazar            #+#    #+#             */
/*   Updated: 2017/11/27 22:15:03 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_countif_f(char *str, int (*f)(char))
{
	int	count;

	count = 0;
	while (*str)
	{
		while (f(*str))
			++str;
		if (!f(*str) && *str)
		{
			++count;
			while (!f(*str) && *str)
				++str;
		}
	}
	return (count);
}
