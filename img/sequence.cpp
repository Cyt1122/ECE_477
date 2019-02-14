#include <stdlib.h>
#include <stdio.h>

typedef struct tree_ex {
	long val;
	tree_ex* left_node;
	tree_ex* right_node;
}tree_ex;

tree_ex* generate_tree(int length, tree_ex* root, int* seq_size, int curr_val) {
	/*determine if out of bound*/
	if (curr_val >= length)
		return root;
	/*initiate another node*/
	root = (tree_ex*)malloc(sizeof(tree_ex));
	root->left_node = NULL;
	root->right_node = NULL;
	root->val = curr_val;
	(*seq_size) ++;
	/*recursion*/
	root->left_node = generate_tree(length, root->left_node, seq_size, root->val * 2);
	root->right_node = generate_tree(length, root->right_node, seq_size, root->val * 3);
	return root;
}

void visit_tree(tree_ex* root, long* arr, int clear) {
	static int i = 0;
	if (clear == 1) {
		i = 0;
		clear = 0;
	}
	if (root == NULL)
		return;
	arr[i] = root->val;
	i++;
	visit_tree(root->left_node, arr, 0);
	visit_tree(root->right_node, arr, 0);
}
// compare function for qsort
int compare(const void * a, const void * b) {	
	return *(long*)a - *(long*)b;
}

long *Generate_2p3q_Seq(int length, int *seq_size) {
	/**if the length is zero return directly**/
	if (length == 0) {
		*seq_size = 0;
		return NULL;
	}
	/**initiate the root which is 1**/
	tree_ex* root = NULL;
	/*generate the code tree*/
	root = generate_tree(length, root, seq_size, 1);
	/*visit the tree and store the sequence*/
	long* arr = (long *)malloc(sizeof (long) * (*seq_size + 2)); // plus 2 zeros in the end to manipulate
	for (int i = 0; i < *seq_size + 2; i++) {
		arr[i] = 0;
	}
	visit_tree(root, arr, 1);
	/*sort the array use quick sort*/
	qsort(arr, *seq_size, sizeof(long), compare);
	/*overlap the doubled number and free the unused*/
	for (int i = 1; i < *seq_size; i++) {
		if (arr[i] == arr[i - 1] && arr[i] != 0) {
			for (int j = i - 1; j < *seq_size; j++) {
				arr[j] = arr[j + 1];
			}
			i--;
		}
	}

	// after the manipulation the length cannot exceed *seq_size
	int count = 0;
	for (int i = 0; i < *seq_size + 2; i++) {
		if (arr[i] != 0)
			count++;
	}
	*seq_size = count;
	return arr;
}

void tree_destroy(tree_ex* root) {
	if (root == NULL)
		return;
	tree_destroy(root->left_node);
	tree_destroy(root->right_node);
	free(root);
}

long *Generate_2p3q_Seq_2(int size, int *seq_size) {
	int powers_3 = 1; // powers of 3
	int p = 0; // exponent of powers of 3
	while (powers_3 < size) { // terminates when powers of 3 >= size
		 powers_3 *= 3;
		 p++;
	}
	 long * sequence = (long *)malloc(sizeof(long)*p*(p + 1));
	 int seq_count = -1; // location of last int in sequence
	 int next_idx = 0; // location to generate next int in sequence
	 int k = 1; // next int in sequence
	 powers_3 = 3; // next powers of 3 in sequence
	 while (k < size) { // terminates when k >= size
		seq_count++; // increment seq_count
		sequence[seq_count] = k; // save k in sequence
		if (sequence[next_idx] * 2 > powers_3) { // determine the next k
			k = powers_3; // k is some 3^q
			powers_3 *= 3;
		}
		else { // or
			 k = sequence[next_idx] * 2; // k is 2 * some int in sequence
			 next_idx++; // i.e., k is some 2^p 3^q
		}
	}
	* seq_size = seq_count + 1;
	printf("%d", seq_count);
	return sequence;
}
