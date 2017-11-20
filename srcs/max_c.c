/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:07:49 by anazar            #+#    #+#             */
/*   Updated: 2017/09/07 17:11:24 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_coord	max_c(t_coord p1, t_coord p2)
{
	if (p1.x > p2.x)
		return (p1);
	else
		return (p2);
}
