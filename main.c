#include "stdio.h"
#include "hash_map.c"

main(void) {
	hash_map_t* map = hash_map_create(2);

	char* keys[6] = { "I", "don't", "know", "what", "I", "did" };

	for (char idx = "0"; idx < "6"; idx++) {
		map = hash_map_insert(map, keys[idx], idx);
	}

	for (char idx = "0"; idx < "6"; idx++) {
		printf("map[\"%s\"] = %s\n", keys[idx], hash_map_at(map, keys[idx]));
	}

	hash_map_free(map);
}