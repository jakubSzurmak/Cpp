#include <iostream>
#include "Sll.h"
#include "Vector.h"

typedef struct Edge {
  int dest;
  int weight;
  struct Edge* next;
} Edge;

typedef struct Node {
  Edge* head;
} Node;

typedef struct Graph {
  int size;
  Node* nodes;
} Graph;

typedef struct {
  int data;
  int priority;
} QueueItem;

typedef struct {
  QueueItem* items;
  int count;
  int capacity;
} PriorityQueue;

void init(PriorityQueue* queue, int size){
  queue->count = 0;
  queue->capacity = size;
  queue->items = new QueueItem[size];
}

void push(PriorityQueue* queue, int data, int priority) {
  if (queue->count == queue->capacity) {
    queue->capacity = (int)(1.5*queue->capacity);
    queue->items = (QueueItem*) realloc(queue->items, sizeof(QueueItem)*(1.5*queue->capacity));
  }
  int i;
  for (i = queue->count - 1; i >= 0; i--) {
    if (queue->items[i].priority > priority) {
      queue->items[i + 1] = queue->items[i];
    } else {
      break;
    }
  }
  queue->items[i + 1].data = data;
  queue->items[i + 1].priority = priority;
  queue->count++;
}

int pop(PriorityQueue* queue) {
  if (queue->count == 0) {
    return -1;
  }
  int data = queue->items[0].data;
  int i;
  for (i = 0; i < queue->count - 1; i++) {
    queue->items[i] = queue->items[i + 1];
  }
  queue->count--;
  return data;
}

Graph* createGraph(int size) {
  auto graph = new Graph;
  graph->size = size;
  graph->nodes = new Node[size];
  for (int i = 0; i < size; i++) {
    graph->nodes[i].head = nullptr;
  }
  return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
  Edge* edge = new Edge;
  edge->dest = dest;
  edge->weight = weight;
  edge->next = graph->nodes[src].head;
  graph->nodes[src].head = edge;
}

char *readCityName() {
  char ch = '-';
  short len = 0;
  short size = 4;
  char *buff = (char *) realloc(nullptr, sizeof(*buff) * size);

  while (ch != ' ') {
    ch = (char) getchar();
    if (ch == '\n') {
      ch = (char) getchar();
    } else if (ch == ' ') {
      break;
    }
    buff[len] = ch;
    len++;
    if (len == size) {
      buff = (char *) realloc(buff, sizeof(*buff) * (int) (1.5 * len));
      size = (short) (1.5 * size);
      if (buff == nullptr) {
        free(buff);
        return nullptr;
      }
    }
  }
  buff[len] = '\0';
  len++;
  return (char *) realloc(buff, sizeof(*buff) * len);
}

char *parseCityName(char **rows, int i, int j, int W) {
  int len = 0, size = 4;
  char *buff = (char *) realloc(nullptr, sizeof(*buff) * size);

  while (rows[i][j] != '.' && rows[i][j] != '#' && rows[i][j] != '*') {
    if (j == 0) {
      j--;
      break;
    }
    j--;
  }
  j++;
  int index = 0;
  while (j < W && rows[i][j] != '.' && rows[i][j] != '#' && rows[i][j] != '*') {
    buff[index] = rows[i][j];
    rows[i][j] = '.';
    len++;
    index++;
    j++;
    if (len == size) {
      buff = (char *) realloc(buff, sizeof(*buff) * (int) (1.5 * len));
      size = (int) (1.5 * size);
    }
  }

  buff[len] = '\0';
  len++;
  return (char *) realloc(buff, sizeof(*buff) * len);
}

char *seekCityName(char **rows, int i, int j, int W, int H) {
  if (i - 1 >= 0 && rows[i - 1][j] != '#' && rows[i - 1][j] != '*' && rows[i - 1][j] != '.') {
    return parseCityName(rows, i - 1, j, W);
  } else if (i - 1 >= 0 && j - 1 >= 0 && rows[i - 1][j - 1] != '#' && rows[i - 1][j - 1] != '*'
      && rows[i - 1][j - 1] != '.') {
    return parseCityName(rows, i - 1, j - 1, W);
  } else if (i - 1 >= 0 && j + 1 < W && rows[i - 1][j + 1] != '#' && rows[i - 1][j + 1] != '*'
      && rows[i - 1][j + 1] != '.') {
    return parseCityName(rows, i - 1, j + 1, W);
  } else if (j - 1 >= 0 && rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
    return parseCityName(rows, i, j - 1, W);
  } else if (j + 1 < W && rows[i][j + 1] != '#' && rows[i][j + 1] != '*' && rows[i][j + 1] != '.') {
    return parseCityName(rows, i, j + 1, W);
  } else if (i + 1 < H && rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
    return parseCityName(rows, i + 1, j, W);
  } else if (i + 1 < H && j - 1 >= 0 && rows[i + 1][j - 1] != '#' && rows[i + 1][j - 1] != '*'
      && rows[i + 1][j - 1] != '.') {
    return parseCityName(rows, i + 1, j - 1, W);
  } else if (i + 1 < H && j + 1 < W && rows[i + 1][j + 1] != '#' && rows[i + 1][j + 1] != '*'
      && rows[i + 1][j + 1] != '.') {
    return parseCityName(rows, i + 1, j + 1, W);
  } else {
    return nullptr;
  }
}

