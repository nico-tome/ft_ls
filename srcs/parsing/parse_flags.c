/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:34:51 by ntome             #+#    #+#             */
/*   Updated: 2026/07/10 16:23:24 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static int	update_flag(t_flags *flags, char flag)
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
	else if (flag == 'A')
		flags->ua_flag = 1;
	else if (flag == '@')
		flags->auth_flag = 1;
	else if (flag == 'd')
		flags->d_flag = 1;
	else if (flag == 'g')
		flags->g_flag = 1;
	else if (flag == 'G')
		flags->ug_flag = 1;
	else if (flag == 'm')
		flags->m_flag = 1;
	else if (flag == 'n')
		flags->n_flag = 1;
	else if (flag == 'p')
		flags->p_flag = 1;
	else if (flag == '1')
		flags->one_flag = 1;
	else if (flag == 'e')
		flags->e_flag = 1;
	else if (flag == 'U')
		flags->uu_flag = 1;
	else if (flag == 'Q')
		flags->uq_flag = 1;
	else if (flag == 's')
		flags->s_flag = 1;
	else if (flag == '%')
		flags->only_dir_flag = 1;
	else if (flag == '&')
		flags->no_color_flag = 1;
	return (0);
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

static int	parse_long_flag(int *exit_code, t_flags *flags, char *flag)
{
	if (!ft_strcmp(flag, "--help"))
	{
		print_help();
		return (1);
	}
	if (!ft_strcmp(flag, "--all"))
		return (update_flag(flags, 'a'));
	else if (!ft_strcmp(flag, "--almost-all"))
		return (update_flag(flags, 'A'));
	else if (!ft_strcmp(flag, "--author"))
		return (update_flag(flags, '@'));
	else if (!ft_strcmp(flag, "--directory"))
		return (update_flag(flags, 'd'));
	else if (!ft_strcmp(flag, "--no-group"))
		return (update_flag(flags, 'G'));
	else if (!ft_strcmp(flag, "--numeric-uid-gid"))
		return (update_flag(flags, 'n'));
	else if (!ft_strcmp(flag, "--directory-indicator"))
		return (update_flag(flags, 'p'));
	else if (!ft_strcmp(flag, "--emojies"))
		return (update_flag(flags, 'e'));
	else if (!ft_strcmp(flag, "--keep-uppercase"))
		return (update_flag(flags, 'U'));
	else if (!ft_strcmp(flag, "--only-dir"))
		return (update_flag(flags, '%'));
	else if (!ft_strcmp(flag, "--quote-names"))
		return (update_flag(flags, 'Q'));
	else if (!ft_strcmp(flag, "--reverse"))
		return (update_flag(flags, 'r'));
	else if (!ft_strcmp(flag, "--size"))
		return (update_flag(flags, 's'));
	else if (!ft_strcmp(flag, "--no-color"))
		return (update_flag(flags, '&'));
	else if (!ft_strcmp(flag, "--recursive"))
		return (update_flag(flags, 'R'));
	else
	{
		ft_printf("ft_ls : the option << %s >> is not valid.\n", flag);
		ft_printf("Type << ft_ls --help >> for more informations.\n");
		*exit_code = 2;
		return (1);
	}
}

static int	parse_flag(int *exit_code, t_flags *flags, char *flag)
{
	int	i;

	if (flag[1] == '-')
	{
		i = parse_long_flag(exit_code, flags, flag);
		return (i);
	}
	i = 1;
	while (flag[i])
	{
		if (!ft_strchr(VALID_FLAGS, flag[i]))
		{
			*exit_code = 2;
			write(2, "ft_ls : invalid option '", 24);
			write(2, &flag[i], 1);
			write(2, "'\nType « ft_ls --help » for more infos.\n", 42);
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
			if (parse_flag(&ctx->exit_code, &ctx->flags, av[i]))
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
