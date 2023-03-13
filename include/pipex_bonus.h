/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:26:21 by yichan            #+#    #+#             */
/*   Updated: 2023/03/14 00:39:36 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/includes/libft.h"
# include <sys/wait.h>
// # include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

//utils.c
void	show_heredoc(char *line, int *fd);
void	ft_perror(char *str);
// void	ft_error(char *str);
void	pipex(int ac, char **av, char**envp);

// pipex.c
char	**getpath(char **envp);
char	*connector(char *s1, char medium, char *s2);
void	strclear(char **str);
pid_t	fileopen(char *path, char flag);

#endif