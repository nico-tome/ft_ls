/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:11:01 by ntome             #+#    #+#             */
/*   Updated: 2026/06/29 12:37:24 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdlib.h>

int	reset_flags(t_flags *flags)
{
	flags->l_flag = 0;
	flags->ur_flag = 0;
	flags->a_flag = 0;
	flags->r_flag = 0;
	flags->t_flag = 0;
	flags->d_flag = 0;
	flags->one_flag = 0;
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
		free(flags->args);
		flags->args = tmp;
		tmp = flags->args->next;
	}
	free(flags->args);
}

int	main(int ac, char **av)
{
	t_flags		flags;
	t_element	element;

	if (reset_flags(&flags))
		return (1);
	if (ft_init_flags(&flags, ac, av))
		return (1);
	while (flags.args)
	{
		read_files(&element, flags.args);
		//parse
		//sort
		//print
	}
	free_args(&flags);
	return (0);
}
