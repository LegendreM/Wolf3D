/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:52:11 by mlegendr          #+#    #+#             */
/*   Updated: 2014/12/08 16:59:52 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

static t_roi	sub_left(t_inter left, t_inter right,
	t_mlx_image_8u *image)
{
	t_roi	roi;

	if (left.from == kBot)
	{
		roi.width = fabs(right.x - left.x) * image->width;
		roi.x = (double)(fmod(right.x, 1)) * (double)image->width;
	}
	else if (left.from == kTop)
	{
		roi.width = fabs(right.x - left.x) * image->width;
		roi.x = fmod(left.x, 1) * image->width;
	}
	else if (left.from == kLeft)
	{
		roi.width = fabs(right.y - left.y) * image->width;
		roi.x = fmod(right.y, 1) * image->width;
	}
	else
	{
		roi.width = fabs(right.y - left.y) * image->width;
		roi.x = fmod(left.y, 1) * image->width;
	}
	return (roi);
}

static void		tag_left(t_inter left, t_inter right, t_env *env)
{
	t_roi			roi;
	t_mlx_image_8u	*image;

	if (left.from == kBot)
		image = right.wall.textures.bot;
	else if (left.from == kTop)
		image = left.wall.textures.top;
	else if (left.from == kLeft)
		image = right.wall.textures.left;
	else
		image = left.wall.textures.right;
	roi = sub_left(left, right, image);
	roi.height = (double)roi.width / (double)env->tag->width *
	(double)env->tag->height;
	roi.y = (-roi.height + image->height) / 2;
	put_tag(env->tag, image, roi, env->tag_color);
}

static t_roi	sub_right(t_inter left, t_inter right,
	t_mlx_image_8u *image)
{
	t_roi			roi;

	if (right.from == kBot)
	{
		roi.width = fabs(left.x - right.x) * image->width;
		roi.x = (double)(fmod(left.x, 1)) * (double)image->width - roi.width;
	}
	else if (right.from == kTop)
	{
		roi.width = fabs(left.x - right.x) * image->width;
		roi.x = fmod(right.x, 1) * image->width - roi.width;
	}
	else if (right.from == kLeft)
	{
		roi.width = fabs(left.y - right.y) * image->width;
		roi.x = fmod(left.y, 1) * image->width - roi.width;
	}
	else
	{
		roi.width = fabs(left.y - right.y) * image->width;
		roi.x = fmod(right.y, 1) * image->width - roi.width;
	}
	return (roi);
}

static void		tag_right(t_inter left, t_inter right, t_env *env)
{
	t_roi			roi;
	t_mlx_image_8u	*image;

	if (right.from == kBot)
		image = left.wall.textures.bot;
	else if (right.from == kTop)
		image = right.wall.textures.top;
	else if (right.from == kLeft)
		image = left.wall.textures.left;
	else
		image = right.wall.textures.right;
	roi = sub_right(left, right, image);
	roi.height = (double)roi.width / (double)env->tag->width *
	(double)env->tag->height;
	roi.y = (-roi.height + image->height) / 2;
	put_tag(env->tag, image, roi, env->tag_color);
}

void			tag(t_env *env)
{
	t_inter			left;
	t_inter			right;

	left = greater(env->player.angle, env->player, env->info);
	if (left.dist > DIST_MAX_TAG)
		return ;
	left = greater(fmod(env->player.angle + M_PI / 18, M_PI * 2),
		env->player, env->info);
	right = greater(fmod(env->player.angle + 35 * M_PI / 18, M_PI * 2),
		env->player, env->info);
	tag_left(left, right, env);
	tag_right(left, right, env);
}
