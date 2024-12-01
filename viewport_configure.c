/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_configure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 03:24:14 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 03:39:04 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	viewport_configure(t_viewport *port, t_scene *scene, t_camera *camera)
{
	t_vec3	*focal_length_vec;
	t_vec3	*u;
	t_vec3	*v;
	t_vec3	*w;

	focal_length_vec = vec3_new(0, 0, camera->focal_length);
	w = vec3_sub(camera->center, focal_length_vec);
	u = vec3_div_scalar(port->u, 2);
	v = vec3_div_scalar(port->v, 2);
	vec3_ip_sub(w, u);
	vec3_ip_sub(w, v);
	free(u);
	free(v);
	if (!port || !scene || !camera || !focal_length_vec)
		return ;
	port->pxl_d_u = vec3_div_scalar(port->u, scene->width);
	port->pxl_d_v = vec3_div_scalar(port->v, scene->height);
	port->upperleft = w;
	u = vec3_add(port->pxl_d_u, port->pxl_d_v);
	vec3_ip_mult(u, 0.5);
	vec3_ip_add(u, w);
	port->p00 = u;
}
