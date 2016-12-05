/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 15:27:58 by mlegendr          #+#    #+#             */
/*   Updated: 2016/06/02 15:39:31 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static t_pixel_8u	average_color(t_pixel_8u col1, t_pixel_8u col2, double aa)
{
	t_pixel_8u	new_pix;

	new_pix.red = (unsigned char)((double)col1.red *
			aa + (double)col2.red * (1 - aa));
	new_pix.blue = (unsigned char)((double)col1.blue *
			aa + (double)col2.blue * (1 - aa));
	new_pix.green = (unsigned char)((double)col1.green *
			aa + (double)col2.green * (1 - aa));
	return (new_pix);
}

static void			norme2(t_draw_col_struct s, t_env env, int i)
{
	if (s.j <= s.end + s.jump)
	{
		s.text_y = (s.j - s.start - s.jump) / s.dist * s.image->height;
		pixel_8u(env.aliased_img, i, s.j, get_pixel_8u(s.image, s.text_x,
			s.text_y));
	}
	else if (s.j < s.end + s.jump + 1 && env.aa)
	{
		pixel_8u(env.aliased_img, i, s.j, average_color(
			get_pixel_8u(s.image, s.text_x, s.image->height - 1),
			new_pixel_8u(139, 136, 120, 0), s.aa));
	}
	else
		pixel_8u(env.aliased_img, i, s.j, new_pixel_8u(139, 136, 120, 0));
}

static void			norme1(t_draw_col_struct s, t_env env, int i, t_inter inter)
{
	if (inter.from == kTop || inter.from == kBot)
		s.text_x = fmod(inter.x, 1.0f) * (double)s.image->width;
	else
		s.text_x = fmod(inter.y, 1.0f) * (double)s.image->width;
	if (s.j < s.start + s.jump)
	{
		s.text_x = fmod(s.angle, M_PI * 2.0f / 2.0f) / (M_PI * 2.0f / 2.0f)
					* env.skybox->width;
		s.text_y = (double)s.j * 2 / (double)env.win_height * ((double)
			env.skybox->height / 3.0f) + ((double)env.skybox->height / 3.0f);
		pixel_8u(env.aliased_img, i, s.j,
					get_pixel_8u(env.skybox, s.text_x, s.text_y));
	}
	else if (s.j < s.start + s.jump + 1 && env.aa)
	{
		pixel_8u(env.aliased_img, i, s.j, average_color(get_pixel_8u(s.image,
				s.text_x, 0), get_pixel_8u(env.skybox, fmod(s.angle, M_PI *
					2.0f / 2.0f) / (M_PI * 2.0f / 2.0f) * env.skybox->width,
				(double)s.j * 2 / (double)env.win_height *
				((double)env.skybox->height / 3.0f) +
				((double)env.skybox->height / 3.0f)), s.aa));
	}
	else
		norme2(s, env, i);
}

static void			draw_col(t_draw_col_struct s, t_env env, int i,
								t_inter inter)
{
	s.j = -1;
	s.jump = env.player.jump_alt * (s.dist / 1500.0);
	s.half = s.dist / 2.0f;
	s.start = env.aliased_img->height / 2.0f - s.half;
	s.end = env.aliased_img->height / 2.0f + s.half;
	s.aa = s.half - floor(s.half);
	if (inter.from == kTop)
		s.image = inter.wall.textures.top;
	else if (inter.from == kBot)
		s.image = inter.wall.textures.bot;
	else if (inter.from == kLeft)
		s.image = inter.wall.textures.left;
	else
		s.image = inter.wall.textures.right;
	while (++s.j < env.aliased_img->height)
	{
		norme1(s, env, i, inter);
	}
}

void				raycast(t_env env)
{
	int					i;
	double				angle;
	t_inter				inter;
	t_draw_col_struct	s;

	i = -1;
	while (++i < env.aliased_img->width)
	{
		angle = fmod(env.player.angle - env.player.fov / 2.0f +
			((double)i / (double)env.aliased_img->width) *
			env.player.fov + 2 * M_PI, 2 * M_PI);
		inter = greater(angle, env.player, env.info);
		s.dist = 3.0f / inter.dist * 277.0f;
		s.angle = angle;
		draw_col(s, env, i, inter);
	}
}
