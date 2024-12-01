/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:00:52 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 02:11:05 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	*ray_new(t_point3 *origin, t_vec3 *direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (0);
	ray->direction = vec3_new(direction->x, direction->y, direction->z);
	ray->origin = vec3_new(origin->x, origin->y, origin->z);
	return (ray);
}
