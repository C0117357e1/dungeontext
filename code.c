#include <stdio.h>
#include  <stdlib.h>
#include<time.h>
#include <windows.h>


typedef struct {
	int room;//����
	int floor;//�K�w
}dungeons;
dungeons dungeon = { 1,1 };

typedef struct {
	int hp;//���݂̗̑�
	int mhp;//�ő�̗�
	int atk;//�U����
	int def;//�h���
	int luck;//�^
	int shield;//���������Ă���H
	int sword;//���������Ă���H
	int upatk;//�㏸�����U����
	int potion;//�|�[�V�����������Ă���H
	int scroll;//�X�N���[���������Ă���?
	int key;//���������Ă���H
	
}name;
name pstatus = { 30,30,3,0,0,0,0,0,0};

typedef struct {
	char name[30];//�G�̖��O
	int ehp;//�G�̗̑�
	int eatk;//�G�̍U����
	int eatkd;//�G�̍U���́@�_�C�X�̕�
	int edrop;//����̃h���b�v��
	int esword;//�G�̕���	
}estatuss;
estatuss estatus[5] = { { "�X���C��",10,1,6,3,0 },{ "�X�P���g���i�C�g",20,3,6,6,0 },{ "���U�[�h�}��",30,5,8,9,0 },{ "�~�m�^�E���XG",90,7,10,0,0 },{ "���^���b�N�X���C��",10,0,3,15,0 } }; //f �� F  �@

int event5flag = 0;
int bossflag = 0;
int countflag = 17;
int luckymonsterflag = 0;
int roomcount = 0;
char havetxt[2][10] = {"�Ȃ�","����"};

void event();
void battle();
void rule();

