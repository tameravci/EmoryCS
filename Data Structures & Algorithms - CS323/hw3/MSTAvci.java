package span;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;

import graph.Edge;
import graph.Graph;

public class MSTAvci implements MSTAll{
	
		public List<SpanningTree> getMinimumSpanningTrees(Graph graph) {
			Set<Integer> visited = new HashSet<>();
			PriorityQueue<Edge> queue = new PriorityQueue<>();
			SpanningTree tree = new SpanningTree();
			List<SpanningTree> trees = new ArrayList<>();
			add(queue, visited, graph, 0);
			getMSTAux(graph, trees, queue, tree, visited);
			return trees;
		}
		
		
		public void getMSTAux(Graph graph, List<SpanningTree> trees, PriorityQueue<Edge> queue, SpanningTree tree, Set<Integer> visited) {
			if(!trees.isEmpty() && trees.get(0).compareTo(tree) < 0)
				return;
			if(tree.size() + 1 == graph.size()) {
				trees.add(tree);
				return;
			}
			List<Edge> l = new ArrayList<>();
			for (Edge e: queue) {
				if(visited.contains(e.getSource()))
					l.add(e);
			}
			queue.removeAll(l); 
			if(queue.isEmpty())
				return;
			Edge e;
			do
			{
				e = queue.poll();
				if(!visited.contains(e.getSource())) {
					PriorityQueue<Edge> q = new PriorityQueue<>(queue);
					Set<Integer> s = new HashSet<>(visited);
					SpanningTree t = new SpanningTree(tree);
					t.addEdge(e);
					add(q, s, graph, e.getSource());
					getMSTAux(graph, trees, q, t, s);
				}
			}
			while(!queue.isEmpty() && queue.peek().compareTo(e) == 0);
		}
			
		
		/**
		 * @param queue Queue of all vertices awaited to explore
		 * @param visited Set of visited vertices
		 * @param graph Graph
		 * @param target Target vertex
		 */
		private void add(PriorityQueue<Edge> queue, Set<Integer> visited, Graph graph, int target)
		{
			visited.add(target);
			
			for (Edge edge : graph.getIncomingEdges(target))
			{
				if (!visited.contains(edge.getSource()))
					queue.add(edge);
			}
		}
	} 

