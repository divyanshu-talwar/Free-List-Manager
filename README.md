# Free-List-Manager
## About
* This is a basic implemetation of a free list manager which keeps track of malloc() and free() function calls.
* Contributor - Divyanshu Talwar

#### Basic Functionalities
* A malloc X call results in a malloc() call for X Bytes and enqueues this pointer into the `free_list`.
* A free X call results in freeing the Xth pointer, which was allocated by the Xth malloc() call. This call also dequeues the freed pointer from the `free_list`.
* A print call prints the current status of the `free_list`. The current status represents the malloced pointer addresses still in the memory (i.e. not freed until now), their respective size and position at which the malloc call was requested.

## Installation and Execution
* Run `make` command on the console and the Makefile would run the shell.