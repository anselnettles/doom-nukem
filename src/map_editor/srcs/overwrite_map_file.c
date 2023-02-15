#include "../includes/map_editor.h"

/*
	Checks file access.
*/
static void	access_error(char *path)
{
	if (access(path, F_OK) == 0)
	{	
		if (access(path, R_OK) != 0)
			tt_errors("No READ permission to the file");
		if (access(path, W_OK) != 0)
			tt_errors("No WRITE permission to the file");
		if (access(path, X_OK) != 0)
			tt_errors("No EXECUTE permission to the file");
	}
	else
		tt_errors("File is not accessible at given path");
	//Enhance option: chmod, create...
}

/*
	Overwrites the entire map file at char *path.
*/
static void	overwrite_file_content(char *path, t_map *data, t_editor_images *images)
{
	FILE	*fp;
	int		i2;
	int		i1;
	int		i0;

	i2 = 0;
	i1 = 0;
	i0 = 0;
	fp = fopen(path, "w+");
	while(i2 < images->row1)
	{
		i1 = 0;
		while (i1 < images->column1)
		{
			i0 = 0;
			while (i0 < PARAM_COUNT)
			{
				fputc(data->map_temp[i2][i1][i0], fp);
				i0++;
			}
			i1++;
			if (i1 != images->column1)
				fputc(' ', fp);
		}
		fputc('\n', fp);
		i2++;
	}
	fclose(fp);
}

/*
	Function checks if file exists at given path. 
	If OK, overwrite file with ***arr
		else, error message

	Return: 1 on success, 0 on failure.
	
	Enhance: else -> chmod, create...
*/
int	overwrite_map_file(t_map *data, t_editor_images *images)
{
	char *path;

/*	Below how to reduce file management break chance
	// char path[100];
	// printf("%s\n", getcwd(path, 100));

	// getwd = root area?
	// if getcwd == getwd

	// if cwd != hardcoded char *path_exe
	// 	error, exit
*/	
	path = "./test_maps/default.txt";
	if (access(path, (F_OK | R_OK | W_OK | X_OK)) == 0)
	{
		overwrite_file_content(path, data, images);
		return (1);
	}
	else
		access_error(path);
	return (0);
}
