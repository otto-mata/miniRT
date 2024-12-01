/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:06:30 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 04:23:08 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_point3	*ray_at(t_ray *ray, double t)
{
	t_vec3		*mult;
	t_point3	*add;

	if (!ray)
		return (0);
	mult = vec3_mult_scalar(ray->direction, t);
	if (!mult)
		return (0);
	add = vec3_add(ray->origin, mult);
	if (!add)
		return (0);
	free(mult);
	return (add);
}
