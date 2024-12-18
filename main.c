/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:10:54 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/04 17:48:54 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw(t_data *img, t_scene *scene)
{
	int		i;
	int		j;
	t_vec3	*pixel_center;
	t_vec3	*u;
	t_ray	*ray;

	i = 0;
	while (i < scene->width)
	{
		j = 0;
		while (j < scene->height)
		{
			u = vec3_mult_scalar(scene->camera->viewport->pxl_d_u, i);
			vec3_ip_add(u, scene->camera->viewport->p00);
			pixel_center = vec3_mult_scalar(scene->camera->viewport->pxl_d_v,
					j);
			vec3_ip_add(pixel_center, u);
			ray = ray_new(scene->camera->center, vec3_sub(pixel_center,
						scene->camera->center));
			my_mlx_pixel_put(img, i, j, ray_color(ray));
			free(ray);
			free(pixel_center);
			free(u);
			j++;
		}
		i++;
	}
}

void	mlx_setup(t_scene *scene)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, scene->width, scene->height, "Hello world!");
	img.img = mlx_new_image(mlx, scene->width, scene->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw(&img, scene);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

int	main(void)
{
	t_scene	*scene;

	scene = scene_new(1.0, 340, 0.8, 2.0);
	mlx_setup(scene);
	return (0);
}
