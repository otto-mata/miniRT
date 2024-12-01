/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:00:08 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 05:21:29 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_sphere(t_point3 *center, double radius, t_ray *r)
{
	t_vec3	*oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(center, r->origin);
	a = vec3_dot(r->direction, r->direction);
	b = -2.0 * vec3_dot(r->direction, oc);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

uint64_t	ray_color(t_ray *ray)
{
	t_vec3		*unit_dir;
	t_vec3		*u;
	t_vec3		*v;
	uint64_t	v_color;
	double		a;

	if (hit_sphere(vec3_new(0, 0, -1), 0.5, ray))
		return (color(255, 255, 0, 0));
	unit_dir = vec3_unit(ray->direction);
	if (!unit_dir)
		return (0);
	a = 0.5 * (unit_dir->y + 1.0);
	u = vec3_new(1, 1, 1);
	vec3_ip_mult(u, (1.0 - a));
	v = vec3_new(0.5, 0.7, 1.0);
	vec3_ip_mult(v, a);
	vec3_ip_add(u, v);
	v_color = vec3_color(u);
	free(u);
	free(v);
	return (v_color);
}
