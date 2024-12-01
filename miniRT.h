/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:16:24 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/01 05:00:44 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "ray/ray.h"
# include "scene.h"
# include <mlx.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

typedef t_vec3	t_color3;

uint64_t		color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
uint64_t		vec3_color(t_color3 *color_v);
uint64_t		ray_color(t_ray *ray);
#endif