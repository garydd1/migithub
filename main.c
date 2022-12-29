#include <stdio.h>
// int ft_strlen(char *str);
// char    *ft_toupper(char *str);
#include "libstr.h"

int main(void)
{
    char    str[] = "Hola Mi Al8oha";
    printf("str len : %d: ", ft_strlen(str));
    printf("\nstr mayous: %s: ", ft_toupper(str));
    return (0);
}
