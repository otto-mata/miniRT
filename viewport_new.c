/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   viewport_new.c                                       ┌─┐┌┬┐┌┬┐┌─┐        */
/*                                                        │ │ │  │ │ │        */
/*   By: tblochet <tblochet@student.42.fr>                └─┘ ┴  ┴ └─┘        */
/*                                                        ┌┬┐┌─┐┌┬┐┌─┐        */
/*   Created: 2024/12/01 03:20:08 by tblochet             │││├─┤ │ ├─┤        */
/*   Updated: 2025/01/05 23:22:56 by tblochet             ┴ ┴┴ ┴ ┴ ┴ ┴        */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_viewport	*viewport_new(double height, double width)
{
	t_viewport	*view;

	view = malloc(sizeof(t_viewport));
	if (!view)
		return (0);
	view->height = height;
	view->width = width;
	view->u = vec3_new(width, 0, 0);
	view->v = vec3_new(0, -height, 0);
	return (view);
}
