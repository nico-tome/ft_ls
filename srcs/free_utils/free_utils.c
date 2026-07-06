/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:56:15 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 18:27:43 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	free_args(t_arg *args)
{
	t_arg	*tmp;

	while (args)
	{
		tmp = args->next;
		if (args->path)
			free(args->path);
		free(args);
		args = tmp;
	}
}

static void	free_files(t_file *files)
{
	t_file	*tmp;

	while (files)
	{
		tmp = files->next;
		if (files->path)
			free(files->path);
		if (files->name)
			free(files->name);
		if (files->sorting_name)
			free(files->sorting_name);
		free(files);
		files = tmp;
	}
}

void	free_elements(t_dir **dirs)
{
	t_dir	*dir;
	t_dir	*tmp;

	dir = *dirs;
	while (dir)
	{
		tmp = dir->next;
		if (dir->files)
			free_files(dir->files);
		if (dir->content)
			free_elements(&dir->content);
		if (dir->path)
			free(dir->path);
		if (dir->sorting_path)
			free(dir->sorting_path);
		free(dir);
		dir = tmp;
	}
}
