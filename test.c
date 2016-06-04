#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i = 0;
	int capacity, heapType;
	int example[] = {7, 11, 50, 12, 33, 51, 55, 21, 55, 80, 34};
	/* printf("Enter Capcity: ");
	scanf("%d", &capacity);
	printf("Enter Heap Type: ");
	scanf("%d", &heapType); */
	
	capacity = 15;
	heapType = 1;
	
	/* create priority queue */
	PQ *pq = pq_create(capacity, heapType);
		
	/* insert values into priority queue */
	for(i = 0; i < 11; i++)
		pq_insert(pq, i, example[i]);
	printf("\n0. ORIGINAL MIN-HEAP");
	pq_print(pq);
	
	/**** testing insert/perc-up ****/
	pq_insert(pq, i, 25);
	i++;
	pq_print(pq);
	printf("\n1. TESTING INSERT/PERC-UP");
	printf("\n\t1a. Expected Heap: 7 11 25 12 33 50 55 21 55 80 34 51");
	printf("\n\t1b. Expected: Error");
	pq_insert(pq, 11, 60);
	printf("\n\t1c. Expected: Error");
	pq_insert(pq, 15, 90);
	printf("\n\t1d. Expected: Error");
	pq_insert(pq, -1, 90);
	
	/**** testing capacity and size ****/
	printf("\n\n2. TESTING CAPACITY/SIZE");
	printf("\n\t2.a Expected: Capcity: 15\tSize: 12");
	printf("\n\t\tCapacity: %d\tSize: %d\n", pq_capacity(pq), pq_size(pq));
	
	/**** testing change priority ****/
	double new_priority = 90;
	int id = 11;
	if(pq_change_priority(pq, id, new_priority) == 1){
		printf("\n3. TESTING CHANGE PRIORITY");
		pq_print(pq);
		printf("\n\t3a. Expected Heap: 7 11 50 12 33 51 55 21 55 80 34 90");
	}

	//reset it back
	new_priority = 25;
	id = 11;
	pq_change_priority(pq, id, new_priority);
	//test 3b
	new_priority = 90;
	id = 0;
	if(pq_change_priority(pq, id, new_priority) == 1){
		pq_print(pq);
		printf("\n\t3b. Expected Heap: 11 12 25 21 33 50 55 90 55 80 34 51");
	}
	printf("\n\t3c. Expected: ERROR");
	pq_change_priority(pq, -1, new_priority);
	printf("\n\t3d. Expected: ERROR");
	pq_change_priority(pq, 16, new_priority);
	
	
	/**** testing remove by id ****/
	int id2 = 5;
	if(pq_remove_by_id(pq, id2) == 1){
		printf("\n\n4. TESTING REMOVE BY ID");
		pq_print(pq);
		printf("\n\t4a. Expected Heap: 11 12 25 21 33 50 55 90 55 80 34");
	}  
	id2 = 1;
	if(pq_remove_by_id(pq, id2) == 1){
		pq_print(pq);
		printf("\n\t4b. Expected Heap: 12 21 25 34 33 50 55 90 55 80");
	}
	printf("\n\t4c. Expected: ERROR");
	pq_remove_by_id(pq, -1);
	printf("\n\t4d. Expected: ERROR");
	pq_remove_by_id(pq, 30);
	pq_print(pq);
	
	
	/**** testing get priority ****/
 	double new;
	int id3 = 0;
	if(pq_get_priority(pq, id3, &new) == 1){
		printf("\n\n5. TESTING GET PRIORITY");
		printf("\n\t5a. Expected: 90");
		printf("\n\t\tResult: %2.0f\n", new);
	}
	id3 = 6;
	if(pq_get_priority(pq, id3, &new) == 1){
		printf("\t5b. Expected: 55");
		printf("\n\t\tResult: %2.0f\n", new);
	}
	id3 = 9;
	if(pq_get_priority(pq, id3, &new) == 1){
		printf("\t5c. Expected: 80");
		printf("\n\t\tResult: %2.0f", new);
	}
	printf("\n\t5d. Expected: ERROR");
	pq_get_priority(pq, 12, &new);
	printf("\n\t5e. Expected: ERROR");
	pq_get_priority(pq, -1, &new);
	printf("\n\t5f. Expected: ERROR");
	pq_get_priority(pq, 5, &new);  
	
	
	/**** testing delete top ****/
	double p;
	int id4;
	if(pq_delete_top(pq, &id4, &p) == 1){
		printf("\n\n6. TESTING DELETE TOP");
		pq_print(pq);
		printf("\n\t6a. Expected Heap: 21 33 25 34 80 50 55 90 55");
		printf("\n\t6a. Expected ID: 3\tExpected Priority: 12");
		printf("\n\t\tResult: ID: %d\tPriority: %2.0f", id4, p);
	} 

	
	/**** testing contains ****/
	int id5 = 11;
	pq_print(pq);
	if(pq_contains(pq, id5) == 1){
		printf("\n\n7. TESTING CONTAINS");
		printf("\n\t7a. Expected: Success at ID %d", id5);
	}
	id5 = 4;
	if(pq_contains(pq, id5) == 1)
		printf("\n\t7b. Expected: Success at ID %d", id5);
	id5 = 5;
	if(pq_contains(pq, id5) == 0)
		printf("\n\t7c. Expected: Failure at ID %d", id5);
	id5 = 60;
	if(pq_contains(pq, id5) == 0)
		printf("\n\t7d. Expected: Failure at ID %d", id5);
	id5 = -1;
	if(pq_contains(pq, id5) == 0)
		printf("\n\t7e. Expected: Failure at ID %d", id5); 

		
	//pq_print(pq);
	/* free priority queue */
	pq_free(pq);
	
	printf("\n");
	return 0;
}
