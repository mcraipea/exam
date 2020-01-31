#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    ft_putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
}

int     ft_atoi_spe(char *buffer, int *i)
{
    int         result = 0;
    int         virg = 0;
    int         neg = 0;

    while (buffer[*i] && buffer[*i] == ' ')
        *i += 1;
    if (buffer[*i] == '-')
    {
        neg += 1;
        *i += 1;
    }
    while (buffer[*i] && buffer[*i] >= '0' && buffer[*i] <= '9')
    {
        result = 10 * result + buffer[*i] - '0';
        *i += 1;
    }
    if (buffer[*i] == '.')
    {
        *i += 1;
        virg += 1;
    }
     while (buffer[*i] && buffer[*i] >= '0' && buffer[*i] <= '9')
        *i += 1;
    while (buffer[*i] && buffer[*i] == ' ')
        *i += 1;
    if (neg == 1)
        result *= -1;
    if (virg > 0)
        result += 1;
    return (result);
}

int     main(int argc, char **argv)
{
    FILE        *fd;
    char        buffer[1024];
    int         ret;

    int         w = 0;
    int         h = 0;
    char        c;
    char        **tab;
    int         i = 0;

    char        contour;
    int         x_pos;
    int         y_pos;
    int         width;
    int         height;

    if (argc != 2)
    {
        ft_putstr("Error: argument\n");
        return (1);
    }
    else
    {
        if ((fd = fopen(argv[1], "r")) == NULL)
        {
            ft_putstr("Error: file open\n");
            return (1);
        }
        if ((ret = fread(buffer, sizeof(char), 1023, fd)) < 0)
        {
            ft_putstr("Error: file read\n");
            return (1);
        }
        buffer[ret] = '\0';
        ft_putstr(buffer); //a supprimer
        printf("\n");
        w = ft_atoi_spe(buffer, &i);
        h = ft_atoi_spe(buffer, &i);
        c = buffer[i];
        i += 2;
        tab = malloc(h * sizeof(char*));
	    for (int j = 0; j < h; j++)
	    {
	    	tab[j] = malloc(w * sizeof(char));
	    	for (int k = 0; k < w; k++)
		    	tab[j][k] = c;
	    }
        while (buffer[i])
        {
            contour = buffer[i++];
            x_pos = ft_atoi_spe(buffer, &i);
            y_pos = ft_atoi_spe(buffer, &i);
            width = ft_atoi_spe(buffer, &i) + x_pos;
            height = ft_atoi_spe(buffer, &i) + y_pos;
            c = buffer[i++];
            printf("contour = %c  x_pos = %i y_pos = %i width = %i height = %i char = %c\n", contour, x_pos, y_pos, width, height, c);
            if (buffer[i] == '\n')
                i++;
            if (contour == 'R')
            {
                for (int j = y_pos; j < height; j++)
	            {
                    for (int k = x_pos; k < width; k++)
                        tab[j][k] = c;
                }
            }
            else if (contour == 'r')
            {
                for (int j = y_pos; j < height; j++)
	            {
                    for (int k = x_pos; k < width; k++)
                        if (j == y_pos || j == height - 1 || k == x_pos || k == width - 1)
                            tab[j][k] = c;
                }
            }
        }
        for (int j = 0; j < h; j++)
	    {
            ft_putstr(tab[j]);
		    ft_putstr("\n");
	    }
    }
    return (0);
}