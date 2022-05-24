/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:09:39 by amahla            #+#    #+#             */
/*   Updated: 2022/05/24 18:00:38 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;
	int		fd_file[2];

	if (ac == 5)
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
		ft_putendl_fd("./pipex file1 cmd1 cmd2 file2", 2);
	}
	return (0);
}
