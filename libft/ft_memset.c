/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 11:58:12 by mlegendr          #+#    #+#             */
/*   Updated: 2014/11/10 16:14:55 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char *charac;

	charac = s;
	while (len--)
	{
		*(charac++) = (unsigned char)c;
	}
	return (s);
}
