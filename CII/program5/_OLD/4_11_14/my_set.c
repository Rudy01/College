#include <stdio.h>
#include <stdlib.h>
#include "my_set.h"

typedef struct node Node;

// LH = left higher		EQ = equal heights		RH = right higher
typedef enum Balanced{LH, EH, RH} Balanced;	// Enum for determing if a tree is balanced

// TREE STRUCTURE.
struct node
{
	int data;		// Each node contains an int, and left / right pointers.
	Node * left;	// which point to another node and so on.
	Node * right;		
	Balanced bf;	// Know whether the function is balanced or not.
};

struct my_set
{
	Node * root;	
};

typedef struct my_set My_set;

//	 Function declarations
void in_order_traverse(Node* root, void (*visit)(int));
void           destroy(Node* root);
Boolean     SearchTree(Node *head, int item);
int           FindSize(Node *temp, Node *numb);
Node*              Add(Node *head, Node *temp, Boolean *taller, int item);
Status          Remove(Node *head, int item);

// Helpers for the size function
int balanced(MY_SET hMY_SET);
int _balanced(Node* temp);
int height(Node* node);
int max(int a, int b);

// Balancing functions
Node*  Balance_Left(Node *head, Boolean *taller);
Node* Balance_Right(Node *head, Boolean *taller);

// Takes no arguments; returns a handle to a default MY_SET
MY_SET my_set_init_default(void)
{
	My_set *temp;	
	temp  = (My_set*)malloc(sizeof(My_set));	// Alloc space for a MY_SET
	
	// See if the malloc failed:
	if(temp == NULL)
	{
		printf("Error - failed to malloc default MY_SET object!\n");
		return NULL;
	}
	
	// If it succeded, then we are free to set root to NULL
	if(temp != NULL)
	{
		temp->root = NULL;
	}
	
	// And return a handle to the MY_SET object!
	return (MY_SET)temp;
}

// Returns TRUE if item is in the set; exit on error
Boolean my_set_is_element(MY_SET hMY_SET, int item)	
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *temp = pSet->root;
	Boolean Code;
	
	// First see if the list is empty.
	if(temp == NULL)
		return FALSE;
		
	// Other wise run through the list until we find the item!
	if(temp != NULL)
	{
		// Call Search tree to do this for us.
		Code = SearchTree(temp, item);
	}

	if(Code == TRUE)
		return TRUE;

//	Failed to find the item!
	return FALSE;
}

// Returns TRUE if an item is in the set. False if it is not.
Boolean SearchTree(Node *head, int item)
{
	Boolean test;
	
	// Run through the list until we find the item!
	if(head != NULL)
	{
		if(head->data == item) 	// If we find the item, return TRUE!
			return TRUE;
		test = SearchTree(head->left, item);		// Search  left side
		test = SearchTree(head->right, item);	// Search right side
	}
	
	// If one of the recursive functions found the item, return SUCCESS!
	if(test == TRUE)
		return TRUE;
	
	// If we get here, return FALSE - we didn't find the item.
	return FALSE;
}

// Returns TRUE if the set is empty; exit on error
Boolean my_set_is_empty(MY_SET hMY_SET)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;

//	If MY_SET is NULL, there is no set.
	if(hMY_SET == NULL)
	{
		return TRUE;
	}
	
//	If the head pointer points to NULL, there is no set.
	if(head == NULL)
	{
		return TRUE;
	}
	
//	If it isn't NULL, there is some sort of a list.
	return FALSE;
}

// Returns the number of elements in the set; -1 on error
int my_set_size(MY_SET hMY_SET)			
{
	int number_of_nodes = 0;
	My_set *pSet = (My_set*)hMY_SET;
	Node *temp = pSet->root;
	Node *numb = (Node*) malloc(sizeof(Node));
	
	// Verify that hMY_SET exists.
	if(hMY_SET == NULL)
		return -1;	// Return error if it doesn't.
	
	/* Assuming we have at least one node, run through the tree.
	   (Using pre-order)
	  NOTE: using recursion, so needed a good way to get the ACTUAL
	  number of nodes in the set. numb is ONLY used for its data, as it
	  should not be modified by recursion. May be a simpler way but this works!
	*/
	number_of_nodes = FindSize(temp, numb);
	
	destroy(numb);		// Prevent memory leaks.
	
	return number_of_nodes;
}

int FindSize(Node *temp, Node *numb)
{
	if(temp != NULL)
	{
		numb->data++;	// Increase n for each node we find.
		FindSize(temp->right, numb);	// Search right
		FindSize(temp->left, numb);	// Search left
	}
	
	// Return the number of nodes.
	return numb->data;
}

