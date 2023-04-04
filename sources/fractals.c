/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:15:31 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:24:31 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_julia(t_fractol *f, long double pr, long double pi)
{
	long double		tmp;
	int				is_in_set;

	f->n = -1;
	is_in_set = 1;
	while (++f->n < f->max_iterations)
	{
		if ((ft_check_imgsquare(pr, pi)) > 4.0)
		{
			is_in_set = 0;
			break ;
		}
		tmp = 2 * pr * pi + f->ki;
		pr = pr * pr - pi * pi + f->kr;
		pi = tmp;
	}
	f->n *= 10;
	ft_put_pixel(f, is_in_set);
}

void	ft_mandelbrot(t_fractol *f, long double pr, long double pi)
{
	long double		zr;
	long double		zi;
	int				is_in_set;
	long double		tmp;

	zr = 0;
	zi = 0;
	f->n = -1;
	is_in_set = 1;
	while (++f->n < f->max_iterations)
	{
		if ((ft_check_imgsquare(zr, zi)) > 4.0)
		{
			is_in_set = 0;
			break ;
		}
		tmp = 2 * zr * zi + pi;
		zr = zr * zr - zi * zi + pr;
		zi = tmp;
	}
	f->n *= 10;
	ft_put_pixel(f, is_in_set);
}

void	ft_burning_ship(t_fractol *f, long double pr, long double pi)
{
	long double		zr;
	long double		zi;
	int				is_in_set;
	long double		tmp;

	zr = 0;
	zi = 0;
	f->n = -1;
	is_in_set = 1;
	while (++f->n < f->max_iterations)
	{
		if ((ft_check_imgsquare(zr, zi)) > 4.0)
		{
			is_in_set = 0;
			break ;
		}
		tmp = fabsl(zr * zr - zi * zi + pr);
		zi = fabsl(2 * zr * zi + pi);
		zr = tmp;
	}
	f->n *= 10;
	ft_put_pixel(f, is_in_set);
}
