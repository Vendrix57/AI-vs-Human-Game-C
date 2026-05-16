#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/* ===============================
   WAIT FOR ENTER
================================*/
void waitForEnter(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

/* ===============================
   HP BAR
================================*/
void hpBar(char name[], int hp, int maxHP)
{
    int maxBar = 10;
    int filled = (hp * maxBar) / maxHP;

    printf("%-6s HP: %3d [", name, hp);

    for (int i = 0; i < filled; i++)
        printf("#");

    for (int i = filled; i < maxBar; i++)
        printf("-");

    printf("]\n");
}

/* ===============================
   AI DECISION ENGINE
   0 = Heal
   1 = Attack
   2 = Special
================================*/
int ai_decision(int PlayerHP, int AiHP, int PlayerAttackCount, int AiSpecialUsed)
{
    int attack_score;
    int heal_score;
    int special_score = -1000;

    attack_score = (100 - PlayerHP) + (AiHP / 2);

    int simulated_heal = AiHP + 15;
    if (simulated_heal > 100)
        simulated_heal = 100;

    heal_score = simulated_heal - (PlayerHP / 2);

    if (AiHP < 30)
        heal_score += 15;

    if (PlayerAttackCount >= 2)
        attack_score += 15;

    if (AiSpecialUsed == 0)
    {
        special_score = (100 - PlayerHP) + 25;

        if (PlayerHP <= 50)
            special_score += 20;
    }

    if (special_score >= attack_score && special_score >= heal_score)
        return 2;

    if (attack_score >= heal_score)
        return 1;

    return 0;
}

/* ===============================
   MAIN
================================*/
int main()
{
    srand(time(NULL));

    int PlayerHP = 100;
    int AiHP = 100;

    int PlayerAttackCount = 0;
    int PlayerSpecialUsed = 0;
    int AiSpecialUsed = 0;

    int ValidTurn;
    char Choice;
    int Round;

    printf("=====================================\n");
    printf("         ***PLAYER vs AI***\n");
    printf("=====================================\n");

    printf("\n      \"Only one will survive.\"\n");

    printf("\n\n\n\n\n\n\n\n\n\nPress ENTER to begin...");
    waitForEnter();

    system("cls");

    printf("Entering Battle...\n");
    sleep(1);

    int Countdown = 3;

    while (Countdown >= 1)
    {
        printf("\t%d\n", Countdown);
        sleep(1);
        Countdown--;
    }

    printf("     FIGHT!!!\n");
    sleep(1);

    for (Round = 1; Round <= 30; Round++)
    {
        system("cls");

        printf("=====================================\n");
        printf("              ROUND %02d\n", Round);
        printf("=====================================\n\n");

        hpBar("Player", PlayerHP, 100);
        hpBar("AI", AiHP, 100);

        printf("\n-------------------------------------\n");
        printf("Actions:\n");
        printf("\n a -> Attack (20 dmg)\n");
        printf(" h -> Heal (15 HP)\n");
        printf(" b -> Special Attack (35-50 dmg, once)\n");
        printf("-------------------------------------\n");

        printf("Your choice: ");
        scanf(" %c", &Choice);

        ValidTurn = 1;

        /* PLAYER TURN */

        if (Choice == 'a')
        {
            AiHP -= 20;
            PlayerAttackCount++;
            printf("\nYou attacked and dealt 20 damage!\n");
        }
        else if (Choice == 'h')
        {
            PlayerHP += 15;
            if (PlayerHP > 100)
                PlayerHP = 100;

            printf("\nYou healed yourself for 15 HP!\n");
        }
        else if (Choice == 'b')
        {
            if (PlayerSpecialUsed == 0)
            {
                int damage = 35 + rand() % 16;
                AiHP -= damage;
                PlayerSpecialUsed = 1;
                PlayerAttackCount++;

                printf("\n*** SPECIAL ATTACK! ***\n");
                printf("You dealt %d damage!\n", damage);
            }
            else
            {
                printf("\nSpecial attack already used!\n");
                ValidTurn = 0;
            }
        }
        else
        {
            printf("\nInvalid action! Try again.\n");
            ValidTurn = 0;
        }

        if (ValidTurn == 0)
        {
            sleep(2);
            continue;
        }

        if (AiHP < 0)
            AiHP = 0;
        if (PlayerHP < 0)
            PlayerHP = 0;

        if (AiHP == 0 || PlayerHP == 0)
            break;

        sleep(1);

        /* AI TURN */

        printf("\nAI is thinking...\n");
        sleep(1);

        int ai_action = ai_decision(PlayerHP, AiHP, PlayerAttackCount, AiSpecialUsed);

        if (ai_action == 1)
        {
            PlayerHP -= 20;
            printf("AI chose ATTACK and dealt 20 damage!\n");
        }
        else if (ai_action == 0)
        {
            AiHP += 15;
            if (AiHP > 100)
                AiHP = 100;

            printf("AI chose HEAL and recovered 15 HP!\n");
        }
        else if (ai_action == 2)
        {
            int damage = 35 + rand() % 16;
            PlayerHP -= damage;
            AiSpecialUsed = 1;

            printf("AI used *** SPECIAL ATTACK ***!\n");
            printf("AI dealt %d damage!\n", damage);
        }

        if (AiHP < 0)
            AiHP = 0;
        if (PlayerHP < 0)
            PlayerHP = 0;

        if (AiHP == 0 || PlayerHP == 0)
            break;

        sleep(2);
    }

    printf("\n=====================================\n");

    if (PlayerHP > AiHP)
        printf("\tPLAYER WINS!\n");
    else if (AiHP > PlayerHP)
        printf("\tAI WINS!\n");
    else
        printf("\tDRAW!\n");
        

    printf("=====================================\n");

    return 0;
}