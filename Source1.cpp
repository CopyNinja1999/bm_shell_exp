#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <stack>
#include <deque>
#include <queue>
using namespace std;
vector<vector<int> > adj;
struct vertice {
	size_t postOrder = 0;
	size_t preOrder = 0;
	size_t ccNum = 0;
	size_t index = 0;
	bool visited = false;
};
vertice* v;//record the status
int Max(int a, int b, int c)
{
	int max;
	if (a >= b)
	{
		if (a >= c) {
			max = a;
		}
		else
			max = c;
	}
	else if (b >= c) { max = b; }
	else max = c;
	return max;
}
void Input_data(const string& filename) {
	std::fstream in(filename.c_str());
	cout << "reading file:" << filename << endl;
	string s;
	size_t n = 0, m = 0;
	string data1, data2;
	while (true)
	{
		std::getline(in, s);
		istringstream is(s);
		is >> data1 >> data2;
		int d1 = stoi(data1);
		int d2 = stoi(data2);
		n = Max(n, d2, d1);
		m += 1;
		if (in.eof()) { break; }
	}
	//this block will count the number of lines and calculate the maximun number appeared in the file, which are the parameters n, m(vertice, edge)
	in.clear();
	in.seekg(0, ios::beg);
	n += 1;
	m -= 1;
	v = new vertice[n];
	for (size_t i = 0; i < n; i++) {
		v[i].index = i;
	}
	adj = vector<vector<int> >(n, vector<int>());
	for (size_t i = 0; i < m; i++)
	{
		int x, y;
		std::getline(in, s);
		istringstream is(s);
		is >> data1 >> data2;
		x = stoi(data1);
		y = stoi(data2);
		adj[x].push_back(y);
	}
	in.close();
	//this block will assign data into the vertice template in terms of the adjancancy list
}
void dfsStack() {
	//using naive c++ stl stack
	size_t n = adj.size();
	for (size_t i = 0; i < n; i++)
	{
		v[i].visited = false;
	}
	stack<vertice> S;
	for (size_t k = 0; k < n; k++) {
		if (v[k].visited) { continue; }
		else
			v[k].visited = true;//start point v[0]
		S.push(v[k]);
		while (!S.empty())
		{
			vertice u = S.top();
			S.pop();//these two steps represent the operation pop
			size_t m = adj[u.index].size();
			int  index = -1;
			for (size_t j = 0; j < m; j++)
			{
				size_t i = adj[u.index][j];
				if (!v[i].visited)
				{
					index = i;
					break;
				}
			}
			if (index != -1)
			{
				S.push(u);
				v[index].visited = true;
				S.push(v[index]);
			}
		}
	}


	//S.~stack<vertice>();//release memory
}
void dfsDeque() {
	size_t n = adj.size();
	for (size_t i = 0; i < n; i++)
	{
		v[i].visited = false;
	}
	deque<vertice> D;
	for (size_t k = 0; k < n; k++) {
		if (v[k].visited) { continue; }
		else
			v[k].visited = true;//start point v[0]
		D.push_front(v[k]);
		while (!D.empty())
		{
			vertice u = D.front();
			D.pop_front();
			size_t m = adj[u.index].size();
			int index = -1;
			for (size_t j = 0; j < m; j++)
			{
				size_t i = adj[u.index][j];
				if (!v[i].visited)
				{
					index = i;
					break;
				}
			}
			if (index != -1)
			{
				D.push_front(u);
				v[index].visited = true;
				D.push_front(v[index]);
			}
		}
	}
	//D.~deque<vertice>();//release memory

}
void bfsQueue()
{
	size_t n = adj.size();
	for (size_t i = 0; i < n; i++)
	{
		v[i].visited = false;
	}
	queue<vertice> Q;
	for (size_t k = 0; k < n; k++) {
		if (v[k].visited) {
			continue;
		}
		else
			v[k].visited = true;
		Q.push(v[k]);
		while (!Q.empty())
		{
			vertice u = Q.front();
			Q.pop();//these two steps represent the operation dequeue()
			size_t m = adj[u.index].size();
			for (size_t j = 0; j < m; j++)
			{
				size_t i = adj[u.index][j];
				if (!v[i].visited)
				{
					v[i].visited = true;
					Q.push(v[i]);
				}
			}

		}
	}
	//Q.~queue<vertice>();
}
void bfsDeque() {
	size_t n = adj.size();
	for (size_t i = 0; i < n; i++)
	{
		v[i].visited = false;
	}
	deque<vertice> D;
	for (size_t k = 0; k < n; k++) {
		if (v[k].visited) { continue; }
		else
			v[k].visited = true;
		D.push_back(v[k]);
		while (!D.empty())
		{
			vertice u = D.front();
			D.pop_front();//these two steps represent the operation dequeue()
			size_t m = adj[u.index].size();
			for (size_t j = 0; j < m; j++)
			{
				size_t i = adj[u.index][j];
				if (!v[i].visited)
				{
					v[i].visited = true;
					D.push_back(v[i]);
				}
			}

		}
	}
	//D.~deque<vertice>();
}
void write_output_dfs() {
	ofstream exp_data("bipartite_test.txt");// For the convenience of analyzing
		auto start = chrono::steady_clock::now();
		dfsStack();
		auto end1 = chrono::steady_clock::now();
		dfsDeque();
		auto end2 = chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_time1 = end1 - start;
		std::chrono::duration<double> elapsed_time2 = end2 - end1;
		exp_data <<adj.size() << " " << elapsed_time1.count() * 1000 << " " << elapsed_time2.count() * 1000 << "\n";
	exp_data.close();
}
void Print_data() {
	int n = adj.size();
	for (int i = 0; i < n; i++) {
		int m = adj[i].size();
		cout << i << ": ";
		for (int j = 0; j < m; j++) { cout << adj[i][j] << " ,"; }
		cout << endl;

	}

}
int main() {
	Input_data("out.txt");
	//Print_data();
	write_output_dfs();
}