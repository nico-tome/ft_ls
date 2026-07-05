/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:46:42 by ntome             #+#    #+#             */
/*   Updated: 2026/07/05 19:56:07 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	setup(t_ctx *ctx)
{
	ctx->flags.l_flag = 0;
	ctx->flags.r_flag = 0;
	ctx->flags.t_flag = 0;
	ctx->flags.a_flag = 0;
	ctx->flags.d_flag = 0;
	ctx->flags.e_flag = 0;
	ctx->flags.ur_flag = 0;
	ctx->flags.uu_flag = 0;
	ctx->flags.one_flag = 0;
	ctx->flags.debugg_flag = 0;
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

	ctx.exit_code = 0;
	ctx.print_path = -1;
	ctx.args = NULL;
	elements = NULL;
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
		read_target(&ctx, target->path, &elements);
		target = target->next;
	}
	print_ls(&ctx, &elements);
	free_args(ctx.args);
	free_elements(&elements);
	return (ctx.exit_code);
}
