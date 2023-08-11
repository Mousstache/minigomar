/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:00:59 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 22:24:24 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
void	error_message_exit(char *str)
{
	ft_printf("bash: exit: %s: numeric argument required\n", str);
}

long long	ft_atoi_max(char *str)
{
	int					neg;
	int					i;
	unsigned long long	res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		neg *= -1;
		if (str[i] == '-')
			i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if (res > LL_MAX || (res > (LL_MAX + 1) && neg == -1))
			return (error_message_exit(str), 2);
	}
	return ((long long)res * neg);
}

int	ft_exit_error(char **arg)
{
	t_data		*data;
	long long	tmp;

	data = starton();
	tmp = ft_atoi_max(arg[1]);
	if (arg[2] && ft_is_num(arg[1]))
	{
		ft_printf("%s", "bash: exit: too many arguments\n");
		return (0);
	}
	else if (arg[1] && !ft_is_num(arg[1]))
	{
		printf("exit\n");
		ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
		free_arg(0, 2, 1, data->onecmd->arg, data->tab, &data->onecmd->lst);
		exit(2);
	}
	free_arg(0, 2, 1, data->onecmd->arg, data->tab, &data->onecmd->lst);
	exit((unsigned char)tmp);
}

int	ft_exit(char **arg, char ***env)
{
	t_data	*data;

	data = starton();
	if (data->nbcmd == 1)
		return (exit_one(arg));
	else if (data->nbcmd > 1)
		return (exit_fork(arg, *env));
	return (0);
}

void	dupclose(int fd[2])
{
	dup2(fd[0], STDOUT_FILENO);
	dup2(fd[1], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	exit_one(char **arg)
{
	t_data	*data;

	data = starton();
	if (!*arg || !arg[1])
	{
		dupclose(data->fddup);
		free_arg(0, 3, 1, data->tab, data->env_copy, data->onecmd->arg,
				&data->onecmd->lst);
		exit(0);
	}
	if (arg[1] && !ft_strcmp(arg[1], "--"))
	{
		if (!arg[2])
		{
			dupclose(data->fddup);
			free_arg(0, 3, 1, data->tab, data->env_copy, data->onecmd->arg,
					&data->onecmd->lst);
			exit(0);
		}
		else if (!ft_exit_error(arg + 1))
			return (0);
	}
	dupclose(data->fddup);
	ft_exit_error(arg);
	return (0);
}
