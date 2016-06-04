


Name:	Aloysius Paredes
NetID:	apared5

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.
-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class ans in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.  



	As we know, a heap and an array is essentially the same thing. So I created a node that held the an ID, priority, and position (index in the heap). Many of the functions in this program required modifying the heap based on the node's ID value, so I created an array of node pointers (every index initialized to point to NULL). Like the IDs that ran from 0 to (n-1), the array of node pointers run from 0 to (n-1) where n is the maximum capacity of the heap (max number of nodes). Index 0 of the node pointer array points to the node that has ID 0. Index 1 of the node pointer array points to the node that has ID 1. And so on...
	
	This is especially useful to meet the runtime requirements as I will always know where any ID is because it is array accessible as the indices correspond to the IDs. Additionally, each node holds it's position with respect to the heap. So regardless of where the node is in the heap, I will always be able to know where it is whether if I'm looking for it based on ID or based on position/index of the heap; thus, I did not need to perform a search through the heap or the pointer array.

	My priority queue ADT holds the size (which is updated at every insertion/deletion) and capacity, thus allowing me to meet the O(1) runtime for size/capacity functions as I just need to return the priority queue's size and capacity. No need to search and count.

	The contains function is O(1) since the node pointer array can directly access any node (by ID) and check to see if there is anything at that node. No need to search through every node.

-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?


	Normally, pq_insert inserts to the end of the heap, and the percolates up. Having to keep track of the node pointers in a separate array, inserting into the heap, I also had to insert a new node pointer in the node pointer array to point to the node with the inputed ID. Of course pq_insert needed error checking to make sure the inputed ID was within range. Additionally, with the new node pointer array, we can quickly check to see if the inputed ID is already being used by another node. As it is an array, we can quickly jump to that index of the inputed ID to check to see if that spot isn't NULL (meaning that spot is already being occupied by another node).
	
	The insert function always calls perc_up. As such, perc_up needed to be modified to account for the node pointers. Whenever a swap (swapping IDs, priorities, and postitions) was made, the node pointer array also needed to be maintained (ie the proper swap needed to be made on the node pointer array).


	This is O(log n) because of perc up.

-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?


	The modifications above required maintenance on the node pointer array as well. A way that I thought about performing pq_delete_top was to just call remove_by_id. As I had access to any node in my heap instantly (through array index locations), I can just removed the very first index (since I knew the position and ID of the first node in the heap) and call remove_by_id based on that node's ID. 
	
	remove_by_id is tricky in that the deletion of the node was very particular. I needed to hold the old and new priority. After the proper variables were replaced (node deleted), the current size of the priority queue was decreased. And based on if the priority queue was a min-heap or a max-heap, and based on if the new priority was greater than or less than the new priority, perc down or perc up was performed. And of course, perc up and perc down accounted for maintaining the node pointer array so everything is still consistent.

	This is O(log n) due to percolation.


-----------------------------------------------
Explain how your implementation of bst_change_priority worked,
why it is correct and why it achieves the runtime requirement.


	Before changing any of the priorities by ID, I error checked to make sure that the ID being inputed is within range, and that the ID being accessed has a node (ie check to see if the ID is even in the priority queue). If it passes those checks, then it is known that there is a node in the priority queue with that ID, so the following change priority algorithm is performed: First a check to see if the heap is a min-heap or a max-heap. If the heap is a min heap, I compared the old priority (current priority being changed) to the new priority being passed in. If the old priority is less than the new priority and based on the properties of a min-heap, we know that the node at that position in the heap needed to be percolated down. Before percolating down, the priority needed to be changed. I took advantage of the node pointers as I had direct access to it (since the indices of the node pointer array correspond to the ID I would be looking for). As such, the priority of the node being pointed to by that ID needed to be changed to the new priority. Afterwards, that value is percolated down in the heap. It is percolated up if the old priority is greater than the new priority. Vice versa for max-heap.

	As I don't need to perform a linear search to find the node with the inputed ID, the runtime is O(log n) because of the node pointer array prevents the linear runtime and only perc up and perc down control the runtime.

	This is O(log n) due to percolation.

-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?


	As mentioned above, I created a node pointer array where the indices of the array correspond to the IDs of each node in the heap. pq_get_priority attempts to located a node with a specific ID. As I have access to the ID in constant time through properties of the array, and as long as it passes the error checks, I have direct access to that node with the inputed ID; thus, the runtime is O(1).





