/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:28:41 by amahla            #+#    #+#             */
/*   Updated: 2022/05/24 18:51:04 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_array(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}

char	*find_cmd(t_list *elem, char **env)
{
	char	*path;
	char	**env_path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	if (ft_strstr(elem->arg[0], "/") && access(elem->arg[0], F_OK) == 0)
		path = ft_strdup(elem->arg[0]);
	env_path = ft_split(env[i] + 5, ':');
	i = -1;
	while (!path && env_path[++i])
	{	
		path = ft_strjoin2(env_path[i], "/", elem->arg[0]);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_array(env_path);
	return (path);
}

void	child_process(t_list *elem, int *fd_file, int *fds, char **env)
{
	char	*path;

	path = find_cmd(elem, env);
	dup2(fd_file[0], STDIN_FILENO);
	if (!elem->next)
		dup2(fd_file[1], STDOUT_FILENO);
	else
		dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	close(fd_file[0]);
	close(fd_file[1]);
	execve(path, elem->arg, env);
	perror("execve ");
	close(0);
	close(1);
	close(2);
	if (path)
		free(path);
}

int	parent_process(t_list *elem, int pid, int *fd_file, int *fds)
{
	int	status;

	waitpid(pid, &status, 0);
	if (!elem->next)
	{
		close(fd_file[0]);
		close(fd_file[1]);
		close(fds[0]);
		close(fds[1]);
	}
	else
	{
		close(fd_file[0]);
		fd_file[0] = dup(fds[0]);
		close(fds[0]);
		close(fds[1]);
	}
	return (status);
}

void	process_pipex(t_list **cmd, int *fd_file, char **env, char *file_out)
{
	int		fds[2];
	int		pid;
	t_list	*elem;

	elem = *cmd;
	while (elem)
	{
		if (pipe(fds) == -1)
			clear_all(cmd, fd_file, file_out);
		pid = fork();
		if (pid == -1)
		{
			perror("fork :");
			clear_all(cmd, fd_file, file_out);
		}
		if (pid == 0)
		{
			child_process(elem, fd_file, fds, env);
			ft_lstclear(cmd, &free_array);
			exit(EXIT_FAILURE);
		}
		if (parent_process(elem, pid, fd_file, fds))
			clear_all(cmd, fd_file, file_out);
		elem = elem->next;
	}
}