void findAndAllocateCities(char **rows, Vector *graphNodes, Sll *cities, int W, int H, int nodeCounter) {
  int x, y;
  for (int i = 0; i < nodeCounter; i++) {
    if (graphNodes->getAt(i)->terrainType == '*') {
      x = graphNodes->getAt(i)->x;
      y = graphNodes->getAt(i)->y;
      char *name = seekCityName(rows, y, x, W, H);
      if (name != nullptr) {
        cities->appendCity(name, x, y, i);
        graphNodes->getAt(i)->cityName = name;
      }
    }
  }
}

void deleteSLL(Sll *cities) {
  while (cities) {
    Sll *next = cities->getNext();
    delete cities;
    cities = next;
  }
}

int searchNodeId(Vector *graphNodes, int currId, int x, int y, char flag, int W){
  if(flag == 'l'){
    return currId-1;
  }else if(flag == 'r'){
    return currId+1;
  }else if(flag == 'a'){
    graphNode* temp;
    for(int i=currId-1; i >= currId-W && i >= 0; i--){
      temp = graphNodes->getAt(i);
      if(temp->x == x && temp->y == y){
        return temp->id;
      }
    }
  }else if(flag == 'b'){
    graphNode* temp;
    for(int i = currId+1; i <= currId+W && i < graphNodes->getSize(); i++){
      temp = graphNodes->getAt(i);
      if(temp->x == x && temp->y == y){
        return temp->id;
      }
    }
  }
  return -1;
}

void fillAdjacencyList(char** rows, int nodeCounter, int cityCounter, Graph *adjacencyList, Vector *graphNodes, int W, int H) {
  if(nodeCounter - cityCounter != 0){
    graphNode* currNode;
    int neighId;
    for(int i = 0; i < nodeCounter; i++){
      currNode = graphNodes->getAt(i);
      if(currNode->y-1 >= 0 && (rows[currNode->y-1][currNode->x] == '*' || rows[currNode->y-1][currNode->x] == '#')){
        neighId = searchNodeId(graphNodes, i, currNode->x, currNode->y-1, 'a', W);
        if(neighId != -1) {
          addEdge(adjacencyList, i, neighId, 1);
        }
      }if(currNode->y+1 < H && (rows[currNode->y+1][currNode->x] == '*' || rows[currNode->y+1][currNode->x] == '#')){
        neighId = searchNodeId(graphNodes, i, currNode->x, currNode->y+1, 'b', W);
        if(neighId != -1) {
          addEdge(adjacencyList, i, neighId, 1);
        }
      }if(currNode->x-1 >= 0 && (rows[currNode->y][currNode->x-1] == '*' || rows[currNode->y][currNode->x-1] == '#')){
        neighId = searchNodeId(graphNodes, i, currNode->x-1, currNode->y, 'l', W);
        if(neighId != -1) {
          addEdge(adjacencyList, i, neighId, 1);
        }
      }if(currNode->x+1 < W  && (rows[currNode->y][currNode->x+1] == '*' || rows[currNode->y][currNode->x+1] == '#')){
        neighId = searchNodeId(graphNodes, i, currNode->x+1, currNode->y, 'r', W);
        if(neighId != -1) {
          addEdge(adjacencyList, i, neighId, 1);
        }
      }
    }
  }
}

int getCityId(Sll *cities, char *cityName){
  while(cities != nullptr){
    if(strcmp(cities->getCityName(), cityName) == 0){
      return cities->getId();
    }
    cities = cities->getNext();
  }
  return -1;
}

void appendFlightEdges(int nF, Sll* cities, Graph* adjacencyList){
  int iInsert = 0;
  int time;
  char *source, *destination;
  Sll* temp = cities;
  for (int i = 0; i < nF; i++) {
    source = readCityName();
    destination = readCityName();
    std::cin >> time;
    while(temp != nullptr){
      if(strcmp(source, temp->getCityName()) == 0){
        break;
      }
      iInsert += 1;
      temp = temp->getNext();
    }
    addEdge(adjacencyList, getCityId(cities, source), getCityId(cities, destination), time);
    temp = cities;
    delete[] source;
    delete[] destination;
  }
}

