#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "ds_common.h"
#include <assert.h>
#include "queue.h"
#include "string.h"

int main(int argc, const char *argv[])
{
	printf("%d\n", naiveStrMatching("abcdefghi", "efg"));
	printf("%d\n", kmpStrMatching("abcdefghi","efg"));
	return 0;
}
