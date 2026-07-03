/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:34:09 by ntome             #+#    #+#             */
/*   Updated: 2026/07/03 12:52:59 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"
#include <dirent.h>

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
	ft_printf("%s-D%s\tuse debugg mode\n", GREEN, RESET);
	ft_printf("%s--help%s\tshow this help\n", GREEN, RESET);
}

// -l -R -r -a -t -d -1

static int	check_print(t_element *element, t_flags *flags)
{
	if (element->name[0] == '.' && !flags->a_flag)
		return (0);
	return (1);
}

static void	get_color(t_element *element, char **color)
{
	mode_t	mode;

	mode = element->stat.st_mode;
	*color = RESET;
	if (S_ISDIR(mode))
		*color = BLUE;
	else if (S_ISREG(mode))
	{
		if (mode & ((S_IXUSR | S_IXGRP | S_IXOTH)))
			*color = GREEN;
		else
			*color = RESET;
	}
}

void	print_ls(t_element *element, t_flags *flags)
{
	char	*color;

	while (element && element->name)
	{
		if (check_print(element, flags))
		{
			get_color(element, &color);
			printf("%s%s%s  ", color, element->name, RESET);
		}
		element = element->next;
	}
	printf("\n");
}
