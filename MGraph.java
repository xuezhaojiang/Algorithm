package test;

import java.util.HashSet;

public class MGraph {
	private static int  DIM= 6;
	private static int UNCONNECTED=1000;
	private static int INFINITY=10000;
	
	public static int min(int a, int b) {
		return a > b ? b : a;
	}
	public static void VisitFuncion(int v){
		System.out.println(v);
	}
	
	public static void DFSTraverse(int[][] Graph){
		boolean[] visited=new boolean[DIM];
		for(int v=0;v<DIM;v++)
			visited[v]=false;
		for(int v=0;v<DIM;v++)
			if(!visited[v])
				DFS(Graph,visited,v);
	}

	public static void DFS(int[][] Graph,boolean[] visited,int v){
		visited[v]=true;
		VisitFuncion(v);
		for(int w=FirstAdjVex(Graph,v);w>=0&&w<DIM;w=NextAdjVex(Graph,v,w))
			if(!visited[w])
				DFS(Graph,visited,w);
	}
	public static int FirstAdjVex(int[][] Graph,int v){
		int w=0;
		for(w=0;w<DIM;w++)
			if(Graph[v][w]>0&&Graph[v][w]!=UNCONNECTED)
				break;
		return w;
	}

	public static int NextAdjVex(int[][] Graph,int v,int w){
		int i=0;
		for(i=w+1;i<DIM;i++)
			if(Graph[v][i]>0&&Graph[v][w]!=UNCONNECTED)
				break;
		return i;
	}
	private static void ShortestPath(int[][] Graph,int v0,int [][] PathMatrix,int[] D) {
		/*
		Graph是有向图
		起点\终点 0  1  2  3
		 0
		 1
		 2
		 3
		
		PathMatric[i][j]是从v0出发到vi的路上，途径vj
		
		终点\经过 0  1  2  3
		 0       0 -1 -1 -1 
		 1       0  
		 2       0  2  3  1
		 3       0
		从0到0不经过1，2，3所以值为-1
		从0出发，所以0的列为0表示起点
		表示0->3->1->2
		
		D[i]是从v0出发到达vi的最短距离
		*/
		for(int i=0;i<DIM;i++){
			D[i]=Graph[v0][i];
			for(int j=0;j<DIM;j++){
				PathMatrix[i][j]=-1;
			}
			PathMatrix[i][v0]=0;
			PathMatrix[i][i]=1;
		}
		HashSet<Integer> S=new HashSet<>();//S是已经找到最短路径的顶点的集合
		S.add(v0);
		
		int min;
		int m = 0;
		for(int i=1;i<DIM;i++){//仅仅控制循环次数，向s中添加dim-1个顶点
			min=INFINITY;
			for(int j=0;j<DIM;j++){
				if(!S.contains(j)){//j还没找到
					if(D[j]<min){
						m=j;
						min=D[j];
					}
				}
			}
			S.add(m);//顶点m已经找到最短路径
			
			for(int j=0;j<DIM;j++){//更新最短路径
				if(!S.contains(j)&&(min+Graph[m][j]<D[j])){
					//最短路径只可能是已经找到的最短路径或者是新增加的这条路径
					D[j]=min+Graph[m][j];
					//更新路径
					for(int k=0;k<DIM;k++){
						//copy到m的路径
						PathMatrix[j][k]=PathMatrix[m][k];
					}
					//更新从j到j
					PathMatrix[j][j]=PathMatrix[j][m]+1;
				}
			}
		}
	}
	public static int[][] InitGraph() {
		int[][]Graph2 = new int[][]{ { 0, 2, 10, 5, 3, 1000 }, { 1000, 0, 12, 1000, 1000, 10 }, { 1000, 1000, 0, 1000, 7, 1000 },
				{ 2, 1000, 1000, 0, 2, 1000 }, { 4, 1000, 1000, 1, 0, 1000 }, { 3, 1000, 1, 1000, 2, 0 } };
		return Graph2;	
	}
	public static void main(String[] args) {
		int[][] Graph = null;
		Graph=InitGraph();
		DFSTraverse(Graph);
	}
}