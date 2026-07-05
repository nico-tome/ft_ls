/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:34:09 by ntome             #+#    #+#             */
/*   Updated: 2026/07/05 19:28:01 by ntome            ###   ########.fr       */
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

static int	check_print(t_file *file, t_flags *flags)
{
	if (file->name[0] == '.' && !flags->a_flag)
		return (0);
	return (1);
}

static void	get_color(t_file *file, char **color)
{
	mode_t	mode;

	mode = file->stat.st_mode;
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

static void	print_files(t_ctx *ctx, t_file *files)
{
	int		code;
	char	*color;

	code = 0;
	while (files)
	{
		if (check_print(files, &ctx->flags))
		{
			code = 1;
			get_color(files, &color);
			ft_printf("%s%s%s  ", color, files->name, RESET);
		}
		files = files->next;
	}
	if (code)
		ft_printf("\n");
}

void	print_ls(t_ctx *ctx, t_dir **dirs)
{
	t_dir	*dir;

	if (!dirs || !*dirs)
		return ;
	dir = *dirs;
	while (dir)
	{
		if (ctx->print_path || ctx->flags.ur_flag)
			ft_printf("%s:\n", dir->path);
		if (dir->files)
			print_files(ctx, dir->files);
		if (ctx->flags.ur_flag && dir->content)
		{
			ft_printf("\n");
			print_ls(ctx, &dir->content);
		}
		dir = dir->next;
		if (dir)
			ft_printf("\n");
	}
	ft_printf("\n");
}
