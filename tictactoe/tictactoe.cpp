
#include <iostream>

using namespace std;
int wincondition(int tttboard[3][3]);
void printboard(int T[3][3]);
int main()
{
  int x;
  int y;
  int i1,i2;
  int tttboard[3][3];
  int winner=0;
  int counter=0;
int invalid;
char ans;

      // Set each element to a value

do
{
    for ( x = 0; x < 3; x++ )
        {
            for ( y = 0; y < 3; y++ )
            tttboard[x][y] = 0;
        }

winner = 0;
counter=0;

   do
   {

printboard(tttboard);
  do
    {
            invalid=0;
            cout<<"Player 1, input indicies of choice \n Row:";
            cin>>i1;
            cin.ignore();
            cout<<"Column:";
            cin>>i2;
            cin.ignore();
            if((tttboard[i1][i2]==1) || (tttboard[i1][i2]==2))
                    {
                        cout<<"invalid entry, try again, sucka!\n";
                        invalid=1;
                    }
            if((i1>2)|| (i1<0))
                    {
                        cout<<"invalid entry, try again, sucka!\n";
                        invalid=1;
                    }
              if((i2>2)||( i2<0))
                    {
                        cout<<"invalid entry, try again, sucka!\n";
                        invalid=1;
                    }

     }while(invalid==1);

    tttboard[i1][i2] = 1;
    counter++;
      if(counter==9)
      break;
        printboard(tttboard);

// Checking win condition
          winner=wincondition(tttboard);
          if((winner ==1) || (winner ==2))
          break;

      do
        {
            invalid=0;
            cout<<"Player 2, input indicies of choice \n Row:";
            cin>>i1;
            cin.ignore();
            cout<<"Column:";
            cin>>i2;
            cin.ignore();
            if((tttboard[i1][i2]==1) || (tttboard[i1][i2]==2))
                {
                    cout<<"invalid entry, try again, sucka!\n";
                    invalid=1;
                }
        }while(invalid==1);

        tttboard[i1][i2] = 2;

        for ( x = 0; x < 3;x++ )
        {
                for ( y = 0; y < 3; y++ )
                    cout<< "     "<<tttboard[x][y] <<" ";

            cout<<"\n \n";
        }
   // checking winning condition
               winner=wincondition(tttboard);
          if((winner ==1) || (winner ==2))
            break;

        counter++;
      if(counter==9)
        break;

    } while (counter!=9);

printboard(tttboard);
    if((winner==1) || (winner==2))
            cout<<" "<<winner<<" is the Winner!";
   else
            cout<<"Game over, No winner...";


cout<<"Thanks for playing\n ";
     cout<<"Want to play it again? (y/n)...\n";
     cin>>ans;
   }while(ans=='y' || ans=='Y');

}

int wincondition(int tttboard[3][3]) //returns the winner (1 or 2)
{
    if(((tttboard[0][0]==1) &&(tttboard[0][1]==1) && (tttboard[0][2]==1)) || ((tttboard[0][0]==2) &&(tttboard[0][1]==2) && (tttboard[0][2])==2))
                    {
                   cout<<"Condition 1 Met";
                   return tttboard[0][0];
                    }

if(((tttboard[1][0]==1) &&(tttboard[1][1]==1) && (tttboard[1][2]==1)) || ((tttboard[1][0]==2) &&(tttboard[1][1]==2) && (tttboard[1][2])==2))
                    {
                   cout<<"Condition 2 Met";
                    return tttboard[1][0];
                    }

if(((tttboard[2][0]==1) &&(tttboard[2][1]==1) && (tttboard[2][2]==1)) || ((tttboard[2][0]==2) &&(tttboard[2][1]==2) && (tttboard[2][2])==2))
                    {
                   cout<<"Condition 3 Met";
                   return tttboard[2][0];
                    }

if(((tttboard[0][0]==1) &&(tttboard[1][0]==1) && (tttboard[2][0]==1)) || ((tttboard[0][0]==2) &&(tttboard[1][0]==2) && (tttboard[2][0])==2))
                    {
                   cout<<"Condition 4 Met";
                   return tttboard[1][0];
                    }

if(((tttboard[0][1]==1) &&(tttboard[1][1]==1) && (tttboard[2][1]==1)) || ((tttboard[0][1]==2) &&(tttboard[1][1]==2) && (tttboard[2][1])==2))
                    {
                   cout<<"Condition 5 Met";
                    return tttboard[1][1];
                    }

if(((tttboard[0][0]==1) &&(tttboard[0][1]==1) && (tttboard[0][2]==1)) || ((tttboard[0][0]==2) &&(tttboard[0][1]==2) && (tttboard[0][2])==2))
                    {
                   cout<<"Condition 6 Met";
                   return tttboard[1][2];
                    }

if(((tttboard[0][0]==1) &&(tttboard[1][1]==1) && (tttboard[2][2]==1)) || ((tttboard[0][0]==2) &&(tttboard[1][1]==2) && (tttboard[2][2])==2))
                    {
                   cout<<"Condition 7 Met";
                   return tttboard[0][0];
                    }

if(((tttboard[0][2]==1) &&(tttboard[1][1]==1) && (tttboard[2][0]==1)) || ((tttboard[0][2]==2) &&(tttboard[1][1]==2) && (tttboard[2][0])==2))
                    {
                   cout<<"Condition 8 Met";
                    return tttboard[1][1];
                    }
return 0;
}

void printboard(int T[3][3])
{
    int x;
    int y;

    for  (x=0;x<3;x++)
    {
        if (x==0)
            cout<<"\nColumn:       0      1      2 \n\n              |      |      |\n              V      V      V\n\n\nRow: 0 ->";
          if (x==1)
                    cout<<"Row: 1 ->";
        if (x==2)
                    cout<<"Row: 2 ->";
                for(y=0;y < 3; y++)
                {
                    cout<< "     "<<T[x][y] <<" ";
                }
            cout<<"\n \n";
    }


cout<<"\n\n";
}
/*for ( x = 0; x < 3;x++ )
            {
                for ( y = 0; y < 3; y++ )
                cout<< "     "<<tttboard[x][y] <<" ";
                cout<<"\n \n";
            }
        */

