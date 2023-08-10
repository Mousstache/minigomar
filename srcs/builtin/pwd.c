/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:02:35 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/08 20:12:25 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 300

int	ft_pwd(char **arg, char ***env)
{
	char	cwd[BUFFER_SIZE];

	(void)env;
	(void)arg;
	if (getcwd(cwd, BUFFER_SIZE) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("bash");
		return (1);
	}
	return (0);
}
