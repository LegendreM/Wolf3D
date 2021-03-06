/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:18:46 by mlegendr          #+#    #+#             */
/*   Updated: 2014/11/12 15:59:16 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_bzero(void *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}
