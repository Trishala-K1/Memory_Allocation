#include "oslabs.h"

//checks for null block
int check_null(struct MEMORY_BLOCK block){
	if(block.process_id == 0 && block.start_address == 0 && block.end_address == 0 && block.segment_size == 0){
	    return 1;
    }
	else
		return 0;
}

//create a null block
struct MEMORY_BLOCK set_null(struct MEMORY_BLOCK *block)
{
	(*block).process_id =0;
	(*block).start_address = 0;
	(*block).end_address = 0;
	(*block).segment_size = 0;
	return *block;
}

//........................................................................................................................................

//best_fit_allocate:
struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
	int i,difference,closest[*map_cnt];
        int lowest = 99999;
        /*
        for(i=0;i<*map_cnt;i++){
            difference =  memory_map[i].segment_size - request_size;
            closest[i] = difference;
        }
        int index;
        for(i=0;i<*map_cnt;i++){
            if(closest[i] < lowest)
                lowest = closest[i];
                index = i;
        }

        */
       for(i=0;i<*map_cnt;i++){
           if(memory_map[i].segment_size >= request_size){
                difference = memory_map[i].segment_size - request_size;
                closest[i] = difference;
                }
            else{
                closest[i] = -1;
            }
       }

       int index;
       for(i=0;i<*map_cnt;i++){
           if(closest[i] != -1){
               if(closest[i] <=lowest){
               lowest = closest[i];
               index = i;
               }
           }
       }

        struct MEMORY_BLOCK elem = memory_map[index]; 
        if(elem.segment_size ==request_size ){
            elem.process_id = process_id;
            return elem;
        }
        else if (request_size <elem.segment_size){
           struct MEMORY_BLOCK split1,split2;
           
           split1.process_id = process_id;
           split1.segment_size = request_size;
           split1.start_address = elem.start_address;
           split1.end_address = elem.start_address + request_size-1;

           split2.segment_size = elem.segment_size - split1.segment_size;
           split2.process_id =0;
           split2.start_address = split1.end_address+1;
           split2.end_address = split2.start_address + split2.segment_size-1;
           memory_map[*map_cnt] = split2;
           memory_map[index] = split1;
           *map_cnt += 1;
           return split1;
        }
        
        else
        return NULLBLOCK; 

    }

//........................................................................................................................................

//first_fit_allocate:
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
	int sizeDiff = 10000;
	int index = 0;
	for (int i = 0; i < *map_cnt; i++){
		if(memory_map[i].segment_size - request_size <= sizeDiff && memory_map[i].process_id == 0){
			sizeDiff = memory_map[i].segment_size - request_size;
			index = i;
		}
	}
	if(sizeDiff == 10000){
		struct MEMORY_BLOCK nullblock;
		return set_null(&nullblock);
	}
	else if(sizeDiff == 0){
		memory_map[index].process_id = process_id;
		return memory_map[index];
	}
	else{
		struct MEMORY_BLOCK chunk;
		chunk.process_id = 0;
		chunk.start_address = memory_map[index].start_address + request_size;
		chunk.end_address = memory_map[index].end_address;
		chunk.segment_size = chunk.end_address - chunk.start_address + 1;
		memory_map[*map_cnt] = chunk;
		(*map_cnt)++;
		
		memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
		memory_map[index].process_id = process_id;
		memory_map[index].segment_size = request_size;
		
		return memory_map[index];
	}
}  

//........................................................................................................................................

//worst_fit_allocate:
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
	int sizeDiff = 10000;
	int index = 0;
	for (int i = 0; i < *map_cnt; i++){
		if(memory_map[i].segment_size - request_size <= sizeDiff && memory_map[i].process_id == 0)
		{
			sizeDiff = memory_map[i].segment_size - request_size;
			index = i;
		}
	}
	if(sizeDiff == 10000){
		struct MEMORY_BLOCK nullblock;
		return set_null(&nullblock);
	}
	else if(sizeDiff == 0){
		memory_map[index].process_id = process_id;
		return memory_map[index];
	}
	else{
		struct MEMORY_BLOCK chunk;
		chunk.process_id = 0;
		chunk.start_address = memory_map[index].start_address + request_size;
		chunk.end_address = memory_map[index].end_address;
		chunk.segment_size = chunk.end_address - chunk.start_address + 1;
		memory_map[*map_cnt] = chunk;
		(*map_cnt)++;
		
		memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
		memory_map[index].process_id = process_id;
		memory_map[index].segment_size = request_size;
		
		return memory_map[index];
	}
}

//........................................................................................................................................

//next_fit_allocate:
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address){
	int sizeDiff = 10000;
	int index = 0;
	for (int i = 0; i < *map_cnt; i++){
		if(memory_map[i].segment_size - request_size <= sizeDiff && memory_map[i].process_id == 0){
			sizeDiff = memory_map[i].segment_size - request_size;
			index = i;
		}
	}
	if(sizeDiff == 10000){
		struct MEMORY_BLOCK nullblock;
		return set_null(&nullblock);
	}
	else if(sizeDiff == 0){
		memory_map[index].process_id = process_id;
		return memory_map[index];
	}
	else{
		struct MEMORY_BLOCK chunk;
		chunk.process_id = 0;
		chunk.start_address = memory_map[index].start_address + request_size;
		chunk.end_address = memory_map[index].end_address;
		chunk.segment_size = chunk.end_address - chunk.start_address + 1;
		memory_map[*map_cnt] = chunk;
		(*map_cnt)++;
		
		memory_map[index].end_address = memory_map[index].start_address + request_size - 1;
		memory_map[index].process_id = process_id;
		memory_map[index].segment_size = request_size;
		
		return memory_map[index];
	}

} 

//........................................................................................................................................

//release memory
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt){
	int free_block;
	for (int i = 0; i < *map_cnt; i++){
		if(freed_block.process_id == memory_map[i].process_id){
			free_block = i;
			break;
		}
	}
	if (memory_map[free_block-1].process_id == 0 && memory_map[free_block + 1]. process_id == 0){
		memory_map[free_block-1].end_address = memory_map[free_block + 1].end_address;
		memory_map[free_block-1].segment_size = (memory_map[free_block-1].end_address - memory_map[free_block-1].start_address) + 1;
		*map_cnt = *map_cnt - 2;
		for(int i = free_block; i < *map_cnt; i++){
			memory_map[i] = memory_map[i+2];
        }
	}
	else if (memory_map[free_block-1].process_id ==0){
		memory_map[free_block-1].end_address = memory_map[free_block].end_address;
		memory_map[free_block-1].segment_size = (memory_map[free_block-1].end_address - memory_map[free_block-1].start_address) + 1;
		*map_cnt = *map_cnt - 1;
		for(int i = free_block; i < *map_cnt; i++){
			memory_map[i] = memory_map[i+1];
        }
	}
	else if (memory_map[free_block+1].process_id ==0){
		memory_map[free_block].end_address = memory_map[free_block+1].end_address;
		memory_map[free_block].segment_size = (memory_map[free_block].end_address - memory_map[free_block].start_address) + 1;
		memory_map[free_block].process_id = 0;
		*map_cnt = *map_cnt - 1;
		for(int i = free_block; i < *map_cnt; i++){
			memory_map[i] = memory_map[i+1];
        }
	}
	else{
		memory_map[free_block].process_id = 0;
	}

}
