/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 21:46:04 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_struct(t_data *data, char **env)
{
	(void)env;
	data->fork = 1;
	data->previous = -1;
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (ft_free_tab(data->tab), 1);
	return (0);
}

t_data	*starton(void)
{
	static t_data	data = {0};

	return (&data);
}

int	valid_syntax(char **input, t_data *data)
{
	char	*tmp;

	if (quotes(*input))
		return (ft_printf("quote fail\n"), free(*input), 1);
	if (syntax(*input))
		return (ft_printf("syntax error\n"), free(*input), 1);
	data->var_name = NULL;
	data->var_value = NULL;
	if (ft_strchr(*input, '$'))
	{
		tmp = *input;
		*input = ft_expand(tmp, data);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	data = starton();
	(void)argv;
	(void)argc;
	(void)env;
	data->env_copy = create_env(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	while (1)
	{
		input = readline("minisheu> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		// yassine
		negatif(input);
		if (valid_syntax(&input, data))
			continue ;
		input = parse_input(input);
		if (!input)
			exit(1);
		if (here_doc(data, input))
			return (1);
		data->tab = ft_split(input, "|");
		data->nbcmd = ft_strlen_total(input, "|");
		free(input);
		if (init_struct(data, data->env_copy))
			return (1);
		ft_pipex(data, data->tab, &data->env_copy);
		for (int i = 0; i < data->nb_hd; i++)
		{
			free(data->docs[i].del);
			close(data->docs[i].fd[0]);
		}
		if (data->nb_hd)
			free(data->docs);
		ft_free_tab(data->tab);
	}
	ft_free_tab(data->env_copy);
	return (0);
}
