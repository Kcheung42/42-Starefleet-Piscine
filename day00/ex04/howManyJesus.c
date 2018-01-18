/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   howManyJesus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 22:48:42 by kcheung           #+#    #+#             */
/*   Updated: 2017/08/20 14:39:44 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define d  256

int howManyJesus(char *book, char *jesus)
{
	int m = strlen(jesus);
	int n = strlen(book);
	int h1 = 0; // hash value for pat
	int h2 = 0; // hash value for txt
	int	power = 1;// prime base to highest power
	int	count = 0;
	int i,j;
	int	q = 101;

	/* calc. highest power of base  */
	for (i = 0; i < m - 1; i++)
		power = (power * d) % q;

	/* calc. the hash value of the first window and pattern */
	for (i = 0; i < m; i++)
	{
		h1 = (d * h1 + jesus[i]) % q;
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
				if (book[i + j] != jesus[j])
					break;
			}
			/* if jesus matches book j length of jesus */
			if (j == m)
				count++;
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
	return (count);
}
