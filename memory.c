#include "oslabs.h"
#include <stdbool.h>

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    struct MEMORY_BLOCK NULLBLOCK, allocated_memory;
    int i, is_available_space, best_fit_segment, initial_guess;
    is_available_space = 0;
    initial_guess = 1;

    for (i = 0; i < *map_cnt; i++) {
        if ((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            if (initial_guess) {
                best_fit_segment = i;
                initial_guess = 0;
            }
            is_available_space = 1;
            if (memory_map[i].segment_size < memory_map[best_fit_segment].segment_size) {
                best_fit_segment = i;
            }
        }
    }

    if (!is_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;
        return NULLBLOCK;
    }

    if (memory_map[best_fit_segment].segment_size == request_size) {
        memory_map[best_fit_segment].process_id = process_id;
        return memory_map[best_fit_segment];
    } else {
        allocated_memory.segment_size = memory_map[best_fit_segment].segment_size - request_size;
        allocated_memory.process_id = 0;
        allocated_memory.end_address = memory_map[best_fit_segment].end_address;
        memory_map[best_fit_segment].end_address = memory_map[best_fit_segment].start_address + request_size - 1;
        allocated_memory.start_address = memory_map[best_fit_segment].end_address + 1;
        memory_map[best_fit_segment].segment_size = request_size;
        memory_map[best_fit_segment].process_id = process_id;

        memory_map[*map_cnt] = allocated_memory;
        (*map_cnt)++;

        return memory_map[best_fit_segment];
    }
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    int i, is_available_space, first_fit_segment;
    struct MEMORY_BLOCK NULLBLOCK, allocated_memory;

    is_available_space = 0;

    for (i = 0; i < *map_cnt; i++) {
        if ((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            is_available_space = 1;
            first_fit_segment = i;
            break;
        }
    }

    if (!is_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;
        return NULLBLOCK;
    }

    if (memory_map[first_fit_segment].segment_size == request_size) {
        memory_map[first_fit_segment].process_id = process_id;
        return memory_map[first_fit_segment];
    } else {
        allocated_memory.segment_size = memory_map[first_fit_segment].segment_size - request_size;
        allocated_memory.process_id = 0;
        allocated_memory.end_address = memory_map[first_fit_segment].end_address;
        memory_map[first_fit_segment].end_address = memory_map[first_fit_segment].start_address + request_size - 1;
        allocated_memory.start_address = memory_map[first_fit_segment].end_address + 1;
        memory_map[first_fit_segment].segment_size = request_size;
        memory_map[first_fit_segment].process_id = process_id;

        memory_map[*map_cnt] = allocated_memory;
        (*map_cnt)++;

        return memory_map[first_fit_segment];
    }
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id, int last_address) {
    int i, is_available_space, next_fit_segment;
    struct MEMORY_BLOCK NULLBLOCK, allocated_memory;

    is_available_space = 0;

    for (i = last_address; i < *map_cnt; i++) {
        if ((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            is_available_space = 1;
            next_fit_segment = i;
            break;
        }
    }

    if (!is_available_space) {
        for (i = 0; i < last_address; i++) {
            if ((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
                bool match = 1;
                next_fit_segment = i;
                break;
            }
        }
    }

    if (!is_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;
        return NULLBLOCK;
    }

    if (memory_map[next_fit_segment].segment_size == request_size) {
        memory_map[next_fit_segment].process_id = process_id;
        return memory_map[next_fit_segment];
    } else {
        allocated_memory.segment_size = memory_map[next_fit_segment].segment_size - request_size;
        allocated_memory.process_id = 0;
        allocated_memory.end_address = memory_map[next_fit_segment].end_address;
        memory_map[next_fit_segment].end_address = memory_map[next_fit_segment].start_address + request_size - 1;
        allocated_memory.start_address = memory_map[next_fit_segment].end_address + 1;
        memory_map[next_fit_segment].segment_size = request_size;
        memory_map[next_fit_segment].process_id = process_id;

        memory_map[*map_cnt] = allocated_memory;
        (*map_cnt)++;

        return memory_map[next_fit_segment];
    }
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    int i, is_available_space, worst_fit_segment, worst_fit_location;
    struct MEMORY_BLOCK NULLBLOCK, allocated_memory;

    is_available_space = 0;
    worst_fit_segment = 0;

    for (i = 0; i < *map_cnt; i++) {
        if ((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            is_available_space = 1;
            if (memory_map[i].segment_size > worst_fit_segment) {
                worst_fit_segment = memory_map[i].segment_size;
                worst_fit_location = i;
            }
        }
    }

    if (!is_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;
        return NULLBLOCK;
    }

    if (memory_map[worst_fit_location].segment_size == request_size) {
        memory_map[worst_fit_location].process_id = process_id;
        return memory_map[worst_fit_location];
    } else {
        allocated_memory.segment_size = memory_map[worst_fit_location].segment_size - request_size;
        allocated_memory.process_id = 0;
        allocated_memory.end_address = memory_map[worst_fit_location].end_address;
        memory_map[worst_fit_location].end_address = memory_map[worst_fit_location].start_address + request_size - 1;
        allocated_memory.start_address = memory_map[worst_fit_location].end_address + 1;
        memory_map[worst_fit_location].segment_size = request_size;
        memory_map[worst_fit_location].process_id = process_id;

        memory_map[*map_cnt] = allocated_memory;
        (*map_cnt)++;

        return memory_map[worst_fit_location];
    }
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt) {
    bool flag = false;
    if ((*map_cnt == 1) && (memory_map[0].end_address == 0) &&
        (memory_map[0].start_address == 0) && (memory_map[0].process_id == 0) &&
        (memory_map[0].segment_size == 0))
        return;
    else {
        for (int i = 0; i < *map_cnt; i++) {
            if ((freed_block.start_address == memory_map[i].start_address) &&
                (freed_block.end_address == memory_map[i].end_address) &&
                (freed_block.process_id == memory_map[i].process_id)) {
                memory_map[i].process_id = 0;
                if (i > 0) {
                    if (memory_map[i - 1].process_id == 0) {
                        memory_map[i - 1].end_address = freed_block.end_address;
                        memory_map[i - 1].segment_size = memory_map[i - 1].segment_size + freed_block.segment_size;
                        for (int index = i; index <= *map_cnt; index++) {
                            memory_map[index] = memory_map[index + 1];
                        }
                        *map_cnt = *map_cnt - 1;
                        flag = true;
                    }
                }
                if (i < *map_cnt - 1) {
                    if (flag == false) {
                        i = i + 1;
                    }
                    if (memory_map[i].process_id == 0) {
                        memory_map[i].start_address = memory_map[i - 1].start_address;
                        memory_map[i].segment_size = memory_map[i].end_address - memory_map[i].start_address + 1;
                        for (int index = i; index <= *map_cnt; index++) {
                            memory_map[index - 1] = memory_map[index];
                        }
                        *map_cnt = *map_cnt - 1;
                    }
                }
                break;
            }
        }
    }
}
