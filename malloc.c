#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

/*
void	*malloc(size_t size)
{
}
*/

void	ini_pg_size(void *pg, size_t pg_size)
{
	memcpy(pg, (void *)pg_size, sizeof(pg_size));
}


size_t	get_block_size(void *block)
{
	size_t	block_size;

	block_size = 0;
	memcpy((void *)block_size, block, sizeof(size_t));
	return(block_size);
}


void	*get_new_page()
{
	int 	pg_size;
	void	*pg;

	pg_size = getpagesize();
	pg = mmap(NULL, pg_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ini_pg_size(pg, (size_t)pg_size);
	return pg;
}

/*
void	*allocate(void *pg, size_t size)
{
	size_t block_size;

	get_block_size(pg, size);
}
*/

//sizeof(size_t) = 8
//sizeof(int) = 4
int		main()
{
	void	*pg;
	size_t	block_size;

	pg = get_new_page();
	block_size = get_block_size(pg);
	printf("%zu\n", block_size);
	return(0);
}
