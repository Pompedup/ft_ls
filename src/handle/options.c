/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:40:12 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 17:16:09 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			options(char *str, int options)
{
	char *pos;

	while (*str)
	{
		if ((pos = ft_strchr(OPTIONS, *str)))
		{
			if (options | 1 << (pos - OPTIONS))
				options += 1 << (pos - OPTIONS);
		}
		else
		{
			ft_printf(USAGE, *str, OPTIONS);
			exit(0);
		}
		str++;
	}
	return (options);
}
