/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:39:11 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 03:47:44 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "vec3/vec3.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_scene		t_scene;
typedef struct s_viewport	t_viewport;
typedef struct s_camera		t_camera;

struct						s_scene
{
	int						width;
	int						height;
	double					aspect_ratio;
	t_camera				*camera;
};

struct						s_camera
{
	double					focal_length;
	t_point3				*center;
	t_viewport				*viewport;
};

struct						s_viewport
{
	double					height;
	double					width;
	t_vec3					*u;
	t_vec3					*v;
	t_vec3					*pxl_d_u;
	t_vec3					*pxl_d_v;
	t_vec3					*upperleft;
	t_vec3					*p00;
};

t_camera					*camera_new(double view_width, double view_height,
								double focal_length);
t_viewport					*viewport_new(double height, double width);
void						viewport_configure(t_viewport *port, t_scene *scene,
								t_camera *camera);
t_scene						*scene_new(double ratio, int width,
								double cam_focal_length,
								double viewport_height);
#endif