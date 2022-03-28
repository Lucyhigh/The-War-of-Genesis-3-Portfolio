//#pragma once
//#include "GameNode.h"
//
//namespace BFS
//{
//	class GraphList :public GameNode
//	{
//	private:
//		List<int>[] _adj;
//		int _size;
//
//	public:
//		GraphList(int n)
//		{
//			_size = n;
//			_adj = new List<int>[_size];
//
//			for (int i = 0; i < _size; i++)
//				_adj[i] = new List<int>();
//		}
//
//		void AddEdge(int a, int b)
//		{
//			_adj[a].Add(b);
//			_adj[b].Add(a);
//		}
//
//		// 1) now를 방문
//		// 2) now와 연결된 정점을 확인해서 "방문안했다면" 방문하기
//		 void BFS(int start)
//		{
//			Queue<int> q = new Queue<int>();
//			bool[] visited = new bool[_size];
//
//			q.Enqueue(start);
//			visited[start] = true;
//
//			while (q.Count > 0)
//			{
//				int now = q.Dequeue();
//				Console.WriteLine(now);
//
//				foreach(int next in _adj[now])
//				{
//					// 이미 방문했는가?
//					if (visited[next])
//						continue;
//
//					q.Enqueue(next);
//					visited[next] = true;
//				}
//			}
//		}
//	};
//
//	class Program :public GameNode
//	{
//		static void Main(string[] args)
//		{
//			GraphList g = new GraphList(6);
//
//			g.AddEdge(0, 1);
//			g.AddEdge(0, 3);
//
//			g.AddEdge(1, 2);
//			g.AddEdge(1, 3);
//
//			g.AddEdge(3, 4);
//
//			g.AddEdge(4, 5);
//
//			g.BFS(0);
//		}
//	};
//}