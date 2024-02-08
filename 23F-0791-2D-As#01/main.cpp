#include <iostream>
#include <ctime>
#include<Windows.h>

#define RESET   "\033[0m"   
#define RED     "\033[1m\033[31m"  
#define BLUE    "\033[1m\033[34m" 
#define GREEN   "\033[32m"     
#define YELLOW  "\033[1m\033[33m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m" 
#define BOLD    "\033[1m"

using namespace std;

struct Horse {
    string name;
    int speed;
    int endurance;
    int position;
    int fatigue;
};

const int totalHorses = 8;
const int finishLine = 150;

void moveHorse(Horse* horse) {
    (*horse).position += (*horse).speed + (*horse).endurance  ;

    if ((*horse).position < 0) {
        (*horse).position = 0; 
    }
}

void applyFatigue(Horse* horse) {

    (*horse).fatigue += (((*horse).speed) * (5) - ((*horse).endurance)) / 5;
}

void applyObstacles(Horse* horse) {
    int obstacleChance = rand() % 10;
    if (obstacleChance < 2) {
        cout << RED << "Obstacle encountered: Mud Pit - " << (*horse).name << " slowed down.\n" << RESET;
        (*horse).position -= 2;
        (*horse).fatigue += 3;
        if ((*horse).position < 0) {
            (*horse).position = 0; 
        }
    }
}

void raceTrack(const Horse* horses) {
    cout << "Race Track:\n";
    for (int i = 0; i < totalHorses; i++) {
        cout << GREEN << "|";
        for (int j = 0; j < finishLine; j++) {
            if (j == horses[i].position) {
                cout << MAGENTA << i + 1 <<  GREEN; // Display horse number at its position
            }
            else {
                cout << "-";
            }
        }
        cout << "|\n" << RESET;
    }
}

void raceStatus(const Horse* horses) {
    cout << "\nRace Status:\n";
    for (int i = 0; i < totalHorses; i++) {
        cout << BOLD << YELLOW << i + 1 << ". " << horses[i].name << " - Position: " << horses[i].position
            << ", Fatigue: " << horses[i].fatigue << "\n" << RESET;
    }
}

bool raceFinished(const Horse* horses) {
    for (int i = 0; i < totalHorses; i++) {
        if (horses[i].position >= finishLine) {
            cout << BLUE << "\nRace Ended. Winner: " << horses[i].name << "\n" << RESET;
            return true;
        }
    }
    return false;
}

int main() {
    srand(time(0));

    Horse horses[totalHorses] = {
        {"Eren yeager"},
        {"Mikasa Eren"},
        {"Zeak yeager"},
        {"Ervin Smith"},
        {"Armin psuda"},
        {"Bertold Hoover"},
        {"Reiner trator"},
        {"Areeba yeager"}
    };

    for (int i = 0; i < totalHorses; ++i) {
        horses[i].speed = rand() % 10;
        horses[i].endurance = rand() % 10;
        horses[i].position = rand() % 10;
        horses[i].fatigue = rand() % 10;
    }


    cout << CYAN << "Starting Horse Racing Simulation...\n" << RESET;
    Sleep(3000);

    int count = 1;
    while (!raceFinished(horses)) {
        cout << CYAN << "\nRace Status After iteration " << count << ":\n" << RESET;
        for (int i = 0; i < totalHorses; i++) {
            moveHorse(&horses[i]);
            applyFatigue(&horses[i]);
            applyObstacles(&horses[i]);
        }
        raceTrack(horses);
        raceStatus(horses);
        count++;
        system("pause");
    }

    return 0;
}
