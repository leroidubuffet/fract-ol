/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:55:42 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:47:47 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_keyboard_update(int keycode, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	fractal->range_r = fractal->min_r - fractal->max_r;
	fractal->range_i = fractal->max_i - fractal->min_i;
	if (keycode == KEY_ESC)
	{
		ft_print_bye();
		ft_exit(fractal);
		return (0);
	}
	if (keycode == KEY_Z || keycode == KEY_X)
		ft_zoom(keycode, fractal, WIDTH / 2, HEIGHT / 2);
	if ((keycode >= KEY_LEFT && keycode <= KEY_DOWN) || (keycode >= KEY_ONE \
	&& keycode <= KEY_SIX) || (keycode >= KEY_Q && keycode <= KEY_R))
		ft_key_control(keycode, fractal);
	mlx_clear_window(fractal->mlx, fractal->win);
	ft_draw_fractal(fractal);
	return (0);
}

int	ft_mouse_update(int buttoncode, int x, int y, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	fractal->range_r = fractal->min_r - fractal->max_r;
	fractal->range_i = fractal->max_i - fractal->min_i;
	if (buttoncode == MOUSE_WHEEL_DOWN)
		ft_zoom(4, fractal, x, y);
	if (buttoncode == MOUSE_WHEEL_UP)
		ft_zoom(5, fractal, x, y);
	if (buttoncode == MOUSE_LEFT_CLICK)
		ft_mouse_control(fractal, x, y);
	mlx_clear_window(fractal->mlx, fractal->win);
	ft_draw_fractal(fractal);
	return (0);
}

static void	ft_fractal_init(t_fractol *fractal)
{
	fractal->min_r = -2.0;
	fractal->max_r = 1.0;
	fractal->min_i = -1.5;
	fractal->max_i = fractal->min_i + (fractal->max_r - fractal->min_r)
		* HEIGHT / WIDTH;
	fractal->zoom = 1;
	fractal->distance = 0.05;
	fractal->max_iterations = 80;
	fractal->mlx = mlx_init();
	fractal->r_factor = 0;
	fractal->g_factor = 0;
	fractal->b_factor = 0;
	if (!fractal->mlx)
		exit(1);
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "Fract'olio");
	if (!fractal->win)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_fractol	fractal;
	t_img		imgs;

	if (argc < 2)
	{
		ft_putstr("Please specify the set you want to open.\n");
		ft_print_sets();
		return (1);
	}
	if (ft_check_args(argv, argc, &fractal))
		return (1);
	ft_fractal_init(&fractal);
	ft_img_init(&imgs, &fractal);
	ft_keyboard_update(0, &fractal);
	ft_print_instructions(&fractal);
	mlx_hook(fractal.win, 04, 1L << 2, ft_mouse_update, &fractal);
	mlx_hook(fractal.win, 02, 1L << 0, ft_keyboard_update, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
