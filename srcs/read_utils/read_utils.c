/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:38:04 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 22:33:57 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static t_dir	*create_new_dir(t_ctx *ctx, char *path)
{

	t_dir	*new;
	new = malloc(sizeof(t_dir));
	if (!new)
	{
		malloc_error("read_utils.c", 110);
		return (NULL);
	}
	new->files = NULL;
	new->next = NULL;
	new->content = NULL;
	new->path = ft_strdup(path);
	new->sorting_path = ft_strdup(path);
	if (!ctx->flags.uu_flag)
		ft_strlowerise(&new->sorting_path);
	return (new);
}

static t_file	*create_new_file(t_ctx *ctx, char *path, struct dirent *entry)
{
	t_file	*new_file;

	if (!ctx->flags.a_flag && !ctx->flags.ur_flag && entry->d_name[0] == '.')
		return (NULL);
	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->name = ft_strdup(entry->d_name);
	new_file->path = ft_strdup(path);
	new_file->sorting_name = ft_strdup(path);
	if (!ctx->flags.uu_flag)
		ft_strlowerise(&new_file->sorting_name);
	new_file->next = NULL;
	lstat(path, &new_file->stat);
	return (new_file);
}

static t_file	*file_as_arg(t_ctx *ctx, char *path)
{
	t_file *new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->name = ft_strdup(path);
	new_file->path = ft_strdup(path);
	new_file->sorting_name = ft_strdup(path);
	if (!ctx->flags.uu_flag)
		ft_strlowerise(&new_file->sorting_name);
	new_file->next = NULL;
	lstat(path, &new_file->stat);
	return (new_file);
}

static void	fill_dir(t_ctx *ctx, t_dir *element, DIR *dir)
{
	struct dirent	*entry;
	t_file			*new_file;
	char			*path;
	char			*tmp;

	while ((entry = readdir(dir)) != NULL)
	{
		tmp = ft_strjoin(element->path, "/");
		if (tmp)
		{
			path = ft_strjoin(tmp, entry->d_name);
			free(tmp);
			if (path)
			{
				new_file = create_new_file(ctx, path, entry);
				if (new_file)
					insert_new_file(ctx, &element, new_file);
				free(path);
			}
		}
	}
}

static void	rec(t_ctx *ctx, t_dir **element)
{
	t_file	*file;

	file = (*element)->files;
	while (file)
	{
		if (ctx->flags.debugg_flag)
			print_debugg_file(file);
		if (S_ISDIR(file->stat.st_mode) && file->name[0] != '.')
			read_target(ctx, file->path, &((*element)->content), NULL);
		file = file->next;
	}
}

void	read_target(t_ctx *ctx, char *path, t_dir **elements, t_dir **files)
{
	t_dir	*new_element;
	t_file	*new_file;
	DIR		*dir;

	dir = ctx->flags.d_flag ? NULL : opendir(path);
	if (!dir)
	{
		new_file = file_as_arg(ctx, path);
		if (new_file)
			insert_new_file(ctx, files, new_file);
		return ;
	}
	new_element = create_new_dir(ctx, path);
	if (!new_element)
		return ;
	fill_dir(ctx, new_element, dir);
	closedir(dir);
	if (ctx->flags.ur_flag)
		rec(ctx, &new_element);
	insert_new_dir(ctx, elements, new_element);
}
