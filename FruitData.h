#ifndef	__FRUIT_DATASTRUCTURE_HEADER__
#define	__FRUIT_DATASTRUCTURE_HEADER__

typedef struct FruitData {
	char *common;
	char *latin;
	int latinIndex;
} FruitData;


void printFuitWithID(const FruitData *element, int id);
void printDataPointerArray(
		FruitData * const *dataPtrArray, int datalength);
void printDataArray(const FruitData *dataArray, int datalength);


void searchInCommonName(const FruitData *fruitDataArray, int nFruits, char *key);
void searchInLatinName(FruitData * const *fruitDataPointers, int nFruits, char *key);

#endif	/* __FRUIT_DATASTRUCTURE_HEADER__ */