int main() {

	dungeon.room = 1;
	dungeon.floor = 1;


	int playstate = 1;					//�����ƗV�т܂�
	char playstatechoice[100];			 //�Ō�Ɂ@�u������񂠂��т܂����v�@���߂̕ϐ�

	while (playstate == 1) {
		while (1) {
			printf("Cursed Brave�`���ꂽ�E�ҁ`\n");
			printf(" 1 ���߂���\n 2 ���[������\n 3 �Q�[���I��\n>");
			char tmp[100] = { 0 };
			gets(tmp);
			if (strlen(tmp) > 1) {
				printf("1~3����͂��Ă�������\n");
			}
			else if (tmp[0] == '1') {
				system("cls");
				break;
			}
			else if (tmp[0] == '2') {
				system("cls");
				rule();

			}
			else if (tmp[0] == '3') {
				return 0;
			}
		}

		int flag = 1;
		while (pstatus.hp > 0) {
			if (flag == 0) {
				printf("\n\n\nENTER�L�[����͂��Ă�������\n>");
				char str[100] = { 0 };
				gets(str);
				system("cls");	
			}
			flag = 0;
			srand(time(NULL));
			int door1 = 1 + rand() % 6;
			int door2 = 1 + rand() % 6;
			int door3 = 1 + rand() % 6;

			if (event5flag == 1) {  //�@���̔��̐�̏�����ɓ��ꂽ�@�@EVENT�@���s

				door1 = 1;
				door2 = 4;
				door3 = 6;
				event5flag = 0;
			}


			char Door1[10];
			char Door2[10];
			char Door3[10];

			switch (door1)
			{
			case 1:
				strcpy_s(Door1, 10, "EVENT");
				break;
			case 2:
				strcpy_s(Door1, 10, "EVENT");
				break;
			case 3:
				strcpy_s(Door1, 10, "EVENT");
				break;
			case 4:
				strcpy_s(Door1, 10, "BATTLE");
				break;
			case 5:
				strcpy_s(Door1, 10, "BATTLE");
				break;
			case 6:
				strcpy_s(Door1, 10, "REST");
				break;
			default:
				break;

			}

			switch (door2)
			{
			case 1:
				strcpy_s(Door2, 10, "EVENT");
				break;
			case 2:
				strcpy_s(Door2, 10, "EVENT");
				break;
			case 3:
				strcpy_s(Door2, 10, "EVENT");
				break;
			case 4:
				strcpy_s(Door2, 10, "BATTLE");
				break;
			case 5:
				strcpy_s(Door2, 10, "BATTLE");
				break;
			case 6:
				strcpy_s(Door2, 10, "REST");
				break;
			default:
				break;

			}

			switch (door3)
			{
			case 1:
				strcpy_s(Door3, 10, "EVENT");
				break;
			case 2:
				strcpy_s(Door3, 10, "EVENT");
				break;
			case 3:
				strcpy_s(Door3, 10, "EVENT");
				break;
			case 4:
				strcpy_s(Door3, 10, "BATTLE");
				break;
			case 5:
				strcpy_s(Door3, 10, "BATTLE");
				break;
			case 6:
				strcpy_s(Door3, 10, "REST");
				break;
			default:
				break;

			}


			

			int correctdoorselection = 0;   //�I���͐��������ǂ���
			int selecteddoor = 0;				//�I�΂ꂽ�h�A
			char str[100];
			while (correctdoorselection == 0)
			{
				

			

				printf("HP: %d\t/%d \t�u�@��:%s - ��:%s - ��:%s �v  \n����: %d   �K�w: %d �c��̕�����: %d\n ���� 1= %s\t\t���� 2= %s\t\t ���� 3= %s\n\n������I�����ĉ�����(1�`3):\n", pstatus.hp, pstatus.mhp, havetxt[pstatus.sword],havetxt[pstatus.shield], havetxt[pstatus.key], dungeon.room, dungeon.floor, countflag, Door1, Door2, Door3);
				printf("___________________\n"
					"|�I�v�V�������j���[|\n"
					"|�C�x���g�m�F:e    |\n"
					"|���[���m�F:r      |\n"
					"|�X�e�[�^�X�m�F:s  |\n"
					"|�Q�[���I��:q      |\n"
					"|__________________|\n>"
				);
				roomcount++;
				gets(str);

				if (strlen(str) > 1)
				{
					printf("\n�������l����͂��Ă�������\n\n");
				}
				else if (isdigit(str[0]))
				{
					if (str[0] == '1') {
						selecteddoor = door1;
						correctdoorselection = 1;
					}
					else if (str[0] == '2') {
						selecteddoor = door2;
						correctdoorselection = 1;
					}
					else if (str[0] == '3') {
						selecteddoor = door3;
						correctdoorselection = 1;
					}

					else printf("\n�������l����͂��Ă�������\n\n");
				}
				else {
					if (str[0] == 'e')
					{
						system("cls");
						printf("\n-------------------EVENT LIST----------------------\n\n"
							"1  ���͂̐�𔭌�����\n"
							"2  �V�N�ȐH���𔭌�����\n"
							"3  ������ɓ���\n"
							"4  ������ɓ���\n"
							"5  �ŏ��ɗ����Ă��܂�\n"
							"6  �g���b�v�Ɉ���������\n"
							"7  �{�X������𔭌����Ă��܂�\n"
							"8  ���b�L�[�����X�^�[�o��\n"
							"9  �G���������Ȏ���������\n"
							"10 �������������\n"
							"11 ���̐�̏�񂪎�ɓ���\n"
							"12 �Ñ�̃X�N���[���𔭌�����!\n"
							"13 �����ɏP���Ă��܂�\n\n"
						);

						printf("\nENTER�������Ă������� \n");
						char str[100] = { 0 };

						gets(str);
						system("cls");
					}
					else if (str[0] == 'r') {
						system("cls");

						rule();

					}

					else if (str[0] == 's' || str[0] == 'S') {
						int atkmin = pstatus.atk + pstatus.upatk;
						int atkmax = pstatus.atk + 5 + pstatus.upatk;

						int eatkmin0 = estatus[0].eatk;
						int eatkmax0 = estatus[0].eatk + estatus[0].eatkd - 1;

						int eatkmin1 = estatus[1].eatk;
						int eatkmax1 = estatus[1].eatk + estatus[1].eatkd - 1;

						int eatkmin2 = estatus[2].eatk;
						int eatkmax2 = estatus[2].eatk + estatus[2].eatkd - 1;

						int eatkmin3 = estatus[3].eatk;
						int eatkmax3 = estatus[3].eatk + estatus[3].eatkd - 1;

						int eatkmin4 = estatus[4].eatk;
						int eatkmax4 = estatus[4].eatk + estatus[4].eatkd - 1;
						
						system("cls");

						printf("\n\n\n-------------------GAME STATUS----------------------\n\n");
						printf("\nPLAYER\n\n����HP:     %d\t\t/�ő�HP:    %d\t��: %s\t��: %s\n�|�[�V����: %d��\t\t�X�N���[��: %d��\n�U����:     %d�`%d\t�h���b�v��: %d\t��: %s\n\n", pstatus.hp, pstatus.mhp,havetxt[pstatus.sword], havetxt[pstatus.shield], pstatus.potion, pstatus.scroll, atkmin, atkmax, pstatus.luck, havetxt[pstatus.key]);
						printf("\n\n%s\nHP:%d\t\t/�U����:%d�`%d\t�h���b�v��:%d UP\n", estatus[0].name, estatus[0].ehp, eatkmin0, eatkmax0, estatus[0].edrop);
						printf("%s\nHP:%d\t\t/�U����:%d�`%d\t�h���b�v��:%d UP\n", estatus[1].name, estatus[1].ehp, eatkmin1, eatkmax1, estatus[1].edrop);
						printf("%s\nHP:%d\t\t/�U����:%d�`%d\t�h���b�v��:%d UP\n", estatus[2].name, estatus[2].ehp, eatkmin2, eatkmax2, estatus[2].edrop);
						printf("%s\nHP:%d\t\t/�U����:%d�`%d\t�h���b�v��:%d UP\n", estatus[4].name, estatus[4].ehp, eatkmin4, eatkmax4, estatus[4].edrop);
						printf("%s\nHP:%d\t\t/�U����:%d�`%d\t�h���b�v��:%d UP\t��: %s\n\n\n\n\n\n", estatus[3].name, estatus[3].ehp, eatkmin3, eatkmax3, estatus[3].edrop, havetxt[estatus[3].esword]);

						printf("\nENTER�������Ă������� \n");
						char str[100] = { 0 };

						gets(str);
						system("cls");
					}

					else if (str[0] == 'q')

					{



						int selectplaycorrectn = 0;
						while (selectplaycorrectn == 0)
						{
							printf("�Q�[���I�����܂����H y(YES) or n(NO) :  ");

							gets(playstatechoice);

							if (strlen(playstatechoice) > 1)
							{
								printf("\nINVALID INPUT, Please put y(YES) or n(NO) \n\n");
							}

							else
							{
								if (playstatechoice[0] == 'y')
								{
									pstatus.hp = -10;
									correctdoorselection = 1;

									break;

								}
								else if (playstatechoice[0] == 'n')
								{
									printf("\n\n\n");
									system("cls");
									break;
								}
								else
									printf("\nINVALID INPUT, Please put y(YES) or n(NO) \n\n");
							}

						}
						selectplaycorrectn = 0;



					}
				
					else printf("\nINVALID INPUT, Please put a number from 1 to 3\n\n");
				}
			}
			correctdoorselection = 0;


			switch (selecteddoor) {
			case 1:
				printf("\nSelected event\n\n");
				event();
				break;
			case 2:
				printf("\nSelected event\n\n");
				event();
				break;
			case 3:
				printf("\nSelected event\n\n");
				event();
				break;
			case 4:
				printf("\nSelected battle\n\n");
				battle();
				break;
			case 5:
				printf("\nSelected battle\n\n");
				battle();
				break;
			case 6:
				printf("\nSelected healing room\n");
				pstatus.hp = restroom(pstatus.mhp, pstatus.hp);
				break;
			default:
				break;
			}



			dungeon.room += 1;
			countflag--;


			if (dungeon.floor == 1 && dungeon.room == 18) {
				dungeon.floor = 2;
				dungeon.room = 1;
				countflag = 13;
			}
			else if (dungeon.floor == 2 && dungeon.room == 14) {
				dungeon.floor = 3;
				dungeon.room = 1;
				countflag = 9;
			}
			else if (dungeon.floor == 3 && dungeon.room == 10) {
				dungeon.floor = 4;
				dungeon.room = 1;
				pstatus.hp = pstatus.mhp;

				printf("\n\n\n\n\n\n\nHP���S�񕜂���\n\n\n\n\n\n\n\n"); Sleep(2000);
				printf("------------BOSS�����ꂽ!!!!!!!!!!!!------------------\n"); Sleep(1000);
				luckymonsterflag = 0;
				bossflag = 1;
				battle();
				break;
			}






		}



		int selectplaycorrect = 0;
		while (selectplaycorrect == 0)
		{
			printf("������x��蒼��? y(YES) or n(NO) :  ");

			gets(playstatechoice);

			if (strlen(playstatechoice) > 1)
			{
				printf("\nINVALID INPUT, Please put y(YES) or n(NO) \n\n");
			}

			else
			{
				if (playstatechoice[0] == 'y')
				{
					dungeon.floor = 1;  //dungeon������
					dungeon.room = 1;

					pstatus.hp = 30;   //player������
					pstatus.mhp = 30;
					pstatus.atk = 3;
					pstatus.upatk = 0;
					pstatus.def = 0;
					pstatus.luck = 0;
					pstatus.potion = 0;
					pstatus.key = 0;
					pstatus.sword = 0;
					pstatus.shield = 0;


					estatus[0].eatk = 1; //�G������
					estatus[0].eatkd = 6;
					estatus[1].eatk = 3;
					estatus[1].eatkd = 6;
					estatus[2].eatk = 5;
					estatus[2].eatkd = 8;
					estatus[3].eatk = 5;
					estatus[3].eatkd = 10;
					printf("\n\n\n");
					selectplaycorrect = 1;
					bossflag = 0;
					system("cls");
				}
				else if (playstatechoice[0] == 'n')
				{
					return 0;
				}
				else
					printf("\nINVALID INPUT, Please put y(YES) or n(NO) \n\n");
			}

		}
		selectplaycorrect = 0;

	}


}




