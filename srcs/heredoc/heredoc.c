/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:15:00 by maheraul          #+#    #+#             */
/*   Updated: 2023/08/11 20:37:09 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// << avion ls << bateau -R | cat << terre
// here[0] = {
// 	.delim = "avion"
// 	.fd[2];
// }
// here[1] = {
// 	.delim = "bateau"
// 	.fd[2];
// }
// here[2] = {
// 	.delim = "terre"
// 	.fd[2];
// }
//printf("STR = %s\n", str);

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_hd)
		{
			close(data->docs->fd[1]);
			close(data->docs->fd[0]);
			if (data->docs->del != NULL)
				free(data->docs->del);
		}
		free(data->docs);
		data->stop = true;
		exit(130);
	}
}

int	count_hd(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			n++;
		i++;
	}
	return (n);
}

char *next_word(char *str)
{
	int i;
	char *del;

	int len = 0;
	i = 0;
	while(str && str[i] && (str[i] == ' ' || str[i] == '\t' ))
		i++;
	while(str && str[i] && str[i] != ' ' && str[i] != '\t')
	{
		i++;
		len++;
	}
	del = ft_calloc(sizeof(char), len + 1);
	i = 0;
	len = 0;
	while(str && str[i] && (str[i] == ' ' || str[i] == '\t' ))
		i++;
	while(str && str[i] && str[i] != ' ' && str[i] != '\t')
		del[len++] = str[i++];
	return(del);
}
char	*del_is(t_doc *doc, char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	t_data *data = starton();
	while (n < data->nb_hd)
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			doc[n].index = n;
			doc[n].del = next_word(&str[i+2]);
			pipe(doc[n].fd);
			n++;
		}
		i++;
	}
	return (0);
}

void	child_hd(char *del, int fd1) // ecrire dans le pipe
{
	char	*line;

	signal(SIGINT, &exit_hd);
	while (1)
	{
		line = readline("> "); //stocker la ligne
		if (!line ||!ft_strcmp(line, del))// break si entree
			break ;
		ft_putendl_fd(line, fd1); //ecrire dans le pipe 1
		free(line);
	}
	close(fd1); //fermer le pipe ecriture
	// exit(0);
}

bool	here_doc(t_data *data, char *str)
{
	int i;
	t_doc *doc;
	pid_t pid;

	i = 0;
	data->nb_hd = count_hd(str);
	if (data->nb_hd == 0)
		return (false);
	doc = ft_calloc(sizeof(t_doc), data->nb_hd);
	if (!doc)
		return (true);
	del_is(doc ,str);
	i = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		while(i < data->nb_hd)
		{
			close(doc[i].fd[0]);
			child_hd(doc[i].del, doc[i].fd[1]);
			free(doc[i].del);
			i++;
		}
		free_arg(2, 0, 0, str, doc);
		exit(0);
	}
	else if (pid > 0)
	{
		i = 0;
		while(i < data->nb_hd)
			close(doc[i++].fd[1]);
	}
	waitpid(pid, 0, 0);
	signal(SIGINT, &ctrlc);
	data->docs = doc;
	return (data->stop);
}
