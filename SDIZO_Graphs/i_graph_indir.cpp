#include "i_graph_indir.h"

int i_graph_indir::find_subset(subset subsets[], int i)
{
	if (subsets[i].parent != i)
	{
		subsets[i].parent = find_subset(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

void i_graph_indir::union_subsets(subset subsets[], int x, int y)
{
	int xroot = find_subset(subsets, x);
	int yroot = find_subset(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
	{
		subsets[xroot].parent = yroot;

	}
	else if (subsets[xroot].rank > subsets[yroot].rank)
	{
		subsets[yroot].parent = xroot;
	}
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

bool i_graph_indir::compare_edges(const edge& a,const edge& b)
{
	return a.w > b.w;
}
