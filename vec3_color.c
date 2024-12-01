/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:03:14 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 04:10:27 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint64_t	vec3_color(t_color3 *color_v)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (!color_v)
		return (0);
	r = 255.999 * color_v->x;
	g = 255.999 * color_v->y;
	b = 255.999 * color_v->z;
	return (color(255, r, g, b));
}
