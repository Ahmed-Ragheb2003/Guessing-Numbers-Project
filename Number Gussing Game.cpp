#include <iostream>
#include<cstdlib>
using namespace std;


enum enGussGameLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4 };

struct stRoundInfo
{
	enGussGameLevel GussGameLevel;
	string TextRecordLevel;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerRight = false;
};

struct stGameResult
{
	stRoundInfo RoundsList[100];
	enGussGameLevel GussGameLevel;
	short NumberOfRounds;
	short NumberRightAnswer = 0;
	short NumberWrongAnswer = 0;
	bool isPass = false;
};


int RandomNumber(int Form, int To) 
{
	int Random = rand() % (To - Form + 1) + Form;
	return Random;
}

string GetGameGussLevelText(enGussGameLevel GussGameLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med","Hard","Mix" };
	return arrQuestionLevelText[GussGameLevel - 1];
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F"); // turn screen to Green
	}
	else
	{
		system("color 4F");// turn screen to Red
		cout << "\a";
	}
}

int ReadHowManyRound()
{
	int NumberRound = 0;
	do
	{
		cout << "How many Round do you want [1 to 10]: ";
		cin >> NumberRound;

	} while (NumberRound < 1 || NumberRound > 10);

	return NumberRound;
}

enGussGameLevel ReadGussGameLevel()
{
	int GussGameLevel = 0;
	do		
	{
		cout << "Enter Rounds Game Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> GussGameLevel;

	} while (GussGameLevel < 1 || GussGameLevel > 4);

	return (enGussGameLevel)GussGameLevel;
}

enGussGameLevel GetRandomGameLevel()
{
	int RandomLevel = RandomNumber(1, 3);
	return (enGussGameLevel)RandomLevel;
}


stRoundInfo GenerateRound(enGussGameLevel GussGameLevel)
{
	stRoundInfo RoundInfo;	

	if (GussGameLevel == enGussGameLevel::MixLevel)
	{
		GussGameLevel = GetRandomGameLevel();
	}

	RoundInfo.GussGameLevel = GussGameLevel;


	switch (GussGameLevel)
	{

	case enGussGameLevel::EasyLevel:
		RoundInfo.CorrectAnswer = RandomNumber(1, 5);
		RoundInfo.TextRecordLevel = "PLease, Guss Number From 1 TO 5 ..:)";
		return RoundInfo;
		
	case enGussGameLevel::MedLevel:
		RoundInfo.CorrectAnswer = RandomNumber(1, 10);
		RoundInfo.TextRecordLevel = "PLease, Guss Number From 1 TO 10 ..:)";
		return RoundInfo;

	case enGussGameLevel::HardLevel:
		RoundInfo.CorrectAnswer = RandomNumber(1, 15);
		RoundInfo.TextRecordLevel = "PLease, Guss Number From 1 TO 15 ..:)";
		return RoundInfo;

	}

	return RoundInfo;
}

void GenerateRoundsGame(stGameResult& GameResult)
{
	for (short Round = 0; Round < GameResult.NumberOfRounds; Round++)
	{
		GameResult.RoundsList[Round] =
			GenerateRound(GameResult.GussGameLevel);
	}
}

int ReadRoundAnswer()
{
	int AnswerRound = 0;
	cin >> AnswerRound;
	return AnswerRound;
}

void PrintTheRounds(stGameResult& GameResult, int RoundNumber)
{
	cout << "\n";
	cout << "_____________ Round [" << RoundNumber + 1 << "/" 
		<< GameResult.NumberOfRounds << "] _____________\n\n";

	cout << GameResult.RoundsList[RoundNumber].TextRecordLevel;
	cout << "\n_______________________________________\n\n";
}



void CorrectTheRoundAnswer(stGameResult& GameResult, int RoundNumber)
{
	if (GameResult.RoundsList[RoundNumber].PlayerAnswer != GameResult.RoundsList[RoundNumber].CorrectAnswer)
	{
		GameResult.RoundsList[RoundNumber].AnswerRight = false;
		GameResult.NumberWrongAnswer++;

		cout << "Worng Answer :-( \n";
		cout << "The Right answer is: ";
		cout << GameResult.RoundsList[RoundNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		GameResult.RoundsList[RoundNumber].AnswerRight = true;
		GameResult.NumberRightAnswer++;
		cout << "Right answer :-) \n";
	}

	cout << endl;
	SetScreenColor(GameResult.RoundsList[RoundNumber].AnswerRight);
}


void AskAndCorrectRoundListAnswer(stGameResult& GameResult)
{

	for (short i = 0; i < GameResult.NumberOfRounds; i++)
	{
		PrintTheRounds(GameResult, i);

		GameResult.RoundsList[i].PlayerAnswer = ReadRoundAnswer();
		CorrectTheRoundAnswer(GameResult, i);
	}

	GameResult.isPass = (GameResult.NumberRightAnswer >= GameResult.NumberWrongAnswer);
}

string GetFinalResult(bool Pass)
{

	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";

}

void PrintGameResult(stGameResult& GameResult)
{
	cout << "\n";
	cout << "\t\t\t_________________________________________________\n\n";
	cout << "\t\t\t\tFinal Result is " << GetFinalResult(GameResult.isPass);
	cout << "\n\t\t\t_________________________________________________\n\n";
	cout << "\t\t\tNumber of Question     : " << GameResult.NumberOfRounds << endl;
	cout << "\t\t\tQuestion Level         : " << GetGameGussLevelText(GameResult.GussGameLevel) << endl;
	cout << "\t\t\tNumber of Right Answer : " << GameResult.NumberRightAnswer << endl;
	cout << "\t\t\tNumber of Worng Answer : " << GameResult.NumberWrongAnswer << endl;
	cout << "\t\t\t_________________________________________________\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void PlayGussGame()
{
	stGameResult GameResult;

	GameResult.NumberOfRounds = ReadHowManyRound();
	GameResult.GussGameLevel = ReadGussGameLevel();
	
	system("cls");

	GenerateRoundsGame(GameResult);
	AskAndCorrectRoundListAnswer(GameResult);
	PrintGameResult(GameResult);
}

void ReadToStartGame()
{
	cout << "\n\n\n\n";
	cout << "\t\t\t\t_________________________________________________\n\n";
	cout << "\t\t\t\t\t      Number Gussing Game.";
	cout << "\n\t\t\t\t_________________________________________________\n";
	cout << "\n\t\t\t\t    Plaese Press any key to Start Game:";
	cin.ignore();

}

void StartGame()
{
	ReadToStartGame();
	system("cls");
	char PLayAgain = 'Y';
	do
	{
		ResetScreen();

		PlayGussGame();

		cout << "\n\t\t\tDo You Want To Play again? Y/N? ";
		cin >> PLayAgain;

	} while (toupper(PLayAgain) == 'Y');


}

void EndGame()
{
	system("cls");
	cout << endl;
	cout << endl;
	cout << "\n\n\n\t\t\t\t\t______________________________________________\n";
	cout << "\n\n\t\t\t\t\t\t\tThank You ...)\n";
	cout << "\n\t\t\t\t\t______________________________________________\n";
}



int main()
{
	srand((unsigned)time(NULL));

	StartGame();
	EndGame();

	system("pause>0");
	return 0;

}

