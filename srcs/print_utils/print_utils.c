/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:34:09 by ntome             #+#    #+#             */
/*   Updated: 2026/06/29 12:37:09 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	print_help(void)
{
	ft_printf("Usage: ls [%sOPTION%s]... [%sFILES%s]...\n",
		YELLOW, RESET, YELLOW, RESET);
	ft_printf("Show informations about [%sFILES%s].\n\n", YELLOW, RESET);
	ft_printf("%s-l%s\tuse long format display\n", GREEN, RESET);
	ft_printf("%s-R%s\tuse recursive subdirectories\n", GREEN, RESET);
	ft_printf("%s-r%s\treverse sort order\n", GREEN, RESET);
	ft_printf("%s-a%s\tdon't ignore entries that start with .\n", GREEN, RESET);
	ft_printf("%s-t%s\tsort by date, newest first\n", GREEN, RESET);
	ft_printf("%s-d%s\tonly show directory names\n", GREEN, RESET);
	ft_printf("%s-1%s\tshow one file per line\n", GREEN, RESET);
	ft_printf("%s--help%s\tshow this help\n", GREEN, RESET);
}

// -l -R -r -a -t -d -1
