/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:40:55 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/02 14:54:43 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char    save[999999];
    char    buf[1];
    char    *line;

    int     i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    save[i] = '\0';
    while (read(fd, buf, 1) == 1)
    {
        save[i] = buf[0];
        save[i + 1] = '\0';
        if (save[i]=='\n')
            break ;
        ++i;
    }
    if (save[0] == '\0')
        return (NULL);
    line = malloc(i + 1);
    i = 0;
    while (save[i])
    {
        line[i] = save[i];
        ++i;
    }
    line[i] = '\0';
    return (line);

}
// gcc -Wall -Werror -Wextra -g3 -fsanitize=address -D BUFFER_SIZE=42  get_next_line/get_next_line.c
#include <stdio.h>
#include <fcntl.h>
int main(int ac, char **av)
{
    char    *str;
    int     fd;

    (void)ac;

    fd = open(av[1], O_RDONLY);

    str = get_next_line(fd);
    printf("res:%s\n", str);
    str = get_next_line(fd);
    printf("res:%s\n", str);

    close(fd);

    return (0);
}