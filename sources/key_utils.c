/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:34:09 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:24:46 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_key_control(int keycode, t_fractol *f)
{
	ft_key_control_color(keycode, f);
	ft_key_control_julia(keycode, f);
	ft_key_control_move(keycode, f);
}

void	ft_key_control_move(int keycode, t_fractol *f)
{
	if (keycode == 124)
	{
		f->min_r -= f->range_r * f->distance;
		f->max_r -= f->range_r * f->distance;
	}
	if (keycode == 123)
	{
		f->min_r += f->range_r * f->distance;
		f->max_r += f->range_r * f->distance;
	}
	if (keycode == 126)
	{
		f->min_i -= f->range_i * f->distance;
		f->max_i -= f->range_i * f->distance;
	}
	if (keycode == 125)
	{
		f->min_i += f->range_i * f->distance;
		f->max_i += f->range_i * f->distance;
	}
}

void	ft_key_control_julia(int keycode, t_fractol *f)
{
	if (keycode == KEY_Q)
		f->kr += 0.005;
	if (keycode == KEY_W)
		f->kr -= 0.005;
	if (keycode == KEY_E)
		f->ki += 0.005;
	if (keycode == KEY_R)
		f->ki -= 0.005;
}

void	ft_key_control_color(int keycode, t_fractol *f)
{
	if (keycode == KEY_ONE)
		f->r_factor += 5;
	if (keycode == KEY_TWO)
		f->r_factor -= 5;
	if (keycode == KEY_THREE)
		f->g_factor += 5;
	if (keycode == KEY_FOUR)
		f->g_factor -= 5;
	if (keycode == KEY_FIVE)
		f->b_factor += 5;
	if (keycode == KEY_SIX)
		f->b_factor -= 5;
}
