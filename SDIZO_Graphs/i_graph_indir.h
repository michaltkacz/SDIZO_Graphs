#pragma once

class i_graph_indir
{
public:
	virtual void mst_prim() = 0;
	virtual void mst_kruskal() = 0;

protected:
	struct edge
	{
		int v1;
		int v2;
		int w;
	};

	bool compare_edges(const edge& a, const edge& b);

	struct subset
	{
		int parent;
		int rank;
	};

	int find_subset(subset subsets[], int i);
	void union_subsets(subset subsets[], int x, int y);

};
