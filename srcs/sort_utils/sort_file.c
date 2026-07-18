/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:35:50 by ntome             #+#    #+#             */
/*   Updated: 2026/07/18 20:29:31 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void	insert_by_name(t_dir **elements, t_file *new)
{
	t_file	*curr;

	if (strcoll(new->sorting_name, (*elements)->files->sorting_name) < 0)
	{
		new->next = (*elements)->files;
		(*elements)->files = new;
		return ;
	}
	curr = (*elements)->files;
	while (curr->next && strcoll(new->sorting_name, curr->next->sorting_name) >= 0)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

static void	insert_by_reverse_name(t_dir **elements, t_file *new)
{
	t_file	*curr;

	if (strcoll(new->sorting_name, (*elements)->files->sorting_name) > 0)
	{
		new->next = (*elements)->files;
		(*elements)->files = new;
		return ;
	}
	curr = (*elements)->files;
	while (curr->next && strcoll(new->sorting_name, curr->next->sorting_name) <= 0)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

static void	insert_by_time(t_dir **dir, t_file *new)
{
	t_file	*curr;

	if (new->stat.st_mtim.tv_sec > (*dir)->files->stat.st_mtim.tv_sec)
	{
		new->next = (*dir)->files;
		(*dir)->files = new;
		return ;
	}
	curr = (*dir)->files;
	while (curr->next && new->stat.st_mtim.tv_sec <= curr->next->stat.st_mtim.tv_sec)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

static void	insert_by_reverse_time(t_dir **dir, t_file *new)
{
	t_file	*curr;

	if (new->stat.st_mtim.tv_sec < (*dir)->files->stat.st_mtim.tv_sec)
	{
		new->next = (*dir)->files;
		(*dir)->files = new;
		return ;
	}
	curr = (*dir)->files;
	while (curr->next && new->stat.st_mtim.tv_sec > curr->next->stat.st_mtim.tv_sec)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

void	insert_new_file(t_ctx *ctx, t_dir **elements, t_file *new_file)
{
	if (!(*elements)->files)
		(*elements)->files = new_file;
	else
	{
		if (ctx->flags.t_flag && !ctx->flags.r_flag)
			insert_by_time(elements, new_file);
		else if (ctx->flags.t_flag && ctx->flags.r_flag)
			insert_by_reverse_time(elements, new_file);
		else if (!ctx->flags.t_flag && ctx->flags.r_flag)
			insert_by_reverse_name(elements, new_file);
		else
			insert_by_name(elements, new_file);
	}
}
