#include <iostream>
#include "Headers/String.h"
#include "Headers/Sll.h"
#include "Headers/Vector.h"
#include <cmath>

char *readCityName() {
  char ch = '-';
  short len = 0;
  short size = 8;
  char *buff = (char *) realloc(nullptr, sizeof(*buff) * size);

  while (ch != ' ') {
    ch = (char) getchar();
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
  return (char *) realloc(buff, sizeof(*buff) * len);
}

char *parseCityName(char **rows, Sll *cities, int i, int j, int W) {
  int len = 0, size = 8;
  char *buff = (char *) realloc(nullptr, sizeof(*buff) * size);
  while (j != -1 && rows[i][j] != '.' && rows[i][j] != '#' && rows[i][j] != '*') {
    j -= 1;
  }
  j += 1;
  int beginning = j;
  while (j != W - 1 && rows[i][j] != '.' && rows[i][j] != '#' && rows[i][j] != '*') {
    buff[len] = rows[i][j];
    j += 1, len += 1;
    if (len == size) {
      buff = (char *) realloc(buff, sizeof(*buff) * (int) (1.5 * len));
      size = (int) (1.5 * size);
    }
  }

  for (int k = 0; k < len; k++) {
    rows[i][beginning] = '.';
    beginning += 1;
  }
  buff[len] = '\0';
  len++;
  return (char *) realloc(buff, sizeof(*buff) * len);
}

char *seekCityName(char **rows, Sll *cities, int i, int j, int W, int H) {
  if (i == 0) {
    if (j == 0) {
      if (rows[i][j + 1] != '#' && rows[i][j + 1] != '*' && rows[i][j + 1] != '.') {
        return parseCityName(rows, cities, i, j + 1, W);
      } else if (rows[i + 1][j + 1] != '#' && rows[i + 1][j + 1] != '*' && rows[i + 1][j + 1] != '.') {
        return parseCityName(rows, cities, i + 1, j + 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else {
        return nullptr;
      }
    } else if (j == W - 1) {
      if (rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
        return parseCityName(rows, cities, i, j - 1, W);
      } else if (rows[i + 1][j - 1] != '#' && rows[i + 1][j - 1] != '*' && rows[i + 1][j - 1] != '.') {
        return parseCityName(rows, cities, i + 1, j - 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else {
        return nullptr;
      }
    } else {
      if (rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
        return parseCityName(rows, cities, i, j - 1, W);
      } else if (rows[i + 1][j - 1] != '#' && rows[i + 1][j - 1] != '*' && rows[i + 1][j - 1] != '.') {
        return parseCityName(rows, cities, i + 1, j - 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else if (rows[i + 1][j+1] != '#' && rows[i + 1][j+1] != '*' && rows[i + 1][j+1] != '.') {
        return parseCityName(rows, cities, i + 1, j+1, W);
      }else {
        return nullptr;
      }
    }
  } else if (i == H - 1) {
    if (j == 0) {
      if (rows[i - 1][j] != '#' && rows[i - 1][j] != '*' && rows[i - 1][j] != '.') {
        return parseCityName(rows, cities, i - 1, j, W);
      } else if (rows[i + 1][j + 1] != '#' && rows[i + 1][j + 1] != '*' && rows[i + 1][j + 1] != '.') {
        return parseCityName(rows, cities, i + 1, j + 1, W);
      } else if (rows[i][j + 1] != '#' && rows[i][j + 1] != '*' && rows[i][j + 1] != '.') {
        return parseCityName(rows, cities, i, j + 1, W);
      } else {
        return nullptr;
      }
    } else if (j == W - 1) {
      if (rows[i - 1][j] != '#' && rows[i - 1][j] != '*' && rows[i - 1][j] != '.') {
        return parseCityName(rows, cities, i - 1, j, W);
      } else if (rows[i - 1][j - 1] != '#' && rows[i - 1][j - 1] != '*' && rows[i - 1][j - 1] != '.') {
        return parseCityName(rows, cities, i - 1, j - 1, W);
      } else if (rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
        return parseCityName(rows, cities, i, j - 1, W);
      } else {
        return nullptr;
      }
    } else {
      if (rows[i - 1][j - 1] != '#' && rows[i - 1][j - 1] != '*' && rows[i - 1][j - 1] != '.') {
        return parseCityName(rows, cities, i - 1, j - 1, W);
      } else if (rows[i - 1][j] != '#' && rows[i - 1][j] != '*' && rows[i - 1][j] != '.') {
        return parseCityName(rows, cities, i - 1, j, W);
      } else if (rows[i - 1][j + 1] != '#' && rows[i - 1][j + 1] != '*' && rows[i - 1][j + 1] != '.') {
        return parseCityName(rows, cities, i - 1, j + 1, W);
      } else if (rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
        return parseCityName(rows, cities, i, j - 1, W);
      } else if (rows[i][j + 1] != '#' && rows[i][j + 1] != '*' && rows[i][j + 1] != '.') {
        return parseCityName(rows, cities, i, j + 1, W);
      } else {
        return nullptr;
      }
    }
  } else {
    if (j == 0) {
      if (rows[i - 1][j] != '#' && rows[i - 1][j] != '*' && rows[i - 1][j] != '.') {
        return parseCityName(rows, cities, i - 1, j, W);
      } else if (rows[i - 1][j + 1] != '#' && rows[i - 1][j + 1] != '*' && rows[i - 1][j + 1] != '.') {
        return parseCityName(rows, cities, i - 1, j + 1, W);
      } else if (rows[i][j + 1] != '#' && rows[i][j + 1] != '*' && rows[i][j + 1] != '.') {
        return parseCityName(rows, cities, i, j + 1, W);
      } else if (rows[i + 1][j + 1] != '#' && rows[i + 1][j + 1] != '*' && rows[i + 1][j + 1] != '.') {
        return parseCityName(rows, cities, i + 1, j + 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else {
        return nullptr;
      }
    } else if (j == W - 1) {
      if (rows[i - 1][j - 1] != '#' && rows[i - 1][j - 1] != '*' && rows[i - 1][j - 1] != '.') {
        return parseCityName(rows, cities, i - 1, j - 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else if (rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
        return parseCityName(rows, cities, i, j - 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else if (rows[i + 1][j - 1] != '#' && rows[i + 1][j - 1] != '*' && rows[i + 1][j - 1] != '.') {
        return parseCityName(rows, cities, i + 1, j - 1, W);
      } else {
        return nullptr;
      }
    } else {
      if (rows[i - 1][j - 1] != '#' && rows[i - 1][j - 1] != '*' && rows[i - 1][j - 1] != '.') {
        return parseCityName(rows, cities, i - 1, j - 1, W);
      } else if (rows[i - 1][j] != '#' && rows[i - 1][j] != '*' && rows[i - 1][j] != '.') {
        return parseCityName(rows, cities, i - 1, j, W);
      } else if (rows[i - 1][j + 1] != '#' && rows[i - 1][j + 1] != '*' && rows[i - 1][j + 1] != '.') {
        return parseCityName(rows, cities, i - 1, j + 1, W);
      } else if (rows[i][j - 1] != '#' && rows[i][j - 1] != '*' && rows[i][j - 1] != '.') {
        return parseCityName(rows, cities, i, j - 1, W);
      } else if (rows[i][j + 1] != '#' && rows[i][j + 1] != '*' && rows[i][j + 1] != '.') {
        return parseCityName(rows, cities, i, j + 1, W);
      } else if (rows[i + 1][j - 1] != '#' && rows[i + 1][j - 1] != '*' && rows[i + 1][j - 1] != '.') {
        return parseCityName(rows, cities, i + 1, j - 1, W);
      } else if (rows[i + 1][j] != '#' && rows[i + 1][j] != '*' && rows[i + 1][j] != '.') {
        return parseCityName(rows, cities, i + 1, j, W);
      } else if (rows[i + 1][j + 1] != '#' && rows[i + 1][j + 1] != '*' && rows[i + 1][j + 1] != '.') {
        return parseCityName(rows, cities, i + 1, j + 1, W);
      } else {
        return nullptr;
      }
    }
  }
  return nullptr;
}

void findAndAllocateCities(char **rows, Sll *cities, int W, int H) {
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (rows[i][j] == '*') {
        char *name = seekCityName(rows, cities, i, j, W, H);
        if (name != nullptr) {
          cities->appendCity(name, j, i);
        }
      }
    }
  }
}

int getCityId(Sll *cityNode, Vector *graphNodes, int nodeCounter) {
  int x, y;
  for (int i = 0; i < nodeCounter; i++) {
    x = graphNodes->getAt(i)->x;
    y = graphNodes->getAt(i)->y;
    if (x == cityNode->getX() && y == cityNode->getY()) {
      return graphNodes->getAt(i)->id;
    }
  }
  return -1;
}

/*
void appendFlightEdges(int nF, int cityCounter, int nodeCounter, Sll *cities, Vector *graphNodes,
                       short **adjacencyMatrix) {

  short time, iInsert, jInsert;
  bool srcFound = false;
  bool dstFound = false;
  Sll *citiesHead;

  for (int i = 0; i < nF; i++) {
    citiesHead = cities;
    char *source = readCityName();
    char *destination = readCityName();
    std::cin >> time;

    for (int j = 0; j < cityCounter; j++) {
      if (srcFound && dstFound) {
        break;
      }
      if (citiesHead != nullptr) {
        if (strcmp(source, citiesHead->getCityName()) != 0) {
          if (strcmp(destination, citiesHead->getCityName()) == 0) {
            dstFound = true;
            jInsert = getCityId(citiesHead, graphNodes, nodeCounter);
          }
          citiesHead = citiesHead->getNext();
          continue;
        }
        iInsert = getCityId(citiesHead, graphNodes, nodeCounter);
        srcFound = true;
        break;
      }
    }
    if (iInsert == -1 || jInsert == -1) {
      continue;
    }
    adjacencyMatrix[iInsert][jInsert] = time;
  }
}
*/
void fillAdjacencyMatrix(int nodeCounter, Vector *graphNodes, short **adjacencyMatrix) {
  int index = 0;
  while (index < nodeCounter) {
    for (int i = 0; i < nodeCounter; i++) {
      graphNode *src = graphNodes->getAt(index);
      graphNode* dst = graphNodes->getAt(i);


      if (i != index) {
        if (graphNodes->getAt(index)->x + 1 == graphNodes->getAt(i)->x && graphNodes->getAt(index)->y == graphNodes->getAt(i)->y) {
          adjacencyMatrix[index][i] = 1;
        } else if (graphNodes->getAt(index)->x - 1 == graphNodes->getAt(i)->x && graphNodes->getAt(index)->y == graphNodes->getAt(i)->y) {
          adjacencyMatrix[index][i] = 1;
        } else if (graphNodes->getAt(index)->x == graphNodes->getAt(i)->x && graphNodes->getAt(index)->y + 1 == graphNodes->getAt(i)->y) {
          adjacencyMatrix[index][i] = 1;
        } else if (graphNodes->getAt(index)->x == graphNodes->getAt(i)->x && graphNodes->getAt(index)->y - 1 == graphNodes->getAt(i)->y) {
          adjacencyMatrix[index][i] = 1;
        } else {
          continue;
        }
      }
    }
    index += 1;
  }
}

int main() {
  int W, H, nF, qType, nodeCounter = 0, cityCounter = 0;
  Sll *cities = new Sll();
  auto graphNodes = new Vector(16);

  // gather all nodes and create an array of them, index in array is vertice number(unique)
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
  findAndAllocateCities(rows, cities, W, H);

  Sll *copy = cities;
  graphNode* temp;
  for (int j = 0; j < nodeCounter; j++) {
    if (copy != nullptr) {
      if (copy->getX() == graphNodes->getAt(j)->x && copy->getY() == graphNodes->getAt(j)->y) {
        graphNodes->getAt(j)->cityName = copy->getCityName();
        copy = copy->getNext();
      }
    } else {
      break;
    }
  }

  //Append cityNames to each graphNode after, delete SLL

  for (int i = 0; i < H; i++) {
    delete[] rows[i];
  }
  delete[] rows;

  auto adjacencyMatrix = new short *[nodeCounter];
  for (int i = 0; i < nodeCounter; i++) {
    adjacencyMatrix[i] = new short[nodeCounter];
  }
  for (int i = 0; i < nodeCounter; i++) {
    for (int j = 0; j < nodeCounter; j++) {
      adjacencyMatrix[i][j] = 7;
    }
  }

  fillAdjacencyMatrix(nodeCounter, graphNodes, adjacencyMatrix);

  for(int i = 0; i < nodeCounter; i++){
    for(int j = 0; j < nodeCounter; j++){
      std::cout << adjacencyMatrix[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << "ASD";
  std::cin >> nF;
  if (nF > 0) {
    //appendFlightEdges(nF, cityCounter, nodeCounter, cities, graphNodes, adjacencyMatrix);
  }

  std::cin >> qType;

  return 0;
}
