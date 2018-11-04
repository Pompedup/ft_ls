/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 12:56:50 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 16:11:06 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
********************************************************************************
**	Function: nb_line_file
**	----------------
**
**
**		nb_line: the number of lines to display
**		word_tot: the number of words to display
**	****
**		words_by_line: the number of words per line
**
**
**   returns: explain
********************************************************************************
*/

int		nb_line_file(int nb_lines, int word_tot)
{
	int	words_by_line;
	int	nb_word_full;

	words_by_line = word_tot/nb_lines + (word_tot % nb_lines != 0);
	nb_word_full = words_by_line * nb_lines;
	return (nb_lines - (nb_word_full - word_tot));
}

/*
********************************************************************************
**	Function: name
**	----------------
**		What it do
**
**		param: explain
**	****
**		var: explain
**
**   returns: explain
********************************************************************************
*/

void	sort_by_line(t_file **bgn, int repeat)
{
	t_file **move;
	t_file *tmp;
	int i;

	move = &((*bgn)->next);
	bgn = move;
	while (*move && *bgn && repeat)
	{
		i = 0;
		while (*move && i < repeat)
		{
			i++;
			move = &((*move)->next);
		}
		if (*move)
		{
			tmp = *move;
			*move = (*move)->next;
			tmp->next = *bgn;
			*bgn = tmp;
			bgn = &(tmp->next);
		}
		if (!*move)
		{
			bgn = &((*bgn)->next);
			if (bgn)
				move = bgn;
			repeat--;
		}
	}
}

/*
********************************************************************************
**	Function: repeat
**	----------------
**		Call display_name for all the name of elements from the chained list
**			file end put a new_line when it's necessary
**
**		folder: the folder to display
**		lines_full: the number of lines wich will be full
**		per_line: the number of file name to display per line
**	****
**		file: contain adress of the chained list to display
**		end_line: a variable to know when put a new line
**		i: an index to know how many files we display
**
**   returns: nothing
********************************************************************************
*/

void	repeat(t_folder *folder, size_t lines_full, size_t per_line)
{
	t_file	*file;
	size_t	end_line;
	size_t	i;

	end_line = per_line;
	i = 0;
	file = folder->files;
	while (file)
	{
		display_name(file->type, file->exec, folder->len_max, file->name);
		file = file->next;
		i++;
		if (per_line == 1 || i == end_line || !file)
		{
			end_line += per_line;
			if (lines_full)
				lines_full--;
			else
				end_line--;
			ft_printf("\n");
		}
	}
}

/*
********************************************************************************
**	Function: adjust
**	----------------
**		Calculate the number of element we will display by line
**			Then call sort_by_line and() repeat()
**
**		folder: the folder to display
**		len_col: the witdh of the terminal
**	****
**		tmp:	_first the number of name we can display per line
**				_second the number of name we will display per line
**		nb_lines: number of lines to print
**		lines_full: the number of line before decrement the number of words per
**			line
**
**   returns: nothing
********************************************************************************
*/

void	adjust(t_folder *folder, size_t len_col)
{
	size_t	tmp;
	size_t	nb_lines;
	size_t	lines_full;

	tmp = len_col / (folder->len_max + 1);
	if (!tmp)
	{
		tmp++;
		folder->len_max = 0;
	}
	nb_lines = folder->nb_files / tmp + (folder->nb_files % tmp > 0);
	tmp = folder->nb_files / nb_lines + (folder->nb_files % nb_lines > 0);
	sort_by_line(&folder->files, nb_lines - 1);
	lines_full = nb_line_file(nb_lines, folder->nb_files) - 1;
	repeat(folder, lines_full, tmp);
}
