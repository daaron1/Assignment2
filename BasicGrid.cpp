#include "BasicGrid.h"
#include <fstream>

BasicGrid::BasicGrid(){
}

void BasicGrid::gridSetUp(int x, int y)
{
  grid = (char**) calloc(x, sizeof(char*));
  for ( int i = 0; i < x; i++ )
  {
    grid[i] = (char*) calloc(y, sizeof(char));
  }

  gridNext = (char**) calloc(x, sizeof(char*));
  for ( int i = 0; i < x; i++ )
  {
    gridNext[i] = (char*) calloc(y, sizeof(char));
  }

  x_dim=x;
  y_dim=y;

  for (int x = 0; x < x_dim; x++)
  {
    for(int y=0;y<y_dim;y++)
    {
      gridNext[x][y]='.';
    }
  }
}

BasicGrid::BasicGrid(string filename)
{

  int x =0;
  int y= 0;

  ifstream myfile(filename);
  if (myfile.is_open())
  {
    myfile >> y;
    myfile >> x;

    gridSetUp(x,y);

    string line;

    int lineCount = 0;

    while ( getline (myfile,line) )
    {
     for(int j=0; j<=x ;++j)
     {
       if(line[j]==('X'))
       {
         placeCell(j,lineCount-1);
       }
     }
     lineCount++;
    }

    myfile.close();
  }
  else cout << "Unable to open file";

  updateGrid();

}



BasicGrid::BasicGrid(int x, int y)
{

  gridSetUp(x,y);

  updateGrid();
}

BasicGrid::~BasicGrid()
{

}




void BasicGrid::RandomizeGrid(double dens)
{

  int population = 0;

  double size = (x_dim*y_dim);
  double prob = 0;
  srand(time(0));
  while(dens>prob)
  {

    int x_rand = rand() % x_dim;
    int y_rand = rand() % y_dim;

    placeCell(x_rand,y_rand);
    population++;
    prob = (population/size);
    placeCell(x_rand,y_rand);

  }

}

//-------------------------------

void BasicGrid::placeCell(int x, int y)
{
  gridNext[x][y] = 'X';
}

//-------------------------------


void BasicGrid::print(){
  for (int y = 0; y < y_dim; y++)
  {
    for(int x=0;x<x_dim;x++)
    {
      cout<<grid[x][y]<<' ';
    }
    cout<<endl;
  }
}
//-------------------------------


void BasicGrid::printNeighbors(){
  for (int y = 0; y < y_dim; y++)
  {
    for(int x=0;x<x_dim;x++)
    {
      cout<<getDonutNeighbors(x,y)<<' ';
    }
    cout<<endl;
  }
}

//-------------------------------

void BasicGrid::printNext(){
  for (int y = 0; y < y_dim; y++){
    for(int x=0;x<x_dim;x++)
    {
      cout<<gridNext[x][y]<<' ';
    }
    cout<<endl;
  }
}

//-------------------------------

void BasicGrid::updateGrid()
{
  for (int y = 0; y < y_dim; y++)
  {
    for(int x=0;x<x_dim;x++)
    {
      grid[x][y]=gridNext[x][y];
    }
  }
}

//-------------------------------

bool BasicGrid::generate(int choice)
{
  for (int y = 0; y < y_dim; y++)
  {
    for(int x=0;x<x_dim;x++)
    {
      int numNeighbors;
      if(choice==1)
      {
        numNeighbors = getNeighbors(x,y);
      }
      else if(choice==2)
      {
        numNeighbors = getDonutNeighbors(x,y);
      }
      else if(choice==3)
      {
        numNeighbors = getMirrorNeighbors(x,y);
      }


      if(numNeighbors<=1)
      {
        gridNext[x][y]='.';
      }
      else if(numNeighbors==3)
      {
        gridNext[x][y]='X';
      }
      else if(numNeighbors>=4)
      {
        gridNext[x][y]='.';
      }

    }
  }
  if(isStable())
  {
    return false;
  }
  updateGrid();
  return true;
}
//-------------------------------

bool BasicGrid::isStable()
{
  for (int y = 0; y < y_dim; y++)
  {
    for(int x=0;x<x_dim;x++)
    {
      if(grid[x][y]!=gridNext[x][y])
      {
        return false;
      }
    }
  }
  cout<<"Grid above is stable - huzzah!"<<endl;
  return true;
}

//-------------------------------

