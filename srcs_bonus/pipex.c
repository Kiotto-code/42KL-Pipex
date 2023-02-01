/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:00:15 by yichan            #+#    #+#             */
/*   Updated: 2023/02/01 13:45:09 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <stdio.h>
/*
H - here_doc
I - input;
O - output;loca
*/

void	executer(char *cmd, char *envp[])
{
	int		i;
	char	**command;
	char	**paths;
	char	*object;

	command = ft_split(cmd, ' ');
	paths = getpath(envp);
	if (paths == NULL)
		ft_perror("ERROR");
	i = 0;
	while (paths[i])
	{
		object = connector(paths[i], '/', command[0]);
		if (access(object, F_OK) == 0)
		{
			if (execve(object, command, envp) == -1)
				ft_perror("ERROR");
		}
		free(object);
		i ++;
	}
	strclear(command);
	strclear(paths);
	ft_perror("ERROR: command not found");
}
/*strcmp to check the line equal to limiter(block)*/
/*nodup is needed if written inside the fd[1] directly*/

void	ins_limiter(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	ft_putstr_fd("pipe heredoc>", 1);
	while (1)
	{
		line = ft_strtrim(get_next_line(0), "\n");
		if (!line)
			break ;
		if (ft_strcmp(limiter, line) == 0)
		{
			close(fd[1]);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("pipe heredoc>", 1);
		show_heredoc(line, fd);
		free(line);
	}
	free(line);
	close(fd[1]);
	perror("ERROR");
}

void	here_doc(int ac, char *av[])
{
	int	fd[2];
	int	pid;

	if (ac < 6)
		ft_error("ERROR: wrong argument numbers");
	if (pipe(fd) == -1)
		perror("ERROR");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR");
	if (pid == 0)
		ins_limiter(fd, av[2]);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_perror("ERROR");
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

/* 
STDIN_FILENO == 0;
STDOUT_FILENO == 1;
*/

void	command_executing(char *cmd, char *envp[])
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		ft_perror ("ERROR");
	pid = fork();
	if (pid == -1)
		ft_perror("ERROR");
	if (pid == 0)
	{
		close (fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_perror("ERROR");
		close(fd[1]);
		executer(cmd, envp);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_perror("ERROR");
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	pipex(int ac, char **av, char**envp)
{
	int		num;
	pid_t	fd_in;
	pid_t	fd_out;

	if (!ft_strcmp(av[1], "here_doc"))
	{
		num = 3;
		here_doc(ac, av);
		fd_out = fileopen((av[ac -1]), 'h');
	}
	else
	{
		num = 2;
		fd_in = fileopen(av[1], 'I');
		fd_out = fileopen(av[ac -1], 'O');
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_perror("ERROR");
	}
	while (num < ac - 2)
		command_executing(av[num++], envp);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR");
	executer(av[ac - 2], envp);
}
