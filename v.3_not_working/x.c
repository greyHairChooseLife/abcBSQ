#include <fcntl.h>  // open(), clone()
#include <unistd.h>  // read(), write()
#include <stdlib.h>  // malloc(), free()
#include <stdio.h>  // debug

char	ground;
char	rock;
char	box;

int	atoi_(char *str)
{
	int	nbr;

	nbr = 0;
	while (*str != '\0')
	{
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return (nbr);
}

int	get_size_of_argu(char *map_file_name, int *length_of_parsed_array)
{
	int	fd;
	int	size_argu;
	char	buff[100];
	char	buff_core[1];
	char	*p_buff;
	int	i;

	
	//read(fd, length_of_parsed_array, 1);
	//*length_of_parsed_array -= '0';


	p_buff = buff;
	size_argu = 0;
	fd = open(map_file_name, O_RDONLY);

	i = 0;
	while (read(fd, p_buff, 1) != 0)
	{
		if (buff[i++] == '\n')
		{
			break;
		}
		p_buff++;
	}
	i -= 4;
	while (i > 0)
	{
		*buff_core = *buff;
		i--;
	}
	printf("buff_core : ___ %c\n", buff_core[0]);
	printf("buff_core : ___ %c\n", buff_core[1]);
	*length_of_parsed_array = atoi_(buff_core);

	printf("atoi return : ___ %d", *length_of_parsed_array);
	


	close(fd);

	fd = open(map_file_name, O_RDONLY);
	while (read(fd, buff, 1) != 0)
		size_argu++;
	close(fd);
	return (size_argu);
}

void	push_data_into_array(char *map_file_name, char *raw_map_data_array)
{
	int	fd;
	int	i;
	
	i = 0;
	fd = open(map_file_name, O_RDONLY);
	while (read(fd, raw_map_data_array, 1) != 0)
		raw_map_data_array++;
	close(fd);
}

void	make_1D_to_2D(char *raw_m_data, int **parsed_m_data, int size_argu, int length_of_parsed_array)
{
	write(1, raw_m_data, size_argu);
			
	ground = raw_m_data[1];
	rock = raw_m_data[2];
	box = raw_m_data[3];

	printf("ground : %c", ground);
	printf("rock : %c\n", rock);
	int	i = 0;
	int	j = 0;

// 아래의 숫자 5는 map raw data의 0번째 행이 개행까지 5칸이라는 제한 하의 숫자다. 즉 행의 길이가 1자리 숫자인 경우다. 
// 따라서 수식으로 바뀌어야 하는 값이다. 0번째 행을 분석해서 지도의 행 수가 2자리인지 3자리인지에 따라 달라져야한다.	
	while (*raw_m_data != '\n')
		raw_m_data++;
	raw_m_data++;
	printf("length of parsed array:   %d\n", length_of_parsed_array);
		
	while (i < length_of_parsed_array)
	{
		while (*raw_m_data != '\n')
		{
			printf("raw_m_data : %d     %c\n",j,  *raw_m_data);
			if (*raw_m_data == ground)
			{
				parsed_m_data[i][j] = 1;
			}
			else if(*raw_m_data == rock)
			{
				parsed_m_data[i][j] = 0;
			}
			raw_m_data++;
			j++;
		}
		raw_m_data++;
		j = 0;
		i++;
	}

	
}

int	main(int argc, char **argv)
{
	int	n;
	char	*raw_map_data_array;
	int	size_argu;

	int	length_of_parsed_array = 99;

	int	**parsed_array;
	int	i;

	if (argc < 2)
	{
		//read(0, abc, 100);
					// should i find squar with it??
	}
	else if(argc >= 2)
	{
		n = 2;
		while (n <= 3)
		{
		// get size of raw data to malloc
			size_argu = get_size_of_argu(argv[n - 1], &length_of_parsed_array);
			
			raw_map_data_array = (char *)malloc(sizeof(char) * size_argu);
			if(raw_map_data_array != NULL)
				printf("malloc1 OK\n");

			parsed_array = (int **)malloc(sizeof(int *) * length_of_parsed_array * length_of_parsed_array);
			if(parsed_array != NULL)
				printf("malloc2 OK\n");
			i = 0;
			while (i < length_of_parsed_array)
				parsed_array[i++] = (int *)malloc(sizeof(int) * length_of_parsed_array);
			if(parsed_array != NULL)
				printf("malloc3 OK\n");
		// push argu data into array
			push_data_into_array(argv[n - 1], raw_map_data_array);
		// make 1D array to 2D array, modify contents
			make_1D_to_2D(raw_map_data_array, parsed_array, size_argu, length_of_parsed_array);

			printf("\nprint below\n");
	
			printf("\n right here : %d", parsed_array[0][0]);
			printf("\n right here : %d", parsed_array[0][1]);
			printf("\n right here : %d", parsed_array[0][2]);		
			printf("\n right here : %d", parsed_array[0][3]);		
			printf("\n right here : %d\n", parsed_array[0][4]);		

	//		find_squar();
	//		print_squar();
	

			free(raw_map_data_array);
			i = 0;
			while (i < length_of_parsed_array)
				free(parsed_array[i++]);
			free(parsed_array);
			n++;
		}
	}

	return (0);
}
