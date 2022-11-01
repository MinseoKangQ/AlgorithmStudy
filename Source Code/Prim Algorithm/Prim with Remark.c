#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100 // 최대 정점의 개수
// 시작 distance는 0, 나머지 무한대, 무한대 표현하기 위해서 INF 정의
#define INF 1000L 

// 그래프를 행렬로 표현하기 위한 구조체 선언
typedef struct GraphType {

	int n;  // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치 값 저장하는 2차 배열

} GraphType;

// Prim 알고리즘 적용시 중요한 1차 배열 distance[]
// 방문 여부 체크하는 배열 selected[]
// 두 배열 모두 정점의 개수만큼 필요함
int distance[MAX_VERTICES];
int selected[MAX_VERTICES];

int get_min_vertex(int n) { // 정점의 개수 n 전달받음
	
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) { // 방문하지 않은 것이라면
			v = i; // 방문하지 않은 정점 v 발견
			break;
		}

	// v 정점에 대해 최소값을 갖는 i를 찾아야 함
	for (int i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v]))
			v = i; // 최소 정점에 해당하는 v 얻을 수 있음
	}
	return v;

}

void prim(GraphType* g, int s) {

	int i, u, v;

	// 시작 제외한 나머지는 무한대로 초기화
	for (u = 0; u < g->n; u++)
		distance[u] = INF;

	// 시작 0으로 초기화
	distance[s] = 0;

	// 모든 인접한 정점을 찾아야 함
	for (i = 0; i < g->n; i++) { // 정점의 개수만큼
		u = get_min_vertex(g->n); // distance 값 가장 작은 것 뽑기
		selected[u] = TRUE; // 방문함을 표시
		if (distance[u] == INF) return; // 최소값으로 넘겨받은 것이 무한대라면 무의미
		printf("정점 %d 추가\n", u); // 선택된 정점 출력

		// 새로운 v 찾기
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) // 무한대가 아니여야 하고
				if (!selected[v] && g->weight[u][v] < distance[v]) // 방문하지 않았어야 함
					distance[v] = g->weight[u][v]; // distance 갱신
		}
	}

}

int main() {

	// 가중치 행렬에 대한 값을 채워줘야 함
	GraphType g = { 7, // 정점의 개수
		{ { 0, 29, INF, INF, INF, 10, INF }, // 0번째 행에 해당하는 초기값
		  { 29, 0, 16, INF, INF, INF, 15 }, // 1번째 행에 해당하는 초기값
		  { INF, 16, 0 , 12, INF, INF, INF }, // 2번째 행에 해당하는 초기값
		  { INF, INF, 12, 0 , 22, INF, 18 }, // 3번째 행에 해당하는 초기값
		  { INF, INF, INF, 22, 0 , 27, 25 }, // 4번째 행에 해당하는 초기값
		  { 10, INF, INF, INF, 27, 0, INF}, // 5번째 행에 해당하는 초기값
		  { INF, 15, INF, 18, 25, INF, 0 }  // 6번째 행에 해당하는 초기값
		}
	};

	prim(&g, 0); // start 정점 0 전달

}