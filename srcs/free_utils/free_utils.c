/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:56:15 by ntome             #+#    #+#             */
/*   Updated: 2026/07/03 15:05:05 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	free_args(t_arg *args)
{
	t_arg	*tmp;

	tmp = args->next;
	while (args->next)
	{
		if (args->path)
			free(args->path);
		free(args);
		args = tmp;
		tmp = args->next;
	}
	if (args->path)
		free(args->path);
	free(args);
}

void	free_elements(t_element *elements)
{
	t_element	*tmp;

	tmp = elements->next;
	while (elements)
	{
		if (elements->path)
			free(elements->path);
		if (elements->name)
			free(elements->name);
		if (elements->content)
			free_elements(elements->content);
		free(elements);
		elements = tmp;
		tmp = elements->next;
	}
}
