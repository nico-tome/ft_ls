/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:38:04 by ntome             #+#    #+#             */
/*   Updated: 2026/07/03 13:46:41 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static int	read_entry(struct dirent *entry, t_element *element, char *path)
{
	char	*tmp;
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
	printf("real path: %s\n", complete_path);
	if (lstat(complete_path, &element->stat))
	{
		perror("ft_ls\0");
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

static int	create_content(t_element *element)
{
	element->content = malloc(sizeof(t_element));
	if (!element->content)
		return (1);
	element->content->name = NULL;
	element->content->content = NULL;
	element->content->next = NULL;
	element->content->is_dir = 0;
	element->content->type = 0;
	return (0);
}

static int	rec(t_element *elements, char *target, t_flags *flags, char *path)
{
	char	*complete_path;
	char	*tmp;

	tmp = ft_strjoin(target, "/");
	if (!tmp)
		return (1);
	complete_path = ft_strjoin(path, tmp);
	free(tmp);
	if (!complete_path)
		return (1);
	while (elements)
	{
		if (elements->is_dir)
		{
			if (create_content(elements))
				read_element(elements->content, elements->name, flags, complete_path);
		}
		elements = elements->next;
	}
	free(complete_path);
	return (0);
}

int	read_element(t_element *elements, char *target, t_flags *flags, char *path)
{
	char	*real_path;

	real_path = create_path(path, taget);
	if (!real_path)
		return (1);
}
