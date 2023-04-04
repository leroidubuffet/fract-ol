/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybolivar <ybolivar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:58:33 by ybolivar          #+#    #+#             */
/*   Updated: 2023/04/03 17:24:16 by ybolivar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

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
