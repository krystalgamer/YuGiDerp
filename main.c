/* 
 * File:   main.c
 * Author: NAMS
 *
 * Created on 31 de Agosto de 2015, 12:07
 */

#include <windows.h>
#include <stdio.h>

#include "addr.h"
/*
 * 
 */


HANDLE hProc;

void DrawMenu();
void WriteMem(LPVOID addr, LPCVOID buffer,size_t size, BYTE output);
void EditNumCards(BYTE victim);
void PrintCards(CARD cards[]);
int ReadCards(CARD cards[], LPVOID addr);
void EditHP(BYTE victim);
void EditCard(CARD cards[]);
void WINAPI FieldChooser();
void ChooseField();

int main(void) {
  
   
    //Variaveis
   CARD cards[5];
   HWND hndl;//process handler
   DWORD pid;
    
    hndl = FindWindow(0,"ePSXe - Enhanced PSX emulator");//Vamos ver se jogo ta ligado
    if(!hndl){
        printf("ePSXE is not running stopping..\n"); //Falhou a conseguir janela
        exit(1);
    }
    
    printf("ePSXE found!\n");
    GetWindowThreadProcessId(hndl, &pid);//Precisamos do pid 
    
    hProc = OpenProcess(PROCESS_ALL_ACCESS, 0 , pid);
    
    //Falhou a abrir processo, gg
    if(!hProc){
        printf("Couldn't open process..Exiting \n ");//Falhou a conseguir janela
        exit(3);
    }

    int sair = 1;
        
    CreateThread(NULL, 0, FieldChooser, NULL, 0, NULL);
    while(sair)
    {
        DrawMenu();
        scanf("%d", &sair);
        getchar();
        
        system("cls");
        switch(sair){
            
            case 1:
                WriteMem((LPVOID)Y_ATTACK_FIRST_TURN, &atacar, sizeof(atacar),1);
                break;
            case 2:
                ReadCards(cards,Y_POS_1);
                EditCard(cards);
                    break;
            case 3:
            case 4:
                    EditNumCards(sair == 3 ? Y_PLAYER : Y_ENEMY);
                break;
            case 5:
                ReadCards(cards,Y_POS_1);
                PrintCards(cards);
                break;
            case 6:
            case 7:
                    EditHP(sair == 6 ? Y_PLAYER : Y_ENEMY);
                    break;
            case 8:
                ChooseField();
        }
        
    }
       /** getchar();
        getchar();
        getchar();
        getchar();*/
        
    return 0;
}

void WriteMem(LPVOID addr, LPCVOID buffer,size_t size, BYTE output){
    
    int i = WriteProcessMemory(hProc, addr, buffer, size, NULL);
    
    if(output){
        if(i)
            printf("Success\n");
        else
            printf("Fail\n");}
    
}

void DrawMenu(){
    
        puts("1- Attack on 1st turn");
        puts("2- EDIT CARD STATS");
        puts("3- Player Cards Ammount");
        puts("4- Enemy Cards Ammount");
        puts("5- Dispaly Cards");
        puts("6- Player HP");
        puts("7- Enemy HP");
        puts("8- Field Chooser");
    
}

int ReadCards(CARD cards[], LPVOID addr){
    for(int i = 0;i<5;i++){
        ReadProcessMemory(hProc, (Y_POS_1 + Y_POS_DIS * i), &cards[i], sizeof(cards[0]), 0); //Ler e armazenar
        
    }
    
    return 0;//Retorna bytes lidos
}

void PrintCards(CARD cards[]){
    
    for(int i = 0; i<5;i++)
        printf("POS-%d ID: %u ATK:%u DEF:%u\n",i+1,cards[i].id, cards[i].atk, cards[i].def);
    
    getchar();
   
}

void EditNumCards(BYTE victim){
    
    static BYTE cardsDrawn = 0;
    
    puts("Choose the cards:");
    scanf("%hhu",&cardsDrawn);
    
    if(cardsDrawn > 40)
        cardsDrawn = 40;

    cardsDrawn = 40 - cardsDrawn;//If the enemy has 5 cards then 45 have been drawn :P
    
    WriteMem( victim ? Y_ENEMY_CARDS : Y_PLAYER_CARDS, &cardsDrawn, sizeof(BYTE),1);
   
}

void EditHP(BYTE victim){
    
    static WORD HP = 0;
    
    puts("Choose the HP:");
    scanf("%hu",&HP);

    WriteMem( victim ? Y_ENEMY_LP : Y_PLAYER_LP, &HP, sizeof(WORD),1);
    WriteMem( victim ? Y_ENEMY_LP_VISUAL : Y_PLAYER_LP_VISUAL, &HP, sizeof(WORD),1);
}

void EditCard(CARD cards[]){
    
    DWORD pos = 0;
    printf("Choose card pos(1-5): ");
    scanf("%u", &pos);//Get pos
    if(pos > 5)//Bigger than boundaries
        pos = 5;
    
    
    //ReadCards()
    printf("Choose ATK: ");
    scanf("%u", &cards[pos-1].atk);
    printf("\nChoose DEF: ");
     scanf("%u", &cards[pos-1].def);
            
   
    WriteMem(Y_POS_1 + Y_POS_DIS * (pos-1), &cards[pos-1], sizeof(cards[0]),1);
            
    getchar();
  }

void WINAPI FieldChooser(){
    
    
    while(1)
    {
    if(Y_FIELD_CHOOSE == TRUE){
        WriteMem(Y_FIELD, &Y_CHOSEN_FIELD, sizeof(BYTE), NO_OUTPUT);
        
        
    }
    Sleep(234);
    }
}

void ChooseField(){
    
    if(Y_FIELD_CHOOSE){
        Y_FIELD_CHOOSE = FALSE;
        puts("Field Chooser disabled!");
        return;
    }
    puts("Field Chooser enabled!");
    puts("Available: 0-Normal 1-Forest 2-Wasteland 3-Mountain 4-Meadow 5-Sea 6-Dark");
    printf("Please choose  field: ");
    scanf("%hhu", &Y_CHOSEN_FIELD);
    
    Y_FIELD_CHOOSE = TRUE;
    getchar();
    
    
}
    
    

