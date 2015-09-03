#define Y_POS_DIS 0x1C
#define Y_FIELD (LPVOID)(0x0B27979)
#define Y_ATTACK_FIRST_TURN ((LPVOID)0x0B27803)
#define Y_PLAYER_CARDS ((LPVOID)0x0B76510)
#define Y_ENEMY_CARDS (LPVOID)(Y_PLAYER_CARDS + 0x20)
#define Y_ENEMY_LP 0x0B7652C
#define Y_PLAYER_LP (Y_ENEMY_LP - 0x20)
#define Y_ENEMY_LP_VISUAL (Y_ENEMY_LP - 0x2)
#define Y_PLAYER_LP_VISUAL (Y_PLAYER_LP - 0x2)
#define Y_POS_1 ((LPVOID)0x0C33210)
#define Y_POS_2 (Y_POS_1 + Y_POS_DIS)
#define Y_POS_3 (Y_POS_2 + Y_POS_DIS)
#define Y_POS_4 (Y_POS_3 + Y_POS_DIS)
#define Y_POS_5 (Y_POS_4 + Y_POS_DIS)
#define Y_CARD_POS_OF 0xB
unsigned char atacar = 0x00;
#define Y_PLAYER 0
#define Y_ENEMY 1

#define NO_OUTPUT 0

BOOL Y_FIELD_CHOOSE = FALSE;
BYTE Y_CHOSEN_FIELD = 0;


typedef struct _Card{
    
    short int id;
    short int atk;
    short int def;
    
}CARD;
