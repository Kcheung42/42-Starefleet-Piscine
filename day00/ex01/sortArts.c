/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortArts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 10:51:08 by kcheung           #+#    #+#             */
/*   Updated: 2017/07/31 14:11:11 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <string.h>
#include <stdio.h>

void	swap(struct s_art **a, struct s_art **b)
{
	struct s_art	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(struct s_art **arts)
{
	int i;
	int j;

	i = 0;
	while (i < 94871 - 1)
	{
		j = 0;
		while (j < 94871 - 2)
		{
			if (strcmp(arts[j]->name, arts[j + 1]->name) > 0)
			{
				swap(&arts[j], &arts[j + 1]);
			}
			j++;
		}
		i++;
	}
}

int partition(struct s_art **arts, int start, int end)
{
	char	*pivot_val;
	int		p_index;
	int		i;

	pivot_val = arts[end]->name;
	p_index = start;
	i = start;
	while (i < end)
	{
		if (strcmp(arts[i]->name, pivot_val) < 0)
		{
			swap(&arts[i], &arts[p_index]);
			p_index++;
		}
		i++;
	}
	swap(&arts[p_index], &arts[end]);
	return (p_index);

}

void	quick_sort(struct s_art **arts, int start, int end)
{
	int p_index;

	if (start < end)
	{
		p_index = partition(arts, start, end);
		quick_sort(arts, start, p_index - 1);
		quick_sort(arts, p_index + 1, end);
	}
}

void  sortArts(struct s_art **arts)
{
	/* bubble_sort(arts); */
	quick_sort(arts, 0, 94871 - 1);
}
