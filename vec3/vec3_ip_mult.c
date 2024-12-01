/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ip_mult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:36:06 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 01:37:05 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec3_ip_mult(t_vec3 *v, double t)
{
	v->x *= t;
	v->y *= t;
	v->z *= t;
}
