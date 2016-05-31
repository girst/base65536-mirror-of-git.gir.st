/*
	this is a helper program to generate c code for a complete binary
	search tree, containg the codepoints used for base65536, as defined by
	github user ferno. 
	why a binary search tree? because i am studying compsci - that's why! :P
	the struct bnode contains the data in the same format as will be used
	in the 'real' program, but the btree array is not yet in tree form. 

	execute `gcc -std=c99 generate_struct.c -lm`

	(C) 2016 Tobias Girstmair, http://isticktoit.net/
	Released under the GNU GPL v3. See LICENSE for details.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct bnode {
	int block; /* index for the blocks, as defined by ferno */
	int start; /* start of each block, as defined by ferno */
};

/*	it is easier to create a full (perfect) tree, and add those extra bits
	afterwards to the leftmost node in the bottom row. */
struct bnode extra [] = {
	{-1, 5376},
	{1, 13568}
};
struct bnode btree [] = {
/*	{-1, 5376},*/
	{0, 13312}, 
/*	{1, 13568}, */
	{2, 13824}, 
	{3, 14080}, 
	{4, 14336}, 
	{5, 14592}, 
	{6, 14848}, 
	{7, 15104}, 
	{8, 15360}, 
	{9, 15616}, 
	{10, 15872}, 
	{11, 16128}, 
	{12, 16384}, 
	{13, 16640}, 
	{14, 16896}, 
	{15, 17152}, 
	{16, 17408}, 
	{17, 17664}, 
	{18, 17920}, 
	{19, 18176}, 
	{20, 18432}, 
	{21, 18688}, 
	{22, 18944}, 
	{23, 19200}, 
	{24, 19456}, 
	{25, 19968}, 
	{26, 20224}, 
	{27, 20480}, 
	{28, 20736}, 
	{29, 20992}, 
	{30, 21248}, 
	{31, 21504}, 
	{32, 21760}, 
	{33, 22016}, 
	{34, 22272}, 
	{35, 22528}, 
	{36, 22784}, 
	{37, 23040}, 
	{38, 23296}, 
	{39, 23552}, 
	{40, 23808}, 
	{41, 24064}, 
	{42, 24320}, 
	{43, 24576}, 
	{44, 24832}, 
	{45, 25088}, 
	{46, 25344}, 
	{47, 25600}, 
	{48, 25856}, 
	{49, 26112}, 
	{50, 26368}, 
	{51, 26624}, 
	{52, 26880}, 
	{53, 27136}, 
	{54, 27392}, 
	{55, 27648}, 
	{56, 27904}, 
	{57, 28160}, 
	{58, 28416}, 
	{59, 28672}, 
	{60, 28928}, 
	{61, 29184}, 
	{62, 29440}, 
	{63, 29696}, 
	{64, 29952}, 
	{65, 30208}, 
	{66, 30464}, 
	{67, 30720}, 
	{68, 30976}, 
	{69, 31232}, 
	{70, 31488}, 
	{71, 31744}, 
	{72, 32000}, 
	{73, 32256}, 
	{74, 32512}, 
	{75, 32768}, 
	{76, 33024}, 
	{77, 33280}, 
	{78, 33536}, 
	{79, 33792}, 
	{80, 34048}, 
	{81, 34304}, 
	{82, 34560}, 
	{83, 34816}, 
	{84, 35072}, 
	{85, 35328}, 
	{86, 35584}, 
	{87, 35840}, 
	{88, 36096}, 
	{89, 36352}, 
	{90, 36608}, 
	{91, 36864}, 
	{92, 37120}, 
	{93, 37376}, 
	{94, 37632}, 
	{95, 37888}, 
	{96, 38144}, 
	{97, 38400}, 
	{98, 38656}, 
	{99, 38912}, 
	{100, 39168}, 
	{101, 39424}, 
	{102, 39680}, 
	{103, 39936}, 
	{104, 40192}, 
	{105, 40448}, 
	{106, 41216}, 
	{107, 41472}, 
	{108, 41728}, 
	{109, 42240}, 
	{110, 67072}, 
	{111, 73728}, 
	{112, 73984}, 
	{113, 74240}, 
	{114, 77824}, 
	{115, 78080}, 
	{116, 78336}, 
	{117, 78592}, 
	{118, 82944}, 
	{119, 83200}, 
	{120, 92160}, 
	{121, 92416}, 
	{122, 131072}, 
	{123, 131328}, 
	{124, 131584}, 
	{125, 131840}, 
	{126, 132096}, 
	{127, 132352}, 
	{128, 132608}, 
	{129, 132864}, 
	{130, 133120}, 
	{131, 133376}, 
	{132, 133632}, 
	{133, 133888}, 
	{134, 134144}, 
	{135, 134400}, 
	{136, 134656}, 
	{137, 134912}, 
	{138, 135168}, 
	{139, 135424}, 
	{140, 135680}, 
	{141, 135936}, 
	{142, 136192}, 
	{143, 136448}, 
	{144, 136704}, 
	{145, 136960}, 
	{146, 137216}, 
	{147, 137472}, 
	{148, 137728}, 
	{149, 137984}, 
	{150, 138240}, 
	{151, 138496}, 
	{152, 138752}, 
	{153, 139008}, 
	{154, 139264}, 
	{155, 139520}, 
	{156, 139776}, 
	{157, 140032}, 
	{158, 140288}, 
	{159, 140544}, 
	{160, 140800}, 
	{161, 141056}, 
	{162, 141312}, 
	{163, 141568}, 
	{164, 141824}, 
	{165, 142080}, 
	{166, 142336}, 
	{167, 142592}, 
	{168, 142848}, 
	{169, 143104}, 
	{170, 143360}, 
	{171, 143616}, 
	{172, 143872}, 
	{173, 144128}, 
	{174, 144384}, 
	{175, 144640}, 
	{176, 144896}, 
	{177, 145152}, 
	{178, 145408}, 
	{179, 145664}, 
	{180, 145920}, 
	{181, 146176}, 
	{182, 146432}, 
	{183, 146688}, 
	{184, 146944}, 
	{185, 147200}, 
	{186, 147456}, 
	{187, 147712}, 
	{188, 147968}, 
	{189, 148224}, 
	{190, 148480}, 
	{191, 148736}, 
	{192, 148992}, 
	{193, 149248}, 
	{194, 149504}, 
	{195, 149760}, 
	{196, 150016}, 
	{197, 150272}, 
	{198, 150528}, 
	{199, 150784}, 
	{200, 151040}, 
	{201, 151296}, 
	{202, 151552}, 
	{203, 151808}, 
	{204, 152064}, 
	{205, 152320}, 
	{206, 152576}, 
	{207, 152832}, 
	{208, 153088}, 
	{209, 153344}, 
	{210, 153600}, 
	{211, 153856}, 
	{212, 154112}, 
	{213, 154368}, 
	{214, 154624}, 
	{215, 154880}, 
	{216, 155136}, 
	{217, 155392}, 
	{218, 155648}, 
	{219, 155904}, 
	{220, 156160}, 
	{221, 156416}, 
	{222, 156672}, 
	{223, 156928}, 
	{224, 157184}, 
	{225, 157440}, 
	{226, 157696}, 
	{227, 157952}, 
	{228, 158208}, 
	{229, 158464}, 
	{230, 158720}, 
	{231, 158976}, 
	{232, 159232}, 
	{233, 159488}, 
	{234, 159744}, 
	{235, 160000}, 
	{236, 160256}, 
	{237, 160512}, 
	{238, 160768}, 
	{239, 161024}, 
	{240, 161280}, 
	{241, 161536}, 
	{242, 161792}, 
	{243, 162048}, 
	{244, 162304}, 
	{245, 162560}, 
	{246, 162816}, 
	{247, 163072}, 
	{248, 163328}, 
	{249, 163584}, 
	{250, 163840}, 
	{251, 164096}, 
	{252, 164352}, 
	{253, 164608}, 
	{254, 164864}, 
	{255, 165120} 
};

