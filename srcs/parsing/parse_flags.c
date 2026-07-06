/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:34:51 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 20:54:18 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void	update_flag(t_flags *flags, char flag)
{
	if (flag == 'l')
		flags->l_flag = 1;
	else if (flag == 'R')
		flags->ur_flag = 1;
	else if (flag == 'a')
		flags->a_flag = 1;
	else if (flag == 'r')
		flags->r_flag = 1;
	else if (flag == 't')
		flags->t_flag = 1;
	else if (flag == 'd')
		flags->d_flag = 1;
	else if (flag == '1')
		flags->one_flag = 1;
	else if (flag == 'D')
		flags->debugg_flag = 1;
	else if (flag == 'e')
		flags->e_flag = 1;
	else if (flag == 'U')
		flags->uu_flag = 1;
	else if (flag == 'Q')
		flags->uq_flag = 1;
	else if (flag == 's')
		flags->s_flag = 1;
}

static int	add_arg(t_arg *args, char *arg)
{
	t_arg	*new;
	t_arg	*head;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (1);
	new->path = NULL;
	new->next = NULL;
	head = args;
	while (head->next)
		head = head->next;
	head->path = ft_strdup(arg);
	head->next = new;
	return (0);
}

static int	parse_flag(t_flags *flags, char *flag)
{
	int	i;

	if (!ft_strcmp("--help", flag))
	{
		print_help();
		return (2);
	}
	i = 1;
	while (flag[i])
	{
		if (!ft_strchr(VALID_FLAGS, flag[i]))
		{
			write(2, "ft_ls : invalid option '", 24);
			write(2, &flag[i], 1);
			write(2, "'\nType « ls -h » for more infos.\n", 33);
			return (1);
		}
		update_flag(flags, flag[i]);
		i++;
	}
	return (0);
}

int	ft_init_flags(t_ctx *ctx, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (parse_flag(&ctx->flags, av[i]))
			{
				free_args(ctx->args);
				return (1);
			}
		}
		else
		{
			if (add_arg(ctx->args, av[i]))
			{
				free_args(ctx->args);
				return (1);
			}
		}
	}
	return (0);
}
