/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debugg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 12:55:57 by ntome             #+#    #+#             */
/*   Updated: 2026/07/05 19:35:49 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	print_debugg_read_element(char *target, char *path)
{
	ft_printf("%s====[DEBUGG READ ELEMENT]====%s\n", RED, RESET);
	ft_printf("%s[TARGET]%s %s%s%s\n", YELLOW, RESET, PURPLE, target, RESET);
	ft_printf("%s[PATH]%s %s%s%s\n", YELLOW, RESET, PURPLE, path);
	ft_printf("%s=============================%s\n", RED, RESET);
}

void	print_debugg_file(t_file *file)
{
	ft_printf("%s====[DEBUGG FILE]====%s\n", RED, RESET);
	ft_printf("%s[NAME]%s %s%s%s\n", YELLOW, RESET, PURPLE, file->name, RESET);
	ft_printf("%s[PATH]%s %s%s%s\n", YELLOW, RESET, PURPLE, file->path, RESET);
	ft_printf("%s[TYPE]%s %s%d%s\n", YELLOW, RESET, PURPLE, file->stat.st_mode, RESET);
	ft_printf("%s=====================%s\n", RED, RESET);
}

void	malloc_error(char *file, int line)
{
	ft_printf("%s[MALLOC ERROR] Error in %s at line %d%s\n", RED, file, line, RESET);
}