int restroom(int maxhp, int hp)

{
	hp = maxhp;
	printf("HP���S�񕜂���\n\n\n");

	return hp;

}


void event() {/

	srand(time(NULL));
	Sleep(500);
	switch (rand() % 13 + 1) {
	case 1:
		printf("���͂̐�𔭌������I�ő�HP��10�㏸����\n\n\n");
		pstatus.hp = pstatus.hp + 10;
		pstatus.mhp = pstatus.mhp + 10;
		break;

	case 2:
		printf("�V�N�ȐH������茳�C�ɂȂ����I�ő�HP��10�㏸����\n\n\n");
		pstatus.hp = pstatus.hp + 10;
		pstatus.mhp = pstatus.mhp + 10;
		break;

	case 3:
		if (pstatus.key == 0) {
			printf("������ɓ������I�󔠂�������ΊJ����ꂻ�����I\n\n\n");
			pstatus.key = 1;
		}
		else if (pstatus.key == 1 && pstatus.shield == 1) {
			if (pstatus.potion == 2) {
				printf("�|�[�V�����𔭌������B���������������ς��ł���ȏ㎝�ĂȂ��B\n\n\n");

			}
			else {
				printf("�󔠂���|�[�V��������ɓ������I�g���ƍő�HP��75���̒l���񕜂ł���\n\n\n");
				pstatus.potion++;
				pstatus.key = 0;
			}

		}
		else {
			printf("�󔠂��珂����ɓ������I�G����󂯂�_���[�W�����炷���Ƃ��ł���\n\n\n");
			pstatus.shield = 1;
			estatus[0].eatk -= 1;
			estatus[1].eatk -= 2;
			estatus[2].eatk -= 2;
			estatus[3].eatk -= 2;
			pstatus.key = 0;
		}
		break;


	case 4:
		if (pstatus.key == 0) {
			printf("������ɓ������I�󔠂�������ΊJ����ꂻ�����I\n\n\n");
			pstatus.key = 1;
		}
		else if (pstatus.key == 1 && pstatus.shield == 1) {
			if (pstatus.potion == 2) {
				printf("�|�[�V�����𔭌������B���������������ς��ł���ȏ㎝�ĂȂ��B\n\n\n");

			}
			else {
				printf("�󔠂���|�[�V��������ɓ������I�g���ƍő�HP��75���̒l���񕜂ł���\n\n\n");
				pstatus.potion++;
				pstatus.key = 0;
			}

		}
		else {
			printf("�󔠂��珂����ɓ������I�G����󂯂�_���[�W�����炷���Ƃ��ł���\n\n\n");
			pstatus.shield = 1;
			estatus[0].eatk -= 1;
			estatus[1].eatk -= 2;
			estatus[2].eatk -= 2;
			estatus[3].eatk -= 2;
			pstatus.key = 0;
		}
		break;

	case 5:
		printf("�ŏ��ɂ͂܂��Ă��܂����I�ő�HP��5���������I\n\n\n");
		pstatus.hp = pstatus.hp - 5;
		pstatus.mhp = pstatus.mhp - 5;

		break;

	case 6:
		printf("�g���b�v�Ɉ������������IHP��10���������I\n\n\n");
		pstatus.hp = pstatus.hp - 10;
		break;

	case 7:
		if (estatus[3].esword == 0) {
			printf("�{�X������𔭌����Ă��܂����I\n\n\n"); 
			estatus[3].esword = 1;
			estatus[3].eatk += 3;
		}
		else {
			printf("�{�X������𗎂Ƃ��ĂȂ������I\n\n\n"); 
			estatus[3].esword = 0;
			estatus[3].eatk -= 3;

		}
		break;

	case 8:
		printf("�A�C�e������肵�₷�����^���b�N�X���C�����������I\n\n\n");
		luckymonsterflag = 1;
		break;

	case 9:
		printf("�G���������Ȏ������J�n�����c\n"); Sleep(2000);
		srand(time(NULL));
		switch (rand() % 3 + 1) {
		case 1:
			printf("�������������A�G�̍U���͂��㏸���Ă��܂����I\n\n\n");
			estatus[0].eatkd += 1;
			estatus[1].eatkd += 1;
			estatus[2].eatkd += 1;
			estatus[3].eatkd += 1;
			break;
		case 2:
			printf("���������s���A�G�̍U���͂����������I\n\n\n");
			estatus[0].eatkd -= 1;
			estatus[1].eatkd -= 1;
			estatus[2].eatkd -= 1;
			estatus[3].eatkd -= 1;
			break;
		case 3:
			printf("�����������N����Ȃ�����...\n");
			break;
		}
		break;
	case 10:
		while (1) {
			printf("�ЁX�����F�̖�𔭌�����......\n");
			printf("���݂܂����H Yes(y) or No(n)\n>");
			char str[100] = { 0 };
			gets(str);
			if (strlen(str) > 1) {
				printf("y��n����͂��Ă�������\n"); Sleep(500);
				system("cls");
			}
			else if (str[0] == 'y') {

				srand(time(NULL));
				switch (rand() % 3 + 1) {
				case 1:
					pstatus.upatk += 1;
					printf("�̂ɗ͂��݂Ȃ���!�A�E�҂̍U���͂��㏸�����I\n\n\n");
					break;
				case 2:
					pstatus.mhp = pstatus.mhp - 3;
					pstatus.hp = pstatus.hp - 3;
					printf("�̂��Ă���悤�ɒɂ��A�E�҂̍ő�HP��3�����I\n");
					break;

				case 3:
					printf("�����������N����Ȃ�����\n");
					break;
				}
				break;
			}
			else if (str[0] == 'n') {
				printf("������Ɏ̂Ă�...\n");
				break;
			}
			else {
				printf("y��n����͂��Ă�������\n"); Sleep(500);
				system("cls");
			}
		}
		break;
	case 11:
		printf("���̔��̐�����������A�����̒��g��I�ׂ�悤�ɂȂ����I\n\n\n");
		event5flag = 1;
		break;

	case 12:
		printf("�Â̏������������I\n"); Sleep(500);
		if (pstatus.scroll == 2) {
			printf("�X�N���[���𔭌������B���������������ς��ł���ȏ㎝�ĂȂ��B\n\n\n");

		}
		else {
			pstatus.scroll++;
			printf("�X�N���[������ɓ��ꂽ�I�g���Ƌ��͂ȍU�����J��o����\n\n\n");
		}

		break;

	case 13:
		printf("�����ɐQ���݂��P��ꂻ�����I\n");
		srand(time(NULL));
		Sleep(500);
		switch (rand() % 4 + 1) {

		case 1:
			if (pstatus.scroll > 0) {
				printf("�X�N���[���𓐂܂�Ă��܂����I\n\n\n");
				pstatus.scroll--;
			}
			else {
				printf("�����̐ڋ߂ɋC���t�����ނ����I\n");
			}
			break;
		case 2:
			if (pstatus.potion > 0) {
				printf("�|�[�V�����𓐂܂�Ă��܂����P\n\n\n");
				pstatus.potion--;
			}
			else {
				printf("�����̐ڋ߂ɋC���t�����ނ����I\n");
			}
			break;
		case 3:
			if (pstatus.key > 0) {
				printf("���𓐂܂�Ă��܂����I\n\n\n");
				pstatus.key = 0;
			}
			else {
				printf("�����̐ڋ߂ɋC���t�����ނ����I\n");
			}
			break;
		case 4:
			printf("���߂镨�������Ă��Ȃ��������Ƃɕ��𗧂ďP��ꂽ�I�@HP��5��������\n\n\n");
			pstatus.hp = pstatus.hp - 5;
			break;
		}
		break;


	}
	if (pstatus.hp <= 0) {
		Sleep(500);
		printf("�E�҂̔s�k�E�E�E\n\n\n"); //�B
	}

	Sleep(500);
}

