// ThrowDice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

//Name spaces
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using namespace std;

//Methods
void cashier();
int pickBetSize();
void playGame(int betSize);
void menu();
void gameAnimation(int playerDice, int computerDice, int roundCounter);

//Global varibles
int bankroll = 0;
int maxDeposit = 5000;
int maxDepositSize = 5000;
int minDepositSize = 100;
int betSizes[3] = { 100,300,500 }; //Array of betsizes, betSizes[0] needs to be the lowest betsize 
int roundsToWin = 2;
int mainMenuOption = 0;

int main() {
	bool gameRunning = true;
	srand(time(0)); // Använd endast en gång
	cout << "Welcome to the Dice Game! \n\n";

	while (gameRunning) {
		menu();

		if (mainMenuOption == 3) {
			if (bankroll > betSizes[0]) {
				playGame(pickBetSize());
			}
			else {
				cout << "\nYour bankroll is too small please deposit...\n\n";
			}
		}

		else if (mainMenuOption == 2) {
			if (bankroll < 5000) {
				cashier();
			}
			else {
				cout << "\nThe cashier is only open to players with less than " << maxDeposit << "\n";
				cout << "Your bankroll is: " << bankroll << "\n\n";
			}
		}

		else if (mainMenuOption == 1) {
			cout << endl << "Thanks for playing! " << endl;
			gameRunning = false;
		}

		else if (mainMenuOption == 0) {
		}

		else {
			cout << std::endl << "Please pick a valid option" << std::endl << std::endl;
		}
	}
}

// Main Menu where user can pick option
void menu() {
	cout << "Main Menu    \n";
	cout << " (3) Play    \n";
	cout << " (2) Cashier \n";
	cout << " (1) Quit  \n\n";
	cout << "Please pick your option: ";
	cin >> mainMenuOption;
}

// Player picks his betsize here
int pickBetSize() {
	int betSize;

	cout << "\nBetsize";
	cout << "\n (3) " << betSizes[2];
	cout << "\n (2) " << betSizes[1];
	cout << "\n (1) " << betSizes[0];
	cout << "\n\nHow much do you like to bet? ";
	cin >> betSize;

	switch (betSize) {
	case 1: return betSizes[0];
	case 2: return betSizes[1];
	case 3: return betSizes[2];
	default: cout << "\nPlease pick a valid option\n"; pickBetSize();
	}
	return 0;
}

// Gameplay takes place here
void playGame(int betSize) {
	int playerScore = 0;
	int computerScore = 0;
	int roundCounter = 1;
	bool playRunning = true;

	while (playRunning) {
		int playerDice = rand() % 6 + 1;
		int computerDice = rand() % 6 + 1;

		gameAnimation(playerDice, computerDice, roundCounter);

		if (playerDice > computerDice) {
			playerScore++;

			if (playerScore >= roundsToWin) {
				playRunning = false;
				bankroll += betSize;
				cout << "\nYou Won " << betSize << "\n";
				cout << "Current bankroll: " << bankroll << "\n\n";
				break;
			}
		}

		if (computerDice > playerDice) {
			computerScore++;

			if (computerScore >= roundsToWin) {
				playRunning = false;
				bankroll -= betSize;
				cout << "\nYou Lost " << betSize << "\n";
				cout << "Current bankroll: " << bankroll << "\n\n";
				break;
			}
		}
		roundCounter++;
	}
}

// Simulate a roll animation
void gameAnimation(int playerDice, int computerDice, int roundCounter) {
	cout << "\n***Round " << roundCounter << "***\n";
	sleep_for(400ms);
	cout << "Player throws... ";
	sleep_for(400ms);
	cout << playerDice << endl;

	sleep_for(400ms);
	cout << "Computer throws... ";
	sleep_for(400ms);
	cout << computerDice << endl;
}

// Cashier where player can deposit to bankroll
void cashier() {
	int deposit;

	cout << endl;
	cout << "Cashier \n";
	cout << " Bankroll: " << bankroll << "\n";
	cout << " Max deposit: " << (maxDepositSize - bankroll) << "\n\n";
	cout << "Please enter the amount to deposit: ";
	cin >> deposit;

	if (deposit < minDepositSize) {
		cout << "\nYour deposit is too small (minimum deposit " << minDepositSize << ")\n";
	}
	else if (deposit > maxDepositSize) {
		cout << "\nYour deposit is too large (maximum deposit " << maxDepositSize << ")\n";
	}
	else {
		bankroll += deposit;
		cout << "\nThank you for your deposit!\n";
	}
	cout << "Current bankroll: " << bankroll << "\n\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
