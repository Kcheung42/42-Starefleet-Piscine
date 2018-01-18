/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchPriceV3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:56:27 by kcheung           #+#    #+#             */
/*   Updated: 2017/07/31 22:14:30 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

size_t hash(char *input)
{
	unsigned long int	hashval;
	int					i;

	hashval = 0;
	while ((i = *input++))
		hashval = i + (hashval << 6) + (hashval << 16) - hashval;
	return (hashval);
}	//return hash result

struct s_dict *dictInit(int capacity)
{
	struct s_dict *hash_table;

	if (capacity < 1)
		return (NULL);

	/* allocate memory for the table */
	if (!(hash_table = (struct s_dict*)malloc(sizeof(struct s_dict))))
		return (NULL);

	/* allocate memory for all head nodes */
	if (!(hash_table->items = (struct s_item **)malloc(sizeof(struct s_item *) * capacity)))
		return (NULL);

	/* set head nodes to null */
	for (int i = 0; i < capacity; i++) {
		hash_table->items[i] = NULL;
	}
	hash_table->capacity = capacity;
	return (hash_table);

} //initialize the dictionnary, given as parameter the capacity of the array.

struct s_item	*create_pair(char *key, struct s_art *value)
{
	struct s_item	*entry;

	/* allocate memmory for s_item (bin) */
	if (!(entry = (struct s_item *)malloc(sizeof(*entry))))
		return (NULL);

	/* allocate memory for s_art (artpiece)  */
	if (!(entry->value = (struct s_art *)malloc(sizeof(struct s_art))))
		return (NULL);
	entry->key = strdup(key);
	entry->value = value;
	entry->next = NULL;
	return (entry);
}

int	dictInsert(struct s_dict *dict, char *key, struct s_art *value)
{
	int		bin;
	int		ret;
	struct s_item	*new_entry;
	struct s_item	*cur;
	struct s_item	*prev;

	ret = 0;
	bin = hash(key) % dict->capacity;
	cur = dict->items[bin];

	/* Go to end of list or until key already exists*/
	while (cur != NULL && strcmp(key, cur->key) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	/* Theres Already a pair! */
	if (cur != NULL && !strcmp(key, cur->key))
		return (ret);
	/* Nope couldnt find it, Entering */
	else
	{
		/* create new entry */
		new_entry = create_pair(key, value);
		/* case head of list */
		if (cur == dict->items[bin])
		{
			dict->items[bin] = new_entry;
			new_entry->next = cur;
		}
		/* case end of list */
		else if (cur == NULL)
			prev->next = new_entry;

		/* case mid of list */
		else
		{
			new_entry->next = cur;
			prev->next = new_entry;
		}
	}
	ret = 1;
	return (ret);

}	//add one element in the dictionnary, if FAIL return 0, otherwise 1

struct s_art *dictSearch(struct s_dict *dict, char *key)
{
	int		bin;
	struct s_item	*cur;

	bin =  hash(key) % dict->capacity;
	cur = dict->items[bin];

	while (cur != NULL && strcmp(key, cur->key))
		cur = cur->next;
	if (cur == NULL || strcmp(key, cur->key))
		return (NULL);
	return (cur->value);


}	//find one element in the dictionnary, if not found, return NULL

int searchPrice(struct s_dict *dict, char *name)
{
	int				price;
	struct	s_art	*target;
	target = dictSearch(dict, name);

	if (target)
	{
		price = target->price;
		return (price);
	}
	else
		return (-1);

}
