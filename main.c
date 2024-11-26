#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define MAX_ROUNDS 50
#define MAX_MOVE_LENGTH 100


bool coinToss();
void displayStatus(int playerHP, int enemyHP, int roundsRemaining, int hp, char nameRace[][20], int class, int computerClass);
void playerTurn(int* playerHP, int* enemyHP, int* damageDealt, int* enemyArmor, int* armor, int* healingDone, bool* enemyDefense, bool* defense, int choice, int hp, int round, int fullMoon, char nameRace[][20],int computerClass, int class);
void enemyTurn(int* playerHP, int* enemyHP, int* damageDealt, int* enemyArmor, int* armor, int* healingDone, bool* enemyDefense, bool* defense, int choice, int hp, int round, int fullMoon, char nameRace[][20],int class, int computerClass);
int displayMoves(int* choice, bool alpha, int class);
void record(int choice, int computerChoice, int round, int damageDealt, int healingDone, int armor, int enemyArmor, bool monkeysPawActive, bool retaliateActive);
void printSummary(int round, bool firstMove, bool win, int fullMoon);
bool monkeysPaw(int* enemyStat,int choice, char nameRace[][20], int class, int computerClass, bool user);
void retaliate(int* neutralHP, int* neutralArmor, int choice, char nameRace[][20], int class, int computerClass, bool user, int attackerClass);
bool lunarBlessing(int classWereWolfOnly, int fullMoon, int round, int choice, char nameRace[][20], int class, int computerClass, bool user);
void typeshit(char talk[], char nameRace[][20], int class, int computerClass, bool user);
void typeshitNumeroDos(char talk[]);
void dialogue(int number, char* dialogueOutput);
int smartChoice(int computerClass, int enemyHP, int maxHP);
void clearInputBuffer();

char playerMoves[MAX_ROUNDS][MAX_MOVE_LENGTH];
char enemyMoves[MAX_ROUNDS][MAX_MOVE_LENGTH];
bool alpha = false;


