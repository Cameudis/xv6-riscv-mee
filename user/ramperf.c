/*
 * ramperf.c
 * Copyright (C) 2025 cameudis <cameudis@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define KB 1024
#define MB (1024 * KB)
#define TEST_SIZE (32 * MB)  // 4MB 测试内存块大小

char buf[TEST_SIZE];

// uint64 ticks(void) {
//     uint64 xticks;
//     asm volatile("csrr %0, time" : "=r"(xticks));
//     return xticks;
// }

uint64 ticks(void) {
  return uptime();
}

void test_memset() {
    uint64 start, end;
    start = uptime();
    memset(buf, 0, TEST_SIZE);
    end = uptime();
    printf("memset time: %ld ticks\n", end - start);
}

void test_memcpy() {
    char *dst = (char *)malloc(TEST_SIZE);
    if (!dst) {
        printf("malloc failed\n");
        exit(1);
    }
    uint64 start, end;
    start = uptime();
    memcpy(dst, buf, TEST_SIZE);
    end = uptime();
    printf("memcpy time: %ld ticks\n", end - start);
    free(dst);
}

int main(void) {
    printf("Starting memory performance test on xv6-riscv...\n");
    test_memset();
    test_memcpy();
    exit(0);
}
