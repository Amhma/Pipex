#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "get_next_line.h"


//===================================================================//
//						PARSE.C
//===================================================================//

void	free_array(char **arg);

void	error_write(char *line)
{
	unlink("here_doc");
	free(line);
	exit(EXIT_FAILURE);
}

void	clear_lst(t_list **cmd, int	*fd_file)
{
	close(fd_file[0]);
	close(fd_file[1]);
	ft_lstclear(cmd, &free_array);
	exit(EXIT_FAILURE);
}

int	open_heredoc(char *limiter)
{
	int		fd;
	int		wr;
	char	*line;

	fd = open("here_doc", O_CREAT | O_WRONLY, 0644);
	line = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (ft_strcmp(line, limiter) == 0 && ft_strlen(line) == ft_strlen(line) + 1
			&& line[ft_strlen(line) - 1] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		if (wr == -1)
		{
			perror("write ");
			error_write(line);
		}
		free(line);
	}
	close(fd);
	fd = open("here_doc", O_CREAT | O_RDONLY, 0644);
	free(line);
	return (fd);
}

void	open_file(int ac, char **av, int *fd_in, int *fd_out)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
	{
		*fd_in = open(av[1], O_RDONLY, 0644);	
		if (*fd_in == -1)
		{
			perror("open ");
			exit(EXIT_FAILURE);
		}
	}
	else
		*fd_in = open_heredoc(av[2]);
	if (ft_strcmp(av[1], "here_doc") != 0)
		*fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		*fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		if (ft_strcmp(av[1], "here_doc") != 0)
			unlink("here_doc");
		close(*fd_in);
		perror("open ");
		exit(EXIT_FAILURE);
	}
}

void	parse(int ac, char **av, t_list **cmd, int *fd_file)
{
	int	i;
	int	y;

	i = 2;
	y = 1;
	if (ft_strcmp(av[1], "here_doc") == 0)
		i++;
	open_file(ac, av, fd_file, fd_file + 1);
	while (i < ac - 1)
	{
		if ((ft_strcmp(av[1], "here_doc") == 0 && i == 3) || i == 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), fd_file[0], 0));
		else if (i == ac - 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), 0, fd_file[1]));
		else
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), 0, 0));
		if (ft_lstsize(*cmd) != y++)
			clear_lst(cmd, fd_file);
		i++;
	}
}

//==================================================================//
//					PROCESS.C
//==================================================================//

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
	if (ft_strstr(elem->arg[0], "/") && access(elem->arg[0], F_OK) == 0)
		path = ft_strdup(elem->arg[0]);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);	
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
	dup2(fd_file[0], 0);
	if (!elem->next)
		dup2(fd_file[1], 1);
	else
		dup2(fds[1], 1);
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

void	parent_process(t_list *elem, int pid, int *fd_file, int *fds)
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
}

void	process_pipex(t_list **cmd, int *fd_file, char **env)
{
	int		fds[2];
	int		pid;
	t_list	*elem;

	elem = *cmd;
	while (elem)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
		{
			perror("fork :");
			clear_lst(cmd, fd_file);
		}
		if (pid == 0)
		{
			child_process(elem, fd_file, fds, env);
			ft_lstclear(cmd, &free_array);
			exit(EXIT_FAILURE);
		}
		else
			parent_process(elem, pid, fd_file, fds);
		elem = elem->next;
	}
}

//================================================================//
//							PIPEX.C	
//================================================================//

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;
	int		fd_file[2];

	cmd = NULL;
	parse(ac, av, &cmd, fd_file);
	process_pipex(&cmd, fd_file, env);
	ft_lstclear(&cmd, &free_array);
	if (ft_strcmp(av[1], "here_doc") == 0)
		unlink("here_doc");
	return (0);
}
