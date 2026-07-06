/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:46:42 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 20:46:06 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	setup(t_ctx *ctx)
{
	ft_bzero(&ctx->flags, sizeof(t_flags));
	ctx->args = malloc(sizeof(t_arg));
	if (!ctx->args)
		return (1);
	ctx->args->next = NULL;
	ctx->args->path = NULL;
	return (0);
}


int	main(int ac, char **av)
{
	t_ctx	ctx;
	t_arg	*target;
	t_dir	*elements;
	t_dir	*files;

	ctx.exit_code = 0;
	ctx.print_path = -1;
	ctx.args = NULL;
	elements = NULL;
	files = malloc(sizeof(t_dir));
	if (!files)
		return (1);
	files->files = NULL;
	files->next = NULL;
	files->path = NULL;
	files->sorting_path = NULL;
	files->content = NULL;
	if (setup(&ctx))
		return (1);
	if (ft_init_flags(&ctx, ac, av))
		return (1);
	if (!ctx.args->path)
		ctx.args->path = ft_strdup(".\0");
	target = ctx.args;
	while (target && target->path)
	{
		ctx.print_path++;
		read_target(&ctx, target->path, &elements, &files);
		target = target->next;
	}
	print_ls(&ctx, &files, &elements);
	free_args(ctx.args);
	free_elements(&elements);
	free_elements(&files);
	return (ctx.exit_code);
}
