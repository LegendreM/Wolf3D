/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 13:34:08 by mlegendr          #+#    #+#             */
/*   Updated: 2014/11/13 17:33:31 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*ret;
	unsigned int	i;

	if (f == NULL)
		return (NULL);
	ret = (char *)malloc(sizeof(ret) * ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = f(s[i]);
	ret[i] = '\0';
	return (ret);
}
