int	ft_check_args(char **str, int argc, t_fractol *f)
{
	if (ft_check_args_set(str, f))
		return (1);
	if (ft_check_args_coords(str, argc, f))
		return (1);
	return (0);
}

int	ft_check_args_set(char **str, t_fractol *f)
{
	if (ft_fractol_strcmp("Mandelbrot", str[1]))
	{
		ft_putstr("You chose Mandelbrot\n");
		f->set = 1;
	}
	else if (ft_fractol_strcmp("Julia", str[1]))
	{
		ft_putstr("You chose Julia\n");
		f->set = 2;
	}
	else if (ft_fractol_strcmp("Burning", str[1]))
	{
		ft_putstr("You chose Burning ship\n");
		f->set = 3;
	}
	else
	{
		ft_print_sets();
		return (1);
	}
	return (0);
}

int	ft_check_args_coords(char **str, int argc, t_fractol *f)
{
	if (f->set == 2)
	{
		if (argc < 4)
		{
			ft_putstr("Julia must be followed by two coordinates.\n");
			return (1);
		}
		else
		{
			if (!ft_isdecimal(str[2]) || !ft_isdecimal(str[3]))
			{
				ft_putstr("Julia coordinates must be decimal numbers using \
a point separator\n");
				return (1);
			}
			f->kr = ft_atof(str[2]);
			f->ki = ft_atof(str[3]);
		}
	}
	return (0);
}

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

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	ft_fractol_strcmp(const char *str1, const char *str2)
{
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
		{
			return (0);
		}
		str1++;
		str2++;
	}
	return (1);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (c);
	return (0);
}

int	ft_skip_space_sign(char *str, int *is_neg)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*is_neg *= -1;
		i++;
	}
	return (i);
}

void	ft_exit(t_fractol *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img_data->img);
	mlx_destroy_window(fractal->mlx, fractal->win);
	exit(0);
}


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

void	ft_print_bye(void)
{
	ft_putstr("\nCome back later for more fractal fun.\nSee you soon!\n");
}

void	ft_print_sets(void)
{
	ft_putstr("Available fractals are:\n\tMandelbrot"
		"\n\tJulia (must be followed by two coordinates)\n"
		"\tBurning ship\n");
}

void	ft_print_instructions(t_fractol *fractal)
{
	ft_putstr("Welcome to fractol!\nUse the following controls:\
		\n\tCursor keys:\tMove around the fractal\n\tz:\t\tzoom out\
		\n\tx:\t\tzoom in\n\t1-6:\t\tchange color\n\tESC:\t\texit\n");
	if (fractal-> set == 2)
	{
		ft_putstr("\tq/w:\t\tincrease/decrease r factor\n\te/r:\
		increase/decrease i factor\n");
	}
}

int	ft_isdecimal(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		if (str[i] == '.')
			dot_count++;
		if (dot_count > 1)
			return (0);
		i++;
	}
	return (1);
}

double	ft_atof(char *str)
{
	int		i;
	double	nb;
	int		is_neg;
	double	div;

	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = ft_skip_space_sign(str, &is_neg);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		nb = (nb * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	return (nb * is_neg);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long int		num;
	int				sign;
	int				i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		if (num * sign > 2147483647)
			return (-1);
		else if (num * sign < -2147483648)
			return (0);
		else
			num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(sign * num));
}

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
