#include <iostream>
#include "BasicGrid.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    // BasicGrid bg(5,5);

    // bg.placeCell(9,5);
    // bg.placeCell(8,5);
    // bg.placeCell(7,5);
    // bg.placeCell(9,4);
    // bg.placeCell(8,3);

    // bg.placeCell(2,0);
    // bg.placeCell(3,1);
    // bg.placeCell(4,1);
    // bg.placeCell(2,4);
    // bg.placeCell(3,4);
    // bg.placeCell(0,2);
    //bg.RandomizeGrid(.75);

    // bg.placeCell(1,6);
    // bg.placeCell(12,6);
    // bg.placeCell(0,6);

    // bg.updateGrid();

    // while(1==1)
    // {
    //   cout << endl;
    //   cout<<"-------------------"<<endl;
    //   bg.print();
    //   bg.printNeighbors();
    //   bg.generate(3);
    //   bg.printNext();
    //   cout<<"-------------------"<<endl;
    //   bg.print();
    //   bg.printNeighbors();
    //   cout << "Enter 1 to continue 2 to quit: ";
    //   int choice;
    //   cin >> choice;
    //
    //   if(choice==2)
    //   {
    //     break;
    //   }
    //
    // }


    int userIn = 0;

    cout<<endl;
    cout<<"-------≈≈≈GAME OF LIFE≈≈-------"<<endl;
    cout<<"Enter 1 to generate random grid - Enter 2 to enter grid file:  ";
    cin>>userIn;
    int xIn=0;
    int yIn=0;
    double probIn =0;

    BasicGrid bg;

    if(userIn == 1)
    {

      cout<<"-------≈≈≈≈Ω≈≈≈≈-------"<<endl;
      cout<<"Enter grid width(x): ";
      cin>>xIn;


      cout<<"Enter grid height(y): ";
      cin>>yIn;

      cout<<"Enter grid population density[Between 0 and 1]: ";
      cin>>probIn;
      bg = BasicGrid(xIn,yIn);
    }


    else if(userIn == 2)
    {
      string filename;
      cout<<"Enter file name/ file path: ";
      cin>>filename;
      bg = BasicGrid(filename);
    }


    bg.updateGrid();

    int pauses = 0;
    cout<<"Enter 1 to simulate until stable - Enter 2 to allow generation pauses:  ";
    cin>>pauses;

    bg.RandomizeGrid(probIn);
    bg.updateGrid();
    int gridSetting = 0;
    cout<<"Enter 1 for normal mode, 2 for donut mode, and 3 for mirror mode: ";
    cin>>gridSetting;

    if (pauses==1)
    {
      while(1==1)
      {
          cout << endl;
          cout<<"-------------------"<<endl;
          bg.print();
          if(!bg.generate(gridSetting))
          {
            break;
          }
      }
    }

    if (pauses==2)
    {

      while(1==1)
      {
          cout << endl;
          cout<<"-------------------"<<endl;
          bg.print();
          if(!bg.generate(gridSetting))
          {
            break;
          }
          cout << "Enter 1 to continue 2 to quit: ";
          int cont;
          cin >> cont;
          if(cont==2)
          {
            break;
          }
      }
    }
}