// Call visit on each node in the set. (Inorder traversal)
Status my_set_traverse(MY_SET hMY_SET, void (*visit)(int))
{
	My_set * temp = (My_set*) hMY_SET;

	if (temp != NULL) 	// Make sure the set isn't empty!
	{
		in_order_traverse(temp->root, visit);	// Another function will do the work.
		return SUCCESS;
	}

	return FAILURE;		// If temp was NULL, must return a FAILURE. 
}

// Traverse the list in order of the Nodes.
void in_order_traverse(Node* root, void (*visit)(int))
{
	if(root == NULL)	// Can't traverse an empty set!
	{
		return;
	}
	else
	{
		in_order_traverse(root->left, visit);	// Traverse left side.
		visit(root->data);					// Then visit root.
		in_order_traverse(root->right, visit);	// Traverse right side.
		return;
	}
}

// Adds item to the set if it is not already in it.
Status my_set_add(MY_SET hMY_SET, int item)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	Node *temp = NULL;
	Boolean taller = TRUE;
	
	// If the handle isn't valid, we can't continue!
	if(hMY_SET == NULL)
	{
		printf("Error: hMY_SET is not valid!\n");
		return FAILURE;
	}
	
	temp = (Node*) malloc(sizeof(Node));
	
	if(temp == NULL)
	{
		printf("Error: failed to malloc node!\n");
		return FAILURE;
	}
	
	temp -> data = item;				// Store the item in the node
	
	// Other wise we can just see if there's room somewhere,
	// by looking left / right etc.
	head = Add(head, temp, &taller, item);
	
	if(head != NULL)		// We found a spot!
	{
		pSet->root = head;	// Updated pSet (hMY_SET) to include the new head.
		return SUCCESS;
	}
	
	return FAILURE;		// Something failed...
}


Node* Add(Node *head, Node *temp, Boolean *taller, int item)
{
	// Simple - look left or right. Keep looking left & right for a spot.
	// NOTE: for an AVL tree, MAY need to rebalance the tree to keep the height
	// no higher than 1?
	
	// If this is the first item in the tree, we must start at root!
	if(head == NULL)
	{
		head = temp;						// Set root equal to the new node.
		head ->  left = head -> right = NULL;	// Make left/right side NULL
		temp -> bf = EH;					// Root is equal
		*taller = TRUE;					// Height increased
		printf("HELLO??\n");
	}
	
	else if(head->data == item)
	{
		printf("Error: cannot insert same element twice into the AVL tree!\n");
		return NULL;
	}
		
	else if(item < head->data)	// Look to the left side
	{
		head -> left = Add(head -> left, temp, taller, item);
		if(*taller)
			switch(head -> bf)
			{
				case LH:
					head = Balance_Left(head, taller);	// Node was high on the left side.	
					break;
				case EH:
					head -> bf = LH;	// Node is now higher on the left side.
					break;
				case RH:
					head -> bf = EH;	// Node is now balanced height
					*taller = FALSE;
					break;
			}
	}
	else 					// Look to the right side
	{
		head -> right = Add(head -> right, temp, taller, item);
		if(*taller)
			switch(head -> bf)
			{
				case LH:				
					head -> bf = EH;	// Node is now balanced height
					*taller = FALSE;
					break;
				
				case EH:
					head -> bf = LH;	// Node is now higher on the right side.
					break;
				case RH:				// Node was higher on the right side.	
					head = Balance_Right(head, taller);	
					break;
			}
	}
	
	// If we get here, something didn't work!
	return head;
}


// Find and remove item from the set if it is present. Otherwise ignore.
Status my_set_remove(MY_SET hMY_SET, int item)		
{
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;
	//Node *temp = NULL;
	Status Code;
	
	// If the set isn't initialized, don't bother searching!
	if(hMY_SET == NULL)
	{
		printf("Error: set is not initialized!\n");
		return FAILURE;
	}
	
	// If the set contains no nodes, don't bother searching!
	if(head == NULL)
	{
		printf("Error: No nodes in the set!\n");
		return FAILURE;
	}
	
	// NOT WORKING...
	
	// If the set only has one node, simply compare and return!
	if(head->left == NULL && head->right == NULL)
	{
		if(head->data == item)	// Yep, remove it!
		{
			// Hmm. Seems to have no effect...
			head = NULL;
			pSet->root = NULL;
			return SUCCESS;
		}
	}
	
	// Other wise go through the list and try to find the item.
	Code = Remove(head, item);
	
	if(Code == SUCCESS)
		return SUCCESS;
	
	// If we don't find it, return FAILURE.
	return FAILURE;
}

