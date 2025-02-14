/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   scene_new.c                                          ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/01 02:58:04 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/05 23:06:30 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	*scene_new(double ratio, int width, double cam_focal_length,
		double viewport_height)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (0);
	scene->aspect_ratio = ratio;
	scene->width = width;
	scene->height = width / ratio;
	if (scene->height < 1)
		scene->height = 1;
	scene->camera = camera_new(viewport_height * ratio, viewport_height,
			cam_focal_length);
	viewport_configure(scene->camera->viewport, scene, scene->camera);
	return (scene);
}
