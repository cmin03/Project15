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
int at_home_last_turn = 0;
int has_mouse = 0;
int has_laser = 0;
int has_scratch = 0;
int has_tower = 0;
int scratch_pos = -1;
int tower_pos = -1;

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
void move_cat_by_mood(const char* name);
void shop();
void place_furniture();


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
        printf("%s�� �ƹ��͵� ���� �ʾƿ�.\n", name);
        if (mood > 0) {
            mood--;
            printf("����� ���������: %d -> %d\n", mood + 1, mood);
        }
        if (dice <= 5 && relationship > 0) {
            relationship--;
            printf("������� ���谡 ���������.\n");
        }
    }
    else if (choice == 1) {
        printf("%s�� ���� �ܾ�����.\n", name);
        if (dice >= 5 && relationship < 4) {
            relationship++;
            printf("ģ�е��� �ö󰬾��!\n");
        }
        else {
            printf("�� ���� ���׿�.\n");
        }
    }
    else if (choice == 2) {
        printf("�峭�� ��� %s�� �������.\n", name);
        if (mood < 3) {
            mood++;
            printf("����� ���������! ���� ���: %d\n", mood);
        }
        if (dice >= 4 && relationship < 4) {
            relationship++;
            printf("ģ�е��� ��¦ �ö󰬾��!\n");
        }
    }
    else if (choice == 3) {
        printf("������ �����ͷ� %s�� �ų��� ��Ҿ��!\n", name);
        mood += 2;
        if (mood > 3) mood = 3;
        printf("����� Ȯ ���������! ���� ���: %d\n", mood);
        if (dice >= 2 && relationship < 4) {
            relationship++;
            printf("ģ�е��� �ö�!\n");
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
        printf("%s��(��) ������ ����� �־��!\n", name);
        const char* soups[] = { "���� ����", "����� ����", "����ݸ� ����" };
        int idx = rand() % 3;
        printf("%s 1���� ��������ϴ�!\n", soups[idx]);
        soup_count++;
        printf("���ݱ��� ���� ����: %d��\n", soup_count);
        at_home_last_turn = 0; 
    }

    
    else if (cat_pos == HME_POS) {
        printf("%s��(��) ������ ���� �־��.\n", name);
        if (at_home_last_turn == 1) {
            if (mood < 3) {
                mood = mood + 1;
                printf("����� ���� ���������! ���� ���: %d\n", mood);
            }
            else {
                printf("����� �̹� �ְ���!\n");
            }
        }
        else {
            printf("�̹� �Ͽ� ������ �ؼ� ���� �ʾҾ��.\n");
        }
        at_home_last_turn = 1;
    }

    
    else {
        printf("%s��(��) �ƹ� �ൿ�� ���� �ʾƿ�.\n", name);
        at_home_last_turn = 0;
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
            printf("0. �ƹ��͵� ���� ����\n");
            printf("1. �ܾ��ֱ�\n");
            if (has_mouse) printf("2. �峭�� ��� ����ֱ�\n");
            if (has_laser) printf("3. ������ �����ͷ� ����ֱ�\n");
            printf(">> ");
            scanf_s("%d", &choice);

            
            if (choice == 0 || choice == 1 ||
                (choice == 2 && has_mouse) ||
                (choice == 3 && has_laser)) {
                break;
            }
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n");
        }


        interaction(choice, name);

        Sleep(500);
        move_cat_by_mood(name);

        Sleep(500);
        action(name);
        
        int ������� = 0;

        if (mood > 1) {
            ������� = mood - 1;
        }
        else {
            ������� = 0;
        }

        int �̹�cp = ������� + relationship;

        printf("��� ������ %d�̰�, ģ�е��� %d�̹Ƿ�,\n", �������, relationship);
        printf("�̹� �Ͽ� ���� CP�� %d ����Ʈ�Դϴ�.\n", �̹�cp);

        

        printf("�� ���� CP: %d ����Ʈ\n", cp);
        shop(); 



        Sleep(2500);
        system("cls");
    }

    return 0;
}
void move_cat_by_mood(const char* name) {
    Sleep(500);
    prev_cat_pos = cat_pos;

    if (mood == 0) {
        printf("����� ������ %s��(��) ������ ���ϴ�...\n", name);
        if (cat_pos > 1) {
            cat_pos = cat_pos - 1;
        }
    }
    else if (mood == 1) {
        printf("%s��(��) �� �ɽ��Ѱ�����...\n", name);
        printf("�ٵ� ���̱ⱸ�� �����Ф� �׷��� �� ��� ������\n");

        if (mood > 0) {
            mood = mood - 1;
            printf("����� ������: %d -> %d\n", mood + 1, mood);
        }
    }
    else if (mood == 2) {
        printf("%s��(��) ���� �Ļ� ���� ���̿���. ������ �־��.\n", name);
    }
    else if (mood == 3) {
        printf("%s��(��) ���� �θ��鼭 ���� ���鷯 ���� ���̿���\n", name);
        if (cat_pos < ROOM_WIDTH - 2) {
            cat_pos = cat_pos + 1;
        }
    }

    if (cat_pos == prev_cat_pos) {
        printf("�� ���������. ������ �ִ� ��.\n");
    }

    print_room();
}
void shop() {
    printf("\n������ �Ծ��! �� ��ðھ��?\n");
    printf("0. �� ��\n");
    printf("1. �峭�� ��: 1 CP");
    if (has_mouse) printf(" (ǰ��)");
    printf("\n");

    printf("2. ������ ������: 2 CP");
    if (has_laser) printf(" (ǰ��)");
    printf("\n");

    printf("3. ��ũ��ó: 4 CP");
    if (has_scratch) printf(" (ǰ��)");
    printf("\n");

    printf("4. ĹŸ��: 6 CP");
    if (has_tower) printf(" (ǰ��)");
    printf("\n");

    int buy;
    printf(">> ");
    scanf_s("%d", &buy);

    if (buy == 0) {
        printf("�ƹ� �͵� �� ����.\n");
        return;
    }

    if (buy == 1) {
        if (has_mouse) {
            printf("�̹� �峭�� �� ����.\n");
        }
        else if (cp < 1) {
            printf("CP�� �����ؿ�.\n");
        }
        else {
            has_mouse = 1;
            cp -= 1;
            printf("�峭�� �� ����! ���� CP: %d\n", cp);
        }
    }
    else if (buy == 2) {
        if (has_laser) {
            printf("�̹� ������ ������ ����.\n");
        }
        else if (cp < 2) {
            printf("CP�� �����ؿ�.\n");
        }
        else {
            has_laser = 1;
            cp -= 2;
            printf("������ ������ ����! ���� CP: %d\n", cp);
        }
    }
    else if (buy == 3) {
        if (has_scratch) {
            printf("�̹� ��ũ��ó ����.\n");
        }
        else if (cp < 4) {
            printf("CP�� �����ؿ�.\n");
        }
        else {
            has_scratch = 1;
            cp -= 4;
            printf("��ũ��ó ����! ���� CP: %d\n", cp);
        }
    }
    else if (buy == 4) {
        if (has_tower) {
            printf("�̹� ĹŸ�� ����.\n");
        }
        else if (cp < 6) {
            printf("CP�� �����ؿ�.\n");
        }
        else {
            has_tower = 1;
            cp -= 6;
            printf("ĹŸ�� ����! ���� CP: %d\n", cp);
        }
    }
    else {
        printf("�߸��� �Է��̿���.\n");
    }
}
void place_furniture() {
    
    if (has_scratch && scratch_pos == -1) {
        int pos;
        while (1) {
            pos = rand() % ROOM_WIDTH;
            if (pos != HME_POS && pos != BWL_POS && pos != tower_pos) break;
        }
        scratch_pos = pos;
    }

    
    if (has_tower && tower_pos == -1) {
        int pos;
        while (1) {
            pos = rand() % ROOM_WIDTH;
            if (pos != HME_POS && pos != BWL_POS && pos != scratch_pos) break;
        }
        tower_pos = pos;
    }
}



