/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:46:42 by ntome             #+#    #+#             */
/*   Updated: 2026/07/03 15:06:25 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	reset_flags(t_flags *flags)
{
	flags->l_flag = 0;
	flags->ur_flag = 0;
	flags->a_flag = 0;
	flags->r_flag = 0;
	flags->t_flag = 0;
	flags->d_flag = 0;
	flags->one_flag = 0;
	flags->debugg_flag = 0;
	flags->args = malloc(sizeof(t_arg));
	if (!flags->args)
		return (1);
	flags->args->next = NULL;
	flags->args->path = NULL;
	return (0);
}

void	free_args(t_flags *flags)
{
	t_arg	*tmp;

	tmp = flags->args->next;
	while (flags->args->next)
	{
		if (flags->args->path)
			free(flags->args->path);
		free(flags->args);
		flags->args = tmp;
		tmp = flags->args->next;
	}
	if (flags->args->path)
		free(flags->args->path);
	free(flags->args);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (reset_flags(&flags))
		return (1);
	if (ft_init_flags(&flags, ac, av))
		return (1);
	if (!flags.args->path)
		flags.args->path = ft_strdup(".\0");
	target = flags.args;
	while (target && target->path)
	{
		read_element(&element, target->path, &flags, "./");
		target = target->next;
	}
	print_ls(&element, &flags);
	free_args(&flags);
	return (0);
}
