#pragma once

#include "FBullCowGame.h"
#include <map>

// Replicate Unreal syntax
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame () { Reset (); } // Default constructor

int32 FBullCowGame::GetCurrentTry () const { return myCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength () const { return (int32)myHiddenWord.length (); }
bool FBullCowGame::IsGameWon () const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries () const {
	TMap<int32, int32> wordLengthToMaxTries {{3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
	return wordLengthToMaxTries[myHiddenWord.length ()];
}

void FBullCowGame::Reset () {
	const FString HIDDEN_WORD = "planet"; // This MUST be an isogram
	myHiddenWord = HIDDEN_WORD;

	myCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity (FString guess) const {
	if (!IsIsogram(guess)) {
		return EGuessStatus::NOT_ISOGRAM;
	} else if (!IsLowercase(guess)) {
		return EGuessStatus::NOT_LOWERCASE;
	} else if (guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::WRONG_LENGTH;
	} else {
		return EGuessStatus::OK;
	}
}

// Receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess (FString guess) {
	myCurrentTry++;
	//setup return variable
	FBullCowCount BullCowCount;

	int32 hiddenWordLength = (int32)myHiddenWord.length ();
	int32 guessWordLength = (int32)guess.length ();

	for (int32 MHWChar = 0; MHWChar < hiddenWordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < guessWordLength; GChar++) {
			if (guess[GChar] == myHiddenWord[MHWChar]) {
				if (GChar == MHWChar) {
					BullCowCount.bulls++;
				} else {
					BullCowCount.cows++;
				}
			}
		}
	}

	if (BullCowCount.bulls == guessWordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram (FString word) const {
	// Treat 0 and 1 letter words as isograms
	if (word.length () <= 1) { return true; }

	// hashtable O(n) performance rather than nested for loops O(n^2)
	TMap<char, bool> letterSeen; // Setup the map
	for (auto letter : word) { // for all letters of the word
		letter = tolower (letter); // Handle mixed case
		if (letterSeen[letter]) { // If the letter is in the map
			return false; // We do NOT have an isogram
		} else {
			letterSeen[letter] = true; // Add the letter to the map
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase (FString word) const {
	for (auto letter : word) {
		if (!islower (letter)) {
			return false;
		}
	}
	return true;
}
