/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:01:33 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:46 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_zoom_update_min_max(t_fractol *f, long double zoom)
{
		f->zoom = zoom;
		f->max_r = f->max_r + (f->range_r - f->zoom * f->range_r) / 2;
		f->min_r = f->max_r + f->zoom * f->range_r;
		f->min_i = f->min_i + (f->range_i - f->zoom * f->range_i) / 2;
		f->max_i = f->min_i + f->zoom * f->range_i;
}

void	ft_mouse_control(t_fractol *f, int x, int y)
{
	float	x_dis;
	float	y_dis;

	x_dis = -(x - WIDTH / 2) * f->range_r / WIDTH;
	y_dis = (y - HEIGHT / 2) * f->range_i / WIDTH;
	f->min_r += f->range_r * f->distance + x_dis;
	f->max_r += f->range_r * f->distance + x_dis;
	f->min_i += f->range_i * f->distance + y_dis;
	f->max_i += f->range_i * f->distance + y_dis;
}

void	ft_draw_fractal(t_fractol *f)
{
	long double	pr;
	long double	pi;

	f->y = -1;
	while (++f->y < HEIGHT)
	{
		f->x = -1;
		while (++f->x < WIDTH)
		{
			pr = f->min_r + f->x * (f->max_r - f->min_r) / WIDTH;
			pi = f->min_i + f->y * (f->max_i - f->min_i) / HEIGHT;
			if (f->set == MANDELBROT)
				ft_mandelbrot(f, pr, pi);
			if (f->set == JULIA)
				ft_julia(f, pr, pi);
			if (f->set == BURNING)
				ft_burning_ship(f, pr, pi);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img_data->img, 0, 0);
}

void	ft_zoom(int keycode, t_fractol *f, int x, int y)
{
	if (keycode == MOUSE_WHEEL_UP || keycode == MOUSE_WHEEL_DOWN)
	{
		ft_mouse_control(f, x, y);
	}
	if (keycode == KEY_X || keycode == MOUSE_WHEEL_UP)
	{
		f->max_iterations = f->max_iterations + 10;
		ft_zoom_update_min_max(f, 0.5);
	}
	if (keycode == KEY_Z || keycode == MOUSE_WHEEL_DOWN)
	{
		f->max_iterations = f->max_iterations - 10;
		ft_zoom_update_min_max(f, 2);
	}
}
