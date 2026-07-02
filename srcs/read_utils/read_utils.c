/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:38:04 by ntome             #+#    #+#             */
/*   Updated: 2026/07/02 19:50:35 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"
#include <stdio.h>

static int	read_entry(struct dirent *entry, t_element *element, char *path)
{
	char	*complete_path;

	complete_path = ft_strjoin(path, entry->d_name);
	if (!complete_path)
	{
		printf("%sMalloc Error: ft_strjoin fail in read_utils.c at line 22%s\n",
			RED, RESET);
		return (1);
	}
	element->name = ft_strdup(entry->d_name);
	element->is_dir = entry->d_type == DT_DIR;
	if (lstat(complete_path, &element->stat))
	{
		perror("ft_ls: \0");
		return (1);
	}
	element->content = NULL;
	element->type = entry->d_type;
	free(complete_path);
	return (0);
}

static int	create_next(t_element *elements)
{
	elements->next = malloc(sizeof(t_element));
	if (!elements->next)
		return (1);
	elements->next->next = NULL;
	elements->next->name = NULL;
	elements->next->is_dir = 0;
	elements->next->content = NULL;
	elements->next->type = 0;
	elements = elements->next;
	return (0);
}

static int	rec(t_element *elements, char *target, t_flags *flags, char *path)
{
	char	*complete_path;

	complete_path = ft_strjoin(path, );
}

int	read_element(t_element *elements, char *target, t_flags *flags, char *path)
{
	t_element		*head;
	struct dirent	*entry;
	DIR				*dir;

	head = elements;
	entry = NULL;
	dir = opendir(target);
	if (!dir)
	{
		perror("ls: \0");
		return (1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (read_entry(entry, elements, path))
			return (1);
		if (create_next(elements))
			return (1);
	}
	closedir(dir);
	if (flags->ur_flag && !flags->d_flag)
		return(rec(head, target, flags, path));
	return (0);
}
