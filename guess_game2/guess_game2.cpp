#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// ヒント表示関数
// 改良されたヒント表示関数（距離で調整）
void checkGuess(const int& guess, const int& secret) {
    const int diff = guess - secret;

    if (diff == 0) {
        cout << "正解です！" << endl;
    } else if (diff >= 20) {
        cout << "あと20点以上小さくする必要があります！" << endl;
    } else if (diff >= 15) {
        cout << "あと15点以上小さくする必要があります！" << endl;
    } else if (diff >= 10) {
        cout << "あと10点以上小さくする必要があります！" << endl;
    } else if (diff > 0) {
        cout << "あと少し小さくする必要があります！" << endl;
    } else if (diff <= -20) {
        cout << "あと20点以上大きくする必要があります！" << endl;
    } else if (diff <= -15) {
        cout << "あと15点以上大きくする必要があります！" << endl;
    } else if (diff <= -10) {
        cout << "あと10点以上大きくする必要があります！" << endl;
    } else {
        cout << "あと少し大きくする必要があります！" << endl;
    }
}

std::string getLevelName(int level) {
    switch(level) {
        case 1: return "EASY";
        case 2: return "NORMAL";
        case 3: return "HARD";
        case 4: return "EXPERT";
        case 5: return "MASTER";
        default: return "UNKNOWN";
    }
}

int main() {
    srand(time(0));

    int level;
    int maxNumber, attempts;

    // 難易度選択
    cout << "==== 数当てゲーム ====" << endl;
    cout << "難易度を選んでください：" << endl;
    cout << "1. EASY    (1〜30, 10回)" << endl;
    cout << "2. NORMAL  (1〜50, 8回)" << endl;
    cout << "3. HARD    (1〜75, 6回)" << endl;
    cout << "4. EXPERT  (1〜100, 6回)" << endl;
    cout << "5. MASTER  (1〜120, 5回)" << endl;
    cout << "番号を入力: ";

    while (true) {
    cout << "番号を入力: ";
    if (!(cin >> level)) {
        cout << "無効な入力です。数値で入力してください。";
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
    }

    if (level >= 1 && level <= 5) {
        break;
    } else {
        cout << "無効な難易度番号です。1〜5の数字を入力してください。";
    }
}

switch (level) {
    case 1: maxNumber = 30; attempts = 10; break;
    case 2: maxNumber = 50; attempts = 8; break;
    case 3: maxNumber = 75; attempts = 6; break;
    case 4: maxNumber = 100; attempts = 6; break;
    case 5: maxNumber = 130; attempts = 5; break;
}

    int secret = rand() % maxNumber + 1;
    int guess;
    int totalTries = 0;

    cout << "\n1〜" << maxNumber << " の数を当ててください！" << endl;

    while (attempts > 0) {
        cout << "\n残り回数: " << attempts << endl;
        while (true) {
        cout << "予想を入力してください: ";
        if (cin >> guess) break;
        cout << "無効な入力です。数値を入力してください。\n";
        cin.clear();
        cin.ignore(10000, '\n');
        }


        if (guess == secret) {
            checkGuess(guess, secret);
            break;
        } else {
            checkGuess(guess, secret);
            attempts--;
        }
    }

    if (attempts == 0 && guess != secret) {
        cout << "\n😢 残念！正解は " << secret << " でした。" << endl;
    }

    cout << "\n--- ゲーム終了 ---" << endl;

     string result = (guess == secret) ? "WIN" : "LOSE";
     // ▼▼▼ プレイ履歴CSVに出力 ▼▼▼
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char datetime[20];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", ltm);

    ofstream fout("history.csv", ios::app);
    fout << datetime << "," << getLevelName(level) << "," << secret << "," << totalTries << "," << result << endl;
    fout.close();
    // ▲▲▲ 出力ここまで ▲▲▲

    // 勝率を表示
ifstream fin("history.csv");
string line;
int totalPlays = 0;
int totalWins = 0;

while (getline(fin, line)) {
    // カンマで分割
    stringstream ss(line);
    string dateStr, levelStr, ans, tries, res;
    getline(ss, dateStr, ',');
    getline(ss, levelStr, ',');
    getline(ss, ans, ',');
    getline(ss, tries, ',');
    getline(ss, res, ',');

    // 今回の難易度に一致する行のみ集計
    if (levelStr == getLevelName(level)) {
        totalPlays++;
        if (res == "WIN") totalWins++;
    }
}
fin.close();

// 勝率の表示
if (totalPlays > 0) {
    double winRate = static_cast<double>(totalWins) / totalPlays * 100.0;
    cout << "\n=== 勝率情報 ===" << endl;
    cout << "難易度: " << getLevelName(level) << endl;
    cout << "プレイ回数: " << totalPlays << " 回" << endl;
    cout << "勝率: " << winRate << "%\n" << endl;
}
    return 0;
}