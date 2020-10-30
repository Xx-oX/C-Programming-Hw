#include<stdio.h>
#include<stdlib.h>
typedef struct node {
    int value;
    struct node *next;
} node;

/*declaration*/
void print_node(char*,node*);
node *find_end(node*);
node *partition(node*,node*,node**,node**);
node *qsort_node(node*,node*); 

void print_node (char *str, node *current)
{	
	//print the hole linked list
    printf("%s ", str);
    while (current != NULL)
    {
        printf("%d ",current -> value);
        current = current -> next;
    }
    printf("\n");
}

node *find_end(node *current)
{
	//find the last node in a linked list
    while (current != NULL && current -> next != NULL)
        current = current -> next;
    return current;
}

node *partition (node *ori_head, node *ori_end, node **new_head, node **new_end)
{
	//doing partition and put the result in a new linked list.
    node *pivot = ori_end;
    node *current = ori_head;
    node *previous = NULL;
    node *end = pivot;
    while (current != pivot)
    {
    	if(current -> value < pivot -> value)
    	{
    		if ((*new_head) == NULL) *new_head = current;
    		previous = current;
    		current = current -> next;
		}
		else
		{
			if (previous != NULL) previous -> next = current -> next;
			node *temp = current -> next;
			current -> next = NULL;
			end -> next = current;
			end = current;
			current = temp;
		}
	}
	if ((*new_head) == NULL) *new_head = pivot;
	*new_end = end;
	return pivot;
}
  
node *qsort_node(node *head,node *end) 
{ 
	//recursively doing quick sort by two parts until finsh
	if (head == NULL || head == end) return head; 
    node *new_head = NULL, *new_end = NULL; 
    node *pivot = partition(head, end, &new_head, &new_end); 
    if (new_head != pivot) 
    {  
        node *temp = new_head; 
        while (temp -> next != pivot) 
            temp = temp -> next; 
        temp -> next = NULL;  
        new_head = qsort_node(new_head, temp);  
        temp = find_end(new_head); 
        temp -> next =  pivot; 
    } 
    pivot -> next = qsort_node(pivot -> next, new_end); 
    return new_head;  
} 

int main(int argc,char *argv[]) {
    if (argc != 4) {
        printf("hw8 n m s\n");
        return 1;
        }
    //initialize
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int s = atoi(argv[3]);
    int i; 
    srand(s);
    
    //making original linked list
    node *head = malloc(sizeof(node));
    head -> value = rand() % m;
    head -> next= NULL;
    node *current = head;
    for (i = 1; i < n; i++) 
    {
         current -> next = malloc(sizeof(node));
         current = current -> next;
         current -> value = rand() % m;
         current -> next = NULL;
    }
    
    print_node("Original SSL:", head);
    head = qsort_node(head,find_end(head));
    print_node("Sorted SSL:", head);
    
    return 0;
}
