#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VECTOR_MINIMUM_SIZE 6

Vector* CreateVector() {
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	vector->entities = (Entity*)malloc(sizeof(Entity) * VECTOR_MINIMUM_SIZE);
	vector->length = 0;
	vector->size = VECTOR_MINIMUM_SIZE;
	return vector;
}
void DeleteVector(Vector* vector) {
	free(vector->entities);
	free(vector);
}
void DeepDeleteVector(Vector* vector) {
	for (int i = 0; i < vector->length; i++) {
		free(vector->entities[i]);
	}
	DeleteVector(vector);
}





void VectorExpand(Vector* vector) {
	vector->size *= 2;
	vector->entities = (Entity*)realloc(vector->entities, sizeof(Entity) * vector->size);
}
void TryVectorExpand(Vector* vector) {
	if (vector->size <= vector->length) VectorExpand(vector);
}
void VectorShrink(Vector* vector) {
	vector->size /= 2;
	vector->entities = (Entity*)realloc(vector->entities, sizeof(Entity) * vector->size);
}
void TryVectorShrink(Vector* vector) {
	if (VECTOR_MINIMUM_SIZE < vector->size && vector->length < vector->size / 3) VectorShrink(vector);
}





bool CheckIndexRange(Vector* vector, const int index) {
	if (0 <= index && index < vector->length) return true;
	else return false;
}

void VectorInsert(Vector* vector, const Entity* entity) {
	TryVectorExpand(vector);
	vector->entities[vector->length++] = entity;
}
void VectorDeleteUnstable(Vector* vector, const int index) {
	if (!CheckIndexRange(vector, index)) return;
	vector->length--;
	if(0 < vector->length) vector->entities[index] = vector->entities[vector->length];
	TryVectorShrink(vector);
}
void VectorDeepDeleteUnstable(Vector* vector, const int index) {
	if (!CheckIndexRange(vector, index)) return;
	free(vector->entities[index]);
	vector->length--;
	if(0 < vector->length) vector->entities[index] = vector->entities[vector->length]; // same as VectorDeleteUnstable
	TryVectorShrink(vector);
}
void VectorDelete(Vector* vector, const int index) {
	if (!CheckIndexRange(vector, index)) return;
	vector->entities[index] = NULL;
	vector->length--;
	for (int i = index; i < vector->length; i++) { // shift every other entity
		vector->entities[i] = vector->entities[i + 1];
	}
	TryVectorShrink(vector);
}
void VectorDeepDelete(Vector* vector, const int index) {
	if (!CheckIndexRange(vector, index)) return;
	free(vector->entities[index]);
	vector->entities[index] = NULL; // same as VectorDelete
	vector->length--;
	for (int i = index; i < vector->length; i++) { // shift every other entity
		vector->entities[i] = vector->entities[i + 1];
	}
	TryVectorShrink(vector);
}
Vector* VectorMerge(Vector* vectorA, Vector* vectorB) {
	for (int i = 0; i < vectorB->length; i++) {
		VectorInsert(vectorA, vectorB->entities[i]);
	}
	DeleteVector(vectorB);
	return vectorA;
}

