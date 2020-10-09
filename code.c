#include <stdio.h>
#include  <stdlib.h>
#include<time.h>
#include <windows.h>


typedef struct {
	int room;//部屋
	int floor;//階層
}dungeons;
dungeons dungeon = { 1,1 };

typedef struct {
	int hp;//現在の体力
	int mhp;//最大体力
	int atk;//攻撃力
	int def;//防御力
	int luck;//運
	int shield;//盾を持っている？
	int sword;//剣を持っている？
	int upatk;//上昇した攻撃力
	int potion;//ポーションを持っている？
	int scroll;//スクロールを持っている?
	int key;//鍵を持っている？
	
}name;
name pstatus = { 30,30,3,0,0,0,0,0,0};

typedef struct {
	char name[30];//敵の名前
	int ehp;//敵の体力
	int eatk;//敵の攻撃力
	int eatkd;//敵の攻撃力　ダイスの方
	int edrop;//武器のドロップ率
	int esword;//敵の武器	
}estatuss;
estatuss estatus[5] = { { "スライム",10,1,6,3,0 },{ "スケルトンナイト",20,3,6,6,0 },{ "リザードマン",30,5,8,9,0 },{ "ミノタウロスG",90,7,10,0,0 },{ "メタリックスライム",10,0,3,15,0 } }; //f → F  ①

int event5flag = 0;
int bossflag = 0;
int countflag = 17;
int luckymonsterflag = 0;
int roomcount = 0;
char havetxt[2][10] = {"なし","所持"};

void event();
void battle();
void rule();