void battle() { //�퓬
	int level;

	if (luckymonsterflag == 0) {
		level = dungeon.floor - 1;
	}
	else {
		level = 4;
		luckymonsterflag = 0;
	}
	int ehp = estatus[level].ehp;
	int emhp = estatus[level].ehp;
	int hp = pstatus.hp;
	int mhp = pstatus.mhp;
	int potion = mhp * 3 / 4;
	char str[50];
	if (level == 3) {
		printf("���{��BOSS�����ꂽ!!"); Sleep(1000);
	}
	else {
		printf("�G�Ƒ�������!\n"); Sleep(1000);
	}


	while (hp > 0 && ehp > 0) {
		system("cls");
		printf("�E�҂�HP��%d/%d\n", hp, mhp); Sleep(500);
		printf("%s��HP��%d/%d\n", estatus[level].name, ehp, emhp); Sleep(500);
		printf(" �U��:1 or �A�C�e��:2\n>"); Sleep(500);
		char str[10] = { 0 };
		gets(str);
		printf("-------------------------\n");
		srand(time(NULL));
		int atk = pstatus.atk + (rand() % (6 + pstatus.upatk));
		int eatk = estatus[level].eatk + (rand() % estatus[level].eatkd);
		if (strlen(str) > 1) {
			printf("1��2����͂��Ă�������\n"); Sleep(500);
		}
		else if (str[0] == '1') {
			printf("�E�҂̍U��!\n");
			Sleep(500);
			ehp = ehp - atk;
			printf("%s��%d�̃_���[�W\n", estatus[level].name, atk);
			Sleep(500);
			if (0 >= ehp) {
				printf("�G��|����!\n"); Sleep(500);
				printf("�E�҂̏���!\n"); Sleep(500);
				if (level != 3) {
					printf("�A�C�e���̃h���b�v�����㏸\n"); Sleep(500);
				}
				break;
			}
			printf("�G�̍U��!\n");
			Sleep(500);
			hp = hp - eatk;
			printf("�E�҂�%d�̃_���[�W\n", eatk);
			if (0 >= hp) {
				printf("�E�҂̔s�k�E�E�E\n\n\n"); //�B
				printf("ENTER�L�[����͂��Ă�������\n>");
				gets();
				system("cls");
				break;
			}
			printf("\n\n\nENTER�L�[����͂��Ă�������\n>");
			gets();
			system("cls");
		}
		else if (str[0] == '2') {
			printf("1-�|�[�V���� (%d��)    2-�X�N���[�� (%d��)    3-�߂�\n", pstatus.potion, pstatus.scroll); Sleep(500);
			char tmp[10] = { 0 };
			gets(tmp);
			if (tmp[0] == '1') {
				if (pstatus.potion > 0) {
					hp = hp + potion;
					if (hp > mhp) {
						hp = mhp;
					}
					printf("�|�[�V�������g����%d�񕜂���!\n", potion);
					Sleep(500);
					pstatus.potion--;
					printf("�c��̃|�[�V�����̐���%d��\n", pstatus.potion);
					Sleep(500);
					printf("�G�̍U��!\n");
					hp = hp - eatk;
					Sleep(500);
					printf("�E�҂�%d�̃_���[�W\n", eatk);
					Sleep(500);
					if (0 >= hp) {
						printf("�E�҂̔s�k�E�E�E\n\n\n"); //�B
						printf("ENTER�L�[����͂��Ă�������\n>");
						gets();
						system("cls");
						break;
					}
				}
				else {
					printf("�|�[�V����������܂���\n"); Sleep(500);
				}
			}
			else if (tmp[0] == '2') {
				if (pstatus.scroll > 0) {
					printf("�͂̃X�N���[�����g�p\n"); Sleep(500);
					pstatus.scroll--;
					printf("�E�҂̍U��!\n");
					Sleep(500);
					ehp = ehp - (atk + 10);
					printf("%s��%d�̃_���[�W\n", estatus[level].name, atk + 10);
					Sleep(500);
					if (0 >= ehp) {
						printf("�G��|����!\n"); Sleep(500);
						printf("�E�҂̏���!\n"); Sleep(500);
						if (level != 3) {
							printf("�A�C�e���̃h���b�v�����㏸\n"); Sleep(500);
						}
						break;
					}
					printf("�G�̍U��!\n");
					Sleep(500);
					hp = hp - eatk;
					printf("�E�҂�%d�̃_���[�W\n", eatk);
					Sleep(500);
					if (0 >= hp) {
						printf("�E�҂̔s�k�E�E�E\n\n\n"); //�B
						printf("ENTER�L�[����͂��Ă�������\n>");
						gets();
						system("cls");
						break;
					}
				}
				else {
					printf("�X�N���[��������܂���\n"); Sleep(500);
				}
			}

		}
		else {
			printf("1��2����͂��Ă�������\n"); Sleep(500);
		}


	}
	pstatus.hp = hp;
	if (level == 3) {
		if (0 >= ehp) {
			printf("���߂łƂ�...�I�R���O���`�����[�V����!!!�R���O���`�����[�V����!!!\n");
		}
		else {
			printf("����˂�!�܂����킵�Ă�!\n");
		}
	}
	if (hp > 0 && bossflag == 0) {
		srand(time(NULL));
		int dropluck = rand() % 100;
		pstatus.luck = pstatus.luck + estatus[level].edrop;
		if (pstatus.luck > dropluck) {
			if (pstatus.sword == 0) {
				printf("������ɓ��ꂽ\n\n\n"); Sleep(500);
				pstatus.sword = 1;
				pstatus.atk = pstatus.atk + 5;
				pstatus.luck = 0;
			}
			else {
				if (pstatus.potion == 2) {
					printf("�J�o���������ς��ł���ȏ㎝�ĂȂ�!\n");
				}
				else {
					printf("�|�[�V�����𔭌�����!\n");
					pstatus.potion++;
					pstatus.luck = 0;
				}
			}
		}
	}



}





