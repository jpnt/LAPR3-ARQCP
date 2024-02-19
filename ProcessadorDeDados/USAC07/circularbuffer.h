#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

typedef struct {
	int* buffer;
	int capacity;
	int count;
	int read_idx;
	int write_idx;
} CircularBuffer;

CircularBuffer* circularbuffer_create(int capacity);
void circularbuffer_destroy(CircularBuffer* cb);
int circularbuffer_is_full(CircularBuffer* cb);
int circularbuffer_is_empty(CircularBuffer* cb);
void circularbuffer_enqueue(CircularBuffer* cb, int value);
int circularbuffer_dequeue(CircularBuffer* cb);
void circularbuffer_print(CircularBuffer* cb);

#endif // !CIRCULARBUFFER_H
