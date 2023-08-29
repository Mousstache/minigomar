/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/29 19:49:11 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	valid_syntax(char *input, t_data *data)
{
	if (quotes(input))
		return (ft_printf("quote fail\n"), free(input), 1);
	if (syntax(input))
		return (ft_printf("syntax error\n"), free(input), 1);
	data->var_name = NULL;
	data->var_value = NULL;
	return (0);
}

char	*posquote(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == 34)
		{
			i++;
			while (input[i] && input[i] != 34)
			{
				if (input[i] == 39)
					input[i] *= -1;
				else if (input[i] == -39)
					input[i] *= -1;
				i++;
			}
		}
		else if (input[i] == 39)
		{
			i++;
			while (input[i] && input[i] != 39)
			{
				if (input[i] == 34)
					input[i] *= -1;
				else if (input[i] == -34)
					input[i] *= -1;
				i++;
			}
		}
		i++;
	}
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;
	int		i;

	data = starton();
	(void)argv;
	(void)argc;
	data->env_copy = create_env(env, 0);
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
		negatif(input);
		if (valid_syntax(input, data))
			continue ;
		positif(input);
		input = parse_input(input);
		input = posquote(input);
		input = ft_expandd(input, data);
		if (!*input)
		{
			free(input);
			continue ;
		}
		input = posquote(input);
		negatif(input);
		if (!input)
			exit(1);
		if (here_doc(data, input))
			return (1);
		// negatif(input);
		printf("%s\n", input);
		printf("nbcmd %d\n", data->nbcmd);
		data->tab = ft_split(input, "|");
		data->nbcmd = ft_strlen_total(input, "|");
		// positif(input);
		free(input);
		if (init_struct(data, data->env_copy))
			return (1);
		ft_pipex(data, data->tab, &data->env_copy);
		i = -1;
		while (++i < data->nb_hd)
		{
			free(data->docs[i].del);
			close(data->docs[i].fd[0]);
		}
		if (data->nb_hd)
			free(data->docs);
		ft_free_tab(data->tab);
		// fprintf(stderr, "STATUS FIN DE OBOUCLE = %i\n", data->status);
	}
	ft_free_tab(data->env_copy);
	return (0);
}
