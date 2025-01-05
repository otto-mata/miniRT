/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   camera_new.c                                         ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/01 02:56:03 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/05 23:22:20 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_camera	*camera_new(double view_width, double view_height,
		double focal_length)
{
	t_camera	*cam;

	cam = calloc(1, sizeof(t_camera));
	if (!cam)
		return (0);
	cam->center = calloc(1, sizeof(t_point3));
	if (!cam->center)
		return (0);
	cam->center->x = 0;
	cam->center->y = 0;
	cam->center->z = 0;
	cam->viewport = viewport_new(view_height, view_width);
	cam->focal_length = focal_length;
	return (cam);
}
