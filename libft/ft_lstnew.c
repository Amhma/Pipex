/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:31:18 by amahla            #+#    #+#             */
/*   Updated: 2022/05/23 15:41:24 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstnew(char **arg, int fd_in, int fd_out)
{
	t_list	*elem;

	if (!arg)
		return (NULL);
	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->arg = arg;
	elem->fd_in = fd_in;
	elem->fd_out = fd_out;
	elem->next = NULL;
	return (elem);
}
