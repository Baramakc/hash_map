#include "stdio.h"
#include "hash_map.c"

main(void) {
	hash_map_t* map = hash_map_create(2);

	const char* keys[3] = { "What", "did?","my" };

	for (int idx = 0; idx < 3; idx++) {
		map = hash_map_insert(map, keys[idx], (char)idx);
	}

	for (int idx = 0; idx < 3; idx++) {
		printf("map[\"%s\"] = %s\n", keys[idx], hash_map_at(map, (char)keys[idx]));
	}

	hash_map_free(map);
}