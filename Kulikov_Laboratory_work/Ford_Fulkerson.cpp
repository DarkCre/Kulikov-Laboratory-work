#include "Ford_Fulkerson.h"

const int MAX_E = (int)1e6;
const int MAX_V = (int)1e3;
const int INF = (int)1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
    // ������ �����
    onEnd[edgeCount] = v;                   // �� ����� ������� v
    nextEdge[edgeCount] = firstEdge[u];     // ��������� � ������ ������ ��� u
    firstEdge[u] = edgeCount;               // ������ ������ ������ - ����� �����
    capacity[edgeCount++] = cap;            // ������������� ���������� �����������
    // �������� �����
    onEnd[edgeCount] = u;                   // �� ����� ��������� u
    nextEdge[edgeCount] = firstEdge[v];     // ��������� � ������ ������ ��� v
    firstEdge[v] = edgeCount;               // ������ ������ ������ - ����� �����
    capacity[edgeCount++] = 0;              // ������������� ���������� �����������
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; // ���������� ���������� ������� �� ����
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, min(flow, capacity[edge])); // ���� ����� � ���������
            if (minResult > 0) {                    // ���� �����
                capacity[edge] -= minResult;   // � ������ ����� �������� �����
                capacity[edge ^ 1] += minResult;   // � �������� ����������
                return minResult;
            }
        }
    }
    return 0; // ���� �� ����� ����� �� ���� ������� ������ 0
}

//https://gist.github.com/gdhsnlvr/be6d8f1a275eb9902271
int Ford_Fulkerson(int _numOfVertex, int _numOfEdge, int _sourceVertex, int _destinationVertex, unordered_map<int, pair <int, int>>& Graph1) {
    fill(firstEdge, firstEdge + MAX_V, -1);     // -1 �������� ����� ���
    numOfEdge = _numOfEdge;
    numOfVertex = _numOfVertex;
    sourceVertex = _sourceVertex;
    destinationVertex = _destinationVertex;

    for (const auto& elem : Graph1)
    {
        addEdge(elem.second.first, elem.second.second, elem.first);

    }

    // ���������� ������������� ������
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
        fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    // ������� ������������ �����
    cout << maxFlow << endl;
    return 0;
}