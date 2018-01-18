/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 22:42:21 by kcheung           #+#    #+#             */
/*   Updated: 2017/08/01 23:36:36 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <cstring.h>

char *decompress(char *eBook)
{
	struct s_list	*table;
	int				table_len = 1;
	int	i = 1;
	int	start = 1;

	while (eBook[i] != '>')
	{
		if (eBook[i] == ',')
		{
			strncopy(eBook, start, i - 1);
			start = i;
			table_len++;
		}
		i++;
	}
	if(!(table = (struct s_list *)malloc(sizeof(*table))))
		return (NULL);
	if(!(table->elems = (struct s_elem **)malloc(sizeof(struct s_elem) * table_len)))
		return (NULL);
}

struct s_string *stringInit(void)
{
	struct s_string	*str;

	str = (struct s_string *)malloc(sizeof(*str));
	return (str);
}

int	stringAppend(struct s_string *s, char *add)
{
	int ret = 0;
	int	newlen = 0;
	
	newlen = s->length + strlen(add);

	s->content = realloc(s->content, newlen);
	s->length = newlen;
	strcat(s->content, add);
	return (ret);
}	//return 0 = FAIL, 1 = SUCCESS
