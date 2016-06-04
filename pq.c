/*
Name:	Aloysius Paredes
NetID:	apared5
*/
#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**** STRUCT ****/
typedef struct node_struct {
	int id; //0...(n-1)
	double priority; //val
	int position; //index in the array of nodes
}NODE;

struct pq_struct{
	NODE *heap;		//array of nodes that hold an id and a priority
	NODE **nodePtrs;//array of pointers to corresponding ids
	int size;		//current size
	int capacity;	//max number of nodes
	int type; 		//to check to see if the heap will be a min-heap or a max-heap
};

/**** FUNCTION DEFINITIONS ****/
void pq_print(PQ *pq); //function prototype

/* returns pointer to empty priority queue with given capacity and min/max behavior as specified */
PQ * pq_create(int capacity, int type){
	if(capacity <= 0){
		printf("\n\t\tCapacity must be greater than 0!\n\n");
		exit(1);
	}
	int i = 0;
	//create priority queue
	PQ *p = malloc(sizeof(PQ));
	
	//create heap
	p->heap = malloc(sizeof(NODE) * capacity + 1);
	//set index 0 of heap to arbitrary values
	p->heap[0].priority = -1;
	p->heap[0].id = -1;
	
	//create node pointer array
	p->nodePtrs = malloc(sizeof(NODE*) * capacity);
	//set pointers to point to NULL
	for(i = 0; i < capacity; i++)
		p->nodePtrs[i] = NULL;
	
	//set capacity, size, and heap type
	p->capacity = capacity; //set max capacity
	p->size = 0; //set starting number of elements in tree to 0
	p->type = type;

	return p;
}//end pq_create(...)

/* deallocates all memory associated with passed priority queue */
void pq_free(PQ * pq){	
	free(pq->heap);
	free(pq->nodePtrs);
	free(pq);
}//end pq_free(...)

/* percolate up node at i to it's proper spot*/
void perc_up(PQ *pq, int i){
	//hold priority and id temporarily
	double x = pq->heap[i].priority;
	int d = pq->heap[i].id;
	int pos = pq->heap[i].position;
	
	int parent = i/2;
	/* for min-heap */
	if(pq->type != 0){
		while(parent >= 1 && pq->heap[parent].priority > x){
			//swap
			pq->heap[i].priority = pq->heap[parent].priority;
			pq->heap[i].id = pq->heap[parent].id;

			pq->nodePtrs[pq->heap[parent].id] = &(pq->heap[i]);
			i = parent;
			parent = i/2;
		}
	}
	/* for max-heap */
	if(pq->type == 0){
		while(parent >= 1 && pq->heap[parent].priority < x){
			//swap
			pq->heap[i] = pq->heap[parent];
			pq->nodePtrs[pq->heap[parent].id] = &(pq->heap[i]);

			pq->nodePtrs[pq->heap[parent].id] = &(pq->heap[i]);
			i = parent;
			parent = i/2;
		}
	}
	
	//set the current index to temporary variables
	pq->heap[i].priority = x;
	pq->heap[i].id = d;
	
	//set node pointer
	pq->nodePtrs[d] = &(pq->heap[i]);
}

