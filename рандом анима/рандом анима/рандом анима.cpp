#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

vector<string> readFramesFromFile(const string& filename, const string& delimiter) {
    vector<string> frames;
    ifstream file(filename);

    if (!file) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return frames;
    }

    string line, frame;
    while (getline(file, line)) {
        if (line == delimiter) {
            if (!frame.empty()) {
                frames.push_back(frame);
                frame.clear();
            }
        }
        else {
            frame += line + "\n";
        }
    }
    if (!frame.empty()) {
        frames.push_back(frame);
    }

    return frames;
}

void animate(const vector<string>& frames) {
    const int numFrames = frames.size();
    for (int i = 0; i < numFrames; ++i) {
        clearScreen();
        cout << frames[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int randomInt(int min, int max)
{
    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int main()
{
    string choice;
    do
    {
        setlocale(0, "ru");
        string filename;
        string delimiter;
        int n = randomInt(1, 3);
        if (n == 1)
        {
            filename = "go.txt";
            delimiter = "r";
        }
        else if (n == 2)
        {
            filename = "tytyty.txt";
            delimiter = "?";
        }
        else
        {
            filename = "for.txt";
            delimiter = ",";
        }


        vector<string> frames = readFramesFromFile(filename, delimiter);

        if (!frames.empty())
            animate(frames);

        else
            cout << "Нет кадров для анимации." << endl;
        cin >> choice;
    } while (choice != "nigger");
}