/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:38:04 by ntome             #+#    #+#             */
/*   Updated: 2026/07/18 20:30:21 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"
#include <sys/stat.h>

static char	*create_sort_name(t_ctx *ctx, char *name)
{
	char	*sorting_name;
	int		size;

	size = ft_strlen(name);
	if (ctx->flags.a_flag && name[size - 1] == '.')
		sorting_name = ft_strdup(name);
	else
		sorting_name = ft_strdup(name);
	return (sorting_name);
}

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
	new->sorting_path = create_sort_name(ctx, path);
	return (new);
}

static t_file	*create_new_file(t_ctx *ctx, char *path, struct dirent *entry)
{
	t_file	*new_file;

	if (!ctx->flags.a_flag && !ctx->flags.ua_flag && !ctx->flags.ur_flag && entry->d_name[0] == '.')
		return (NULL);
	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->name = ft_strdup(entry->d_name);
	new_file->path = ft_strdup(path);
	new_file->sorting_name = create_sort_name(ctx, entry->d_name);
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

static int	check_perm(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		perror(path);
		return (0);
	}
	closedir(dir);
	return (1);
}

static void	rec(t_ctx *ctx, t_dir **element)
{
	t_file	*file;
	int		len;

	file = (*element)->files;
	while (file)
	{
		len = ft_strlen(file->name);
		if (S_ISDIR(file->stat.st_mode) && file->name[len - 1] != '.' &&
			(file->name[0] != '.' || ctx->flags.a_flag || ctx->flags.ua_flag) && check_perm(file->path))
			read_target(ctx, file->path, &((*element)->content), NULL);
		file = file->next;
	}
}

static int	check_path(char *path)
{
	struct stat	st;

	if (lstat(path, &st) == -1)
	{
		perror(path);
		return (0);
	}
	return (1);
}

void	read_target(t_ctx *ctx, char *path, t_dir **elements, t_dir **files)
{
	t_dir	*new_element;
	t_file	*new_file;
	DIR		*dir;

	if (!check_path(path))
	{
		ctx->exit_code = 2;
		return ;
	}
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
