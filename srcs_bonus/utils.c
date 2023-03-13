/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:48:29 by yichan            #+#    #+#             */
/*   Updated: 2023/03/14 03:47:23 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*get_env_val(char **envp, char *key)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
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
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
		{
			func();
			ft_error(ft_strjoin("no such file or directory: ", path), 1);
			// ft_perror(path);
		}
	}
	else if (flag == 'O')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'h')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		ft_perror(path);
	return (fd);
}

void	arrclear(char **str)
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
