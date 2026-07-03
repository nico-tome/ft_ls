/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debugg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 12:55:57 by ntome             #+#    #+#             */
/*   Updated: 2026/07/03 13:09:53 by ntome            ###   ########.fr       */
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