struct lnode {
	struct bnode data;
	struct lnode* left;
	struct lnode* right;
};

int find_part (int n) {
	/* http://stackoverflow.com/a/26896494 */
	int x = 1;
	while (x <= n/2) x*=2;

	if (x/2 - 1 <= (n-x)) return x-1;
	else return n - x/2;
}

struct lnode* gen_tree (struct bnode* a, int start, int end) {
	if (start > end) return NULL;
	//int mid = (end-start)/2+start; //will be right-aligned
	//int mid = ceil ((end-start)/2.0)+start; //will be half left-, half middle-aligned
	int mid = find_part (end-start)+start;

	struct lnode* b = malloc (sizeof (struct lnode));
	b->data.block = a[mid].block;
	b->data.start = a[mid].start;
	b->left = gen_tree (a, start, mid-1);
	b->right = gen_tree (a, mid+1, end);

	return b;
}

/* to print it breadth first, we need to implement a queue first :| */
struct queue {
	struct lnode* data;
	struct queue* next;
};
int empty (struct queue* q) {return q == NULL;}
void prepend (struct queue** q, struct lnode* d) {
	struct queue* tmp = malloc (sizeof (struct queue));
	tmp->data = d;
	tmp->next = *q;
	*q = tmp;
}
struct lnode* get_e (struct queue* q, int index) {
	for (int i = 0; i < index; q = q->next, i++);
	return q->data;
}
void del_e (struct queue** q, int index) {
	if (index == 0) {
		struct queue* tmp = (*q)->next;
		free (*q);
		(*q) = tmp;
	} else {
		struct queue* p = (*q);
		for (int i = 0; i < index-1; p = p->next, i++);
		free (p->next);
		p->next = p->next->next;
	}
}
void enqueue (struct queue** q, struct lnode* d, int* size) {
	prepend (q, d);
	(*size)++;
}
struct lnode* dequeue (struct queue** q, int* size) {
	(*size)--;
	struct lnode* retval = get_e (*q, *size);
	del_e (q, *size);
	return retval;
}
void print (struct lnode* l) {
	struct queue* q = NULL;
	int s = 0;

	enqueue (&q, l, &s);
	while (!empty (q)) {
		struct lnode* node = dequeue (&q, &s);
		if (node->data.start != 0) printf ("{%d, %d}, \n", node->data.block, node->data.start);
		if (node->left != NULL) enqueue (&q, node->left, &s);
		if (node->right != NULL) enqueue (&q, node->right, &s);
	}
	// add the extra bits:
	printf ("{%d, %d}, \n{%d, %d}", extra[0].block, extra[0].start, extra[1].block, extra[1].start);
}


int main () {
	int len = 255;
	struct lnode* s = gen_tree (btree, 0, len);
	print (s);

	//NOTE: memory occupied by the tree-as-linked-list is not freed. deal with it. 
}
