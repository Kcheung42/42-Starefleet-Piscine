/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 09:23:19 by kcheung           #+#    #+#             */
/*   Updated: 2017/08/20 13:31:12 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "header.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define d  256

/* return hash reult */
size_t hash(char *input)
{
	unsigned long int	hashval;
	int i;

	hashval = 0;
	while ((i = *input++))
		hashval = i + (hashval << 6) + (hashval << 16) - hashval;
	return (hashval);

}	//return hash result

/* intialize table */
struct s_dict *dictInit(int capacity)
{
	struct s_dict *new_dict;

	if (capacity < 1)
		return (NULL);
	if(!(new_dict = (struct s_dict *)malloc(sizeof(struct s_dict *))))
		return (NULL);
	if(!( new_dict->items = (struct s_item **)malloc(sizeof(struct s_item *) * capacity)))
		return (NULL);

	for (int i = 0; i < capacity; i++)
	{
		new_dict->items[i] = NULL;
	}
	new_dict->capacity = capacity;
	return (new_dict);


} //initialize the dictionnary, given as parameter the capacity of the array.

/* create entry */
struct s_item	*create_pair(char *key, int val)
{
	struct s_item	*entry;

	/* allocate memmory for s_item (bin) */
	if (!(entry = (struct s_item *)malloc(sizeof(*entry))))
		return (NULL);

	entry->key = strdup(key);
	entry->value = val;
	entry->next = NULL;
	return (entry);
}

/* insert entry */
int	dictInsert(struct s_dict *dict, char *key, int value)
{
	int		bin;
	int		ret;
	struct s_item	*new_entry;
	struct s_item	*cur;
	struct s_item	*prev;

	ret = 0;
	bin = hash(key) % dict->capacity;
	if (bin == '@')
		bin += 1;
	cur = dict->items[bin];

	/* Go to end of list or until key already exists*/
	while (cur != NULL && strcmp(key, cur->key) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	/* Theres Already a pair! */
	if (cur != NULL && !strcmp(key, cur->key))
	{
		return (ret);
	}
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

/* search for entry */
int dictSearch(struct s_dict *dict, char *key)
{
	int		bin;
	struct s_item	*cur;

	bin =  hash(key) % dict->capacity;
	cur = dict->items[bin];

	while (cur != NULL && strcmp(key, cur->key))
		cur = cur->next;
	if (cur == NULL || strcmp(key, cur->key))
		return (-1);
	return (cur->value);


}	//find one element in the dictionnary, if not found, return NULL

int search_replace(char *book, struct s_item *word, int index)
{
	char *pattern = word->key;
	int m = strlen(pattern);
	int n = strlen(book);
	int h1 = 0; // hash value for pat
	int h2 = 0; // hash value for txt
	int	power = 1;// prime base to highest power
	int	count = 0;
	int i,j;
	int	q = 101;
	char	c;

	c = index;
	/* calc. highest power of base  */
	for (i = 0; i < m - 1; i++)
		power = (power * d) % q;

	/* calc. the hash value of the first window and pattern */
	for (i = 0; i < m; i++)
	{
		h1 = (d * h1 + pattern[i]) % q;
		h2 = (d * h2 + book[i]) % q;
	}

	/* Shiftrthe window over text one char at a time */
	for (i = 0; i <= n - m; i++)
	{
		/* Check hash value of current window of text and pattern. */
		/* If the hash values match then only check for characters */
		/* one by one */
		if (h1 == h2)
		{
			/* double check each char one by one. */
			for (j = 0; j < m; j++)
			{
				if (book[i + j] != pattern[j])
					break;
			}
			/* if pattern matches book j length of pattern */
			if (j == m)
			{
				for (j = 0; j < m - 1; j++)
					book[i + j] = '@';
				book[i + j] = c + 1;
				/* replace pattern with @@@ and hash index */
				count++;
			}
		}
		/* calc. hash value for next window of text: */
		/* Remove leading letter's hash, add trailing letter's hash */
		if (i < n-m)
		{
			h2 = (d * (h2 - book[i] * power) + book[i + m]) % q;
			if (h2 < 0)
				h2 = h2 + q;
		}
	}
	(void)index;
	return (count);
}

/* Copy book to new book with compressed code */
char	*copy(char *book)
{
	char	*dup_book;
	char	*iter;

	dup_book = (char *)malloc(sizeof(char) * strlen(book));
	iter = dup_book;
	while (*book)
	{
		if (*book == '@')
		{
			*iter = '@';
			iter++;
			while (*book ==  '@')
				book++;
		}
		*iter = *book;
		iter++;
		book++;
	}
	return (dup_book);
}

/* Compress */
char *compress(char *book, struct s_dict *dict)
{
	int i = 0;
	struct s_item *iter;
	char	*output;

	printf("<");
	while (i < dict->capacity)
	{
		iter = dict->items[i];
		while (iter != NULL)
		{
			printf("%s", iter->key);
			if (i == dict->capacity-1 && iter->next == NULL)
				;
			else
				printf(",");
			search_replace(book, iter, i);
			iter = iter->next;
		}
		i++;
	}
	printf(">");

	output = copy(book);
	printf("%s", output);
	(void) book;
	(void) dict;
	return (NULL);
}