int main(){
    srand(time(0));
    bool firstMove;
    int class;
    int computerClass;
    int hp;
    int round;
    int enemyHP;
    int playerHP;
    int choice;
    int computerChoice;
    int attack;
    bool defense = false;
    bool enemyDefense = false;
    int heal = 0;
    int damageDealt = 0;
    int armor = 0;
    int healingDone = 0;
    int enemyArmor = 0;
    int totalRounds;
    char nameRace[3][20];
    bool win = false;
    char dialogueOutput[100];
    int fullMoon;
    char dialogueOutputNumeroDos[100];
    alpha = false;

    strcpy(nameRace[0], "Monkey");
    strcpy(nameRace[1], "Bristleback");
    strcpy(nameRace[2], "Werewolf");

    printf("===========================================================================================================================\n\n");
    printf("For context:\n\tMonkey>Werewolf\n\tWerewolf>Bristleback\n\tBristleback>Monkey\n\n When 80%% of the max round lasts, full moon occurs.\n Monkey's Paw was heavily inspired by mystical artifact that grants its holder three wishes, but with a dark twist:\n every wish comes with unforeseen and often tragic consequences.\n Bristleback is a porcupine, he turns his back when defending.\n\n");
    printf("Race cheat codes:\n\t[Monkey(++Attack)]: Monkey's Paw{skill} 40%% chance -- Enemy moves may get reduced of its effectivity.\n\t[Bristleback(++Defense)]: Retaliate {skill} 60%% chance -- When using defense, may repel the damage according to armor.\n\t[Werewolf(++Heal)]: Lunar blessing {skill} --  When full moon is out, Alpha mode is activated(only attack) is activated -- strong attacks\n\n");
    printf("\n\n===========================================================================================================================\n\n");
    do{
        printf("\nRace(Theme): \n\t[1]Monkey\n\t[2]Bristleback\n\t[3]Werewolf\nChoose your race: ");
        scanf(" %d", &class);
        if(!(class>0 && class<4)){
            printf("Error! Choose only among the 3 dumb player!\n");
        }
    }while(!(class>0 && class<4));

    Sleep(1000);
    printf("\nEnemy is choosing a race...\n\n");
    computerClass = 1;
    Sleep(1000);
    switch(computerClass){
        case 1:
            printf("Enemy chose Monkey!\n");
            break;
        case 2:
            printf("Enemy chose Bristleback!\n");
            break;
        case 3:
            printf("Enemy chose Werewolf!\n");
            break;
    }

    do{
        printf("\nEnter max HP(50-200): ");
        scanf(" %d", &hp);
        if(!(hp>=50 && hp<=200))printf("Error! must be in the range of 50-200\n\n");
    }while(!(hp>=50 && hp<=200));

    playerHP = hp;
    enemyHP = hp;

    do{
        printf("\nEnter max rounds(20-50): ");
        scanf(" %d", &round);
        if(!(round>=20 && round<=50))printf("Error! must be in the range of 20-50\n\n");          
    }while(!(round>=20 && round<=50));

    fullMoon = (int)(round * 0.8); //calculate the 80% of total rounds for fullmoon
    totalRounds = round;
    round=0;

    printf("\nInitiating coin toss..\n\n");

    Sleep(1000);
    system("cls");
    Sleep(1000);
    firstMove = coinToss();
    Sleep(1000);

    //GAME START
    displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
    //This is just for dialogue with who moves first that's why i didnt use loop
    if(firstMove){

        displayMoves(&choice, alpha, class);

        dialogue(class, dialogueOutput);
        typeshit( dialogueOutput, nameRace, class, computerClass, 1);
        Sleep(2000);

        playerTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense,  choice,  hp, round, fullMoon, nameRace, computerClass, class);
        


        system("cls");
        displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
        Sleep(1000);

        computerChoice = smartChoice(computerClass, enemyHP, hp);
        enemyTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense,  computerChoice,  hp, round, fullMoon, nameRace, class, computerClass);


        
        system("cls");
        displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
        Sleep(1000);

    }else{
        Sleep(1000);
        dialogue(computerClass, dialogueOutput);
        typeshit( dialogueOutput, nameRace, class, computerClass, 0);
        Sleep(2000);

        computerChoice = smartChoice(computerClass,  enemyHP, hp);
        enemyTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense,  computerChoice,  hp, round, fullMoon, nameRace, class, computerClass);

        
        system("cls");
        displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
        Sleep(1000);

        displayMoves(&choice, alpha, class);
        playerTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense,  choice,  hp, round, fullMoon, nameRace, computerClass, class);

        
        system("cls");
        displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
        Sleep(1000);
    }

    round++;

    //After first moves the game loops,
    while (round < totalRounds && playerHP > 0 && enemyHP > 0) {

        if(fullMoon==round){//When fullmoon occurs, with or without werewolves
            system("cls");
            dialogue( 9, dialogueOutputNumeroDos);
            typeshitNumeroDos(dialogueOutputNumeroDos);
            alpha = true; // so that werewolves can transform if fullmoon
            printf("Alpha mode: %s\n", alpha ? "true" : "false");
            Sleep(500);
            system("cls");
        }

        if(firstMove == 1){

            system("cls");
            displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
            Sleep(500);

            displayMoves(&choice, alpha, class);
            playerTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense, choice,  hp, round, fullMoon, nameRace, computerClass, class);
            if(enemyHP<=0){
                win = true;
                break;
            }
            
            system("cls");
            displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
            Sleep(1000);

            computerChoice = smartChoice(computerClass, enemyHP, hp);
            enemyTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense, computerChoice,  hp, round, fullMoon, nameRace, class, computerClass);

            
            system("cls");
            displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
            Sleep(1000);

        } else {

            system("cls");
            displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
            Sleep(500);

            computerChoice = smartChoice(computerClass, enemyHP, hp);
            enemyTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense, computerChoice,  hp, round, fullMoon, nameRace, class, computerClass);
            
            if(playerHP<=0){
                win = true;
                break;
            }

            
            system("cls");
            displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
            Sleep(1000);


            displayMoves(&choice, alpha, class);
            playerTurn(&playerHP, &enemyHP, &damageDealt, &enemyArmor, &armor, &healingDone, &enemyDefense, &defense,  choice,  hp, round, fullMoon, nameRace, computerClass, class);

            
            system("cls");
            displayStatus(playerHP, enemyHP, round, hp,  nameRace, class, computerClass);
            Sleep(500);

        }
        ++round;
    }
    Sleep(1000);
    printf("===================== Game Over =====================\n\n");

    displayStatus(playerHP, enemyHP, round-1, hp,  nameRace, class, computerClass);
    Sleep(2000);

    if(playerHP==enemyHP){

        printf("What a rare occurence of a draw!\n");

    }else if(playerHP>enemyHP){

        printf("Congratulations!!! You won!\n");
        if(class==1){
            dialogue(10, dialogueOutput);
            typeshit( dialogueOutput, nameRace, class, computerClass, true);
        }else if(class == 2){
            dialogue(11, dialogueOutput);
            typeshit( dialogueOutput, nameRace, class, computerClass, true);
        }else if(class == 3){
            dialogue(12, dialogueOutput);
            typeshit( dialogueOutput, nameRace, class, computerClass, true);
        }
    }else if(enemyHP>playerHP){

        printf("Enemy won! Better luck next time :( ...!\n");
        if(computerClass==1){
            dialogue(10, dialogueOutput);
            typeshit( dialogueOutput, nameRace, class, computerClass, false);
        }else if(computerClass == 2){
            dialogue(11, dialogueOutput);
            typeshit( dialogueOutput, nameRace, class, computerClass, false);
        }else if(computerClass == 3){
            dialogue(12, dialogueOutput);
            typeshit( dialogueOutput, nameRace, class, computerClass, false);
        }
    }

    Sleep(1000);
    printf("Press enter to see summary...");
    getchar();
    getchar();

    system("cls");

    printSummary(round, firstMove, win, fullMoon);

    if(playerHP>enemyHP){
        printf("\nPlayer Won!\n");
    }else if(enemyHP>playerHP){
        printf("\nEnemy Won!\n");

    }
    printf("Press enter to end...");
    getchar();
    getchar();
    
    return 0;
}





