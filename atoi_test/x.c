#include <stdio.h>
#include <unistd.h>





int	atoi_(char *str)
{
	int	data;

	data = 0;
	while(*str != '\0')
	{
		data = data * 10 + *str - '0';
		str++;
	}
	return (data);
		

}





int	main(void)
{
	char	*str = "12";

	printf("%d\n\n", atoi_(str));

	return 0;
}
