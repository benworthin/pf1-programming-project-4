#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constants
const int MAX_SPEED = 8;
const int MAX_PLAYER_HEALTH = 30;
const int MAX_DL_HEALTH = 50;

// ---------- Basic Mechanisms ----------

// Stun: reduce the opponent's speed to 0.
bool Stun(const int SpeedDif) {

    double prob = (double) (SpeedDif + 1) / MAX_SPEED;
    double dice = (double) rand() / RAND_MAX;

    if (dice < prob) {
        return true;
    } else {
        return false;
    }

}

// Evade: avoid being hitting by the opponent's attack.
bool Evade(const int SpeedDif) {

    double prob = (double) (SpeedDif + 1) / (MAX_SPEED + 2);
    double dice = (double) rand() / RAND_MAX;

    if (dice < prob) {
        return true;
    } else {
        return false;
    }

}

// ---------- Unforgivable Curses ----------

// Avada Kedavra: Cause large health damage (health-10). Can be evaded if the player's speed is higher than the dark lord's speed.
void AvadaKedavra(int & PlayerHealth, int & PlayerSpeed, const int DLHealth, const int DLSpeed) {

    cout << "Dark Lord casts Avada Kedavra." << endl;
    int SpeedDif = PlayerSpeed - DLSpeed;

    if (Evade(SpeedDif) == false) {

        cout << "You are hit. Health-10." << endl;
        PlayerHealth -= 10;

    } else {
        cout << "You evaded it." << endl;
    }

}

// Imperio: Has chance of stun if the dark lord's speed is higher than the player's speed. 
void Imperio(int & PlayerHealth, int & PlayerSpeed, const int DLHealth, const int DLSpeed) {

    cout << "Dark Lord casts Imperio." << endl;

    int SpeedDif = DLSpeed - PlayerSpeed;

    if (Stun(SpeedDif) == true) {

        cout << "You are stunned." << endl;
        PlayerSpeed = 0;

    } else {
        cout << "It takes no effect on you." << endl;
    }

}

// Crucio: Cause medium damage and slow the player (health-5, speed-1). The player's speed cannot be reduced to 0 (minimum 1). 
// Can be evaded if the player's speed is higher than the dark lord's speed.
void Crucio(int &PlayerHealth, int &PlayerSpeed, const int DLHealth, const int DLSpeed) {

    cout << "Dark Lord casts Crucio." << endl;

    int SpeedDif = PlayerSpeed - DLSpeed;

    if (Evade(SpeedDif) == false) {

        cout << "You are hit. Health-5. Speed-1." << endl;
        PlayerHealth -= 5;

        if (PlayerSpeed>1) {
            PlayerSpeed -= 1;
        }

    } else {
        cout << "You evaded it." << endl;
    }

}

// ---------- Dark Lord Move ----------

void DLMove(int & PlayerHealth, int & PlayerSpeed, const int DLHealth, const int DLSpeed) {

    int choice = rand() % 3;

    switch (choice) {
    case 0:
        AvadaKedavra(PlayerHealth, PlayerSpeed, DLHealth, DLSpeed);
        break;
    case 1:
        Imperio(PlayerHealth, PlayerSpeed, DLHealth, DLSpeed);
        break;
    case 2:
        Crucio(PlayerHealth, PlayerSpeed, DLHealth, DLSpeed);
        break;
    default:
        ;
    }

}

// ---------- Hogwarts Spells ----------

// Expelliarmus (Disarming Spell): Has chance of stun if the player's speed is higher than the opponent's speed.
void Expelliarmus(const int PlayerHealth, const int PlayerSpeed, int & DLHealth, int & DLSpeed) {

    cout << "You cast Expelliarmus." << endl;

    int speedDif = PlayerSpeed - DLSpeed;

    if (Stun(speedDif) == true) {

        cout << "Dark Lord is stunned." << endl;
        DLSpeed = 0;

    } else {
        cout << "Dark Lord is not affected by your puny attack." << endl;
    }

}

// TODO: Implement at least two other spells.

// Scourgify (Damage Spell): Cleans the ground below the opponent, causing them to slip and hit their head
// Health -15, can be evaded if the Dark Lord's speed is higher than the player's speed
void Scourgify(const int PlayerHealth, const int PlayerSpeed, int &DLHealth, int &DLSpeed) {

    cout << "You cast Scourgify with a smirk." << endl;

    int speedDif = DLSpeed - PlayerSpeed;

    if (!Evade(speedDif)) {

        cout << "You got him! Health: -15" << endl;
        DLHealth -= 15;

    } else {
        cout << "He evaded it... c'mon man." << endl;
    }

}

// Pack (Medium Damage & Speed Spell): Packs and drops luggage trunk on opponents head (Health -5, Speed -2)
// Can be evaded if the Dark Lord's speed is higher than the player's speed
// Dark Lord's speed cannot be 0 (minimum 1)
void Pack(const int PlayerHealth, const int PlayerSpeed, int &DLHeath, int &DLSpeed) {

    cout << "You cast Pack! There goes your neat luggage..." << endl;

    int speedDif = DLSpeed - PlayerSpeed;

    if (!Evade(speedDif)) {

        cout << "Ouch! That is going to leave a mark. Health -5. Speed -2." << endl;
        DLHeath -= 5;

        if (DLSpeed > 1) {
            DLSpeed -= 2;
        }

    } else {
        cout << "How does a big trunk miss? Get it together!" << endl;
    }

}

// ---------- Player Move ----------

void PlayerMove(const int PlayerHealth, const int PlayerSpeed, int & DLHealth, int & DLSpeed) {
    // TODO: Implement the player's move in each round.  
}

// ---------- Main Function ----------

int main() {

    srand(time(NULL));

    int PlayerHealth = MAX_PLAYER_HEALTH;
    int PlayerSpeed = MAX_SPEED;
    int DLHealth = MAX_DL_HEALTH;
    int DLSpeed = MAX_SPEED;

    cout << "Battle begins!" << endl;
	
	int round = 1;

    while ((PlayerHealth > 0) && (DLHealth > 0)) {
		
		cout << "---------------Round " << round << "---------------" << endl;
		
		// Restore 1 speed at the begining of each round.
        if (PlayerSpeed<MAX_SPEED) PlayerSpeed += 1;
        if (DLSpeed<MAX_SPEED) DLSpeed += 1;

        cout << "Your health is " << PlayerHealth << ", speed is " << PlayerSpeed << ".\n";
        cout << "Dark Lord's health is " << DLHealth << ", speed is " << DLSpeed << ".\n";
		
		// TODO: Call PlayerMove and DLMove functions. You need to decide which one moves first.
		// Remember: The one with higher speed moves first. If they have the same speed, then use a random number to decide.
		// If one's speed is 0 (i.e., stuned), then you should skip his move.
		
		
		round++;
    }

    if (PlayerHealth > 0) {
        cout << "You win!" << endl;
    } else {
        cout << "Dark lord wins." << endl;
    }

    return 0;

}

