#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef	struct block
{
	int* words;
	int lru;

}Block;

typedef struct group
{
	Block* blocks;
	int counter;
	int mru;

}Group;


typedef struct cache
{
	Group* groups;
	int wordsPerBlock;
	int blocksPerGroup;
	int numberGroups;
	int numberBlocks;
	int hit;
	int miss;
	char politics[10];
}Cache;

#endif
