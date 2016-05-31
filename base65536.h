/* base65536 semi-library header.
(C) 2016 Tobias Girstmair, http://isticktoit.net/
Released under the GNU GPL v3. See LICENSE for details. */

#ifndef __BASE65536_H__
#define __BASE65536_H__
#define B65536_TREE_SIZE 257

int base65536_encode_char (const int* in_buf);
int base65536_decode_char (const int in_cp, int* out_buf);

int codepoint_to_utf8 (int unicode, char* buf);
int utf8_to_codepoint (char* buf);

struct block* get_block_by_index (struct block* tree, int index, int len, int pos);
struct block* get_block_by_start (struct block* tree, int start, int len, int pos);

#define NOT_FOUND -2 /*for when tree_find_*() does not return a valid result*/
#define B65K_EOF  -1

int tree_find_index (int block);
int tree_find_block(int index);

struct block {
	int num;
	int start;
};
#endif
