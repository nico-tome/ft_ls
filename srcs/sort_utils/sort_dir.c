/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 16:38:30 by ntome             #+#    #+#             */
/*   Updated: 2026/07/05 19:49:09 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void	insert_by_name(t_dir **elements, t_dir *new)
{
	t_dir	*curr;

	if (ft_strcmp(new->sorting_path, (*elements)->sorting_path) < 0)
	{
		new->next = *elements;
		*elements = new;
		return ;
	}
	curr = *elements;
	while (curr->next && ft_strcmp(new->sorting_path, curr->sorting_path) >= 0)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

static void	insert_by_reverse_name(t_dir **elements, t_dir *new)
{
	t_dir	*curr;

	if (ft_strcmp(new->sorting_path, (*elements)->sorting_path) > 0)
	{
		new->next = *elements;
		*elements = new;
		return ;
	}
	curr = *elements;
	while (curr->next && ft_strcmp(new->path, curr->path) <= 0)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

static void	insert_by_time(t_dir **dir, t_dir *new)
{
	t_dir	*curr;

	if (new->stat.st_mtim.tv_nsec > (*dir)->stat.st_mtim.tv_nsec)
	{
		new->next = *dir;
		*dir = new;
		return ;
	}
	curr = *dir;
	while (curr->next && new->stat.st_mtim.tv_nsec < curr->stat.st_mtim.tv_nsec)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

static void	insert_by_reverse_time(t_dir **dir, t_dir *new)
{
	t_dir	*curr;

	if (new->stat.st_mtim.tv_nsec < (*dir)->stat.st_mtim.tv_nsec)
	{
		new->next = *dir;
		*dir = new;
		return ;
	}
	curr = *dir;
	while (curr->next && new->stat.st_mtim.tv_nsec > curr->stat.st_mtim.tv_nsec)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

void	insert_new_dir(t_ctx *ctx, t_dir **elements, t_dir *new_dir)
{
	if (!*elements)
		*elements = new_dir;
	else
	{
		if (ctx->flags.t_flag && !ctx->flags.r_flag)
			insert_by_time(elements, new_dir);
		else if (ctx->flags.t_flag && ctx->flags.r_flag)
			insert_by_reverse_time(elements, new_dir);
		else if (!ctx->flags.t_flag && ctx->flags.r_flag)
			insert_by_reverse_name(elements, new_dir);
		else
			insert_by_name(elements, new_dir);
	}
}
