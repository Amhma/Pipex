/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_multi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:56:00 by amahla            #+#    #+#             */
/*   Updated: 2022/05/09 14:14:09 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*get_next_line_multi(int fd)
{
	static char		*save[1024];
	char			*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_str_temp(save[fd], fd);
	if (!save[fd])
		return (NULL);
	line = ft_str_to_print(save[fd]);
	save[fd] = ft_str_to_save(save[fd]);
	return (line);
}
