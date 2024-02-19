#include <stdio.h>
#include <stdlib.h>
#include "circularbuffer.h"

CircularBuffer* circularbuffer_create(int capacity) {

	CircularBuffer* cb = (CircularBuffer *) malloc(sizeof(CircularBuffer));
	if (cb == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para a estrutura do buffer circular.\n");
		return NULL;
	}
	// The actual buffer/array
	cb->buffer = (int *) calloc(capacity, sizeof(int));
	if (cb->buffer == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para o buffer.\n");
		free(cb);
		return NULL;
	}
	cb->capacity = capacity;
	cb->count = 0;
	cb->read_idx = 0;
	cb->write_idx = 0;

	return cb;
}

void circularbuffer_destroy(CircularBuffer* cb) {
	free(cb->buffer);
	free(cb);
}

int circularbuffer_is_full(CircularBuffer* cb) {
	return cb->count == cb->capacity;
}

int circularbuffer_is_empty(CircularBuffer* cb) {
	return cb->count == 0;
}

int increment_and_wrap(int value, int length) {
	return (value + 1) % length;
}

void circularbuffer_enqueue(CircularBuffer* cb, int value) {
	cb->buffer[cb->write_idx] = value;

	cb->write_idx = increment_and_wrap(cb->write_idx, cb->capacity);

	if (cb->write_idx == cb->read_idx) {
		cb->read_idx = increment_and_wrap(cb->read_idx, cb->capacity);
	}

	if (cb->count < cb->capacity) {
		cb->count++;
	}

	//TESTE
	/* printf("Foi adicionado o valor: %d\n", value); */
	/* circularbuffer_print(cb); */
}

int circularbuffer_dequeue(CircularBuffer* cb) {
	if (circularbuffer_is_empty(cb)) {
		fprintf(stderr, "Erro: "
		"Não foi possível retirar o último elemento do buffer pois está vazio.\n");
		exit(1);
	}
	int dequeue_value = cb->buffer[cb->read_idx];

	cb->read_idx = increment_and_wrap(cb->read_idx, cb->capacity);

	if (cb->count > 0) {
		cb->count--;
	}

	return dequeue_value;
}

void circularbuffer_print(CircularBuffer* cb) {
	printf("CircularBuffer = {\n  buffer:");
	for (int i = 0; i < cb->capacity; i++) {
		printf(" %d", cb->buffer[i]);
	}
	printf("\n  capacity: %d\n" 
		"  count: %d\n" 
		"  read_idx: %d\n"
		"  write_idx: %d\n}\n",
		cb->capacity, cb->count, cb->read_idx, cb->write_idx);
}
