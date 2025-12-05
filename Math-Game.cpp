#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

enum enGameLevel { Easy = 1, Medium = 2, Hard = 3, Mixture = 4 };

enum enOperatingType { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, Mix = 5 };

enum enGameResult { Win = 1, Lose = 2, Draw = 3 };

struct stRoundInfo {
    short CurrentRound;
    short NumOfRounds;
    enGameLevel UserLevelChoice;
    enOperatingType UserOPChoice;
    enGameResult RoundResult;
    short Num1;
    short Num2;
    short UserAnswer;
    short ActuallyResult;
    char ActualOPChar;
};

struct stGameInfo {
    enGameLevel UserLevelChoice;
    enOperatingType UserOPChoice;
    short NumOfRounds;
    enGameResult GameResult;
    short NumOfWin;
    short NumOfLose;
};

int RandomNum(int From, int To) {
    return rand() % (To - From + 1) + From;
}

short ReadNumOfRounds() {
    short NumOfRounds;
    do {
        cout << " Please Enter How Many Rounds Will You Play ? ";
        cin >> NumOfRounds;
    } while (NumOfRounds <= 0);
    return NumOfRounds;
}

enGameLevel ReadGameLevel() {
    short GameLevel;
    do {
        cout << "\n Please Enter Game Level ? [1] = Easy, [2] = Medium, [3] = Hard, [4] = Mix ? ";
            cin >> GameLevel;
    } while (GameLevel <= 0 || GameLevel > 4);
    return (enGameLevel)GameLevel;
}

string enLevelToString(enGameLevel Level) {
    string GameLevel[4] = { "Easy","Medium","Hard","Mix" };
    return GameLevel[Level - 1];
}

enOperatingType ReadOperatingType() {
    short OP;
    do {
        cout << "\n What Type Of Operating Do You Want ? [1]=Addition, [2]=Subtraction, [3]=Multiplication, [4]=Division, [5]=Mix ? ";
            cin >> OP;
    } while (OP <= 0 || OP > 5);
    return (enOperatingType)OP;
}

string enOperatingToString(enOperatingType OP) {
    string Operating[5] = { "Addition" ,"Subtraction" ,"Multiplication", "Division" ,"Mix" };
    return Operating[OP - 1];
}

char GetRandomOPChar() {
    short RandOp = RandomNum(1, 4);
    switch (RandOp) {
    case 1: 
        return '+';
    case 2: 
        return '-';
    case 3:
        return '*';
    case 4: 
        return '/';
    }
    return '+';
}

short CalculateResult(char OPChar, short Num1, short Num2) {
    switch (OPChar) {
    case '+':
        return Num1 + Num2;
    case '-': 
        return Num1 - Num2;
    case '*': 
        return Num1 * Num2;
    case '/': 
        return Num1 / Num2;
    }
    return 0;
}

char OperatingTypeToChar(enOperatingType OP) {
    switch (OP) {
    case enOperatingType::Addition: 
        return '+';
    case enOperatingType::Subtraction: 
        return '-';
    case enOperatingType::Multiplication:
        return '*';
    case enOperatingType::Division:
        return '/';
    default: return GetRandomOPChar();
    }
}

short GenerateNum(enGameLevel Level) {
    switch (Level) {
    case enGameLevel::Easy:
        return RandomNum(1, 10);
    case enGameLevel::Medium:
        return RandomNum(10, 50);
    case enGameLevel::Hard: 
        return RandomNum(50, 100);
    default: return RandomNum(1, 100);
    }
}

enGameResult DeterminResult(short UserAnswer, short ComputerAnswer) {
    if (UserAnswer == ComputerAnswer)
        return enGameResult::Win;
    else
        return enGameResult::Lose;
}

string enResultToString(enGameResult Result) {
    if (Result == enGameResult::Win)
        return "Right";
    else
        return "Wrong";
}

void SetColorByResult(enGameResult Result) {
    switch (Result) {
    case Win:
        system("Color 2F");
        break;
    case Lose:
        system("Color 4F");
        break;
    case Draw:
        system("Color 6F");
        break;
    }
}

