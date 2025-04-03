#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../src/minilibx-linux/mlx.h"

#define ERROR_MESSAGE "Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <value_1> <value_2>\"\n"
#define WIDTH	800
#define	HEIGHT	800

//COLORS
#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)
#define MAGENTA_BURST   0xFF00FF
#define LIME_SHOCK      0xCCFF00
#define NEON_ORANGE     0xFF6600
#define PSYCHEDELIC_PURPLE 0x660066
#define AQUA_DREAM      0x33CCCC
#define HOT_PINK        0xFF66B2
#define ELECTRIC_BLUE   0x0066FF
#define LAVA_RED        0xFF3300

// COMPLEX number
typedef struct	s_complex
{
	//		real
	double	x;
	//		i
	double	y;
}				t_complex;

/*
 * IMAGE
 * This is basically a pixels buffer
 * values from mlx_get_data_addr()
*/
typedef struct	s_img
{
	void	*img_ptr; //pointer to image struct
	char	*pixels_ptr; //points to the actual pixels
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;
/*
 * FRACTAL ID
 * ~ MLX stuff
 * ~ Image 
 * ~ Hooks values
*/
typedef struct	s_fractal
{
	char	*name;
	//MLX
	void	*mlx_connection; // mlx_init()
	void	*mlx_window; 	 // mlx_new_window()
	//Image
	t_img	img;

	//Hooks member variables //TODO
	double	escape_value; // hypotenuse
	int		iterations_def; // value tight with the image quality and rendering speed
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;

//*** strings utils ***
double  atodbl(char *s);
//*** init ***
void    fractal_init(t_fractal *fractal);
//*** render ***
void    fractal_render(t_fractal *fractal);
//*** math ***
double		map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);
//*** hooks_events ***
int			key_handler(int keysym, t_fractal *fractal);
//*** clean_up ***
int    	close_handler(t_fractal *fractal);
int	mouse_handler(int button, int x, int y, t_fractal *fractal);
int		julia_track(int x, int y, t_fractal *fractal);

#endif
