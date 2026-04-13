#pragma once

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdexcept>

#ifdef _DEBUG
#define dbg(...) printf(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T, bool FREE_EN = false>
class Pool {
  T* cur;
  void *ptr;
  size_t size;
  static constexpr size_t PAGE = 4096;

public:
  Pool(size_t max_elems) : size((max_elems * sizeof(T) + PAGE - 1) & ~(PAGE - 1)) {
    ptr = mmap(NULL, size,
               PROT_READ | PROT_WRITE,
               MAP_PRIVATE | MAP_ANONYMOUS,
               -1, 0);
    if (ptr == MAP_FAILED) {
      throw std::runtime_error("Failed to allocate memory");
    }
    cur = reinterpret_cast<T*>(reinterpret_cast<char *>(ptr) + size);
    dbg("Mapped memory at %lx\n", reinterpret_cast<size_t>(cur));
  }

  ~Pool() {
    munmap(ptr, size);
    dbg("Unmapped memory at %lx\n", reinterpret_cast<size_t>(ptr));
  }

  __attribute__((always_inline))
  T* alloc() {
    dbg("Allocated element at %lx\n", reinterpret_cast<size_t>(cur - 1));
    return --cur;
  }

  __attribute__((always_inline))
  void free(T* ptr) {
    if constexpr (FREE_EN) {
      dbg("Freed element at %lx\n", reinterpret_cast<size_t>(ptr));
      if (ptr == cur) {
        ++cur;
      }
    }
  }
};
