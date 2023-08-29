/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:56:31 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/28 23:31:27 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **arg, char ***env)
{
	(void)env;
	if (arg[0] && arg[1])
	{
		ft_printf("bash: cd: too many arguments\n");
		return (1);
	}
	else if (!arg[0])
		return (chdir(getenv("HOME")));
	else if (arg[0] && chdir(arg[0]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
