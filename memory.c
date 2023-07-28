#include "oslabs.h"

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    int i, bool_available_space, best_fit_size, first_guess;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    first_guess = 1;
    for(i = 0; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            if(first_guess) {
                best_fit_size = i;
                first_guess = 0;
            }
            bool_available_space = 1;
            if(memory_map[i].segment_size < memory_map[best_fit_size].segment_size) {
                best_fit_size = i;
            }
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[best_fit_size].segment_size == request_size) {
        return memory_map[best_fit_size];
    } else {
        tmp.segment_size = memory_map[best_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[best_fit_size].end_address;
        memory_map[best_fit_size].end_address = memory_map[best_fit_size].start_address + request_size-1;
        tmp.start_address = memory_map[best_fit_size].end_address + 1;
        memory_map[best_fit_size].segment_size = request_size;
        memory_map[best_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[best_fit_size];
    }
}
//--------------------------------------------------------------------------------------------------------------------------

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    int i, bool_available_space, first_fit_size;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    for(i = 0; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            bool_available_space = 1;
            first_fit_size = i;
            break;
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[first_fit_size].segment_size == request_size) {
        return memory_map[first_fit_size];
    } else {
        tmp.segment_size = memory_map[first_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[first_fit_size].end_address;
        memory_map[first_fit_size].end_address = memory_map[first_fit_size].start_address + request_size-1;
        tmp.start_address = memory_map[first_fit_size].end_address + 1;
        memory_map[first_fit_size].segment_size = request_size;
        memory_map[first_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[first_fit_size];

    }
}

//--------------------------------------------------------------------------------------------------------------------------

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK   memory_map[MAPMAX],int *map_cnt, int process_id, int last_address) {

    int i, bool_available_space, next_fit_size;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    for(i = last_address; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            bool_available_space = 1;
            next_fit_size = i;
            break;
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[next_fit_size].segment_size == request_size) {
        return memory_map[next_fit_size];
    } else {
        tmp.segment_size = memory_map[next_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[next_fit_size].end_address;
        memory_map[next_fit_size].end_address = memory_map[next_fit_size].start_address + request_size-1;
        tmp.start_address = memory_map[next_fit_size].end_address + 1;
        memory_map[next_fit_size].segment_size = request_size;
        memory_map[next_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[next_fit_size];
    }
}

//--------------------------------------------------------------------------------------------------------------------------

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    int i, bool_available_space, worst_fit_size, worst_fit_location, biggest_available;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    worst_fit_size = 0;
    for(i = 0; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            bool_available_space = 1;
            if(memory_map[i].segment_size > worst_fit_size) {
                worst_fit_size = memory_map[i].segment_size;
                worst_fit_location = i;
            }
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[worst_fit_location].segment_size == request_size) {
        return memory_map[worst_fit_location];
    } else {
        tmp.segment_size = memory_map[worst_fit_location].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[worst_fit_location].end_address;
        memory_map[worst_fit_location].end_address = memory_map[worst_fit_location].start_address + request_size-1;
        tmp.start_address = memory_map[worst_fit_location].end_address + 1;
        memory_map[worst_fit_location].segment_size = request_size;
        memory_map[worst_fit_location].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[worst_fit_location];
    }
}

//--------------------------------------------------------------------------------------------------------------------------

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt) {

    int i, freed_location;

    for(i = 0; i < *map_cnt; i++) {
        if(memory_map[i].process_id == freed_block.process_id) {
            freed_location = i;
        }
    }

    if((memory_map[freed_location-1].process_id == 0) && (memory_map[freed_location+1].process_id == 0)) {
        freed_block.process_id = 0;
        memory_map[freed_location-1].end_address = memory_map[freed_location+1].end_address;
        memory_map[freed_location-1].segment_size = memory_map[freed_location-1].segment_size + freed_block.segment_size + memory_map[freed_location+1].segment_size;

        for(i = freed_location; i < *map_cnt-2; i++) {
            memory_map[i] = memory_map[i+2];
        }
        *map_cnt-=2;

    } else if(memory_map[freed_location-1].process_id == 0) {
        freed_block.process_id = 0;
        memory_map[freed_location-1].end_address = freed_block.end_address;
        memory_map[freed_location-1].segment_size = memory_map[freed_location-1].segment_size + freed_block.segment_size;

        for(i = freed_location; i < *map_cnt-1; i++) {
            memory_map[i] = memory_map[i+1];
        }
        *map_cnt-=1;
    } else if(memory_map[freed_location+1].process_id == 0) {
        freed_block.process_id = 0;
        freed_block.end_address = memory_map[freed_location+1].end_address;
        freed_block.segment_size = freed_block.segment_size + memory_map[freed_location].segment_size;

        for(i = freed_location+1; i < *map_cnt-1; i++) {
            memory_map[i] = memory_map[i+1];
        }
        *map_cnt-=1;
    } else {
        freed_block.process_id = 0;
    }
}
