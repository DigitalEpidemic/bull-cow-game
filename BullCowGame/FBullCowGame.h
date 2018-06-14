/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once

#include <string>

// Replicate Unreal syntax
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

class FBullCowGame {
public:
	FBullCowGame (); // Constructor

	int32 GetMaxTries () const;
	int32 GetCurrentTry () const;
	int32 GetHiddenWordLength () const;
	bool IsGameWon () const;
	EGuessStatus CheckGuessValidity (FString) const;

	void Reset ();
	FBullCowCount SubmitValidGuess (FString guess);

private:
	// See constructor for initialization
	int32 myCurrentTry;
	FString myHiddenWord;
	bool bGameIsWon;

	bool IsIsogram (FString) const;
	bool IsLowercase (FString) const;
};