// ----------- Coin Toss(player is always heads(1), Ai is tails(2)) ----------------
bool coinToss(){
    int first = rand() % 2;

    if(first){
        printf("Player won on the coin toss\n");
    }else{
        printf("Computer won on the coin toss\n");
    }
    return first;
}
//-----------------Game Status----------------
void displayStatus(int playerHP, int enemyHP, int roundsRemaining, int hp, char nameRace[][20], int class, int computerClass) {
    printf("\n====== Game Status ======\n");
    printf("Player(%s) HP: %d/%d\n",nameRace[class-1], playerHP, hp);
    printf("Enemy(%s) HP: %d/%d\n", nameRace[computerClass-1], enemyHP, hp);
    printf("Round: %d\n", roundsRemaining+1);
    printf("=========================\n\n");
}

//----------------------------What happens when player attacks, defends or heals----------------------------------
void playerTurn(int* playerHP, int* enemyHP, int* damageDealt, int* enemyArmor, int* armor, int* healingDone, bool* enemyDefense, bool* defense, int choice, int hp, int round, int fullMoon, char nameRace[][20],int computerClass, int class) {
    
    int attack;
    int heal;
    int actionEffectiveness=0;//This is for monkeyspaw(debuff),  when it activates, it sets the move of the enemy as itself then it reduces its effectivity
    *damageDealt=0;
    bool monkeysPawActive = false;//This is for recording if skill activated or not 
    bool retaliateActive = false;//Same 

    if(class==3){
        if(fullMoon==round && alpha){
            lunarBlessing( class, fullMoon, round, choice, nameRace, class, computerClass, true);
            choice = 1;
        }
    }
        

    if(class==1){ //Monkey attributes
        attack = rand()% 4 + 2;// attack 2-5
        *armor = 1;
        heal = rand()% 2 + 1;
    }else if(class==2){ // Bristleback attributes
        attack = rand()% 3 + 1;
        *armor = rand()% 4 + 2;//Armor 2-5
        heal = 1;
        if(computerClass==3){
            *armor = rand()% 5 + 2;//Slightly increasing armor when fighting werewolf
        }
    }else if(class==3){ //Werewolf
        attack = rand()% 2 + 1;
        *armor = rand()% 2 + 1;
        heal = rand()% 3 + 1; //Heal 1-4
        if(alpha){
            attack = rand()% 3 + 6;//when lunar blessing occurs, attack increases 6-8
        }
    }


    switch(choice){
        Sleep(1000);
        case 1://Player attacks
            printf("Player(%s) chose to attack!\n", nameRace[class-1]);
            actionEffectiveness = attack;
            Sleep(1000);

            if(*enemyDefense == true && attack > *enemyArmor){//When player attacks but enemy defended
                printf("Player(%s) atacks the enemy for %d damage!\n", nameRace[class-1], attack);
                attack -= *enemyArmor;
                Sleep(1000);
                printf("Attack gets reduced by defense to %d!\n", attack);
            } else if(*enemyDefense == true){
                printf("Player(%s) atacks the enemy for %d damage!\n", nameRace[class-1], attack);
                Sleep(1000);
                printf("Attack gets fully blocked!\n");
                attack = 0;
            }
            
            if(attack>0 && computerClass==1){//Checks if enemy is monkey and if attack is greater than 0, there is no need for debuff when its already at 0
                if(monkeysPaw(&actionEffectiveness, choice, nameRace, -1 , computerClass, false)){
                    monkeysPawActive = true;//If monkeyspaw activates, it records it 
                    Sleep(1000);
                    printf("Initial attack damage: %d\n", attack);
                }
                attack = actionEffectiveness;
                Sleep(500);
            }

            printf("Player(%s) attacks the enemy for %d damage!\n", nameRace[class-1], attack);

            if(computerClass == 2 && *enemyDefense==true){ //checks if enemy is BristleBack and if they defended to know that it is no okay for his passive to acivate
                retaliate(playerHP , enemyArmor , choice, nameRace, class, computerClass, false, class);
                retaliateActive = true;//records if retaliate activates
                Sleep(3000);
            }

            *damageDealt = attack;
            *enemyHP -= attack;
            *enemyDefense = false;
            break;
        case 2://Player Defends
            actionEffectiveness = *armor;
            printf("Player(%s) chose to defend!\n", nameRace[class-1]);
            Sleep(1000);

            if(computerClass == 1){
                if(monkeysPaw(&actionEffectiveness, choice, nameRace, -1 , computerClass, false)){
                    monkeysPawActive = true;
                    Sleep(1000);
                    printf("Initial player armor: %d\n", *armor);
                }
                *armor = actionEffectiveness;
                Sleep(500);
            }

            printf("\nNext attack by the enemy would get reduced by %d!\n", *armor);
            *defense = true;
            break;
        case 3://Player Heals
            actionEffectiveness = heal;
            printf("Player(%s) heals themself!\n", nameRace[class-1]);
            Sleep(1000);

            if(computerClass == 1 && *playerHP < hp){
                if(monkeysPaw(&actionEffectiveness, choice, nameRace, -1 , computerClass, false)){
                    monkeysPawActive = true;
                    Sleep(1000);
                    printf("Initial heal amount: %d\n", heal);
                }
                heal = actionEffectiveness;
                Sleep(500);
            }
            *playerHP += heal;
            *healingDone = heal;
            if (*playerHP > hp){
                *healingDone = hp - (*playerHP - heal);
                printf("Player(%s) is already beyond max HP! Reducing heal to %d.\n", nameRace[class-1] , *healingDone);
                Sleep(500);
                printf("+%dHP\n", *healingDone);
                *playerHP = hp;
                
            }
            else{printf("+%dHP\n", *healingDone);}
            break;
    }
    Sleep(3000);

    if(*enemyHP<0){ //This is to ensure there are no negative HP.
        *enemyHP = 0;
    }
    record(choice, -1, round, *damageDealt, *healingDone, *armor, *enemyArmor, monkeysPawActive, retaliateActive);
}
//------------------------------------------Same thing but for AI moves----------------------------------------
void enemyTurn(int* playerHP, int* enemyHP, int* damageDealt, int* enemyArmor, int* armor, int* healingDone, bool* enemyDefense, bool* defense, int choice, int hp, int round, int fullMoon, char nameRace[][20],int class, int computerClass) {
    int attack = 0;
    int heal = 0;
    int actionEffectiveness = 0;
    *damageDealt = 0;
    bool monkeysPawActive = false;
    bool retaliateActive = false;


    if(computerClass==1){ //Monkey attributes
        attack = rand()% 4 + 2;// attack 2-5
        *enemyArmor = 1;
        heal = rand()% 2 + 1;
    }else if(computerClass==2){ // Bristleback attributes
        attack = rand()% 3 + 1;
        *enemyArmor = rand()% 3 + 2; //armor 2-4
        heal = 1;
        if(class==3){
             *enemyArmor = rand()% 5 + 2; //slightly increase armor when werewolf bc werewolf is way too strong
        }
    }else if(computerClass==3){ //Werewolf
        attack = rand()% 2 + 1;
        *enemyArmor = rand()% 2 + 1;
        heal = rand()% 3 + 1; //Heal 1-4

        if(alpha){
            attack = rand()% 3 + 6;//when lunar blessing occurs, attack increases 7-9
        }
    }
    
    if(computerClass==3){
        if(fullMoon==round && alpha){
            lunarBlessing( computerClass, fullMoon, round, choice, nameRace, class, computerClass, false);
            choice = 1;
        }
    }


    switch(choice){
        case 1:
            actionEffectiveness = attack;
            printf("Enemy(%s) chose to attack!\n", nameRace[computerClass-1]);
            Sleep(1000);

            if(*defense == true && attack > *armor){
                printf("Enemy(%s) attacks the Player for %d!\n",nameRace[computerClass-1], attack);
                attack -= *armor;
                Sleep(1000);
                printf("Attack gets reduced by defense to %d!\n", attack);
            } else if(*defense == true){
                printf("Enemy(%s) atacks the Player for %d damage!\n",nameRace[computerClass-1], attack);
                Sleep(1000);
                printf("Attack gets fully blocked!\n");
                attack = 0;
            }

            
            if(attack>0 && class ==1){
                if(monkeysPaw(&actionEffectiveness, choice, nameRace, class , -1, true)){
                    monkeysPawActive = true;
                    Sleep(1000);
                    printf("Initial attack damage: %d\n", attack);
                }
                attack = actionEffectiveness;
                Sleep(500);
            }
            printf("Enemy(%s) attacks the Player for %d damage!\n\n", nameRace[computerClass-1], attack);
            
            if(class == 2 && *defense == true){
                retaliate(enemyHP , armor , choice, nameRace, class, computerClass, true, computerClass);
                retaliateActive = true;
                Sleep(3000);
            }

            *damageDealt = attack;
            *playerHP -= attack;
            *defense = false;
            Sleep(1000);
            break;
        case 2:
            printf("Enemy(%s) chose to defend!\n", nameRace[computerClass-1]);
            actionEffectiveness = *enemyArmor;
            Sleep(1000);

            if(class==1){
                if(monkeysPaw(&actionEffectiveness, choice, nameRace, class , -1, true)){
                    monkeysPawActive = true;
                        Sleep(1000);
                        printf("Initial enemy armor: %d\n", *enemyArmor);
                }
                *enemyArmor = actionEffectiveness;
                Sleep(500);
            }

            printf("\nPlayer's next attack would get reduced by %d!\n", *enemyArmor);
            *enemyDefense = true;
            break;
        case 3:
            printf("Enemy(%s) heals themself!\n", nameRace[computerClass-1]);
            actionEffectiveness = heal;
            Sleep(1000);

            if(class==1  && *enemyHP < hp){
                if(monkeysPaw(&actionEffectiveness, choice, nameRace, class , -1, true)){
                    monkeysPawActive = true;
                        Sleep(1000);
                        printf("Initial heal amount: %d\n", heal);
                }
                heal = actionEffectiveness;
                Sleep(500);
            }

            *enemyHP += heal;
            *healingDone = heal;
            if (*enemyHP > hp){
                *healingDone = hp - (*enemyHP - heal);
                printf("Enemy(%s) is already beyond max HP! Reducing heal to %d.\n",nameRace[computerClass-1], *healingDone);
                printf("+%dHP\n", *healingDone);
                *enemyHP = hp;
            }
            else{printf("+%dHP\n", *healingDone);}
            break;
    }
    Sleep(3000);


    if(*playerHP<0){
        *playerHP = 0;
    }
    record(-1, choice, round, *damageDealt, *healingDone, *armor, *enemyArmor,  monkeysPawActive, retaliateActive);
}

