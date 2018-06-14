/* This is the console executable that makes use of the BullCowGame class
This acts as the view in a MVC pattern and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/
#pragma once

#include <iostream> // <> for standard libraries
#include <string>
#include "FBullCowGame.h"

// Replicate Unreal syntax
using FText = std::string;
using int32 = int;

// Function protoyping
void PrintIntro ();
void PlayGame ();
FText GetValidGuess ();
bool AskToPlayAgain ();
void PrintGameSummary ();

FBullCowGame BCGame; // Instantiate a new game, reuse across plays

// Entry point for the application
int main () {
	bool bPlayAgain = false;

	do {
		PrintIntro ();
		PlayGame ();
		bPlayAgain = AskToPlayAgain ();
	} while (bPlayAgain);

	return 0; // Exit the application
}

void PrintIntro () {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "          }   {         ___ \n";
	std::cout << "          (o o)        (o o) \n";
	std::cout << "   /-------\\ /          \\ /-------\\ \n";
	std::cout << "  / | BULL |O            O| COW  | \\ \n";
	std::cout << " *  |-,--- |              |------|  * \n";
	std::cout << "    ^      ^              ^      ^ \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength ();
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;

	return;
}

// Plays a single game to completion
void PlayGame () {
	BCGame.Reset ();
	int32 maxTries = BCGame.GetMaxTries ();

	// Loop for how many turns there are while the game is not won
	// Still has tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries) {
		FText guess = GetValidGuess ();

		// Submit valid guess to the game
		FBullCowCount bullCowCount = BCGame.SubmitValidGuess (guess);

		std::cout << "Bulls = " << bullCowCount.bulls;
		std::cout << ". Cows = " << bullCowCount.cows << "\n\n";
	}

	PrintGameSummary ();
	return;
}

// Get a guess from the player
FText GetValidGuess () {
	EGuessStatus status = EGuessStatus::INVALID;
	FText guess = "";
	do {
		int32 currentTry = BCGame.GetCurrentTry ();
		std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		
		getline (std::cin, guess);

		status = BCGame.CheckGuessValidity (guess);
		switch (status) {
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength () << " letter word.\n\n";
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// Assume the guess is valid
			break;
		}
	} while (status != EGuessStatus::OK);

	return guess;
}

bool AskToPlayAgain () {
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText response = "";
	getline (std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
}

void PrintGameSummary () {
	if (BCGame.IsGameWon ()) {
		std::cout << "WELL DONE - YOU WIN!\n";
	} else {
		std::cout << "YOU LOSE - BETTER LUCK NEXT TIME!\n";
	}
}
