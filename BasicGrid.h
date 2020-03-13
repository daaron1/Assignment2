#include <iostream>
using namespace std;

class BasicGrid
{
  public:
    BasicGrid();
    BasicGrid(int x, int y);
    BasicGrid(string filename);
    ~BasicGrid();
    // void populate(char arr[][]);
    void print();
    void printNext();

    void placeCell(int x, int y);
    void updateGrid();
    bool generate(int choice);


    void gridSetUp(int x, int y);

    bool isStable();

    void RandomizeGrid(double dens);

    int getNeighbors(int x_cord, int y_cord);
    int getDonutNeighbors(int x_cord, int y_cord);
    int getMirrorNeighbors(int x_cord, int y_cord);

    void printNeighbors();

    int x_dim;
    int y_dim;
    char **grid;
    char **gridNext;

};
