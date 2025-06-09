// cat_soup_game_v2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// 매크로 정의
#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

// 전역 변수
int cat_pos = 5;
int prev_cat_pos = 5;
int soup_count = 0;
int relationship = 2;
int mood = 3;
int cp = 0;

// 함수 선언
void clear_screen();
void print_cat_ascii_art();
void print_intro(char* name);
void print_status();
void print_room();
int roll_dice();
void interaction(int choice, const char* name);
void move_cat(const char* name);
void action(const char* name);
void update_mood(const char* name);

// 화면을 지우는 함수
void clear_screen() {
    Sleep(1000);
    system("cls");
}

// 고양이 아스키 아트 출력
void print_cat_ascii_art() {
    printf(" /\\_/\\  \n");
    printf("( o.o )  야옹!\n");
    printf(" > ^ <  \n");
}

// 게임 인트로 출력
void print_intro(char* name) {
    printf("**** 야옹이와 수프 ****\n");
    print_cat_ascii_art();
    printf("야옹이의 이름을 지어 주세요: ");
    scanf_s("%s", name, 32);
    printf("야옹이의 이름은 %s입니다.\n", name);
    clear_screen();
}

// 현재 상태 출력
void print_status() {
    printf("================ 현재 상태 ================\n");
    printf("현재까지 만든 수프: %d개\n", soup_count);
    printf("CP: %d 포인트\n", cp);
    printf("기분(0~3): %d\n", mood);
    switch (mood) {
    case 0: printf("기분이 매우 나쁩니다.\n"); break;
    case 1: printf("심심해합니다.\n"); break;
    case 2: printf("식빵을 굽습니다.\n"); break;
    case 3: printf("골골송을 부릅니다.\n"); break;
    }
   
    printf("집사와의 관계(0~4): %d\n", relationship);
    switch (relationship) {
    case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
    case 1: printf("간식 자판기 취급입니다.\n"); break;
    case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
    case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
    case 4: printf("집사 껌딱지입니다.\n"); break;
    }
    printf("===========================================\n\n");
}

// 방 상태 출력
void print_room() {
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n");

    for (int i = 0; i < ROOM_WIDTH; i++) {
        if (i == HME_POS) printf("H");
        else if (i == BWL_POS) printf("B");
        else printf(" ");
    }
    printf("\n");

    for (int i = 0; i < ROOM_WIDTH; i++) {
        if (i == cat_pos) printf("C");
        else if (i == prev_cat_pos && prev_cat_pos != cat_pos) printf(".");
        else printf(" ");
    }
    printf("\n");

    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n\n");
}

// 주사위 굴리기
int roll_dice() {
    return rand() % 6 + 1; // 1~6
}

// 상호작용
void interaction(int choice, const char* name) {
    printf("주사위를 굴립니다. 또르륵...\n");
    Sleep(1000);
    int dice = roll_dice();
    printf("%d이(가) 나왔습니다!\n", dice);

    if (choice == 0) {
        printf("%s는 아무것도 하지 않습니다.\n", name);
        printf("4/6 확률로 친밀도가 떨어집니다.\n");

        if (dice <= 4 && relationship > 0) {
            relationship--;
            printf("친밀도가 떨어집니다.\n");
        }
        else {
            printf("다행히 친밀도가 떨어지지 않았습니다.\n");
        }
    }
    else if (choice == 1) {
        printf("%s의 턱을 긁어주었습니다.\n", name);
        printf("2/6 확률로 친밀도가 올라갑니다.\n");

        if (dice >= 5 && relationship < 4) {
            relationship++;
            printf("친밀도가 올라갑니다.\n");
        }
        else {
            printf("친밀도는 그대로입니다.\n");
        }
    }
    printf("현재 친밀도: %d\n", relationship);
}

// 이동
void move_cat(const char* name) {
    Sleep(500);
    printf("[%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.]\n", name);
    printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", (6 - relationship));

    Sleep(500);
    printf("주사위를 굴립니다. 또르륵...\n");
    Sleep(1000);
    int dice = roll_dice();
    printf("%d이(가) 나왔습니다!\n", dice);

    prev_cat_pos = cat_pos;
    int moved = 0;

    if (dice >= (6 - relationship)) {
        if (cat_pos < BWL_POS) {
            cat_pos++;
            moved = 1;
            printf("냄비 쪽으로 움직입니다.\n");
        }
    }
    else {
        if (cat_pos > HME_POS) {
            cat_pos--;
            moved = 1;
            printf("집 쪽으로 움직입니다.\n");
        }
    }

    if (!moved) {
        prev_cat_pos = cat_pos;
        printf("벽에 막혀서 움직이지 못했습니다.\n");
    }

    print_room();
}

// 행동
void action(const char* name) {
    if (cat_pos == BWL_POS) {
        printf("%s이(가) 수프를 만들고 있습니다!\n", name);
        const char* soups[] = { "감자 수프", "양송이 수프", "브로콜리 수프" };
        int idx = rand() % 3;
        printf("%s 1개를 만들었습니다!\n", soups[idx]);
        soup_count++;
        printf("현재까지 만든 수프: %d개\n", soup_count);
    }
    else if (cat_pos == HME_POS) {
        printf("%s은(는) 집에서 편안하게 쉬고 있습니다.\n", name);
    }
}
void update_mood(const char* name) {
    printf("아무 이유 없이 기분이 나빠집니다. 고양이니까?\n");

    int dice = roll_dice();
    printf("주사위를 굴립니다. 또르륵...\n");
    Sleep(1000);
    printf("%d이(가) 나왔습니다.\n", dice);

    if (dice <= (6 - relationship)) {
        if (mood > 0) {
            printf("%s의 기분이 나빠집니다: %d -> %d\n", name, mood, mood - 1);
            mood--;
        }
        else {
            printf("%s의 기분은 이미 최저입니다.\n", name);
        }
    }
    else {
        printf("다행히 기분이 그대로입니다.\n");
    }
}

// 메인 함수
int main() {
    char name[32];
    srand((unsigned int)time(NULL));

    print_intro(name);

    while (1) {
        print_status();
        update_mood(name);
        print_room();

        int choice;
        while (1) {
            printf("어떤 상호작용을 하시겠습니까?\n");
            printf("0. 아무것도 하지 않음\n1. 긁어주기\n>> ");
            scanf_s("%d", &choice);

            if (choice == 0 || choice == 1) {
                break;
            }
            printf("잘못된 입력입니다. 다시 입력해 주세요.\n");
        }

        interaction(choice, name);

        Sleep(500);
        move_cat(name);

        Sleep(500);
        action(name);

        Sleep(2500);
        system("cls");
    }

    return 0;
}
