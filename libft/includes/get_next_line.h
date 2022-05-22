/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:30 by amahla            #+#    #+#             */
/*   Updated: 2022/05/09 14:24:34 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 32

//		get_next_line.c
char	*get_next_line(int fd);

//		get_next_line_multi.c
char	*get_next_line_multi(int fd);

//		get_next_char.c
char	*get_next_char(int fd);

//		get_next_line_utils1.c
char	*ft_str_to_save(char *save);
char	*ft_str_to_print(char *save);
char	*ft_str_temp(char *save, int fd);

//		get_next_line_utils2.c
void	*calloc_gnl(size_t count, size_t size);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlen_gnl(char const *str);
int		ft_strchr_nl(char *str);

//		get_next_char_utils.c
int		ft_strlen_gnc(char const *str);
void	ft_bzero_gnc(char *str);
void	*calloc_gnc(size_t count, size_t size);
char	*ft_strjoin_gnc(char *s1, char *s2, int *y);

#endif
