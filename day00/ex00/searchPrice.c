/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPrice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 10:09:16 by kcheung           #+#    #+#             */
/*   Updated: 2017/07/31 10:26:05 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <string.h>

int searchPrice(struct s_art **arts, char *name)
{
	int	result;
	int	i;

	result = -1;
	i = 0;
	while (arts[i])
	{
		if (!strcmp(arts[i]->name, name))
		{
			return (arts[i]->price);
		}
		i++;
	}
	return (result);
}
