#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    ft_putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
}

int check_digit(char c)
{
    if ((c>='0') && (c<='9')) 
		return 1;
    return 0;
}

int	check_char(char c)
{
	if (c < 48 && c > 57)
		return (1);
	return (0);
}

int     ft_atoi_spe(char *str, int *i)
{
    int         res = 0;
    int         neg = 1;

    while (str[*i] && str[*i] == ' ')
        *i += 1;
	if (check_char(str[*i]))
		return (-10000);
    if (str[*i] == '-')
	{
		*i += 1;
		neg = -1;
	}
	if (check_char(str[*i]))
		return (-10000);
	for (res = 0; str[*i] && check_digit(str[*i]); *i += 1)
        res = res * 10 + str[*i] - '0';
	if (check_char(str[*i]))
		return (-10000);
    if (str[*i] == '.')
        *i += 1;
	if (check_char(str[*i]))
		return (-10000);
   //for (decplace = 1.; str[*i] && isdigit(str[*i]); *i++, decplace *= 10.)
   //     res = res * 10. + (*str - '0');
	while (str[*i] && check_digit(str[*i]))
    	*i += 1;
	if (check_char(str[*i]))
		return (-10000);
    while (str[*i] && str[*i] == ' ')
        *i += 1;
    return (neg * res);
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
	int			x_pos_b;
    int         y_pos;
	int			y_pos_b;
    int         width;
    int         width_b;
    int         height;
    int         height_b;

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
        //parser la premiere ligne
        if ((w = ft_atoi_spe(buffer, &i)) <= 0 || w > 300 || w == -10000)
			return (1);
        if ((h = ft_atoi_spe(buffer, &i)) == 0 || h > 300 || h == -10000)
			return (1);
       	if ((c = buffer[i++]) < 33 || c > 126)
			return (1);
        while (buffer[i] && buffer[i] == ' ')
			i++;
		if (buffer[i] && buffer[i] != '\n')
			return (1);
		if (buffer[i] == '\n')
			i++;
        //malloc et creation du tableau
        tab = malloc(h * sizeof(char*));
	    for (int j = 0; j < h; j++)
	    {
	    	tab[j] = malloc(w * sizeof(char));
	    	for (int k = 0; k < w; k++)
		    	tab[j][k] = c;
	    }
        //dessiner les rectangles
        while (buffer[i])
        {
            //parser les infos lignes a lignes
            while (buffer[i] && buffer[i] == ' ')
				i++;
			if ((contour = buffer[i++]) != 'r' && contour != 'R')
				return (1);
            if ((x_pos = ft_atoi_spe(buffer, &i)) < -2148000 || x_pos > 2147000 || x_pos == -10000)
				return (1);
            if ((y_pos = ft_atoi_spe(buffer, &i)) < -2148000 || y_pos > 2147000 || y_pos == -10000)
				return (1);
            if ((width = ft_atoi_spe(buffer, &i) + x_pos) < -2148000 || width > 2147000 || width == -10000)
				return (1);
            if ((height = ft_atoi_spe(buffer, &i) + y_pos) < -2148000 || height > 2147000 || height == -10000)
				return (1);
            if ((c = buffer[i++]) < 33 || c > 126)
				return (1);
		//	printf("x = %i, y = %i, width = %i, height = %i, c = %c\n", x_pos, y_pos, width, height, c);
        	while (buffer[i] && buffer[i] == ' ')
				i++;
		//	printf("buffer = %c\n", buffer[i]);
			if (buffer[i] != '\0' && buffer[i] != '\n')
				return (1);
			if (buffer[i] == '\n')
				i++;
			x_pos_b = x_pos;
            if (x_pos < 0)
                x_pos = 0;
			y_pos_b = y_pos;
            if (y_pos < 0)
                y_pos = 0;
            width_b = width;
            if (width > w)
                width = w;
            height_b = height;
            if (height > h)
                height = h;
            //dessiner si grand R ou petit r
		//	printf("test\n");
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
                        if (j == y_pos_b || j == height_b - 1 || k == x_pos_b || k == width_b - 1)
                            tab[j][k] = c;
                }
            }
        }
        //desiner le tab
        for (int j = 0; j < h; j++)
	    {
            for (int k = 0; k < w; k++)
				write(1, &tab[j][k], 1);
		    ft_putstr("\n");
	    }
    }
    return (0);
}