//---------------------Player choices to move----------------
int displayMoves(int* choice, bool alpha, int class){
    if(class==3){
        if (alpha) {
             printf("Alpha mode is active.\n");
            do{
                // If Alpha Mode is active, only allow attack and the player choices are overrided so its cool., XD
                printf("Player choice:\n");
                    printf("\t[1] Attack\n");
                    printf("\t[[2$1]De$f!t$#ck\n");
                    printf("\t[1%%^3]Hǝt*#&ta$!?k\n");
                    printf("\t[@&]#@$%%ck\n");
                    printf("== ");
                if (scanf(" %d", choice) != 1) {
                        clearInputBuffer(); // Clear the buffer if invalid input
                        *choice = 0; // Set choice to an invalid value
                    }
                if(*choice != 1){
                    system("cls");
                    typeshitNumeroDos("RrrGHhh... I-I mRr-uuu-us-st.... RRrrRoonRrly-yY.... arrghtTtack!!(I must only attack!)");
                }
            }while(*choice != 1);
        }else{//this is for when player chooses werewolf , normal display moves would still work when not in alpha mode
             printf("Player choice:\n");
                printf("\t[1] Attack\n");
                printf("\t[2] Defend\n");
                printf("\t[3] Heal\n");
                printf("== ");
                scanf(" %d", choice);
            if (!(*choice > 0 && *choice < 4)) {
                printf("Invalid Choice! Moves are only between 1 and 3...\n");
            }
        }
    }else{
        printf("Player choice:\n");
                printf("\t[1] Attack\n");
                printf("\t[2] Defend\n");
                printf("\t[3] Heal\n");
                printf("== ");
                scanf("%d", choice);
        if (!(*choice > 0 && *choice < 4)) {
            printf("Invalid Choice! Moves are only between 1 and 3...\n");
        }
    }
    return *choice;
}