int BasicGrid::getNeighbors(int x, int y)
{
   int neighbors = 0;

   int north = y-1;
   int south = y+1;
   int west = x-1;
   int east = x+1;
   int lastx=x_dim-1;
   int lasty=y_dim-1;

   // NORTH, NORTH EAST, NORTH WEST
   if(north>=0)
   {
      // NORTH
      if(grid[x][north]=='X') neighbors++;
      if(west>=0)
      {
        // NORTH WEST
        if(grid[west][north]=='X') neighbors++;
      }
      if(east<=lastx)
      {
        // NORTH EAST
        if(grid[east][north]=='X') neighbors++;
      }
   }

   // SOUTH, SOUTH EAST, SOUTH WEST
   if(south<=lasty)
   {
      // SOUTH
      if(grid[x][south]=='X') neighbors++;
      if(west>=0)
      {
        // SOUTH WEST
        if(grid[west][south]=='X') neighbors++;
      }
      if(east<=lastx)
      {
        // SOUTH EAST
        if(grid[east][south]=='X') neighbors++;
      }
   }

   // WEST
   if(west>=0)
   {
     if(grid[west][y]=='X') neighbors++;
   }

   // EAST
   if(east<=lastx)
   {
     if(grid[east][y]=='X') neighbors++;
   }

   return neighbors;
}




//----------------------========------------------------

int BasicGrid::getMirrorNeighbors(int x, int y)
{
   int neighbors = 0;

   int north = y-1;
   int south = y+1;
   int west = x-1;
   int east = x+1;
   int lastx=x_dim-1;
   int lasty=y_dim-1;

   neighbors+=(getNeighbors(x,y));


   // NORTH OVER TOP EDGE
   if(north<=0)
   {
     if(grid[x][lasty]=='X') neighbors++;

     if(west<=0)
     {
       if(grid[0][0]=='X') neighbors+=3;
     }
   }

   if(south>=lasty)
   {
     if(grid[x][0]=='X') neighbors++;

     if(east>=lastx)
     {
       if(grid[lastx][lasty]=='X') neighbors+=3;
     }
   }

   if(west<=0)
   {
     if(grid[lastx][y]=='X') neighbors++;

     if(south>=lastx)
     {
       if(grid[0][y]=='X') neighbors+=3;
     }
   }

   if(east>=lastx)
   {
     if(grid[0][y]=='X') neighbors++;

     if(north<=lastx)
     {
       if(grid[x][0]=='X') neighbors+=3;
     }
   }

   return neighbors;
}

//----------------------========------------------------




int BasicGrid::getDonutNeighbors(int x, int y)
{
   int neighbors = 0;

   int north = y-1;
   int south = y+1;
   int west = x-1;
   int east = x+1;
   int lastx=x_dim-1;
   int lasty=y_dim-1;


   neighbors+=(getNeighbors(x,y));

   // NORTH OVER TOP EDGE
   if(north<0)
   {
     if(grid[x][lasty]=='X') neighbors++;

     // NORTH WEST OVER TOP LEFT CORNER
     if(west<0)
     {
       if(grid[lastx][lasty]=='X') neighbors++;
     }
     // NORTH EAST OVER TOP RIGHT CORNER
     if(east>lastx)
     {
       if(grid[0][lasty]=='X') neighbors++;
     }

     if(west>=0)
     {
       // NORTH WEST OVER TOP EDGE
       if(grid[west][lasty]=='X') neighbors++;
     }
     if(east<=lastx)
     {
       // NORTH EAST OVER TOP EDGE
       if(grid[east][lasty]=='X') neighbors++;
     }
   }



   // SOUTH OVER BOTTOM EDGE
   if(south>lasty)
   {
     if(grid[x][0]=='X') neighbors++;

     // SOUTH WEST OVER BOTTOM LEFT CORNER
     if(west<0)
     {
       if(grid[lastx][0]=='X') neighbors++;
     }
     // SOUTH EAST OVER BOTTOM RIGHT CORNER
     if(east>lastx)
     {
       if(grid[0][0]=='X') neighbors++;
     }

     if(west>=0)
     {
       // SOUTH WEST OVER TOP EDGE
       if(grid[west][0]=='X') neighbors++;
     }
     if(east<=lastx)
     {
       // SOUTH EAST OVER TOP EDGE
       if(grid[east][0]=='X') neighbors++;
     }
   }


   //WEST
   if(west<0)
   {
     // OVER LEFT EDGE
     if(grid[lastx][y]=='X') neighbors++;

     // SOUTH WEST OVER LEFT EDGE
     if(grid[lastx][south]=='X') neighbors++;

     // NORTH WEST OVER LEFT EDGE
     if(grid[lastx][north]== 'X') neighbors++;
   }

   //EAST
   if(east>lastx)
   {
     // OVER RIGHT EDGE
     if(grid[0][y]=='X') neighbors++;

     // SOUTH EAST OVER LEFT EDGE
     if(grid[0][south]=='X') neighbors++;

     // NORTH EAST OVER LEFT EDGE
     if(grid[0][north]== 'X') neighbors++;
   }

   return neighbors;
}