Status Remove(Node *head, int item)
{
	Status code;

	if(item == head->data)	// If we find the item
	{					// Then delete it!
		if(head->left->data < head->right->data)	// Move right up one.
		{
			head = head->left;
			return SUCCESS;
		}
		else		// Move left up one.
		{
			head = head->right;	
			return SUCCESS;
		}
	}
	
	if(item < head->data)	// Look to the left side
	{
		if(head->left == NULL)	// Store it here! We have room!
		{	
			return FAILURE;
		}
		else		// Keep looking...
		{
			head = head->left;	// Move forward one node.
			code = Remove(head, item);
		}
	}
	else 					// Look to the right side
	{
		if(head->right == NULL)	// we have room.
		{
			return FAILURE;
		}
		else		// Keep looking...
		{
			head = head->right;	// Move forward one node.
			code = Remove(head, item);
		}
	}
	
	// If some recursive function returned a success,
	if(code == SUCCESS)		// Then the item was removed successfully!
		return SUCCESS;
	
	// We didn't find it if we got this far.
	return FAILURE;
}


// Balancing functions.
Node* Balance_Left(Node *head, Boolean *taller)
{
	
		
	return NULL;
}

Node* Balance_Right(Node *head, Boolean *taller)
{
	Node* right = head -> right;		// Right subtree of root
	Node* left;					// Left subtree
	
	switch (right -> bf)
	{
		case RH:
		head -> bf = right -> bf = EH;
		//head = Rotate_Left(head);
		*taller = FALSE;
		break;
		
		case EH:
		printf("Tree is balanced\n");
		break;
		
		case LH:
		break;
	}
	return NULL;
}

// Destroy the data structure and set the handle pointed to by the arg to NULL.
void my_set_destroy(MY_SET* p_hMY_SET)			
{
	My_set *temp = (My_set*)*p_hMY_SET;

	if(temp != NULL)
	{
		destroy(temp->root);
		free(temp);
	}

	*p_hMY_SET = NULL;
	return;
}

// Function called by my_set_destroy
void destroy(Node* root)
{
	if(root == NULL)
	{
		return;
	}
	else
	{
		destroy(root->left);
		destroy(root->right);
		free(root);
	}
}

/* Return the height of the AVL Tree implementation.
  (An empty tree has height 0, a tree with one node has height 1)	*/
int balanced(MY_SET hMY_SET)			
{	
	int lheight = 0;
	int rheight = 0;
	My_set *pSet = (My_set*)hMY_SET;
	Node *head = pSet->root;

	// If the set pointer is NULL, well the list is empty!
	if(head == NULL)
	{				
		return 1;
	}
	
	// Otherwise, search through the list level by level.
	// Once we hit the max level, we can return the # of levels.
	if(head->left == NULL && head->right == NULL)
	{
		return 1;	// Only one node, so height 1. Thus balanced.
	}
	
	// If it isn't height 0 or 1, then we'll have to search the tree.
	// First get the heights of the left side and the right side
	lheight =  height(head -> left);
	rheight =  height(head -> right);
	printf("LEFT: %d\nRIGHT: %d\n", lheight, rheight);
	
	// See if the difference in height is 1 or less. For a balanced AVL tree 
	// it should be 0 or 1. IF IT ISN'T, the AVL tree isn't balanced.
	if(abs(lheight - rheight) <= 1 && _balanced(head -> left) && _balanced(head -> right) )
		return 1;		// AVL Tree is balanced!
		
	// If we get here, the tree is not balanced
	return 0;
}		


int _balanced(Node* temp)
{
	int lheight = 0;
	int rheight = 0;
	
	// If the set pointer is NULL, well the list is empty!
	if(temp == NULL)
	{				
		return 1;
	}
	
	// Otherwise, search through the list level by level.
	// Once we hit the max level, we can return the # of levels.
	if(temp->left == NULL && temp->right == NULL)
	{
		return 1;	// Only one node, so height 1.
	}
	
	// If it isn't height 0 or 1, then we'll have to search the tree.
	// First get the heights of the left side and the right side
	lheight =  height(temp -> left);
	rheight =  height(temp -> right);
	
	// See if the difference in height is 1 or less. For a balanced AVL tree 
	// it should be 0 or 1. IF IT ISN'T, the AVL tree isn't balanced.
	if(abs(lheight - rheight) <= 1 && _balanced(temp -> left) && _balanced(temp -> right) )
		return 1;		// AVL Tree is balanced!
		
	// If we get here, the tree is not balanced
	return 0;
}


int height(Node* node)
{
   // See if the tree is empty
   if(node == NULL)
       return 0;
 
   // If tree is not empty then height = 1 + max of left height and right heights
   return 1 + max(height(node->left), height(node->right));
} 

// returns maximum of two numbers
int max(int a, int b)
{
	// Simply see which is larger
	if(a >= b)
		return a;		// A was larger
	else
		return b;		// B was larger
}    
