#include "string.h"
#include "stdlib.h"
#include "assert.h"
#include "stddef.h"
#include "stdbool.h"
//Добавить ассерты для безопастности

typedef struct _hash_map_t hash_map_t;

typedef struct _hash_map_entry_t {
	char* key;
	char* value;
} hash_map_entry_t;

struct _hash_map_t {
	hash_map_entry_t* entries;
	size_t size;
};

inline hash_map_t* hash_map_insert(hash_map_t* map, const char* key, char* value);
inline hash_map_t* hash_map_expand(hash_map_t* map);
inline void hash_map_free(hash_map_t* map);
inline static size_t hash(char* key);
inline char* hash_map_at(hash_map_t* map, char* key);
inline bool hash_map_has_key(hash_map_t* map, char* key);
inline hash_map_t* hash_map_create(size_t size);

void hash_map_free(hash_map_t* map) {
	for (size_t idx = 0; idx < map->size; idx++) {
		if (map->entries[idx].key != NULL) {
			free(map->entries[idx].key);
		}
	}
	free(map->entries);
	free(map);
}

static size_t hash(char* key) {
	assert(key != NULL);
	size_t hash = 0x12345678;

	for (const char* c = key; *c != '\0'; c++) {
		hash ^= *c;
		hash *= 0x5bd1e995;
		hash ^= hash >> 15;
	}
	return hash;
}

hash_map_t* hash_map_create(size_t size) {
	hash_map_t* map = malloc(sizeof(hash_map_t));

	map->size = size;
	map->entries = calloc(map->size, sizeof(hash_map_entry_t));

	return map;
}

hash_map_t* hash_map_insert(hash_map_t* map, const char* key, char* value) {

	size_t idx = hash(key) % map->size;

	while (map->entries[idx].key != NULL) {
		idx += 1;
		if (idx == map->size) {
			return hash_map_insert(hash_map_expand(map), key, value);
		}
	}
	map->entries[idx].key = calloc(strlen(key) + 1, sizeof(char));
	map->entries[idx].value = value;

	return map;
}

static hash_map_t* hash_map_expand(hash_map_t* map) {
	hash_map_t* expanded = hash_map_create(map->size * 2);

	for (size_t idx = 0; idx < map->size; idx++) {
		if (map->entries[idx].key != NULL) {
			expanded = hash_map_insert(expanded, map->entries[idx].key, map->entries[idx].value);
		}
	}
	hash_map_free(map);
	return expanded;
}

bool hash_map_has_key(hash_map_t* map, char* key) {
	for (size_t idx = hash(key) % map->size; idx < map->size; idx++) {
		char* current = map->entries[idx].key;

		if (current == NULL) continue;
		if (!strcmp(current, key)) {
			return true;
		}
		return false;
	}
}

char* hash_map_at(hash_map_t* map, char* key) {
	for (size_t idx = hash(key) % map->size; idx < map->size; idx++) {
		char* current = map->entries[idx].key;

		if (current == NULL) continue;
		if (!strcmp(current, key)) {
			return map->entries[idx].value;
		}
		
	}
	assert(false);
	return 0;
}