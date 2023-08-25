/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 01:27:25 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/14 00:08:35 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	printtab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		fprintf(stderr, "[%i]{%s}\n", i, tab[i]);
}

void	printstruct(t_cmd *cmds)
{
	for (int i = 0; cmds->arg[i]; i++)
	{
		if (i == 0)
		{
			fprintf(stderr, "CMD = {%s}\n", cmds->arg[0]);
			continue ;
		}
		if (i == 1)
			fprintf(stderr, "ARGS =");
		fprintf(stderr, "[%s]", cmds->arg[i]);
	}
	fprintf(stderr, "\n");
	ft_printlist(cmds->lst);
}

void	ft_perror(char *file)
{
	ft_printf("bash: %s: ", file);
	perror("");
}

void	error_cmd(char *cmd)
{
	if (!cmd)
		ft_printf(" : command not found\n");
	else
		ft_printf("%s: command not found\n", cmd);
}
