#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
int parent[MAX_VERTICES];

// parent 배열 초기화
void set_init(int n) {

	for (int i = 0; i < n; i++) parent[i] = -1;

}

// 간선의 정보
struct Edge {

	int start, end, weight;

};

// 그래프 정보
typedef struct GraphType {

	int n; // 간선의 개수
	struct Edge edges[2 * MAX_VERTICES];

} GraphType;

// 초기화
void graph_init(GraphType* g) {

	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = 999; // 가중치 매우 크다 = 간선 존재 X
	}

}

// 간선 삽입
void insert_edge(GraphType* g, int start, int end, int weight) {

	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = weight;
	g->n++;

}

// 사이클 여부 판정 함수
int set_find(int curr) {

	// 부모노드가 존재하느냐
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) curr = parent[curr]; // 부모의 부모를 다시 curr로
	return curr;

}

void set_union(int a, int b) {

	int root1 = set_find(a); // 5 (uset에 대한 부모노드)
	int root2 = set_find(b); // 0 (vset에 대한 부모노드)
	if (root1 != root2) { // 간선 가능
		parent[root1] = root2;
	}

}

// qsort 함수의 정렬방식을 결정하는 함수 (오름차순이냐 내림차순이냐)
// 1,0,-1 값 중 하나를 리턴
// 리턴값이 1이면 오름차순
// 리턴값이 -1이면 내림차순
// 두 값이 같으면 0을 리턴
int compare(const void *a, const void *b) { // 주소값 넘겨받음

	// if 사용할 수도 있지만 마이너스 구조 사용
	struct Edge *x = (struct Edge*)a; // casting
	struct Edge* y = (struct Edge*)b; // casting
	return (x->weight - y->weight); // 앞에 값이 큼, 1 리턴 => 오름차순

}

void kruskal(GraphType* g) {
	
	int edge_accepted = 0; // 간선의 개수 counting하는 변수, 정점개수-1 이어야
	int uset, vset; // 각각의 선택 여부 판단하는 변수
	struct Edge e; // 구조체 임시 변수

	// 정렬 함수, 
	// 첫번째 매개변수 = 정렬하기 위한 데이터 집합
	// 두번째 = 정렬하기 위한 데이터 개수
	// 세번째 = 한 데이터의 크기 (ex. int = 4 => sizeof 연산자 사용)
	// 네번째 = 정렬을 수행하는 방식에 대한 함수를 기록

	qsort(g->edges, g->n, sizeof(struct Edge), compare); // compare 함수 개발자가 작성

	set_init(g->n); // Parent값 -1로 초기화 해야함

	// kruskal 알고리즘 시작
	int i = 0;
	
	// 반복의 조건(정점개수-1 이어야)
	while (edge_accepted < (g->n - 1)) {
		e = g->edges[i]; // 0번 꺼내면 가장 작은 값의 데이터 가져오게 됨
		uset = set_find(e.start); // 정점의 집합 번호 결정, uset = 5, 2
		vset = set_find(e.end); // 정점의 집합 번호 결정,   vset = 0, 3
		
		// uset과 vset이 같다 = 사이클 만들어질 수 있다
		if (uset != vset) { // 같지 않으면 Spanning Tree 간선으로 인정, 두 개의 정점 출력
			printf("간선:(%d, %d) :%d 선택\n", e.start, e.end, e.weight);
			edge_accepted++; // 간선의 수 하나 증가
			set_union(uset, vset); // 집합으로 만든다
		}
		i++;
	}

}

int main() {

	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));

	graph_init(g);
	// a = 0, b = 1, c = 2, d = 4, e = 5, f = 6, g = 7

	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);

	kruskal(g);

	free(g);

}