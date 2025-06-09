// cat_soup_game_v2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// ��ũ�� ����
#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

// ���� ����
int cat_pos = 5;
int prev_cat_pos = 5;
int soup_count = 0;
int relationship = 2;
int mood = 3;
int cp = 0;

// �Լ� ����
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

// ȭ���� ����� �Լ�
void clear_screen() {
    Sleep(1000);
    system("cls");
}

// ����� �ƽ�Ű ��Ʈ ���
void print_cat_ascii_art() {
    printf(" /\\_/\\  \n");
    printf("( o.o )  �߿�!\n");
    printf(" > ^ <  \n");
}

// ���� ��Ʈ�� ���
void print_intro(char* name) {
    printf("**** �߿��̿� ���� ****\n");
    print_cat_ascii_art();
    printf("�߿����� �̸��� ���� �ּ���: ");
    scanf_s("%s", name, 32);
    printf("�߿����� �̸��� %s�Դϴ�.\n", name);
    clear_screen();
}

// ���� ���� ���
void print_status() {
    printf("================ ���� ���� ================\n");
    printf("������� ���� ����: %d��\n", soup_count);
    printf("CP: %d ����Ʈ\n", cp);
    printf("���(0~3): %d\n", mood);
    switch (mood) {
    case 0: printf("����� �ſ� ���޴ϴ�.\n"); break;
    case 1: printf("�ɽ����մϴ�.\n"); break;
    case 2: printf("�Ļ��� �����ϴ�.\n"); break;
    case 3: printf("������ �θ��ϴ�.\n"); break;
    }
   
    printf("������� ����(0~4): %d\n", relationship);
    switch (relationship) {
    case 0: printf("�翡 ���� ������ �Ⱦ��մϴ�.\n"); break;
    case 1: printf("���� ���Ǳ� ����Դϴ�.\n"); break;
    case 2: printf("�׷����� �� ���� �����Դϴ�.\n"); break;
    case 3: printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n"); break;
    case 4: printf("���� �������Դϴ�.\n"); break;
    }
    printf("===========================================\n\n");
}

// �� ���� ���
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

// �ֻ��� ������
int roll_dice() {
    return rand() % 6 + 1; // 1~6
}

// ��ȣ�ۿ�
void interaction(int choice, const char* name) {
    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
    Sleep(1000);
    int dice = roll_dice();
    printf("%d��(��) ���Խ��ϴ�!\n", dice);

    if (choice == 0) {
        printf("%s�� �ƹ��͵� ���� �ʽ��ϴ�.\n", name);
        printf("4/6 Ȯ���� ģ�е��� �������ϴ�.\n");

        if (dice <= 4 && relationship > 0) {
            relationship--;
            printf("ģ�е��� �������ϴ�.\n");
        }
        else {
            printf("������ ģ�е��� �������� �ʾҽ��ϴ�.\n");
        }
    }
    else if (choice == 1) {
        printf("%s�� ���� �ܾ��־����ϴ�.\n", name);
        printf("2/6 Ȯ���� ģ�е��� �ö󰩴ϴ�.\n");

        if (dice >= 5 && relationship < 4) {
            relationship++;
            printf("ģ�е��� �ö󰩴ϴ�.\n");
        }
        else {
            printf("ģ�е��� �״���Դϴ�.\n");
        }
    }
    printf("���� ģ�е�: %d\n", relationship);
}

// �̵�
void move_cat(const char* name) {
    Sleep(500);
    printf("[%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.]\n", name);
    printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", (6 - relationship));

    Sleep(500);
    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
    Sleep(1000);
    int dice = roll_dice();
    printf("%d��(��) ���Խ��ϴ�!\n", dice);

    prev_cat_pos = cat_pos;
    int moved = 0;

    if (dice >= (6 - relationship)) {
        if (cat_pos < BWL_POS) {
            cat_pos++;
            moved = 1;
            printf("���� ������ �����Դϴ�.\n");
        }
    }
    else {
        if (cat_pos > HME_POS) {
            cat_pos--;
            moved = 1;
            printf("�� ������ �����Դϴ�.\n");
        }
    }

    if (!moved) {
        prev_cat_pos = cat_pos;
        printf("���� ������ �������� ���߽��ϴ�.\n");
    }

    print_room();
}

// �ൿ
void action(const char* name) {
    if (cat_pos == BWL_POS) {
        printf("%s��(��) ������ ����� �ֽ��ϴ�!\n", name);
        const char* soups[] = { "���� ����", "����� ����", "����ݸ� ����" };
        int idx = rand() % 3;
        printf("%s 1���� ��������ϴ�!\n", soups[idx]);
        soup_count++;
        printf("������� ���� ����: %d��\n", soup_count);
    }
    else if (cat_pos == HME_POS) {
        printf("%s��(��) ������ ����ϰ� ���� �ֽ��ϴ�.\n", name);
    }
}
void update_mood(const char* name) {
    printf("�ƹ� ���� ���� ����� �������ϴ�. ����̴ϱ�?\n");

    int dice = roll_dice();
    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
    Sleep(1000);
    printf("%d��(��) ���Խ��ϴ�.\n", dice);

    if (dice <= (6 - relationship)) {
        if (mood > 0) {
            printf("%s�� ����� �������ϴ�: %d -> %d\n", name, mood, mood - 1);
            mood--;
        }
        else {
            printf("%s�� ����� �̹� �����Դϴ�.\n", name);
        }
    }
    else {
        printf("������ ����� �״���Դϴ�.\n");
    }
}

// ���� �Լ�
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
            printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
            printf("0. �ƹ��͵� ���� ����\n1. �ܾ��ֱ�\n>> ");
            scanf_s("%d", &choice);

            if (choice == 0 || choice == 1) {
                break;
            }
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n");
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