void dijkstra(Graph* adjacencyList, Vector *graphNodes, int sourceIndex, int destinationIndex, int qType){
  PriorityQueue pq;
  init(&pq, 8);
  int* dist = new int[graphNodes->getSize()];
  int* previoslyVisited = new int[graphNodes->getSize()];

  for(int i = 0; i < adjacencyList->size; i++){
    dist[i] = INT_MAX;
    previoslyVisited[i] = -1;
  }

  dist[sourceIndex] = 0;
  push(&pq,sourceIndex, 0);

  while(pq.count > 0){
    int current = pop(&pq);
    Edge* edge = adjacencyList->nodes[current].head;
    while(edge != nullptr){
      int v = edge->dest;
      int time = edge->weight;
      if(dist[current] + time < dist[v]){
        dist[v] = dist[current] + time;
        previoslyVisited[v] = current;
        push(&pq, v, dist[v]);
      }
      edge = edge->next;
    }
  }
  if(dist[destinationIndex] == INT_MAX){
    delete[] previoslyVisited;
    delete[] dist;
    return;
  }
  int* pathElems = new int[dist[destinationIndex]];
  if(qType == 1){
    int beginning = -1;
    int pathTime = dist[destinationIndex];
    int current = destinationIndex;
    for(int i = pathTime; i >= 0; i--){
      if(current < 0){
        beginning = i;
        break;
      }
      pathElems[i] = current;
      current = previoslyVisited[current];
    }
    std::cout << dist[destinationIndex] << " ";
    if(beginning == -1){
      beginning = 0;
    }
    for (int i = beginning; i < pathTime; i++) {
      graphNode* temp = graphNodes->getAt(pathElems[i]);
      if(pathElems[i] != sourceIndex && pathElems[i] != destinationIndex && pathElems[i] >= 0 && temp != nullptr && temp->cityName != nullptr){
        std::cout << temp->cityName << " ";
      }
    }

  }else{
    std::cout << dist[destinationIndex] << std::endl;
  }
  delete[] previoslyVisited;
  delete[] dist;
  delete[] pq.items;
}

void getRunQueries(int qN, Vector *graphNodes, Sll *cities, Graph *adjacencyList) {
  int qType;
  char *source, *destination;
  for (int i = 0; i < qN; i++) {
    source = readCityName();
    destination = readCityName();
    if (strcmp(source, destination) == 0) {
      std::cout << 0 << std::endl;
      std::cin >> qType;
      continue;
    }
    std::cin >> qType;
    dijkstra(adjacencyList, graphNodes, getCityId(cities, source),getCityId(cities, destination), qType);
  }
}


int main() {
  int W, H, nF, qN, nodeCounter = 0, cityCounter = 0;
  Sll *cities = new Sll();
  auto graphNodes = new Vector(4);

  std::cin >> W >> H;
  char **rows = new char *[H];

  for (int i = 0; i < H; i++) {
    rows[i] = new char[W];
  }
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      rows[i][j] = (char) getchar();
      if (rows[i][j] == '\n') {
        rows[i][j] = (char) getchar();
      }
      if (rows[i][j] == '#') {
        graphNodes->pushBack(j, i, nodeCounter, '#');
        nodeCounter += 1;
      } else if (rows[i][j] == '*') {
        graphNodes->pushBack(j, i, nodeCounter, '*');
        nodeCounter += 1;
        cityCounter += 1;
      }
    }
  }

  findAndAllocateCities(rows, graphNodes, cities, W, H, nodeCounter);

  Graph* adjacencyList = createGraph(nodeCounter);
  fillAdjacencyList(rows, nodeCounter, cityCounter, adjacencyList, graphNodes, W, H);

  std::cin >> nF;
  if (nF > 0) {
    appendFlightEdges(nF, cities, adjacencyList);
  }
  std::cin >> qN;

  getRunQueries(qN, graphNodes, cities, adjacencyList);

  for(int i = 0; i < H; i++){
    delete[] rows[i];
  }
  delete[] rows;

  deleteSLL(cities);
  int n = adjacencyList->size;
  for (int i = 0; i < n; i++) {
    Edge* edge = adjacencyList->nodes[i].head;
    while (edge != nullptr) {
      Edge* temp = edge;
      edge = edge->next;
      delete temp;
    }
  }
  delete[] adjacencyList->nodes;
  delete adjacencyList;
  delete[] graphNodes->getAt(0);
  delete graphNodes;
  return 0;
}
