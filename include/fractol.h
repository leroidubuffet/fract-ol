/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:09:21 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:57:09 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 400
# define HEIGHT 400

# define MANDELBROT 1
# define JULIA 2
# define BURNING 3

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 125
# define KEY_DOWN 126
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 22
# define KEY_SIX 23
# define KEY_Z 6
# define KEY_X 7
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15

# define MOUSE_WHEEL_UP 5
# define MOUSE_WHEEL_DOWN 4
# define MOUSE_LEFT_CLICK 1

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fractol
{
	void			*mlx;
	void			*win;
	unsigned int	max_iterations;
	unsigned int	n;
	char			set;
	char			r_factor;
	char			g_factor;
	char			b_factor;
	long double		range_r;
	long double		range_i;
	long double		min_r;
	long double		max_r;
	long double		min_i;
	long double		max_i;
	long double		kr;
	long double		ki;
	long double		zoom;
	long double		distance;
	long double		x;
	long double		y;
	t_img			*img_data;
}	t_fractol;

double		ft_atof(char *str);
int			ft_atoi(const char *str);
void		ft_burning_ship(t_fractol *f, long double pr, long double pi);
int			ft_check_args(char **str, int argc, t_fractol *f);
int			ft_check_args_set(char **str, t_fractol *f);
int			ft_check_args_coords(char **str, int argc, t_fractol *f);
long double	ft_check_imgsquare(long double zr, long double zi);
int			ft_create_trgb(int t, int r, int g, int b);
void		ft_draw_fractal(t_fractol *f);
void		ft_exit(t_fractol *fractal);
int			ft_fractol_strcmp(const char *str1, const char *str2);
void		ft_img_init(t_img *imgs, t_fractol *fractal);
int			ft_isdecimal(char *str);
int			ft_isdigit(int c);
int			ft_isspace(int c);
void		ft_julia(t_fractol *f, long double pr, long double pi);
int			ft_keyboard_update(int keycode, void *param);
void		ft_key_control(int keycode, t_fractol *fractol);
void		ft_key_control_move(int keycode, t_fractol *f);
void		ft_key_control_julia(int keycode, t_fractol *f);
void		ft_key_control_color(int keycode, t_fractol *f);
void		ft_mandelbrot(t_fractol *f, long double pr, long double pi);
void		ft_mouse_control(t_fractol *fractol, int x, int y);
int			ft_mouse_update(int buttoncode, int x, int y, void *param);
void		ft_print_bye(void);
void		ft_print_instructions(t_fractol *fractal);
void		ft_print_sets(void);
void		ft_put_pixel(t_fractol *f, int is_in_set);
void		ft_putstr(char *s);
int			ft_skip_space_sign(char *str, int *is_neg);
void		ft_zoom(int keycode, t_fractol *fractol, int x, int y);
void		ft_zoom_update_min_max(t_fractol *fractol, long double zoom);
void		ft_put_pixel_img(t_img img, int x, int y, int color);

#endif