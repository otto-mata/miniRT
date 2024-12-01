/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:58:44 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 02:12:34 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "../vec3/vec3.h"

typedef struct s_ray	t_ray;

struct					s_ray
{
	t_point3			*origin;
	t_vec3				*direction;
};

t_ray					*ray_new(t_point3 *origin, t_vec3 *direction);
t_point3				*ray_at(t_ray *ray, double t);
#endif