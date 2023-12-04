#ifndef	__BINARY_SEARCH_VERBOSE_HEADER__
#define	__BINARY_SEARCH_VERBOSE_HEADER__

/**
 * The classic binary search algorithm implementation
 */
void *
binarysearch(
		const void *key, const void *vData, int n, int tilesize,
		int (*comparator)(const void *, const void *)
		);

#endif	/* __BINARY_SEARCH_VERBOSE_HEADER__ */
