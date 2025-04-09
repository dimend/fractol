/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:55:39 by dimendon          #+#    #+#             */
/*   Updated: 2025/04/09 19:17:09 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include <stdio.h>

void	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

static void	fractal_mlx_init_connection_window(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		error("Malloc failed");
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT,
			fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		error("Malloc failed");
	}
}

static void	fractal_mlx_init_image_pixel(t_fractal *fractal)
{
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection, WIDTH,
			HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		error("Malloc failed");
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
}

void	fractal_init(t_fractal *fractal)
{
	fractal_mlx_init_connection_window(fractal);
	fractal_mlx_init_image_pixel(fractal);
	events_init(fractal);
	data_init(fractal);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)) || (ac == 4
			&& !ft_strncmp(av[1], "julia", 5)))
	{
		fractal.name = av[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_putstr_fd("Wrong command.\n", STDERR_FILENO);
		ft_putstr_fd("./fractol mandelbrot\n", STDERR_FILENO);
		ft_putstr_fd("or\n", STDERR_FILENO);
		ft_putstr_fd("./fractol julia <value1> <value2>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
