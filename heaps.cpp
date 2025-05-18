#include <stdio.h>
#include <stdlib.h>

#define max_size 100

typedef struct {
	int array[max_size]; //create an array with the max size of 100
	int Current_size; // the current amount elements in the array
} heap;

void swap(int *number1, int *number2){
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;	
}

void heapify_up(heap* heaps, int index){
	int parent_index;
	if(index == 0){
		return;
	}
	
	parent_index = (index - 1) / 2;
	
	if(heaps->array[parent_index] > heaps->array[index]){
		swap(&heaps->array[parent_index], &heaps->array[index]);
		
		heapify_up(heaps, parent_index);
	}
}

heap *insertheap(heap* heaps, int data){
	if (heaps->Current_size >= max_size){ // the current amount of elements in the array has reached the max size
		printf("Already reached maximum limit!\n");
		return heaps;
	}
	heaps->array[heaps->Current_size] = data; //place the data into the current newest index of the array
	heapify_up(heaps, heaps->Current_size);// check whether the array fufills the minimum heap property
	heaps->Current_size++; //increase the current amount of elements
	
	return heaps;
}


void print_heaps(heap* heaps){
	int array_index =  0; //the index of the array to be printed
	for(array_index; array_index < heaps->Current_size; array_index++){ //loops until the final element in the array
		printf("%d ", heaps->array[array_index]);
	}
	printf("\n");
	
}

void down_heap(heap* heaps, int index){
	if(index == heaps->Current_size){
		return;
	}
	
	int leftChild_index = index * 2 + 1;
	int rightChild_index =  index * 2 + 2;
	
	int smallestChild;
	if(heaps->array[leftChild_index] <= heaps->array[rightChild_index]){
		smallestChild = leftChild_index;
	}
	else{
		smallestChild = rightChild_index;
	}
	
	if(heaps->array[index] > heaps->array[smallestChild]){
		
		swap(&heaps->array[index], &heaps->array[smallestChild]);
		down_heap(heaps, smallestChild);
	}
	
}

heap *delete_min(heap* heaps){
	if(heaps->Current_size == 0){
		printf("No data in the heap\n");
	}
	heaps->array[0] = heaps->array[heaps->Current_size - 1];
	heaps->Current_size--;
	down_heap(heaps, 0);
	
	return heaps;
}

int main(){
	int amount, number;
	heap *heaps = (heap*) malloc(sizeof(heap));
	heaps->Current_size = 0;
	
	printf("How many numbers do you want to be inserted : ");
	scanf("%d", &amount); getchar();
	
	for(int i = 1; i <= amount; i++){
		printf("Insert a number : ");
		scanf("%d", &number);getchar();
		heaps = insertheap(heaps, number);
		
		printf("Current array :");
		print_heaps(heaps);
	}
	
	printf("Delete Minimum Value in the heap = %d\n", heaps->array[0]);
	heaps = delete_min(heaps);
	
	
	printf("Current array :");
	print_heaps(heaps);
	
	
	return 0;
}
