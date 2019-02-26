/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:27:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 21:09:16 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
********************************************************************************
**	Function: del_t_error
**	----------------
**		Display one t_error, delete it and put the next at it place
**
**		current: the adress of the t_error to delete
**	****
**		to_free: save the adress we have to free
**
**   returns: nothing
********************************************************************************
*/

void	del_t_error(t_error **current)
{
	t_error *to_free;

	to_free = *current;
	*current = (*current)->next;
	ft_printf(UNEXIST_FILE, to_free->name);
	free(to_free);
}

/*
********************************************************************************
**	Function: del_t_errors
**	----------------
**		Call del_t_error until the list is clear
**
**		current: the adress of the first t_error to delete
**
**   returns: nothing
********************************************************************************
*/

void	del_t_errors(t_error **current)
{
	while (*current)
		del_t_error(current);
}

/*
********************************************************************************
**	Function: new_t_error
**	----------------
**		Create a t_error and initialise it
**
**		current: the adress of the first t_error of the list
**		name: the file name to save
**	****
**		next: save the adresse of the t_error to place next
**
**   returns: nothing
********************************************************************************
*/

void	new_t_error(t_error **current, char *name)
{
	t_error *next;

	while (*current && ft_strcmp((*current)->name, name) < 0)
		current = &((*current)->next);
	next = *current;
	if (!(*current = ft_memalloc(sizeof(t_error))))
		return ;
	(*current)->name = name;
	(*current)->next = next;
}
