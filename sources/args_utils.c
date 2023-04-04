/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:26:59 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/04 14:51:57 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_check_args(char **str, int argc, t_fractol *f)
{
	if (!f)
		return (1);
	if (ft_check_args_set(str, f))
		return (1);
	if (ft_check_args_coords(str, argc, f))
		return (1);
	return (0);
}

int	ft_check_args_set(char **str, t_fractol *f)
{
	if (!f)
		return (1);
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
	if (!f)
		return (1);
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
