/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:10:21 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/17 18:58:18 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int type)
{
	char    *str;

    if (s1 == NULL && s2 == NULL)
        return (NULL);
    if (s1 == NULL)
        return (ft_strdup(s2));
    if (s2 == NULL)
        return (ft_strdup(s1));
    str = ft_strjoin(s1, s2);
    if (type == 1 || type == 3)
        free(s1);
    if (type == 2 || type == 3)
        free(s2);
    return (str);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		ii;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	ii = 0;
	while (s2[ii])
	{
		str[i] = s2[ii];
		i++;
		ii++;
	}
	str[i] = '\0';
	return (str);
}
