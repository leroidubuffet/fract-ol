/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:02:25 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:21 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_img_init(t_img *imgs, t_fractol *fractal)
{
	imgs->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!imgs->img)
		exit(1);
	imgs->addr = mlx_get_data_addr(imgs->img, &imgs->bits_per_pixel,
			&imgs->line_length, &imgs->endian);
	if (!imgs->addr)
		exit(1);
	fractal->img_data = imgs;
}

void	ft_put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

long double	ft_check_imgsquare(long double zr, long double zi)
{
	long double		zr_square;
	long double		zi_square;

	zr_square = zr * zr;
	zi_square = zi * zi;
	return (zr_square + zi_square);
}

void	ft_put_pixel(t_fractol *f, int is_in_set)
{
	if (is_in_set == 1)
		ft_put_pixel_img(*f->img_data, f->x, f->y, ft_create_trgb(0, 0, 0, 0));
	else
		ft_put_pixel_img(*f->img_data, f->x, f->y, ft_create_trgb(0, \
		f->n + f->r_factor, f->n + f->g_factor, f->n + f->b_factor));
}
