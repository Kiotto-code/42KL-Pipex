/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:48:29 by yichan            #+#    #+#             */
/*   Updated: 2023/03/04 22:04:13 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	**getpath(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void	show_heredoc(char *line, int *fd)
{
	if (line[ft_strlen(line)] != '\n')
		ft_strlcat(line, "\n", line[ft_strlen(line)]);
	if (write(fd[1], line, ft_strlen(line)) == -1)
		perror("ERROR");
	if (write(fd[1], "\n", 1) == -1)
		perror("ERROR");
}

char	*connector(char *s1, char medium, char *s2)
{
	char	*res;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+2));
	if (!res)
		return (NULL);
	ptr = res;
	while (*s1)
		*res++ = *s1++;
	*res++ = medium;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (ptr);
}

pid_t	fileopen(char *path, char flag)
{
	pid_t	fd;

	fd = -1;
	if (flag == 'I')
		fd = open(path, O_RDONLY);
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'h')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror("ERROR");
	return (fd);
}

void	strclear(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i ++;
	}
	free(str[i]);
}
