#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putstr(char *str);
void	ft_putnbr(int nbr);

int	main(void)
{
	ft_putstr("")	
}
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr < -2147483647)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		nbr = nbr * -1;
		write(1, "-", 1);
	}
	if (nbr / 10 != 0)
	{
		ft_putnbr(nbr / 10);
	}
	c = (nbr % 10) + 48;
	write(1, &c, 1);
}
