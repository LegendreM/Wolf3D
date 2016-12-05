/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tag.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_tag(t_mlx_image_8u *input, t_mlx_image_8u *output, t_roi roi,
	t_pixel_8u color)
{
	int			x;
	int			y;
	t_pixel_8u	px;

	y = roi.y;
	while (y < roi.height + roi.y)
	{
		x = roi.x;
		while (x < roi.width + roi.x)
		{
			if (x >= 0 && y >= 0 && x < output->width && y < output->height)
			{
				px = get_pixel_8u(input, (double)(x - roi.x) /
					(double)roi.width * (double)input->width,
					(double)(y - roi.y) /
					(double)roi.height * (double)input->height);
				if (px.alpha != 255)
					pixel_8u(output, x, y, color);
			}
			++x;
		}
		++y;
	}
}
