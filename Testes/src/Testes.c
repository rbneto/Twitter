/*
 * filaPrioridades.c
 *
 *  Created on: Jun 2, 2015
 *      Author: rafaelbiffineto
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define PARENT(pos) ((pos+1)/2)-1
#define LEFT(pos) (pos+1)*2-1
#define RIGHT(pos) (pos+1)*2

#define EMPTY_HEAP 		-1
#define ROOT 			0
#define INVALID_KEY 		-2
#define INVALID_POSITION 	-3
#define SUCCESS			1

void swap(int *vector, int i, int j) {
	int aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

void min_heapify(int *vector, int position, int heapsize) {
	int leftId, rightId, smallestId;

	leftId = LEFT(position);
	rightId = RIGHT(position);
	smallestId = position;

	if (leftId < heapsize && vector[leftId] < vector[smallestId])
		smallestId = leftId;
	if (rightId < heapsize && vector[rightId] < vector[smallestId])
		smallestId = rightId;

	if (smallestId != position) {
		swap(vector, smallestId, position);
		min_heapify(vector, smallestId, heapsize);
	}
}

void build_min_heap(int *vector, int heapsize) {
	int i;
	for (i = floor(heapsize/2)-1; i >= 0; i--) {
		min_heapify(vector, i, heapsize);
	}
}

int minimum(int *vector, int heapsize) {
	if (heapsize < 1) {
		return EMPTY_HEAP;
	}

	return vector[ROOT];
}

int extract_min(int **vector, int *heapsize) {
	if (*heapsize < 1) {
		return EMPTY_HEAP;
	}

	int value = (*vector)[ROOT];
	swap(*vector, ROOT, (*heapsize)-1);
	(*heapsize)--;
	(*vector) = (int *) realloc(*vector,
			sizeof(int) * (*heapsize));
	min_heapify(*vector, ROOT, *heapsize);

	return value;
}

int decrease_key(int *vector, int heapsize, int position, int newkey) {
	if (newkey < 0) {
		return INVALID_KEY;
	}

	if (position > heapsize-1) {
		return INVALID_POSITION;
	}

	if (newkey >= vector[position]) {
		return INVALID_KEY;
	}

	vector[position] = newkey;
	while (PARENT(position) >= ROOT &&
		   vector[PARENT(position)] > vector[position]) {
		swap(vector, PARENT(position), position);
		position = PARENT(position);
	}

	return SUCCESS;
}

int insert(int **vector, int *heapsize, int key) {
	*vector = (int *) realloc(*vector, sizeof(int) *
			((*heapsize)+1));
	(*vector)[*heapsize] = INT_MAX;
	(*heapsize)++;

	return decrease_key(*vector, *heapsize, (*heapsize)-1, key);
}

void print(int *vector, int n) {
	int i;

	for (i = 0; i < n; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");
}

int *produce_random_vector(int n) {
	int i;
	int *vector = (int *) malloc(sizeof(int) * n);

	srand(time(NULL));

	for (i = 0; i < n; i++) {
		vector[i] = rand() % 1000;
	}

	return vector;
}

int main(int argc, char *argv[]) {
	int *vector = NULL;
	int heapsize = 0;

	insert(&vector, &heapsize, 7);
	insert(&vector, &heapsize, 6);
	insert(&vector, &heapsize, 5);
	insert(&vector, &heapsize, 4);
	insert(&vector, &heapsize, 3);
	insert(&vector, &heapsize, 2);
	insert(&vector, &heapsize, 1);
	print(vector, heapsize);

	decrease_key(vector, heapsize, 6, 0);
	print(vector, heapsize);

	printf("min value: %d\n", extract_min(&vector, &heapsize));
	print(vector, heapsize);

	free(vector);

	return 0;
}
