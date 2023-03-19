/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:33:25 by yichan            #+#    #+#             */
/*   Updated: 2023/03/19 19:08:57 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/*
EXIT-FAILURE == exit(1)
EXIT-SUCCESS == exit(0)
*/

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_exit(int stat)
{
	exit(stat);
}

/* 
error notice when not comply with checker 
OR null is return in essential variable 
*/

// void	ft_error(char *str)
// {
// 	ft_putendl_fd(str, 2);
// 	exit(EXIT_FAILURE);
// }
