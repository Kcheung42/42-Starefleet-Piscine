/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPriceV2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 13:16:14 by kcheung           #+#    #+#             */
/*   Updated: 2017/07/31 13:46:17 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <string.h>

int	len(struct s_art **arts)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (arts[i])
	{
		len += 1;
		i++;
	}
	return (len);

}
int searchPrice(struct s_art **arts, int n, char *name)
{
	//binary
	int	result;
	int	mid;
	int	start;
	int	end;

	start = 0;
	end = n - 1;
	mid = (start + end) / 2;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (!strcmp(arts[mid]->name, name))
			return (arts[mid]->price);
		else if (strcmp(arts[mid]->name, name) > 0)
			end = mid - 1;
		else
			start = mid + 1;
	}
	result = -1;
	return (result);
}
