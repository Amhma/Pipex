/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:25:32 by amahla            #+#    #+#             */
/*   Updated: 2022/05/24 16:33:57 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

//		pipex_parse_bonus.c
void	clear_all(t_list **cmd, int *fd_file, char *file_out);
void	parse(int ac, char **av, t_list **cmd, int *fd_file);

//		pipex_process_bonus.c
void	free_array(char **arg);
void	process_pipex(t_list **cmd, int *fd_file, char **env, char *file_out);

#endif