/* percolate down node at i to it's proper spot*/
void perc_down(PQ *pq, int i){
	//n = pq->size;
	int l = 2 * i; //left child
	int r = l + 1; //right child
	int done = 0, min = l, max = l; //assume min/max is the left child

	//min-heap perc down
	if(pq->type != 0){		
		while(l <= pq->size && !done){
			min = l;
			//check to see if the right child is min
			if(r <= pq->size && pq->heap[r].priority < pq->heap[l].priority)
				min = r;
			if(pq->heap[min].priority < pq->heap[i].priority){
				//swap
				int id = pq->heap[min].id;
				double priority = pq->heap[min].priority;
				int pos = pq->heap[min].position;
				
				int id2 = pq->heap[i].id;
				double priority2 = pq->heap[i].priority;
				int pos2 = pq->heap[i].position;
			 
				pq->heap[min].id = id2;
				pq->heap[min].priority = priority2;
				pq->heap[min].position = pos;
			 
				pq->heap[i].id = id;
				pq->heap[i].priority = priority;
				pq->heap[i].position = pos2;
			 
				pq->nodePtrs[id] = &(pq->heap[i]);
				pq->nodePtrs[id2] = &(pq->heap[min]); 

				i = min;
			}
			else
				done = 1;
			
			l = 2 * i;
			r = l + 1;
		}	
	}
	//max heap perc down
	if(pq->type == 0){
		while(l <= pq->size && !done){
			max = l;
			//check to see if the right child is max
			if(r <= pq->size && pq->heap[r].priority > pq->heap[l].priority)
				max = r;
			if(pq->heap[max].priority > pq->heap[i].priority){
				//swap
				int id = pq->heap[min].id;
				double priority = pq->heap[min].priority;
				int pos = pq->heap[min].position;
				
				int id2 = pq->heap[i].id;
				double priority2 = pq->heap[i].priority;
				int pos2 = pq->heap[i].position;
			 
				pq->heap[min].id = id2;
				pq->heap[min].priority = priority2;
				pq->heap[min].position = pos;
			 
				pq->heap[i].id = id;
				pq->heap[i].priority = priority;
				pq->heap[i].position = pos2;
			 
				pq->nodePtrs[id] = &(pq->heap[i]);
				pq->nodePtrs[id2] = &(pq->heap[min]); 

				i = max;
			}
			else
				done = 1;
			l = 2 * i;
			r = l + 1;
		}	
	}
}

/* returns 1 on success; 0 on failure */
int pq_insert(PQ * pq, int id, double priority){
	//check if id is out of range or there is already an entry for id
	if(id >= pq->capacity || id < 0){
		printf("\n\t\tERROR: 0 <= %d < %d is not valid!!", id, pq->capacity - 1);
		return 0;
	}
	//check if there is already an entry for id
    if(pq->nodePtrs[id] != NULL){
		printf("\n\t\tERROR: %d ID occupied by %2.0f", id, pq->nodePtrs[id]->priority);
		return 0;
	}
	
	(pq->size)++; //increase the size
	
	pq->heap[pq->size].position = pq->size;
	
	//modify heap and node pointer array
	pq->heap[pq->size].priority = priority;
	pq->heap[pq->size].id = id;	
	pq->nodePtrs[id] = &(pq->heap[pq->size]);
	pq->heap[pq->size].position = pq->size;
	
	//perc up to move very last node to it's proper position
	perc_up(pq, pq->size);
	return 1;
}//end pq_insert(...)

/* returns 1 on success; 0 on failure */
int pq_change_priority(PQ * pq, int id, double new_priority){
	//id not in pq
	if(pq->nodePtrs[id] == NULL){
		printf("\n\t\tERROR: No value in ID %d", id);
		return 0;
	}
	//out of range
	if(id >= pq->capacity || id < 0){
		printf("\n\t\tERROR: 0 <= %d < %d is not valid!!", id, pq->capacity - 1);
		return 0;
	}
	
	//check if there is an entry for the given id
	if(pq->nodePtrs[id] != NULL){
		//check if min heap
		if(pq->type != 0){
			//check if old priority < new 
			if(pq->nodePtrs[id]->priority < new_priority){
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc down
				perc_down(pq, pq->nodePtrs[id]->position);
			}
			else{
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc down
				perc_up(pq, pq->nodePtrs[id]->position);
			}
		}
		//check if max heap
		if(pq->type == 0){
			//check if old priority < new 
			if(pq->nodePtrs[id]->priority > new_priority){
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc down
				perc_down(pq, pq->nodePtrs[id]->position);
			}
			else{
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc down
				perc_up(pq, pq->nodePtrs[id]->position);
			}
		}
	}
	return 1;
}//end pq_change_priority(...)

