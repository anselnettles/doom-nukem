#include "./includes/map_editor.h"

void read_file(char *file, char *buf, int size)
{
	int     fd;
    int     ret;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        tt_errors("read_map: open() fail.");
        exit(-1);
    }
    ret = read(fd, buf, size);
    if (ret <= 0)
    {
        tt_errors("read_map: read() fail.\nEmpty, invalid or inaccessible map file.");
        exit(-1);
    }
	close (fd);
    buf[ret] = '\0';
}

int main(int argc, char **argv)
{
	t_editor_images images;
	char    buf[4096 + 1];

	images = (t_editor_images){.buffer_rows = 0, .buffer_columns = 0};
	read_file(argv[1], buf, (8192 + 1));
	printf("read OK -->\n");
	printf("[1=OK, 0=FAIL] validate_buffer_format return: %d\n", validate_buffer_format(buf, &images));
	return (0);
}
