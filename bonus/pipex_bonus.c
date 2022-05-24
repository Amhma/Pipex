/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:16:26 by amahla            #+#    #+#             */
/*   Updated: 2022/05/24 17:16:47 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;
	int		fd_file[2];

	if ((ac >= 4 && ft_strcmp(av[1], "here_doc") != 0)
		|| (ac >= 5 && ft_strcmp(av[1], "here_doc") == 0))
	{
		cmd = NULL;
		parse(ac, av, &cmd, fd_file);
		process_pipex(&cmd, fd_file, env, av[ac -1]);
		ft_lstclear(&cmd, &free_array);
	}
	else
	{
		ft_putendl_fd("pipex: invalid input.", 2);
		ft_putstr_fd("Usage: ", 2);
		ft_putendl_fd("./pipex [ here_doc LIMITER | file1 ] cmd ... file2", 2);
	}
	return (0);
}
