#include <fcntl.h>  // open(), clone()
#include <unistd.h>  // read(), write()
#include <stdlib.h>  // malloc(), free()
#include <stdio.h>  // debug

char	ground;
char	rock;
char	box;

int	get_size_of_argu(char *map_file_name, int *length_of_parsed_array)
{
	int	fd;
	int	size_argu;
	char	buff;

	size_argu = 0;
	fd = open(map_file_name, O_RDONLY);
	read(fd, length_of_parsed_array, 1);
	*length_of_parsed_array -= '0';
	while (read(fd, &buff, 1) != 0)
		size_argu++;
	close(fd);
	return (size_argu + 1);
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

void	make_1D_to_2D(char *raw_m_data, int **parsed_m_data, int size_argu)
{
	write(1, raw_m_data, size_argu);
			
	ground = raw_m_data[1];
	rock = raw_m_data[2];
	box = raw_m_data[3];

	int	i = 0;
	int	j = 0;

	
	raw_m_data += 5;
		
	while (i < 5)
	{
		while (*raw_m_data != '\n')
		{
			if (*raw_m_data == ground)
			{
				parsed_m_data[i][j] = 1;
			}
			else if(*raw_m_data == rock)
			{
				parsed_m_data[i][j] = 0;
			}
			//printf("what is raw_data? : %d, %d --> %d \n", i, j, parsed_m_data[i][j]);
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

	int	length_of_parsed_array;
	int	**parsed_array;
	int	i;

	n = 2;
	if (argc < 2)
	{
		//read(0, abc, 100);
					// should i find squar with it??
	}

	//else if(argc >= 2)
	//{
		//while (n <= 9)
		//if (1 == 1)
		//{
		// get size of raw data to malloc
			size_argu = get_size_of_argu(argv[n - 1], &length_of_parsed_array);
			
			raw_map_data_array = (char *)malloc(sizeof(char) * size_argu);
			if(raw_map_data_array != NULL)
				printf("malloc1 OK\n");

			// wtf, what's wrong
			//parsed_array = (int **)malloc(sizeof(int *) * length_of_parsed_array * length_of_parsed_array);
			printf("length..: %d, \n", length_of_parsed_array);
			
			parsed_array = (int **)malloc(sizeof(int *) * 5 * 5);
			if(parsed_array != NULL)
				printf("malloc2 OK\n");
			i = 0;
			while (i < 5)
				parsed_array[i++] = (int *)malloc(sizeof(int) * 5);
			if(parsed_array != NULL)
				printf("malloc3 OK\n");
		// push argu data into array
			push_data_into_array(argv[n - 1], raw_map_data_array);
		// make 1D array to 2D array, modify contents
			make_1D_to_2D(raw_map_data_array, parsed_array, size_argu);

		// check final array okay?
			printf("\n\n final data ...: %d", parsed_array[3][4]);
			printf("\n\n final data ...: %d", parsed_array[3][3]);		
		// check final array okay? : YES		



		//	get_map(argv[n - 1]);

	//		find_squar();
	//		print_squar();
	//		
			free(raw_map_data_array);
			i = 0;
			//while (i < 5)
			//	free(*parsed_array);
			//free(parsed_array);
			n++;
		//}
	//}

	return (0);
}