/* returns 1 on success; 0 on failure */
int pq_remove_by_id(PQ * pq, int id){
	//id not in pq
	if(pq->nodePtrs[id] == NULL){
		printf("\n\t\tERROR: No value in ID %d", id);
		return 0;
	}
	//out of range
	if(id >= pq->capacity || id < 0){
		printf("\n\t\tERROR: 0 <= %d < %d is not valid!!", id, pq->capacity - 1);
		return 0;
	}
	
	//check if there is an entry with the given id
	if(pq->nodePtrs[id] != NULL){
		NODE *target = (pq->nodePtrs[id]);
		NODE *replacement = &(pq->heap[pq->size]);
		
		int oldPriority = target->priority;		
		int newPriority = replacement->priority;
		int position = target->position;
		
		pq->heap[position].priority = replacement->priority;
		pq->heap[position].id = replacement->id;
		
		pq->heap[pq->size].priority = 0;
		pq->heap[pq->size].id = 0;
		pq->heap[pq->size].position = 0;
		replacement->position = position;
		
		(pq->size)--; //decrease the size
		
		//check if min heap
		if(pq->type != 0){
			if(newPriority > oldPriority)
				perc_down(pq, replacement->position);
			if(newPriority < oldPriority)
				perc_up(pq, replacement->position);
		}
		//check if max heap
		if(pq->type == 0){
			if(newPriority < oldPriority)
				perc_down(pq, replacement->position);
			if(newPriority > oldPriority)
				perc_up(pq, replacement->position);
		}
	}
	//modify pointer
	pq->nodePtrs[id] = NULL;
	return 1;
}//end pq_remove_by_id(...)

/* returns 1 on success; 0 on failure */
int pq_get_priority(PQ * pq, int id, double *priority){
	if(pq->nodePtrs[id] == NULL){
		printf("\n\t\tERROR: No value in ID %d", id);
		return 0;
	}
	//out of range
	if(id >= pq->capacity || id < 0){
		printf("\n\t\tERROR: 0 <= %d < %d is not valid!!", id, pq->capacity - 1);
		return 0;
	}
	//check if there is an entry with the given id
	if(pq->nodePtrs[id] != NULL){
		//*priority is assigned the associated priority
		*priority = pq->nodePtrs[id]->priority;
		return 1;
	}
}//end pq_get_priority(...)

/* returns 1 on success; 0 on failure(empty priority queue) */
int pq_delete_top(PQ * pq, int *id, double *priority){
	if(pq->size <= 0){
		printf("\n\t\tERROR: Heap Empty!!");
		return 0;
	}
	
	//check if queue is non-empty
	if(pq->size > 0){
		//set *id and *priority to the id and priority of the top of the heap
		*priority = pq->heap[1].priority;
		*id = pq->heap[1].id;
		//element is deleted (remove_by_id)
		pq_remove_by_id(pq, pq->heap[1].id);
		return 1;
	}
	
}// end pq_delete_top(...)

/* returns capacity of priority queue (as set on creation) */
int pq_capacity(PQ * pq){
	return pq->capacity;
}//end pq_capacity(...)

/* return the number of elements currently in queue */
int pq_size(PQ * pq){
	return pq->size;
}//end pq_size(...)

/* returns 1 on success; 0 on failure */
int pq_contains(PQ * pq, int id){
	//check if index is within bounds
	if(id < 0){
		printf("\n\t\tERROR: %d must be greater than 0!!", id);
		return 0;
	}
	if(id > pq->capacity - 1){
		printf("\n\t\tERROR: %d must be less than %d!!", id, pq->capacity - 1);
		return 0;
	}
	//check if there is an entry in the queue for the given id
	if(pq->nodePtrs[id] != NULL)
		return 1;
	return 0;
}//end pq_contains(...)


/**** DEBUGGING FUNCTIONS ****/
double priority_at_index(PQ * pq, int index){
	if(pq_contains(pq, index) == 0)
		//nothing there!
		return;
	//return the priority
	return pq->nodePtrs[index]->priority;
} 

/* prints the priority queue */
void pq_print(PQ *pq){
	printf("\n\n\t\t******Priority Queue******\n");
	int max = pq->size, i;
	
	printf("Index:\t\t");
	for(i = 0; i <= pq->capacity; i++)
		printf("%2d ", i);
	
	printf("\nPointers:\t");
	for(i = 0; i < pq->capacity; i++){
		if(pq->nodePtrs[i] == NULL){
			printf("%2.0d ", -1);
			continue;
		}
		printf("%2.0f ", pq->nodePtrs[i]->priority);
	}
	printf(" -");
	
	printf("\n===============");
	for(i = 0; i <= pq->capacity; i++)
		printf("===");
	
	printf("\nID:\t\t");
	for(i = 0; i <= max; i++)
		printf("%2d ", pq->heap[i].id);
	
	printf("\nPriority:\t");
	for(i = 0; i <= max; i++)
		printf("%2.0f ", pq->heap[i].priority);
	
	printf("\nPosition:\t");
	for(i = 0; i <= max; i++)
		printf("%2d ", pq->heap[i].position);
	
	printf("\n");
}