void rule() {  //���[��
	while (1) {
		printf(" 1 �Q�[���̐���\n 2 ������@\n 3 �퓬�����̐���\n 4 �C�x���g�����̐���\n 5 �x�e�����̐���\n 6 �A�C�e���̐���\n 7 �߂�>");
		char tmp[100] = { 0 };
		gets(tmp);
		if (strlen(tmp) > 1) {
			system("cls");
			printf("1~6����͂��Ă�������\n"); Sleep(1500);

		}
		else if (tmp[0] == '1') {
			system("cls");
			printf(
				"--------------�Q�[���̐���-------------------------------------------------\n"
				"���̃Q�[����3�̕����̒�������I��ŒT�����Ă���BOSS�܂łɗE�҂��������{�X��|���Q�[���ł�\n"
				"�����͐퓬�A�C�x���g�A�x�e���烉���_����3�̕������I�΂�A���̒�������I�����Đi��ł����܂�\n"
				"      (��  1 �퓬�@2 �C�x���g 3 �� )\n\n"
				"������1F��17����  2F��13���� 3F��9��������A�Ō�̕����̒T�����I���������_��HP���S�񕜂��{�X��ɓ˓����܂�\n"
			);
			printf(" ENTER�L�[����͂��Ă������� \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '2') {
			system("cls");
			printf(
				"--------------������@-----------------------------------------------------------\n"
				"�L�[�{�[�h��1,2,3�ŕ�����I�����Ă�������\n"
				"�C�x���g(e)���������ꍇ�̓C�x���g���m�F�ł��܂�\n"
				"���[��(r)���������ꍇ�̓��[�����m�F�ł��܂�\n"
				"�Q�[���I��(q)���������ꍇ�̓Q�[�����I�����܂�\n"
				"���X�^�[�g(n)���������ꍇ�̓Q�[�������X�^�[�g���܂�\n"
				"�X�e�[�^�X(s)���������ꍇ�̓v���C���[��G�̃X�e�[�^�X���\������܂�\n"
			);
			printf(" ENTER�L�[����͂��Ă������� \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '3') {
			system("cls");
			printf(
				"--------------�퓬����(BATTLE)�̐���---------------------------------------------\n"
				"�퓬�̕����ł̓����X�^�[�Ɛ퓬�ɂȂ�܂�\n"
				"�퓬�ɏ��������ꍇ�̓A�C�e���̃h���b�v���肪�s���܂�\n"
				"�A�C�e���̃h���b�v���肪�s����x�ɃA�C�e�������ł���\�����㏸���܂�\n"
				"���݂̃h���b�v����G�̃h���b�v���̓X�e�[�^�X����m�F�ł��܂�\n"
			);
			printf(" ENTER�L�[����͂��Ă������� \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '4') {
			system("cls");
			printf(
				"--------------�C�x���g����(EVENT)�̐���------------------------------------------\n"
				"�C�x���g�̕����ł�1�`13�̃C�x���g�������_���ɔ������܂�\n"
				"�C�x���g�̒��ɂ͈�x��������Ɠ��e���ω�����C�x���g������܂�\n"
				"�C�x���g�̓��e�̓��j���[����m�F�ł��܂�\n"
			);
			printf(" �����L�[����͂��Ă������� \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '5') {
			system("cls");
			printf(
				"--------------�x�e����(REST)�̐���-----------------------------------------------\n"
				"�x�e�̕����ł�HP���S�񕜂��܂�\n"
			);
			printf(" ENTER�L�[����͂��Ă������� \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '6') {
			system("cls");
			printf(
				"--------------�A�C�e���̐���-----------------------------------------------------\n"
				"�|�[�V�������g�p����ƍő�̗͂�75%%�̒l���񕜂��܂�(�ő�̗͂�100�Ȃ�75��)\n"
				"�X�N���[�����g�p����Ƌ��͂ȍU�����J��o���܂�\n"
				"�|�[�V������X�N���[����2�܂ł������Ă܂���\n"
			);
			printf(" ENTER�L�[����͂��Ă������� \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '7') {
			system("cls");
			break;
		}
		else {
			printf("���������������ĉ�����\n");
			system("cls");
		}
	}
}

