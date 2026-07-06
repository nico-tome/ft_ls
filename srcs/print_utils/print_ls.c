/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:34:14 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 22:49:27 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void	print_padd(int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		ft_printf(" ");
}

static void	print_long_file(t_file *file, t_padding *padd)
{
	char	*name;
	char	*group;
	char	*date;

	name = getpwuid(file->stat.st_uid)->pw_name;
	group = getgrgid(file->stat.st_gid)->gr_name;
	date = ctime(&file->stat.st_mtim.tv_sec);
	date[ft_strlen(date) - 9] = '\0';
	ft_printf("%c", get_file_type(file));
	print_permission(file);
	print_padd(padd->link - ft_get_int_size(file->stat.st_nlink));
	ft_printf("%u ", file->stat.st_nlink);
	print_padd(padd->name - ft_strlen(name));
	ft_printf("%s ", name);
	print_padd(padd->group - ft_strlen(group));
	ft_printf("%s ", group);
	print_padd(padd->size - ft_get_long_long_size((long long)file->stat.st_size));
	ft_printf("%l ", (long long)file->stat.st_size);
	print_padd(padd->date - ft_strlen(date));
	ft_printf("%s ", date + 4);
}

static void	print_emojie_file(t_file *file)
{
	char	type;

	type = get_file_type(file);
	if (type == 'd')
		ft_printf("📁 ");
	else if (type == '-')
	{
		if (file->stat.st_mode & ((S_IXUSR | S_IXGRP | S_IXOTH)))
			ft_printf("⚙️ ");
		else
			ft_printf("📃 ");
	}
	else if (type == 'l')
		ft_printf("🔗 ");
}

static void	print_file(t_ctx *ctx, t_file *file, t_padding *padd)
{
	char	*color;

	get_color(file, &color);
	if (ctx->flags.s_flag)
	{
		print_padd(padd->block - ft_get_int_size(file->stat.st_blocks / 2));
		ft_printf("%d ", file->stat.st_blocks / 2);
	}
	if (ctx->flags.l_flag)
		print_long_file(file, padd);
	if (ctx->flags.e_flag)
		print_emojie_file(file);
	if (ctx->flags.uq_flag)
		ft_printf("\"");
	ft_printf("%s%s%s", color, file->name, RESET);
	if (ctx->flags.uq_flag)
		ft_printf("\"");
	if (ctx->flags.l_flag || ctx->flags.one_flag)
		ft_printf("\n");
}

static void	print_files(t_ctx *ctx, t_file *files, int print_total)
{
	t_padding	padd;
	int			printed;

	padd = get_padding(ctx, files);
	if (print_total && (ctx->flags.l_flag || ctx->flags.s_flag))
		ft_printf("total %d\n", padd.total_size);
	while (files)
	{
		printed = check_print(files, &ctx->flags);
		if (printed)
			print_file(ctx, files, &padd);
		files = files->next;
		if (files && !ctx->flags.one_flag && !ctx->flags.l_flag && printed)
			ft_printf("  ");
	}
	if (!ctx->flags.one_flag && !ctx->flags.l_flag)
		ft_printf("\n");
}

void	print_ls(t_ctx *ctx, t_dir **files, t_dir **dirs)
{
	t_dir	*dir;

	if (files && (*files)->files)
		print_files(ctx, (*files)->files, 0);
	if (!dirs || !*dirs)
		return ;
	dir = *dirs;
	while (dir)
	{
		if (ctx->print_path || (ctx->flags.ur_flag && dir->files) || (ctx->flags.ur_flag && ctx->flags.l_flag))
			ft_printf("%s:\n", dir->path);
		if (dir->files)
			print_files(ctx, dir->files, 1);
		if (ctx->flags.ur_flag && dir->content)
		{
			ft_printf("\n");
			print_ls(ctx, NULL, &dir->content);
		}
		dir = dir->next;
		if (dir)
			ft_printf("\n");
	}
}
