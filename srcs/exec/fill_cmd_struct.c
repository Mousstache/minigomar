/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:40:06 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/12 22:39:58 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	chevron_comp(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "<"))
		return (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	return (0);
}

int	countarg(char **tab)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (tab[i])
	{
		if (chevron_comp(tab[i]))
		{
			i++;
			if (!tab[i])
				return (-1);
		}
		else
			size++;
		i++;
	}
	return (size);
}

t_cmd	*parse(char *str)
{
	static t_cmd	cmds = {0};
	t_list			*lst;
	char			**input;
	int				j;
	int				i;
	int				v;
	int				r;

	
	j = 0;
	i = 0;
	lst = 0;
	input = ft_split(str, " 	");
	if (!input)
		return (NULL);
	int len = countarg(input);
	if (len == -1)
		return (fprintf(stderr, "ambigous redirect\n"), &cmds);
	cmds.arg = ft_calloc(sizeof(char *), len + 1);
	if (!cmds.arg)
		return (ft_freetab(input), NULL);
	v = 0;
	while (input[i])
	{
		r = chevron_comp(input[i]);
		if (r)
		{
			ft_rediradd_back(&lst, ft_redirnew(ft_strdup(input[i + 1]), r, v));
			if (r == 4)
				v++;
			i++;
		}
		else
			cmds.arg[j++] = delete_quotes(positif(input[i]));
		i++;
	}
	ft_freetab(input);
	cmds.cmd = cmds.arg[0];
	cmds.lst = lst;
	return (&cmds);
}
