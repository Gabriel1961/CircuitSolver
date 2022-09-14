#pragma once
#include <vector>
#include <set>
#include <queue>
#include "Edge.h"
#include "Current.h"
#include "Matrix.h"

// TODO proofing grd(u) >= 3 && min 1 edge that leaves/goes to the node
class CircuitSolver
{
private:
	struct _InternalEdge
	{
		std::vector<Resistor> resistors;
		std::vector<VoltageSource> voltageSrcs;
	};

	std::vector<std::vector<_InternalEdge*>> graph;
public:
	CircuitSolver(const std::vector<Edge>& circuit) : edges(circuit)
	{
		using namespace std;
		int mxn = 0;
		for (auto& e : circuit)
		{
			mxn = max(mxn, max(e.n1, e.n2));
		}
		_root = mxn;
		mxn++;
		graph = std::vector<std::vector<_InternalEdge*>>(mxn, std::vector<_InternalEdge*>(mxn, 0));
		for (auto& e : circuit)
		{
			_InternalEdge* edg = new _InternalEdge();
			graph[e.n1][e.n2] = edg;

			edg->resistors.insert(edg->resistors.begin(), e.resistors.begin(), e.resistors.end());

			edg->voltageSrcs.insert(edg->voltageSrcs.begin(), e.voltageSources.begin(), e.voltageSources.end());
		}
		_mat = new Mat(edges.size(), edges.size()+1);
	}

	std::vector<Current> Solve()
	{
		GetIndependentLoops();
		ProcessLoops();
		ProcessNodes();
		auto res = _mat->Solve();
		std::vector<Current> ans(res.size());
		for (int i = 0; i < res.size(); i++)
		{
			ans[i].value = res[i];
			ans[i].n1 = edges[i].n1;
			ans[i].n2 = edges[i].n2;
		}
		return ans;
	}

	~CircuitSolver()
	{
		/*for (size_t i = 0; i < graph.size(); i++)
			for (size_t j = 0; j < graph[i].size(); j++)
				delete graph[i][j];
		delete _mat;*/
	}
public:
	Mat* _mat;
	int _root;
	std::vector<Edge> edges;
	std::vector<std::vector<int>> loops;
	std::vector<std::vector<int>> usedEdges;
	std::vector<int> vis;
	std::vector<int> cpath;
	std::vector<std::vector<int>> GetIndependentLoops()
	{
		using namespace std;
		usedEdges = vector<vector<int>>(graph.size(), vector<int>(graph.size()));
		vis = vector<int>(graph.size());
		cpath.clear();
		loops.clear();
		_Dfs(_root);
		return loops;
	}

	int SearchEdge(int u, int v)
	{
		for (int i = 0; i < edges.size(); i++)
			if (edges[i].n1 == u && edges[i].n2 == v)
				return i;
		return -1;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="u"></param>
	/// <param name="v"></param>
	/// <param name="tem"></param>
	/// <param name="r"></param>
	/// <returns>index of found edge</returns>
	int ProccessEdge(int u, int v, float& tem, float& r)
	{
		r = 0;
		int it;
		float sign;
		if ((it= SearchEdge(u,v)) != -1) // curent pozitiv
			sign = 1;
		else if ((it = SearchEdge(v,u)) != -1) // curent negativ
			sign = -1;
		else throw exception("edge not found");

		for (auto& src : edges[it].voltageSources)
		{
			tem += src.voltage * sign;
			r += src.internalResistor.resistance * sign;
		}
		for (auto& res : edges[it].resistors)
		{
			r += res.resistance * sign;
		}
		return it;
	}
	void ProcessLoops()
	{
		for (int i = 0; i < loops.size(); i++)
		{
			float tem = 0;
			for (int j = 0; j < loops[i].size() - 1; j++)
			{
				int u = loops[i][j], v = loops[i][j + 1];
				auto& edg = graph[u][v];
				float res = 0;
				int idx = ProccessEdge(u, v, tem, res);
				_mat->a[i][idx] = res;
			}
			int u = loops[i].back(), v = loops[i].front();
			auto& edg = graph[u][v];
			float res = 0;
			int idx = ProccessEdge(u, v, tem, res);
			_mat->a[i][idx] = res;
			_mat->a[i][edges.size()] = tem;
		}
	}

	void ProcessNodes()
	{
		for (int i = 0; i < graph.size()-1; i++)
		{
			for (int j = 0; j < edges.size(); j++)
			{
				if (edges[j].n1 == i)
				{
					_mat->a[loops.size() + i][j] = -1;
				}
				if (edges[j].n2 == i)
				{
					_mat->a[loops.size() + i][j] = 1;
				}
			}
		}
	}

	void _Dfs(int k)
	{
		using namespace std;
		cpath.push_back(k);
		vis[k] = 1;


		for (int i = 0; i < graph[k].size(); i++)
		{
			auto to = graph[k][i];
			if (to)
			{
				if (vis[i] == 0)
				{
					_Dfs(i);
				}
			}
			if((graph[k][i] || graph[i][k]) && vis[i] !=0)
			{
				auto st = find(cpath.begin(), cpath.end(), i);
				if (st != cpath.end())
				{
					int uniq = 0;
					vector<int> loop = vector<int>(st, cpath.end());


					for (int j = 0; j < loop.size() - 1; j++)
						if (usedEdges[loop[j]][loop[j + 1]] == 0)
							uniq++;
					uniq += usedEdges[k][i] == 0;
					if (uniq > 0)
					{
						loops.push_back(loop);
						for (int j = 0; j < loop.size() - 1; j++)
							usedEdges[loop[j]][loop[j + 1]] = 1;
						usedEdges[loop.back()][loop.front()] = 1;
					}
				}
			}
		}
		cpath.pop_back();
	}
};


//if (uniq > 0)
//{
//	loops.push_back(loop);
//	for (int j = 0; j < loop.size() - 1; j++)
//		usedEdges[loop[j]][loop[j + 1]] = usedEdges[loop[j + 1]][loop[j]] = 1;
//	usedEdges[k][i] = usedEdges[i][k] = 1;
//}