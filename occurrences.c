#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

struct words {
	char *w;
	int cnt;
	struct words *next;
};

struct words *word_list = NULL;

static void insert_node(char *in, int len)
{
	struct words *curr = word_list;

	if (!in)
		return;

	while (curr) {
		if (strncmp(curr->w, in, len) == 0) {
			curr->cnt ++;
			return;
		}
		curr = curr->next;
	}

	curr = (struct words *)calloc(1, sizeof(struct words));
	curr->w = (char *)calloc(1, len + 1);

	memcpy(curr->w, in, len);
	curr->cnt = 1;

	curr->next = word_list;
	word_list = curr;
}

static void print_nodes(void)
{
	struct words *p = word_list;
	while(p) {
		printf("%s %d\n", p->w, p->cnt);
		p = p->next;
	}
}

static int check_words(char *str, ssize_t len)
{
	size_t i = 0;
	size_t begin = -1;

	if (!str)
		return -1;

	for (i = 0; i < len; i++) {
		if (isalpha(str[i])) {
			if (begin == -1)
				begin = i;
			continue;
		} else {
			if (begin == -1) {
				continue;
			} else {
				insert_node(&str[begin], i - begin);
				begin = -1;
			}
		}
	}

	return 0;
}

int main()
{
	char buf[1024] = { 0 };
	while (fgets(buf, sizeof(buf), stdin)) {
		check_words(buf, strlen(buf));
	}

	print_nodes();

	return 0;
}
