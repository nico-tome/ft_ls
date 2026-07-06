/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 02:06:42 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 19:59:30 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_int_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int	ft_get_long_long_size(long long int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int	ft_get_hexa_size(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		size++;
	}
	return (size);
}

int	ft_get_unsigned_size(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int	ft_get_ptr_size(void *ptr)
{
	int			size;

	if (!ptr)
		return (ft_strlen("(nil)"));
	size = 2;
	size += ft_get_ptr_in_hexa_size((uintptr_t)ptr);
	return (size);
}
