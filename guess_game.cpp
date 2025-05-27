#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ヒント表示関数
// 改良されたヒント表示関数（距離で調整）
void checkGuess(int guess, int secret) {
    int diff = guess - secret;

    if (diff == 0) {
        cout << "正解です！" << endl;
    } else if (diff >= 20) {
        cout << "あと20点以上小さくする必要があります！" << endl;
    } else if (diff >= 15) {
        cout << "あと15点以上小さくする必要があります！" << endl;
    } else if (diff >= 10) {
        cout << "あと10点以上小さくする必要があります！！" << endl;
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
    cin >> level;

    switch(level) {
        case 1:
            maxNumber = 30;
            attempts = 10;
            break;
        case 2:
            maxNumber = 50;
            attempts = 8;
            break;
        case 3:
            maxNumber = 75;
            attempts = 6;
            break;
        case 4:
            maxNumber = 100;
            attempts = 6;
            break;
        case 5:
            maxNumber = 130;
            attempts = 5;
            break;
        default:
            cout << "無効な選択です。NORMALで開始します。" << endl;
            maxNumber = 50;
            attempts = 8;
    }

    int secret = rand() % maxNumber + 1;
    int guess;

    cout << "\n1〜" << maxNumber << " の数を当ててください！" << endl;

    while (attempts > 0) {
        cout << "\n残り回数: " << attempts << endl;
        cout << "予想を入力してください: ";
        cin >> guess;

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

    return 0;
}