stRoundInfo PlayRound(short CurrentRound, short NumOfRounds, enGameLevel Level, enOperatingType UserOPChoice) {
    stRoundInfo RoundInfo;
    RoundInfo.CurrentRound = CurrentRound;
    RoundInfo.NumOfRounds = NumOfRounds;
    RoundInfo.UserLevelChoice = Level;
    RoundInfo.UserOPChoice = UserOPChoice;

    RoundInfo.Num1 = GenerateNum(RoundInfo.UserLevelChoice);
    RoundInfo.Num2 = GenerateNum(RoundInfo.UserLevelChoice);

    if (UserOPChoice == enOperatingType::Mix) {
        RoundInfo.ActualOPChar = GetRandomOPChar(); 
    }
    else {
        RoundInfo.ActualOPChar = OperatingTypeToChar(UserOPChoice);
    }

    RoundInfo.ActuallyResult = CalculateResult(RoundInfo.ActualOPChar, RoundInfo.Num1, RoundInfo.Num2);
    return RoundInfo;
}

void PrintRoundInfo(stRoundInfo& RoundInfo) {
    cout << "\n Round(" << RoundInfo.CurrentRound << " / " << RoundInfo.NumOfRounds << ") \n";
    cout << " " << RoundInfo.Num1 << " " << RoundInfo.ActualOPChar
        << " " << RoundInfo.Num2 << " = ";
    cin >> RoundInfo.UserAnswer;

    RoundInfo.RoundResult = DeterminResult(RoundInfo.UserAnswer, RoundInfo.ActuallyResult);
    SetColorByResult(RoundInfo.RoundResult);
    cout << "\n Your Answer is " << enResultToString(RoundInfo.RoundResult);
        if (RoundInfo.RoundResult == enGameResult::Lose) {
            cout << " , The Right Answer is " << RoundInfo.ActuallyResult << endl;
        }
}

enGameResult FinalGameResult(short NumOfWin, short NumOfLose) {
    if (NumOfWin > NumOfLose)
        return enGameResult::Win;
    else if (NumOfLose > NumOfWin)
        return enGameResult::Lose;
    else
        return enGameResult::Draw;
}

string enFinalResultToString(enGameResult GameResult) {
    switch (GameResult) {
    case enGameResult::Win:
        return "You Are Win (: ";
    case enGameResult::Lose:
        return "You Are Lose ): ";
    default:
        return "Draw <> ";
    }
    return "0";
}

stGameInfo PlayGame(short NumOfRounds) {
    stGameInfo GameInfo;
    GameInfo.NumOfRounds = NumOfRounds;
    GameInfo.UserLevelChoice = ReadGameLevel();
    GameInfo.UserOPChoice = ReadOperatingType();
    GameInfo.NumOfLose = 0, GameInfo.NumOfWin = 0;

    for (int i = 1; i <= GameInfo.NumOfRounds; i++) {
        stRoundInfo RoundInfo = PlayRound(i, GameInfo.NumOfRounds, GameInfo.UserLevelChoice, GameInfo.UserOPChoice);
        PrintRoundInfo(RoundInfo);
        if (RoundInfo.RoundResult == enGameResult::Win)
            GameInfo.NumOfWin++;
        else
            GameInfo.NumOfLose++;
    }

    GameInfo.GameResult = FinalGameResult(GameInfo.NumOfWin, GameInfo.NumOfLose);
    SetColorByResult(GameInfo.GameResult);
    return GameInfo;
}

void PrintGameInfo(stGameInfo GameInfo) {
    cout << "\n________________________________\n";
    cout << "\n      G A M E  O V E R          \n";
    cout << "\n________________________________\n";

    cout << " Number Of Rounds  : " << GameInfo.NumOfRounds << endl;
    cout << " Game Level        : " <<enLevelToString(GameInfo.UserLevelChoice) << endl;
    cout << " Operating Type    : " <<enOperatingToString(GameInfo.UserOPChoice) << endl;
    cout << " Number Of Win     : " << GameInfo.NumOfWin << endl;
    cout << " Number Of Lose    : " << GameInfo.NumOfLose << endl;
    cout << " Final Result      : " << enFinalResultToString(GameInfo.GameResult) << endl;
}

void StartGame() {
    char Answer;
    do {
        system("cls");
        system("Color 07");
        short NumOfRounds = ReadNumOfRounds();
        stGameInfo GameInfo = PlayGame(NumOfRounds);
        cout << "\n Do You Want To Show Game Info Panel ? (Y / N) ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            PrintGameInfo(GameInfo);
        }
        cout << "\n Do You Play Again ? (Y / N) ? " ;
        cin >> Answer;
    } while (Answer == 'y' || Answer == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}