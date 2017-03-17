#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <inttypes.h>
#include <limits.h>
#ifdef __APPLE__
#include <stdint.h>
#else
#include <cstdint>
#endif

#define MAX_SHARD_SIZE 4294967296 // 4Gb
#define SHARD_MULTIPLES_BACK 4

uint64_t determine_shard_size(uint64_t file_size, int accumulator);
uint64_t shard_size(int hops);

int main(int argc, char **argv) {

    if (argc <= 1) {
        printf("usage: shard_size file_size");
        return 1;
    }

    uint64_t file_size = 0;
    sscanf(argv[1], "%"PRIu64, &file_size);

    if (strlen(argv[1]) > 20 || file_size < 1 || file_size > UINT64_MAX) {
        printf("Invalid file size.\n");
        return 0;
    }

    uint64_t shard_size = determine_shard_size(file_size, 0);

    int total_shards = ceil((double)file_size / shard_size);

    printf("File Size:    %"PRIu64"\n", file_size);
    printf("Shard Size:   %"PRIu64"\n", shard_size);
    printf("Total Shards: %d\n", total_shards);

    return 0;
}

uint64_t shard_size(int hops)
{
    return (8  * (1024 * 1024)) * pow(2, hops);
};

uint64_t determine_shard_size(uint64_t file_size, int accumulator)
{
    if (file_size <= 0) {
        return 0;
    }

    accumulator = accumulator ? accumulator : 0;

    // Determine hops back by accumulator
    int hops = ((accumulator - SHARD_MULTIPLES_BACK) < 0 ) ?
        0 : accumulator - SHARD_MULTIPLES_BACK;

    uint64_t byte_multiple = shard_size(accumulator);
    double check = (double) file_size / byte_multiple;

    // Determine if bytemultiple is highest bytemultiple that is still <= size
    if (check > 0 && check <= 1) {
        while (hops > 0 && shard_size(hops) > MAX_SHARD_SIZE) {
            hops = hops - 1 <= 0 ? 0 : hops - 1;
        }

        return shard_size(hops);
    }

    // Maximum of 2 ^ 41 * 8 * 1024 * 1024
    if (accumulator > 41) {
        return 0;
    }

    return determine_shard_size(file_size, ++accumulator);
}