//-------------------------------------------Storing damage, armor , and HP for Summary ------------------------------
void record(int choice, int computerChoice, int round, int damageDealt, int healingDone, int armor, int enemyArmor, bool monkeysPawActive, bool retaliateActive) {
    
    if (choice != -1) { 
        switch (choice) {
            case 1:
                if (monkeysPawActive) {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player attacks, dealt %d damage (debuffed by Monkey's Paw)", round + 1, damageDealt);
                } else if (retaliateActive) {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player attacks, dealt %d damage (%d damage retaliated)", round + 1, damageDealt, enemyArmor);
                } else {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player attacks, dealt %d damage", round + 1, damageDealt);
                }
                break;
            case 2:
                if (monkeysPawActive) {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player defends, gains %d armor (debuffed by Monkey's Paw)", round + 1, armor);
                } else {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player defends, gains %d armor", round + 1, armor);
                }
                break;
            case 3:
                if (monkeysPawActive) {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player heals, restored %d HP (debuffed by Monkey's Paw)", round + 1, armor);
                } else {
                    snprintf(playerMoves[round], MAX_MOVE_LENGTH, "Round %d: Player heals, restored %d HP", round + 1, healingDone);
                }
                break;
        }
    }


    if (computerChoice != -1) {
        switch (computerChoice) {
            case 1:
                if (monkeysPawActive) {
                    snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy attacks, dealt %d damage (debuffed by Monkey's Paw)", round + 1, damageDealt);
                } else if (retaliateActive) {
                    snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy attacks, dealt %d damage (%d damage retaliated)", round + 1, damageDealt, armor);
                } else {
                    snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy attacks, dealt %d damage", round + 1, damageDealt);
                }
                break;
            case 2:
                if (monkeysPawActive) {
                    snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy defends, gains %d armor (debuffed by Monkey's Paw)", round + 1, enemyArmor);
                } else {
                    snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy defends, gains %d armor", round + 1, enemyArmor);
                }
                break;
            case 3:
                if (monkeysPawActive) {
                    snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy heals, restored %d HP (debuffed by Monkey's Paw)", round + 1, healingDone);
                } else {
                snprintf(enemyMoves[round], MAX_MOVE_LENGTH, "Round %d: Enemy heals, restored %d HP", round + 1, healingDone);
                }
                break;
        }
    }
}
//--------------------Summary--------------------
void printSummary(int round, bool firstMove, bool win, int fullMoon) {
    int i;
    printf("\n================= Game Summary =================\n");

    printf("%s moves 1st!\n", firstMove ? "Player" : "Enemy");

    if(firstMove){
        for (i = 0; i < round; i++) {
            if(fullMoon==i){
                printf("Full moon occured.\n");
            }
            printf("%s\n", playerMoves[i]);
            if (i != round - 1) { // Print enemy move if its not the last round
                printf("%s\n", enemyMoves[i]);
            }else if(i == round -1 && !win){//Would only print player move bc he won already and enemy move isnt possible
                printf("%s\n", enemyMoves[i]);
            }else{
                printf("Round %d: Enemy (x_x) Dead af", round + 1);
            }
        }
    }else{
        for (i = 0; i < round; i++) {
            if(fullMoon==i){
                printf("Full moon occured.\n");
            }
            printf("%s\n", enemyMoves[i]);
            if (i != round - 1) { // Print player move if its not the last round
                printf("%s\n", playerMoves[i]);
            }else if(i == round -1 && !win){//Would only print enemy move bc he won already and player move isnt possible
                printf("%s\n", playerMoves[i]);
            }else{
                 printf("Round %d: Player (x_x) Dead af", round + 1);
            }
        }
    }
}
//----------------------------------------------------------SKILLS-----------------------------------------------------
//-------------------------- Monkey's Passive skill ------------------------------------
bool monkeysPaw(int* enemyStat,int choice, char nameRace[][20], int class, int computerClass, bool user){ 
    int skillChance = 45;
    char dialogueOutput[100];

        if(rand()%100+1<=skillChance){
            switch(choice){
                case 1://Dialogue of monke when skill activated for enemy attack
                    dialogue( 4, dialogueOutput);
                    typeshit( dialogueOutput, nameRace, class, computerClass, user);
                    break;
                case 2://dialogue when Defend
                    dialogue( 5, dialogueOutput);
                    typeshit( dialogueOutput, nameRace, class, computerClass, user);
                    break;
                case 3://dialogue when Heal
                    dialogue( 6, dialogueOutput);
                    typeshit( dialogueOutput, nameRace, class, computerClass, user);
                    break;
            }

            // Reduce the stat, ensuring it doesn't go below 0
            if (*enemyStat > 0) {
                (*enemyStat)--;
            }
            return true;
        }
    return false;
}
//----------------------------------- BristleBack passive skill -------------------------------------------
void retaliate(int* neutralHP, int* neutralArmor,int choice, char nameRace[][20], int class, int computerClass, bool user, int attackerClass){
    int skillChance = 60;
    char dialogueOutput[100];
    if(attackerClass==3){// balancing out bristleback vs werewolf cuz if old skillchance its unwinnable
        skillChance = 85;
    }
    if(rand()%100+1<=skillChance){

        *neutralHP-= *neutralArmor;//Retaliates damage received based on armor 
        dialogue( 7, dialogueOutput);
        typeshit( dialogueOutput, nameRace, class, computerClass, user);

        if(user){
            Sleep(1000);
            printf("Enemy(%s) attack gets retaliated by %d damage!\n", nameRace[computerClass-1], *neutralArmor);
        }else{
            Sleep(1000);
            printf("Player(%s) attack gets retaliated by %d damage!\n", nameRace[class-1], *neutralArmor);
        }
               
    }
}
//-------------------------------------- Werewolf passive skill--------------------------------------
bool lunarBlessing(int classWereWolfOnly, int fullMoon, int round, int choice, char nameRace[][20], int class, int computerClass, bool user){
    char dialogueOutput[100];

    if(classWereWolfOnly==3){//only for werewolf
        dialogue( 8, dialogueOutput);//This is all just dialogue, main purpose is the bool, when true alpha mode occurs(stronger attavks)
        typeshit( dialogueOutput, nameRace, class, computerClass, user);

        return true;
    }
    return false;
}   
//--------------------------------------- Smart computer move choices ------------------------------
int smartChoice(int computerClass, int enemyHP, int maxHP){
    int moveChance = 65; // setting that 65 percent of the time computer would choose their strongest attribute move
    int randomNum= rand()%100+1;

    if(computerClass == 1){//monke computer
        
        if(randomNum <= moveChance){
            return 1;
        }else if(enemyHP == maxHP){// so that computers wouldnt heal when they are at max hp
            return 2;
        }else{
            return rand() % 2 + 2; //randomize choice between 2 and 3
        }
    }else if(computerClass == 2){// bristleback computer

        moveChance = 75; //75 percent of the time bb defends so it would balance out, he has a weak skill if he cant use it
        
        if(rand()%100+1 <= moveChance){
            return 2;
        }else if(enemyHP == maxHP){// so that computers wouldnt heal when they are at max hp
            return 1;
        }else{
            return rand() % 2 * 2 + 1; // randomize choice can only be 1 or 3
        }
    }else if(computerClass == 3){// werewolf computer
        if(alpha){// returns 1 only when alpha mode
            return 1;
        }else if(enemyHP == maxHP){// so that computers wouldnt heal when they are at max hp
            
            if(randomNum <= 83){ //since at max hp , there are only 2 options, defend or attack but defend has a 25% so 25/35 = 83 
                return 2; //25 percent chance to defend when not healing
            }else{
                return 1; 
            }
        }else if(randomNum <= moveChance){
            return 3;
        }else if(randomNum <= 90){
            return 2; //25 percent chance to defend when not healing
        }else{
            return 1; 
        }
    }
}

void typeshitNumeroDos(char talk[]){
    for(int i = 0; strlen(talk)>i;i++){
        printf("%c", talk[i]);
        Sleep(35);
    }
    printf("\n");
}
//--------------------------------Dialogue typewriter animation----------------------------------
void typeshit(char talk[], char nameRace[][20], int class, int computerClass, bool user){
    if(user){
        printf("Player(%s): ", nameRace[class-1]);
    }else{
        printf("Enemy(%s): ", nameRace[computerClass-1]);
    }
    for(int i = 0; strlen(talk)>i;i++){
        printf("%c", talk[i]);
        Sleep(35);
    }
    printf("\n");
}
//--------------------- All of the character dialogues--------------------------------------------------
void dialogue(int number, char* dialogueOutput){

    int randomTalk = rand()%3+1;
    switch(number){
        //First Moves
        case 1://monke
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"The early monkey gets the win! Let's swing!");
                    break;
                case 2:
                    strcpy(dialogueOutput,"*Laughs* Didn't see that coming, did ya? Classic monkey move!");
                    break;
                case 3:
                    strcpy(dialogueOutput,"Oh, you wanted to go first? Not on my watch!");
                    break;
            }
            break;
        case 2://Bristle
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"Stepping up first-let's get this brawl started!");
                    break;
                case 2:
                    strcpy(dialogueOutput,"I'm leading this charge, so brace yourself!");
                    break;
                case 3:
                    strcpy(dialogueOutput,"Guess I'm the one to make the first dent here.");
                    break;
            }
            break;
        case 3://Wolf
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"The wolf leads, but don't mistake it for haste.");
                    break;
                case 2:
                    strcpy(dialogueOutput,"Let's start slow. We have a long game ahead... for you, maybe.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"Speed favors the patient. You ready?");
                    break;
            }
        break;
        //SKills
        case 4://Monkeyspaw attack
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"You asked for a strong blow, but Monkey's Paw decided otherwise.");
                    break;
                case 2:
                    strcpy(dialogueOutput,"Ah, that attack wasn't quite as strong as you hoped, was it? The catch of the paw.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"The paw granted your wish-just not in the way you expected.");
                    break;
            }
        break;
        case 5://Monkeyspaw defense
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"You wished for protection, but the paw leaves you more vulnerable than ever.");
                    break;
                case 2:
                    strcpy(dialogueOutput,"You can try to defend, but the paw's twist is making it weak.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"The paw granted your wish-just not in the way you expected.");
                    break;
            }
        break;
        case 6://Monkeyspaw heal
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"The paw granted your wish for healing, but the cost is a slow recovery.");
                    break;
                case 2:
                    strcpy(dialogueOutput,"You wanted to heal quickly? The paw has other plans.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"The paw granted your wish-just not in the way you expected.");
                    break;
            }
        break;
        case 7://Bristle retaliates
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"Go ahead, attack... but you'll be feeling the sharp end of my defense!");
                    break;
                case 2:
                    strcpy(dialogueOutput,"You thought you could hurt me? Now you're getting a taste of my retaliation!");
                    break;
                case 3:
                    strcpy(dialogueOutput,"Every strike you land just makes the spikes sharper!");
                    break;
            }
        break;
        case 8://Alpha mode XD
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"Snarl... A-Alpha... m-moon... p-p-power... Hhrrrgggghhh!");
                    break;
                case 2:
                    strcpy(dialogueOutput, "AARRGGHH— F-feel... m-my f-fury... N-no escape... die... hhh!");
                    break;
                case 3:
                    strcpy(dialogueOutput,"I've been waiting... waiting for the moon to rise... f-feeling its power... N-no more control... Hhhrrrghhh... Y-you will not survive this! RAWRR!!");
                    break;
            }
        break;
        case 9://Full moon arrives
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"The pale light of the full moon began to pierce through the clouds, casting its silver glow across the battlefield.");
                    break;
                case 2:
                    strcpy(dialogueOutput, "Through the thick veil of clouds, the silver light of the full moon spilled across the desolate field.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"The full moon emerged from its shroud, its cold light stretching across the battlefield in eerie silence.");
                    break;
            }
        break;
        case 10://Win monke
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"Oo-oo-ah-ah! Guess I'm king of the jungle again!");
                    break;
                case 2:
                    strcpy(dialogueOutput, "Eek-eek! That was bananas! Better luck next time!");
                    break;
                case 3:
                    strcpy(dialogueOutput,"Oo-oo-oo! Eee-ee! The Monkey's Paw strikes again-your wishes just ran out!");
                    break;
            }
        break;
        
        case 11://Win bristle
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"You threw everything at me-and still lost. Pathetic");
                    break;
                case 2:
                    strcpy(dialogueOutput, "You fought hard, but I'm just harder.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"You call that a fight? I've seen sharper claws on kittens.");
                    break;
            }
        break;

        case 12://Win wolf
            switch(randomTalk){
                case 1:
                    strcpy(dialogueOutput,"Hrrnnn... Y-you... were never... a match... GRRRRR!");
                    break;
                case 2:
                    strcpy(dialogueOutput, "The moon rises, and so do I-above you.");
                    break;
                case 3:
                    strcpy(dialogueOutput,"The moon sees all, and under its gaze, I am victorious!");
                    break;
            }
        break;    
    }
}
void clearInputBuffer() {
    while(getchar() != '\n');
}