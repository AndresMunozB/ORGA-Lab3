#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct path
{
	Block* blocks;
}Path;

typedef	struct block
{
	int* words;
}Block;


typedef struct cache
{
	Path* paths;
}Cache;

#endif