int main() {

	dungeon.room = 1;
	dungeon.floor = 1;


	int playstate = 1;					//ずっと遊びます
	char playstatechoice[100];			 //最後に　「もう一回あそびますか」　ための変数

	while (playstate == 1) {
		while (1) {
			printf("Cursed Brave～呪われた勇者～\n");
			printf(" 1 初めから\n 2 ルール説明\n 3 ゲーム終了\n>");
			char tmp[100] = { 0 };
			gets(tmp);
			if (strlen(tmp) > 1) {
				printf("1~3を入力してください\n");
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
				printf("\n\n\nENTERキーを入力してください\n>");
				char str[100] = { 0 };
				gets(str);
				system("cls");	
			}
			flag = 0;
			srand(time(NULL));
			int door1 = 1 + rand() % 6;
			int door2 = 1 + rand() % 6;
			int door3 = 1 + rand() % 6;

			if (event5flag == 1) {  //　次の扉の先の情報を手に入れた　　EVENT　実行

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


			

			int correctdoorselection = 0;   //選択は正しいかどうか
			int selecteddoor = 0;				//選ばれたドア
			char str[100];
			while (correctdoorselection == 0)
			{
				

			

				printf("HP: %d\t/%d \t「　剣:%s - 盾:%s - 鍵:%s 」  \n部屋: %d   階層: %d 残りの部屋数: %d\n 部屋 1= %s\t\t部屋 2= %s\t\t 部屋 3= %s\n\n部屋を選択して下さい(1～3):\n", pstatus.hp, pstatus.mhp, havetxt[pstatus.sword],havetxt[pstatus.shield], havetxt[pstatus.key], dungeon.room, dungeon.floor, countflag, Door1, Door2, Door3);
				printf("___________________\n"
					"|オプションメニュー|\n"
					"|イベント確認:e    |\n"
					"|ルール確認:r      |\n"
					"|ステータス確認:s  |\n"
					"|ゲーム終了:q      |\n"
					"|__________________|\n>"
				);
				roomcount++;
				gets(str);

				if (strlen(str) > 1)
				{
					printf("\n正しい値を入力してください\n\n");
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

					else printf("\n正しい値を入力してください\n\n");
				}
				else {
					if (str[0] == 'e')
					{
						system("cls");
						printf("\n-------------------EVENT LIST----------------------\n\n"
							"1  活力の泉を発見する\n"
							"2  新鮮な食事を発見する\n"
							"3  鍵が手に入る\n"
							"4  鍵が手に入る\n"
							"5  毒沼に落ちてしまう\n"
							"6  トラップに引っかかる\n"
							"7  ボスが武器を発見してしまう\n"
							"8  ラッキーモンスター出現\n"
							"9  敵が怪しげな実験をする\n"
							"10 怪しい薬を飲む\n"
							"11 扉の先の情報が手に入る\n"
							"12 古代のスクロールを発見した!\n"
							"13 盗賊に襲われてしまう\n\n"
						);

						printf("\nENTERを押してください \n");
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
						printf("\nPLAYER\n\n現在HP:     %d\t\t/最大HP:    %d\t剣: %s\t盾: %s\nポーション: %d個\t\tスクロール: %d個\n攻撃力:     %d～%d\tドロップ率: %d\t鍵: %s\n\n", pstatus.hp, pstatus.mhp,havetxt[pstatus.sword], havetxt[pstatus.shield], pstatus.potion, pstatus.scroll, atkmin, atkmax, pstatus.luck, havetxt[pstatus.key]);
						printf("\n\n%s\nHP:%d\t\t/攻撃力:%d～%d\tドロップ率:%d UP\n", estatus[0].name, estatus[0].ehp, eatkmin0, eatkmax0, estatus[0].edrop);
						printf("%s\nHP:%d\t\t/攻撃力:%d～%d\tドロップ率:%d UP\n", estatus[1].name, estatus[1].ehp, eatkmin1, eatkmax1, estatus[1].edrop);
						printf("%s\nHP:%d\t\t/攻撃力:%d～%d\tドロップ率:%d UP\n", estatus[2].name, estatus[2].ehp, eatkmin2, eatkmax2, estatus[2].edrop);
						printf("%s\nHP:%d\t\t/攻撃力:%d～%d\tドロップ率:%d UP\n", estatus[4].name, estatus[4].ehp, eatkmin4, eatkmax4, estatus[4].edrop);
						printf("%s\nHP:%d\t\t/攻撃力:%d～%d\tドロップ率:%d UP\t剣: %s\n\n\n\n\n\n", estatus[3].name, estatus[3].ehp, eatkmin3, eatkmax3, estatus[3].edrop, havetxt[estatus[3].esword]);

						printf("\nENTERを押してください \n");
						char str[100] = { 0 };

						gets(str);
						system("cls");
					}

					else if (str[0] == 'q')

					{



						int selectplaycorrectn = 0;
						while (selectplaycorrectn == 0)
						{
							printf("ゲーム終了しますか？ y(YES) or n(NO) :  ");

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

				printf("\n\n\n\n\n\n\nHPが全回復した\n\n\n\n\n\n\n\n"); Sleep(2000);
				printf("------------BOSSが現れた!!!!!!!!!!!!------------------\n"); Sleep(1000);
				luckymonsterflag = 0;
				bossflag = 1;
				battle();
				break;
			}






		}



		int selectplaycorrect = 0;
		while (selectplaycorrect == 0)
		{
			printf("もう一度やり直す? y(YES) or n(NO) :  ");

			gets(playstatechoice);

			if (strlen(playstatechoice) > 1)
			{
				printf("\nINVALID INPUT, Please put y(YES) or n(NO) \n\n");
			}

			else
			{
				if (playstatechoice[0] == 'y')
				{
					dungeon.floor = 1;  //dungeon初期化
					dungeon.room = 1;

					pstatus.hp = 30;   //player初期化
					pstatus.mhp = 30;
					pstatus.atk = 3;
					pstatus.upatk = 0;
					pstatus.def = 0;
					pstatus.luck = 0;
					pstatus.potion = 0;
					pstatus.key = 0;
					pstatus.sword = 0;
					pstatus.shield = 0;


					estatus[0].eatk = 1; //敵初期化
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
	printf("HPが全回復した\n\n\n");

	return hp;

}


void event() {/

	srand(time(NULL));
	Sleep(500);
	switch (rand() % 13 + 1) {
	case 1:
		printf("活力の泉を発見した！最大HPが10上昇した\n\n\n");
		pstatus.hp = pstatus.hp + 10;
		pstatus.mhp = pstatus.mhp + 10;
		break;

	case 2:
		printf("新鮮な食事を取り元気になった！最大HPが10上昇した\n\n\n");
		pstatus.hp = pstatus.hp + 10;
		pstatus.mhp = pstatus.mhp + 10;
		break;

	case 3:
		if (pstatus.key == 0) {
			printf("鍵が手に入った！宝箱を見つければ開けられそうだ！\n\n\n");
			pstatus.key = 1;
		}
		else if (pstatus.key == 1 && pstatus.shield == 1) {
			if (pstatus.potion == 2) {
				printf("ポーションを発見した。しかし鞄がいっぱいでこれ以上持てない。\n\n\n");

			}
			else {
				printf("宝箱からポーションが手に入った！使うと最大HPの75％の値分回復できる\n\n\n");
				pstatus.potion++;
				pstatus.key = 0;
			}

		}
		else {
			printf("宝箱から盾が手に入った！敵から受けるダメージを減らすことができる\n\n\n");
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
			printf("鍵が手に入った！宝箱を見つければ開けられそうだ！\n\n\n");
			pstatus.key = 1;
		}
		else if (pstatus.key == 1 && pstatus.shield == 1) {
			if (pstatus.potion == 2) {
				printf("ポーションを発見した。しかし鞄がいっぱいでこれ以上持てない。\n\n\n");

			}
			else {
				printf("宝箱からポーションが手に入った！使うと最大HPの75％の値分回復できる\n\n\n");
				pstatus.potion++;
				pstatus.key = 0;
			}

		}
		else {
			printf("宝箱から盾が手に入った！敵から受けるダメージを減らすことができる\n\n\n");
			pstatus.shield = 1;
			estatus[0].eatk -= 1;
			estatus[1].eatk -= 2;
			estatus[2].eatk -= 2;
			estatus[3].eatk -= 2;
			pstatus.key = 0;
		}
		break;

	case 5:
		printf("毒沼にはまってしまった！最大HPが5減少した！\n\n\n");
		pstatus.hp = pstatus.hp - 5;
		pstatus.mhp = pstatus.mhp - 5;

		break;

	case 6:
		printf("トラップに引っかかった！HPが10減少した！\n\n\n");
		pstatus.hp = pstatus.hp - 10;
		break;

	case 7:
		if (estatus[3].esword == 0) {
			printf("ボスが武器を発見してしまった！\n\n\n"); 
			estatus[3].esword = 1;
			estatus[3].eatk += 3;
		}
		else {
			printf("ボスが武器を落としてなくした！\n\n\n"); 
			estatus[3].esword = 0;
			estatus[3].eatk -= 3;

		}
		break;

	case 8:
		printf("アイテムを入手しやすいメタリックスライムを見つけた！\n\n\n");
		luckymonsterflag = 1;
		break;

	case 9:
		printf("敵が怪しげな実験を開始した…\n"); Sleep(2000);
		srand(time(NULL));
		switch (rand() % 3 + 1) {
		case 1:
			printf("実験が成功し、敵の攻撃力が上昇してしまった！\n\n\n");
			estatus[0].eatkd += 1;
			estatus[1].eatkd += 1;
			estatus[2].eatkd += 1;
			estatus[3].eatkd += 1;
			break;
		case 2:
			printf("実験が失敗し、敵の攻撃力が減少した！\n\n\n");
			estatus[0].eatkd -= 1;
			estatus[1].eatkd -= 1;
			estatus[2].eatkd -= 1;
			estatus[3].eatkd -= 1;
			break;
		case 3:
			printf("しかし何も起こらなかった...\n");
			break;
		}
		break;
	case 10:
		while (1) {
			printf("禍々しい色の薬を発見した......\n");
			printf("飲みますか？ Yes(y) or No(n)\n>");
			char str[100] = { 0 };
			gets(str);
			if (strlen(str) > 1) {
				printf("yかnを入力してください\n"); Sleep(500);
				system("cls");
			}
			else if (str[0] == 'y') {

				srand(time(NULL));
				switch (rand() % 3 + 1) {
				case 1:
					pstatus.upatk += 1;
					printf("体に力がみなぎる!、勇者の攻撃力が上昇した！\n\n\n");
					break;
				case 2:
					pstatus.mhp = pstatus.mhp - 3;
					pstatus.hp = pstatus.hp - 3;
					printf("体が焼けるように痛い、勇者の最大HPが3減少！\n");
					break;

				case 3:
					printf("しかし何も起こらなかった\n");
					break;
				}
				break;
			}
			else if (str[0] == 'n') {
				printf("薬を床に捨てた...\n");
				break;
			}
			else {
				printf("yかnを入力してください\n"); Sleep(500);
				system("cls");
			}
		}
		break;
	case 11:
		printf("次の扉の先を見透かし、部屋の中身を選べるようになった！\n\n\n");
		event5flag = 1;
		break;

	case 12:
		printf("古の書物を見つけた！\n"); Sleep(500);
		if (pstatus.scroll == 2) {
			printf("スクロールを発見した。しかし鞄がいっぱいでこれ以上持てない。\n\n\n");

		}
		else {
			pstatus.scroll++;
			printf("スクロールを手に入れた！使うと強力な攻撃を繰り出せる\n\n\n");
		}

		break;

	case 13:
		printf("盗賊に寝込みを襲われそうだ！\n");
		srand(time(NULL));
		Sleep(500);
		switch (rand() % 4 + 1) {

		case 1:
			if (pstatus.scroll > 0) {
				printf("スクロールを盗まれてしまった！\n\n\n");
				pstatus.scroll--;
			}
			else {
				printf("盗賊の接近に気が付き撃退した！\n");
			}
			break;
		case 2:
			if (pstatus.potion > 0) {
				printf("ポーションを盗まれてしまった１\n\n\n");
				pstatus.potion--;
			}
			else {
				printf("盗賊の接近に気が付き撃退した！\n");
			}
			break;
		case 3:
			if (pstatus.key > 0) {
				printf("鍵を盗まれてしまった！\n\n\n");
				pstatus.key = 0;
			}
			else {
				printf("盗賊の接近に気が付き撃退した！\n");
			}
			break;
		case 4:
			printf("盗める物を持っていなかったことに腹を立て襲われた！　HPが5減少した\n\n\n");
			pstatus.hp = pstatus.hp - 5;
			break;
		}
		break;


	}
	if (pstatus.hp <= 0) {
		Sleep(500);
		printf("勇者の敗北・・・\n\n\n"); //③
	}

	Sleep(500);
}

void battle() { //戦闘
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
		printf("迷宮のBOSSが現れた!!"); Sleep(1000);
	}
	else {
		printf("敵と遭遇した!\n"); Sleep(1000);
	}


	while (hp > 0 && ehp > 0) {
		system("cls");
		printf("勇者のHPは%d/%d\n", hp, mhp); Sleep(500);
		printf("%sのHPは%d/%d\n", estatus[level].name, ehp, emhp); Sleep(500);
		printf(" 攻撃:1 or アイテム:2\n>"); Sleep(500);
		char str[10] = { 0 };
		gets(str);
		printf("-------------------------\n");
		srand(time(NULL));
		int atk = pstatus.atk + (rand() % (6 + pstatus.upatk));
		int eatk = estatus[level].eatk + (rand() % estatus[level].eatkd);
		if (strlen(str) > 1) {
			printf("1か2を入力してください\n"); Sleep(500);
		}
		else if (str[0] == '1') {
			printf("勇者の攻撃!\n");
			Sleep(500);
			ehp = ehp - atk;
			printf("%sに%dのダメージ\n", estatus[level].name, atk);
			Sleep(500);
			if (0 >= ehp) {
				printf("敵を倒した!\n"); Sleep(500);
				printf("勇者の勝利!\n"); Sleep(500);
				if (level != 3) {
					printf("アイテムのドロップ率が上昇\n"); Sleep(500);
				}
				break;
			}
			printf("敵の攻撃!\n");
			Sleep(500);
			hp = hp - eatk;
			printf("勇者に%dのダメージ\n", eatk);
			if (0 >= hp) {
				printf("勇者の敗北・・・\n\n\n"); //③
				printf("ENTERキーを入力してください\n>");
				gets();
				system("cls");
				break;
			}
			printf("\n\n\nENTERキーを入力してください\n>");
			gets();
			system("cls");
		}
		else if (str[0] == '2') {
			printf("1-ポーション (%d個)    2-スクロール (%d個)    3-戻る\n", pstatus.potion, pstatus.scroll); Sleep(500);
			char tmp[10] = { 0 };
			gets(tmp);
			if (tmp[0] == '1') {
				if (pstatus.potion > 0) {
					hp = hp + potion;
					if (hp > mhp) {
						hp = mhp;
					}
					printf("ポーションを使った%d回復した!\n", potion);
					Sleep(500);
					pstatus.potion--;
					printf("残りのポーションの数は%d個\n", pstatus.potion);
					Sleep(500);
					printf("敵の攻撃!\n");
					hp = hp - eatk;
					Sleep(500);
					printf("勇者に%dのダメージ\n", eatk);
					Sleep(500);
					if (0 >= hp) {
						printf("勇者の敗北・・・\n\n\n"); //③
						printf("ENTERキーを入力してください\n>");
						gets();
						system("cls");
						break;
					}
				}
				else {
					printf("ポーションがありません\n"); Sleep(500);
				}
			}
			else if (tmp[0] == '2') {
				if (pstatus.scroll > 0) {
					printf("力のスクロールを使用\n"); Sleep(500);
					pstatus.scroll--;
					printf("勇者の攻撃!\n");
					Sleep(500);
					ehp = ehp - (atk + 10);
					printf("%sに%dのダメージ\n", estatus[level].name, atk + 10);
					Sleep(500);
					if (0 >= ehp) {
						printf("敵を倒した!\n"); Sleep(500);
						printf("勇者の勝利!\n"); Sleep(500);
						if (level != 3) {
							printf("アイテムのドロップ率が上昇\n"); Sleep(500);
						}
						break;
					}
					printf("敵の攻撃!\n");
					Sleep(500);
					hp = hp - eatk;
					printf("勇者に%dのダメージ\n", eatk);
					Sleep(500);
					if (0 >= hp) {
						printf("勇者の敗北・・・\n\n\n"); //③
						printf("ENTERキーを入力してください\n>");
						gets();
						system("cls");
						break;
					}
				}
				else {
					printf("スクロールがありません\n"); Sleep(500);
				}
			}

		}
		else {
			printf("1か2を入力してください\n"); Sleep(500);
		}


	}
	pstatus.hp = hp;
	if (level == 3) {
		if (0 >= ehp) {
			printf("おめでとう...！コングラチュレーション!!!コングラチュレーション!!!\n");
		}
		else {
			printf("ざんねん!また挑戦してね!\n");
		}
	}
	if (hp > 0 && bossflag == 0) {
		srand(time(NULL));
		int dropluck = rand() % 100;
		pstatus.luck = pstatus.luck + estatus[level].edrop;
		if (pstatus.luck > dropluck) {
			if (pstatus.sword == 0) {
				printf("剣を手に入れた\n\n\n"); Sleep(500);
				pstatus.sword = 1;
				pstatus.atk = pstatus.atk + 5;
				pstatus.luck = 0;
			}
			else {
				if (pstatus.potion == 2) {
					printf("カバンがいっぱいでこれ以上持てない!\n");
				}
				else {
					printf("ポーションを発見した!\n");
					pstatus.potion++;
					pstatus.luck = 0;
				}
			}
		}
	}



}





void rule() {  //ルール
	while (1) {
		printf(" 1 ゲームの説明\n 2 操作方法\n 3 戦闘部屋の説明\n 4 イベント部屋の説明\n 5 休憩部屋の説明\n 6 アイテムの説明\n 7 戻る>");
		char tmp[100] = { 0 };
		gets(tmp);
		if (strlen(tmp) > 1) {
			system("cls");
			printf("1~6を入力してください\n"); Sleep(1500);

		}
		else if (tmp[0] == '1') {
			system("cls");
			printf(
				"--------------ゲームの説明-------------------------------------------------\n"
				"このゲームは3つの部屋の中から一つを選んで探索していきBOSSまでに勇者を強化しボスを倒すゲームです\n"
				"部屋は戦闘、イベント、休憩からランダムに3つの部屋が選ばれ、その中から一つを選択して進んでいきます\n"
				"      (例  1 戦闘　2 イベント 3 回復 )\n\n"
				"部屋は1Fが17部屋  2Fが13部屋 3Fが9部屋あり、最後の部屋の探索が終了した時点でHPが全回復しボス戦に突入します\n"
			);
			printf(" ENTERキーを入力してください \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '2') {
			system("cls");
			printf(
				"--------------操作方法-----------------------------------------------------------\n"
				"キーボードの1,2,3で部屋を選択してください\n"
				"イベント(e)を押した場合はイベントを確認できます\n"
				"ルール(r)を押した場合はルールを確認できます\n"
				"ゲーム終了(q)を押した場合はゲームが終了します\n"
				"リスタート(n)を押した場合はゲームをリスタートします\n"
				"ステータス(s)を押した場合はプレイヤーや敵のステータスが表示されます\n"
			);
			printf(" ENTERキーを入力してください \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '3') {
			system("cls");
			printf(
				"--------------戦闘部屋(BATTLE)の説明---------------------------------------------\n"
				"戦闘の部屋ではモンスターと戦闘になります\n"
				"戦闘に勝利した場合はアイテムのドロップ判定が行われます\n"
				"アイテムのドロップ判定が行われる度にアイテムを入手できる可能性が上昇します\n"
				"現在のドロップ率や敵のドロップ率はステータスから確認できます\n"
			);
			printf(" ENTERキーを入力してください \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '4') {
			system("cls");
			printf(
				"--------------イベント部屋(EVENT)の説明------------------------------------------\n"
				"イベントの部屋では1～13のイベントがランダムに発生します\n"
				"イベントの中には一度発生すると内容が変化するイベントがあります\n"
				"イベントの内容はメニューから確認できます\n"
			);
			printf(" 何かキーを入力してください \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '5') {
			system("cls");
			printf(
				"--------------休憩部屋(REST)の説明-----------------------------------------------\n"
				"休憩の部屋ではHPが全回復します\n"
			);
			printf(" ENTERキーを入力してください \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '6') {
			system("cls");
			printf(
				"--------------アイテムの説明-----------------------------------------------------\n"
				"ポーションを使用すると最大体力の75%%の値分回復します(最大体力が100なら75回復)\n"
				"スクロールを使用すると強力な攻撃を繰り出せます\n"
				"ポーションやスクロールは2個までしか持てません\n"
			);
			printf(" ENTERキーを入力してください \n");
			char str[100] = { 0 };
			gets(str);
			system("cls");
		}
		else if (tmp[0] == '7') {
			system("cls");
			break;
		}
		else {
			printf("正しい数字を入れて下さい\n");
			system("cls");
		}
	}
}

