// Monopoly_Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void greeting();
void Functions();
int dieRoll();
int Chance(int CurrentSpot);
int Chest(int CurrentSpot);
void CalcOutput(int LandedOn[],int EndedOn[],int NumberOfTurns);

const int NUMBER_OF_TILES = 41;
enum Tiles {Start, Mediterranean_Avenue, Community_Chest1, Baltic_Avenue, Income_Tax, Reading_Railroad, Orientel_Avenue, Chance1, Vermont_Avenue, Connecticut_Avenue,
					Jail_Visiting, Charles_Place, Electric_Company, States_Avenue, Virginia_Avenue, Pennsylvania_Railroad, James_Place, Community_Chest2, Tennessee_Avenue, Newyork_Avenue,
					Free_Parking, Kentucky_avenue, Chance2, Indiana_Avenue, Illinois_Avenue, BandO_Railroad, Atlantic_Avenue, Ventnor_Avenue, Water_Works, Marvin_Gardens,
					Go_To_Jail, Pacific_Avenue, North_Carolina_Avenue, Community_Chest3, Pensylvania_Avenue, Short_Line, Chance3, Park_Place, Luxury__Tax, BoardWalk,
					In_Jail};
string TileNames[] = {"Start", "Mediterranean_Avenue", "Community_Chest1", "Baltic_Avenue", "Income_Tax", "Reading_Railroad", "Orientel_Avenue", "Chance1", "Vermont_Avenue", "Connecticut_Avenue",
					"Jail_Visiting", "Charles_Place", "Electric_Company", "States_Avenue", "Virginia_Avenue", "Pennsylvania_Railroad", "James_Place", "Community_Chest2", "Tennessee_Avenue", "Newyork_Avenue",
					"Free_Parking", "Kentucky_avenue", "Chance2", "Indiana_Avenue", "Illinois_Avenue", "BandO_Railroad", "Atlantic_Avenue", "Ventnor_Avenue", "Water_Works", "Marvin_Gardens",
					"Go_To_Jail", "Pacific_Avenue", "North_Carolina_Avenue", "Community_Chest3", "Pensylvania_Avenue", "Short_Line", "Chance3", "Park_Place", "Luxury__Tax", "BoardWalk",
					"In_Jail"};

int main()
{
	greeting();
	Functions();
	return 0;
}

void greeting()
{
	cout << "Hi\n";
	cout << "This Program Will Calculate monopoly movement\n";
	system("Pause");
	system("cls");
}

void Functions()
{
	int LandedOn[NUMBER_OF_TILES];
	int EndedOn[NUMBER_OF_TILES];
	int NumberOfTurns = 0, CurrentSpot = 0;
	int die1;
	int die2;
	int doubleCount;

	for(int i = 0; i < NUMBER_OF_TILES; i++)
	{
		LandedOn[i] = 0;
		EndedOn[i] = 0;
	}

	srand((unsigned)time(0)); 
	
	cout << "Please enter the number of turns :";	
	cin >> NumberOfTurns;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < (NumberOfTurns / 10); j++)
		{
			doubleCount = 0;
			do {
				if (CurrentSpot == In_Jail)
				{
					CurrentSpot = 10; //get out of jail (by paying $50)
				}
				die1 = rand()%6 + 1;
				die2 = rand()%6 + 1;
				if (die1 == die2)
				{
					doubleCount++;
				}
				if (doubleCount >= 3)
				{
					CurrentSpot = In_Jail; //goto jail
				}
				else
				{
					CurrentSpot = (die1 + die2 + CurrentSpot) % 40; //Adds dice and makes sure currentspot goes around the board
					LandedOn[CurrentSpot]++;
					if (( CurrentSpot == 7) || (CurrentSpot == 22) || (CurrentSpot == 36))
					{
						CurrentSpot = Chance(CurrentSpot);
					}
					else if ((CurrentSpot == 2) || (CurrentSpot == 17) || (CurrentSpot == 33))
					{
						CurrentSpot = Chest(CurrentSpot); // ADD CHEST FUNCTION
					}
					else if (CurrentSpot == Go_To_Jail)
					{
						CurrentSpot = In_Jail;
					}
				}
				EndedOn[CurrentSpot]++;
			} while ((die1 == die2) && (CurrentSpot != In_Jail));
		}
		cout << i * 10 << "% calculated!" << endl;
	}
	CalcOutput(LandedOn, EndedOn, NumberOfTurns);
}

int Chance(int CurrentSpot)
{
	int randCard = (rand()%16);
	if (randCard <= 5)
	{
		//Do Nothing
	}
	switch (randCard)
	{
		case 6: // Go to Charles Place
			CurrentSpot = 11;
		break;
		case 7: // Go to Reading RailRoad
			CurrentSpot = 5;
		break;
		case 8: // Go to Nearest RailRoad
		case 9: //OTher go to nearest railroad card
			if ((CurrentSpot < 5) || (CurrentSpot >= 35)) // Go to Reading Railroad
			{
				CurrentSpot = Reading_Railroad;
			}
			else if (CurrentSpot < 15) // Go to Pennsylvania RailRoad
			{
				CurrentSpot = Pennsylvania_Railroad;
			}
			else if (CurrentSpot < 25) // Go to b & o RailRoad
			{
				CurrentSpot = BandO_Railroad;
			}
			else if (CurrentSpot < 35) // Go to ShortLine
			{
				CurrentSpot = Short_Line;
			}
		break;
		case 10: // Go to Go
			CurrentSpot = 0;
		break;
		case 11: // Go to Illinois Avenue
			CurrentSpot = 24;
		break;
		case 12: // Go to BoardWalk
			CurrentSpot = 39;
		break;
		case 13: // Go to Nearest Utility
			if ((CurrentSpot < 12) || (CurrentSpot >= 28)) //Goto Electric Company
			{
				CurrentSpot = 12;
			}
			else  // Goto Water Works
			{
				CurrentSpot = 28;
			}
		break;
		case 14: // Go to Jail
			CurrentSpot = In_Jail;
		break;
		case 15: // Go back 3 spaces
			CurrentSpot -= 3;
		break;
	}
	return CurrentSpot;
}

int Chest(int CurrentSpot)
{
	int randCard = (rand()%16);
	if (randCard < 14)
	{
		//Do Nothing
	}
	else if (randCard = 14)
	{
		CurrentSpot = In_Jail; //go to jail
	}
	else if (randCard = 15)
	{
		CurrentSpot = 0; // go to go
	}
	return CurrentSpot;
}

void CalcOutput(int LandedOn[],int EndedOn[],int NumberOfTurns)
{
	double Percent = 0;
	system("Pause");
	system("cls");
	cout << "Name of space            Times Landed On Times Ended On Percentage Rate" << endl;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(4);
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		Percent = EndedOn[i];
		Percent /= NumberOfTurns;
		Percent *= 100;
		cout << "-------------------------------------------------------------------------\n";
		//cout << TileNames[i] << "\t\t" << LandedOn[i] << "\t\t" << EndedOn[i] << "\t\t" << Percent << endl;
		cout << setw(25) << left << TileNames[i]
			 << setw(16) << LandedOn[i]
			 << setw(15) << EndedOn[i]
			 << setw(15) << Percent << endl;
	}
	system("Pause");
}