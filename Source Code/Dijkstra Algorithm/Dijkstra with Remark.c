// Dijkstra 알고리즘
// 최단 경로 알고리즘
// 네트워크에서 하나의 정점에서 시작해서 다른 나머지 모든 정점까지의 최단 경로를 찾는 알고리즘
// 집합 S를 가지고 출발, S는 시작정점 V로부터 시작함
// 가장 가까운 정점이 발견된다면, S집합의 가장 짧은 거리에 있는 정점을 S에 추가해나감
// S에 모두 추가될 때 까지
// Prim 알고리즘과 유사
// 거쳐감

#include <stdio.h>
#include <limits.h> // 최대 거리 나타내기 위해 필요

// 방문 여부 매크로 처리
#define TRUE 1
#define FALSE 0

// 정점의 최대 개수
#define MAX_VERTICES 10

// 간선이 존재하지 않음
#define INF 1000000

// 가중치 행렬 표현하기 위해서 구조체 선언
typedef struct GraphType {

	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치

} GraphType;

// 최단거리가 구해질 때 마다 그 값을 갱신
int distance[MAX_VERTICES];

// 방문한 정점을 표시
int found[MAX_VERTICES];

// 가장 짧은 거리를 갖는 정점 찾음
int choose(int distance[], int n, int found[]) {

	// 최소값 = min, 최소값의 인덱스 = minpos
	int min, minpos; 

	// min과 minpos 초기화
	min = INT_MAX;
	minpos = -1;

	// min과 해당 minpos 구해서
	for (int i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) { // 거리가 짧아야 && 방문하지 않아야
			min = distance[i];
			minpos = i;
		}
	}

	// minpos 리턴
	return minpos;
}

// 단계별로 진행 현황 출력하기 위한 함수
void print_status(GraphType* g) {

	static int step = 1;
	printf("Step %d ) ", step++);

	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}

	printf("\n");
	printf(" found ) ");
	for (int i = 0; i < g->n; i++) {
		printf("%2d ", found[i]);
	}

	printf("\n\n");

}

// Dijkstra 알고리즘 함수
void shortest_path(GraphType* g, int start) {

	int u;

	// 초기화
	for (int i = 0; i < g->n; i++) {

		distance[i] = g->weight[start][i]; // 정점 i에서 갈 수 있는 모든 정점의 거리
		found[i] = FALSE; // 방문하지 않음으로 표시

	}

	found[start] = TRUE; // 방문함, 집합 S에 포함
	distance[start] = 0; // 자기 자신까지의 비용은 0임

	// start에서 가장 가까운 정점 하나를 선택하기 위한 반복문
	for (int i = 0; i < g->n; i++) {

		print_status(g); // 진행 현황 출력
		u = choose(distance, g->n, found); // u는 가장 짧은 거리를 갖는 정점
		found[u] = TRUE; // 방문함 표시
		
		// distance 배열의 거리값 재설정 -> 작은 값으로 갱신
		for (int w = 0; w < g->n; w++) {
			if (!found[w]) //w가 방문한적 없어야함
				if (distance[u] + g->weight[u][w] < distance[w]) // u로부터 w로 간다, 거쳐서 가는 것이 직접 가는 것보다 짧으면
					distance[w] = distance[u] + g->weight[u][w];
		}
	}

}

int main() {

	// 자기 자신으로 가는 것은 0
	// 간선이 없으면 INF
	GraphType g = { 7,
	{   { 0, 7, INF, INF, 3, 10, INF},
		{ 7, 0, 4, 10, 2, 6, INF },
		{ INF, 4, 0, 2, INF, INF, INF},
		{ INF, 10, 2, 0, 11, 9, 4},
		{ 3, 2, INF, 11, 0, INF, 5},
		{ 10, 6, INF, 9, INF, 0 , INF},
		{ INF, INF, INF, 4, 5, INF, 0}   }
	};

	// 비용 행렬 정보를 가진 g와 시작 정점 0을 전달
	shortest_path(&g, 0);

}