/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:00:15 by yichan            #+#    #+#             */
/*   Updated: 2023/03/30 21:20:49 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <stdio.h>

/*strcmp to check the line equal to limiter(block)*/
/*nodup is needed if written inside the fd[1] directly*/

// void	ins_limiter(int *fd, char *limiter)
// {
// 	char	*line;

// 	limiter = ft_strjoin(limiter, "\n");
// 	close(fd[0]);
// 	while (1)
// 	{
// 		ft_putstr_fd("pipe heredoc>", 1);
// 		line = get_next_line(0);
// 		if (!line)
// 			ft_exit(EXIT_SUCCESS);
// 		if (ft_strcmp(limiter, line) == 0)
// 			break ;
// 		ft_putstr_fd(line, fd[1]);
// 		free(line);
// 	}
// 	close(fd[1]);
// 	free(line);
// 	ft_exit(EXIT_SUCCESS);
// }

/*
H - here_doc
I - input;
O - output;loca
*/

void	executer(char *cmd, char *envp[])
{
	char	**command;
	char	**paths;
	int		i;
	char	*object;

	command = ft_split(cmd, ' ');
	paths = ft_split(get_env_val(envp, "PATH="), ':');
	if (paths == NULL)
		ft_perror("ERROR");
	i = 0;
	while (paths[i])
	{
		object = connector(paths[i], '/', command[0]);
		if (access(object, F_OK) == 0)
		{
			if (execve(object, command, envp) == -1)
				ft_perror(ft_strjoin("command not found: ", command[0]));
		}
		free(object);
		i ++;
	}
	arrclear(paths);
	ft_perror(ft_strjoin("command not found: ", command[0]));
}

void	here_doc(int ac, char *av[])
{
	int	fd[2];
	int	pid;

	if (ac < 6)
		ft_error("ERROR: wrong argument numbers", 1);
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

void	file_executer(char *cmd, char *envp[])
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
		// if (dup2(fd[1], STDOUT_FILENO) == -1)
		// 	ft_perror("ERROR");
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
	int		fd_in;
	int		fd_out;

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
	// executer(av[ac - 2], envp);
	file_executer(av[ac - 2], envp);
	system("leaks -q pipex");
}
