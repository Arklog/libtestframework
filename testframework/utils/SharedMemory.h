//
// Created by pierre on 27/02/23.
//

#ifndef LIBTESTFRAMEWORK_SHAREDMEMORY_H
#define LIBTESTFRAMEWORK_SHAREDMEMORY_H

#include "testframework/Global/output.h"
#include <cerrno>
#include <cstring>
#include <semaphore>
#include <sys/shm.h>

template <typename T> class SharedMemory {
  private:
	std::binary_semaphore shsemaphore;
	T *shared_memory;
	int id;

  public:
	SharedMemory();
	~SharedMemory();

	T get();

	void set(T val);
};

template <typename T> void SharedMemory<T>::set(T val) {
	shsemaphore.acquire();
	*shared_memory = val;
	shsemaphore.release();
}

template <typename T> SharedMemory<T>::~SharedMemory() { shmdt(shared_memory); }

template <typename T> T SharedMemory<T>::get() {
	shsemaphore.acquire();
	T retv = *shared_memory;
	shsemaphore.release();
	return retv;
}

template <typename T>
SharedMemory<T>::SharedMemory()
	: shsemaphore(1), shared_memory(nullptr), id(0) {
	id = shmget(0, sizeof(T), IPC_CREAT | IPC_EXCL | 0660);
	if (id < 0) {
		print_error("SharedMemory: failed to create segment:", strerror(errno));
		_Exit(1);
	}
	shared_memory = (T *)shmat(id, nullptr, 0);
	if (shared_memory == (void *)-1) {
		print_error("ShareMemory: failed to load segment:", strerror(errno));
		_Exit(1);
	}
	std::memset(shared_memory, 0, sizeof(T));
}

#endif // LIBTESTFRAMEWORK_SHAREDMEMORY_H
