/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_alnum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:02:00 by ntome             #+#    #+#             */
/*   Updated: 2026/07/07 12:25:09 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_alnum(const char *s)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (ft_isalnum(s[i]))
			str[j++] = s[i];
		i++;
	}
	while(j <= i)
		str[j++] = '\0';
	return (str);
}
