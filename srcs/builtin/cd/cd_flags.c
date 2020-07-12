#include "shell42.h"
#include "builtin42.h"

void    ft_swap_flags(t_cd *flags, size_t l, size_t p)
{
    flags->l = l;
    flags->p = p;
}

int     ft_cd_flags(char **argv, t_cd *flags)
{
    int     i;  
    int     j;  

    i = 1;
	ft_swap_flags(flags, 1, 0);
    while (argv[i] && argv[i][0] == '-' && ft_strlen(argv[i]) != 1)
    {   
        j = 1;
        while (argv[i][j])
        {   
            if (argv[i][j] != 'L' && argv[i][j] != 'P')
                return (i);
            else if (argv[i][j] == 'L')
                ft_swap_flags(flags, 1, 0); 
            else if (argv[i][j] == 'P')
                ft_swap_flags(flags, 0, 1);
            else
                return (i);
            j++;
        }   
        i++;
    }   
    return (i);
}
