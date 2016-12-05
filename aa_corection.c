/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_corection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxlibft.h"

static char			average_sample(char c1, char c2, char c3, char c4)
{
	int color;

	color = c1 + c2 + c3 + c4;
	color /= 4;
	return ((char)color);
}

static t_pixel_8u	average_color(t_pixel_8u c1, t_pixel_8u c2, t_pixel_8u c3,
								t_pixel_8u c4)
{
	t_pixel_8u	ret;

	ret.red = average_sample(c1.red, c2.red, c3.red, c4.red);
	ret.green = average_sample(c1.green, c2.green, c3.green, c4.green);
	ret.blue = average_sample(c1.blue, c2.blue, c3.blue, c4.blue);
	ret.alpha = average_sample(c1.alpha, c2.alpha, c3.alpha, c4.alpha);
	return (ret);
}

void				aa_corection(t_mlx_image_8u *img1, t_mlx_image_8u *img2)
{
	int		i;
	int		j;

	i = 0;
	while (i < img1->height)
	{
		j = 0;
		while (j < img1->width)
		{
			pixel_8u(img2, j / 2, i / 2, average_color(
				get_pixel_8u(img1, j, i),
				get_pixel_8u(img1, j, i + 1),
				get_pixel_8u(img1, j + 1, i),
				get_pixel_8u(img1, j + 1, i + 1)));
			j += 2;
		}
		i += 2;
	}
}
