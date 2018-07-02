#include "APMagicTower.h"

int FirstTime = 1;

APoint nextpoint(APoint p,int direction)
{
APoint output;
switch(direction)
{
	case Up:
		output.x = p.x;
		output.y = p.y - 1;
		break;
	case Down:
		output.x = p.x;
		output.y = p.y + 1;
		break;

	case Left:
		output.x = p.x - 1;
		output.y = p.y;
		break;

	case Right:
		output.x = p.x + 1;
		output.y = p.y;
		break;
	default:
		output = p;
		break;
}
return output;
}


void keyDown(AHwnd hwnd,AMessage msg)
{
if (status == Dead)
{
if (msg.param == VK_ENTER)
{
	AMessage to_init;
	to_init.type = MSG_INIT;
	APSendMessage(hwnd,to_init);}
return ;
}
APoint temp;
switch(msg.param)
{
	case VK_UP:
		temp = nextpoint(position,Up);
		break;
	case VK_DOWN:

		temp = nextpoint(position,Down);
		break;

	case VK_LEFT:

		temp = nextpoint(position,Left);
		break;

	case VK_RIGHT:

		temp = nextpoint(position,Right);
		break;
	case VK_ESC:
        msg.type = MSG_ESC;
        APSendMessage(hwnd,msg);
		return ;
	default:
		break;
}
my_tower[floor][position.x][position.y] = Background;
AMessage ms;
ms.type = MSG_PAINT;
ms.param = 1;
position_old = position;
switch(my_tower[floor][temp.x][temp.y])
{
	case Background:

		position = temp;
		break;
	case Wall:
		break;
	case Monster1:
	case Monster2:
	case Monster3:
		position = temp;
		if(!fight())
		{
		status = Dead;
		printf(1,"Dead");
		}
		break;
	case YellowDoor:
		if (my_key[0] > 0)
		{
		my_key[0]--;
		position = temp;
		my_tower[floor][temp.x][temp.y] = Background;
		}
		else
		{
		printf(1,"No Yellow Key");
		}
		break;
	case BlueDoor:
		if (my_key[1] > 0)
		{
		my_key[1]--;
		position = temp;
		my_tower[floor][temp.x][temp.y] = Background;
		}
		else
		{
		printf(1,"No Blue Key");
		}
		break;
	case RedDoor:
		if (my_key[1] > 0)
		{
		my_key[1]--;
		position = temp;
		my_tower[floor][temp.x][temp.y] = Background;
		}
		else
		{
		printf(1,"No red Key");
		}
		break;
	case UpStair:
		floor++;
		draw(hwnd);
		break;
	case DownStair:
		floor--;
		draw(hwnd);
		break;
	case YellowKey:
		my_key[0]++;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;
	case BlueKey:
		my_key[1]++;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;
	case RedKey:
		my_key[2]++;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;
	case SBlood:
		hp += 50;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;
	case LBlood:
		hp += 200;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;
	case Attack:
		atk += 1;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;
	case Defend:
		def += 1;
		my_tower[floor][temp.x][temp.y] = Background;
		position = temp;
		break;	
	default:
		break;
}
my_tower[floor][position.x][position.y] = Valiant;
APSendMessage(hwnd,ms);
}

void TowerInit()
{
for (int i = 0;i < BLOCK_NUM_X;i++)
{
for (int j = 0;j < BLOCK_NUM_Y;j++)
{
my_tower[0][i][j] =my_tower[1][i][j] = Background;
if (i == 0 || j == 0 || i == BLOCK_NUM_X - 1 || j == BLOCK_NUM_Y - 1)
{
	my_tower[0][i][j] =my_tower[1][i][j] = Wall;
}
}
}
my_tower[0][3][3] = UpStair;
for (int i = 2;i < 6;i++)
{
my_tower[0][i][2] = my_tower[0][2][i] = Wall;
my_tower[1][i][2] = my_tower[1][2][i] = Wall;
}
for (int i = 1;i <= 8;i++)
{
my_tower[0][i][7] = my_tower[0][7][i] = Wall;
}

my_tower[0][3][6] = my_tower[0][3][5] = my_tower[0][5][3] = YellowDoor;
my_tower[0][3][4] = my_tower[0][4][3] = YellowKey;
my_tower[0][6][6] = Monster3;
my_tower[0][4][4] = my_tower[0][4][5] = my_tower[0][5][4] = my_tower[0][5][5] = Wall;
my_tower[0][6][7] = Background;
my_tower[0][1][3] = Monster1;
my_tower[0][1][4] = Attack;
my_tower[0][3][1] = Monster2;
my_tower[0][4][1] = Defend;
my_tower[0][5][1] = BlueDoor;
my_tower[0][1][5] = YellowDoor;
my_tower[0][4][6] = Attack;
my_tower[0][5][6] = Defend;
my_tower[0][6][7] = LBlood;
my_tower[0][6][8] = RedKey;
for (int i = 2;i < 8;i++)
{
my_tower[0][i][9] = Wall;
}
my_tower[0][4][8] = Monster3;

my_tower[0][8][7] = Background;

my_tower[0][9][2] = my_tower[0][9][3] = my_tower[0][9][4] = my_tower[0][10][2] = my_tower[0][10][4] = my_tower[0][11][2] = my_tower[0][11][3] = my_tower[0][11][4] = Wall;
//o
my_tower[0][9][6] = my_tower[0][9][7] = my_tower[0][9][8] = my_tower[0][10][6] = my_tower[0][11][6]  = my_tower[0][10][8] = my_tower[0][11][8] = my_tower[0][10][10] = my_tower[0][11][10] = my_tower[0][11][9] = my_tower[0][9][10] = Wall;

//s 
//1 floor
my_tower[1][3][3] = DownStair;

my_tower[1][1][5] = RedDoor;
my_tower[1][1][6] = Monster3;
my_tower[1][5][1] = Wall;
my_tower[1][1][4] = my_tower[1][1][3] = my_tower[1][1][2] = Attack;
my_tower[1][1][1] = my_tower[1][2][1] = my_tower[1][3][1] = Defend;
my_tower[1][4][1] = SBlood;
my_tower[1][5][3] = my_tower[1][4][5] = my_tower[1][5][4] = my_tower[1][5][5] = Wall;
my_tower[1][4][6] = Wall;
for (int i = 7;i < 11;i++)
{
my_tower[1][2][i] = my_tower[1][4][i] = Wall;
my_tower[1][1][i] = Defend;
}
my_tower[1][1][10] = my_tower[1][4][10] = YellowKey;

my_tower[1][3][9] = SBlood;
my_tower[1][3][10] = Attack;
my_tower[1][3][6] = my_tower[1][3][7] = my_tower[1][3][8] = Monster1; 
my_tower[1][5][10] = Monster2;

my_tower[1][7][2] = my_tower[1][7][3] = my_tower[1][8][2] = my_tower[1][8][3] = Wall;
my_tower[1][10][2] = my_tower[1][10][3] = my_tower[1][11][2] = my_tower[1][11][3] = Wall;
for (int i = 6;i < 12;i++)
{
my_tower[1][i][9] = my_tower[1][i][7] = my_tower[1][i][5] = Wall;
}
my_tower[1][7][6] = BlueKey;
my_tower[1][6][5] =my_tower[1][12][5] =Monster3;
my_tower[1][9][1]  = my_tower[1][9][4] = BlueDoor;
my_tower[1][6][8] = my_tower[1][11][8] = Wall;
my_tower[1][8][8] = my_tower[1][9][8] =Wall;
my_tower[1][6][2] = my_tower[1][6][3] = Attack;
my_tower[1][12][2] = my_tower[1][12][3] = Defend;
my_tower[1][7][8] = my_tower[1][10][8] = Monster3;
my_tower[1][2][6] = LBlood;
//2 floor
//init my_tower


}//init the tower

void init(AHwnd hwnd)
{
status = Play;

	TowerInit();

	hp = START_HP;
	atk = START_ATK;
	def = START_DEF;
	//init the Viliant

	floor = 0;
	position.x = position.y = 1;
	my_tower[floor][position.x][position.y] = Valiant;
	my_key[0] = 3;
	my_key[1] = my_key[2] = 0;
 background = APLoadBitmap ("background.bmp");
 wall = APLoadBitmap ("wall.bmp");
 monster2 = APLoadBitmap ("monster2.bmp");
 monster3 = APLoadBitmap ("monster3.bmp");
 valiant = APLoadBitmap ("valiant.bmp");
 yellowdoor = APLoadBitmap ("yellowdoor.bmp");
 bluedoor = APLoadBitmap ("bluedoor.bmp");
 reddoor = APLoadBitmap ("reddoor.bmp");
 upstair = APLoadBitmap ("upstair.bmp");
 downstair = APLoadBitmap ("downstair.bmp");
 yellowkey = APLoadBitmap ("yellowkey.bmp");
 bluekey = APLoadBitmap ("bluekey.bmp");
 redkey = APLoadBitmap ("redkey.bmp");
 sblood = APLoadBitmap ("sblood.bmp");
 lblood = APLoadBitmap ("lblood.bmp");
 attack = APLoadBitmap ("attack.bmp");
 defend = APLoadBitmap ("defend.bmp");
 monster1 = APLoadBitmap ("monster1.bmp");

	//bitmap init	
	AMessage msg;
	msg.type = MSG_PAINT;
	msg.param = 0;
	APSendMessage(hwnd,msg);
    
   if (FirstTime)
   {
       FirstTime = 0;
       APen pen;
       ABrush brush;
       pen.color = RGB(0x18,0x74,0xcd);
       pen.size = 1;
       brush.color = RGB(0x18,0x74,0xcd);
       APSetPen(&hwnd->TitleDc,pen);
       APSetBrush(&hwnd->TitleDc,brush);
       APDrawRect(&hwnd->TitleDc,0,0,SCREEN_WIDTH,WND_TITLE_HEIGHT);
       AFont font;
       font.color = RGB(0x08,0x08,0x08);
       APSetFont(&hwnd->TitleDc,font);
       APDrawText(&hwnd->TitleDc,hwnd->title,20,20);
   }

}


bool fight()
{
printf(1,"hp before:%d\n",hp);
int mhp,matk,mdef,mid;
switch(my_tower[floor][position.x][position.y])
{
	case Monster1:
	mid = 0;
	break;
	case Monster2:
	mid = 1;
	break;
	case Monster3:
	mid = 2;
	break;
	default:
	mid = 0;
	break;
}
mhp = monster_info[mid][0];
matk = monster_info[mid][1];
mdef = monster_info[mid][2];//load monster info
if (atk <= mdef)
{
	return false;
}//cannot win
while(true)
{
	mhp -= (atk - mdef);
	if (mhp <= 0)
	{
		
printf(1,"hp after:%d\n",hp);
		return true;
	}
	if (matk < def)
	{
		continue;
	}
	hp -= (matk - def);
	if (hp <= 0)
	{
		return false;
	}
}

//
}

void draw(AHwnd hwnd)
{
for (int i = 0;i < BLOCK_NUM_X;i++)
{
for (int j = 0;j < BLOCK_NUM_Y;j++)
{
drawone(hwnd,i,j);
}
}
    

}

void drawone(AHwnd hwnd,int i,int j)
{
//printf(1,"draw one:%d\n",++con);
ABitmap temp;
switch(my_tower[floor][i][j])
{
case Background:
	temp = background;
	//temp = APLoadBitmap ("background.bmp");
	break;
case Wall:
	temp = wall;
	//temp = APLoadBitmap ("wall.bmp");
	break;
case Monster1:
	temp = monster1;
	//temp = APLoadBitmap ("monster1.bmp");
	break;
case Monster2:
	temp = monster2;	
	//temp = APLoadBitmap ("monster2.bmp");
	break;
case Monster3:
	temp = monster3;
	//temp = APLoadBitmap ("monster3.bmp");
	break;
case Valiant:	
	//temp = APLoadBitmap ("background.bmp");
	temp = background;
	APDcCopy(&hwnd->Dc,i * BLOCK_WIDTH ,j * BLOCK_WIDTH,APCreateCompatibleDCFromBitmap(temp),0,0,BLOCK_WIDTH,BLOCK_WIDTH,COLOR_NULL);
	//temp = APLoadBitmap ("valiant.bmp");
	temp = valiant;
	break;
case YellowDoor:
	temp = yellowdoor;
	//temp = APLoadBitmap ("yellowdoor.bmp");
	break;
case BlueDoor:
	temp = bluedoor;
	//temp = APLoadBitmap ("bluedoor.bmp");
	break;
case RedDoor:
	temp = reddoor;
	//temp = APLoadBitmap ("reddoor.bmp");
	break;
case UpStair:
	temp = upstair;
	//temp = APLoadBitmap ("upstair.bmp");
	break;
case DownStair:
	temp = downstair;
	//temp = APLoadBitmap ("downstair.bmp");
	break;
case YellowKey:
	temp = yellowkey;
	//temp = APLoadBitmap ("yellowkey.bmp");
	break;
case BlueKey:
	temp = bluekey;
	//temp = APLoadBitmap ("bluekey.bmp");
	break;
case RedKey:
	temp = redkey;
	//temp = APLoadBitmap ("redkey.bmp");
	break;
case SBlood:
	temp = sblood;
	//temp = APLoadBitmap ("sblood.bmp");
	break;
case LBlood:
	temp = lblood;
	//temp = APLoadBitmap ("lblood.bmp");
	break;
case Attack:
	temp = attack;
	//temp = APLoadBitmap ("attack.bmp");
	break;
case Defend:
	temp = defend;
	//temp = APLoadBitmap ("defend.bmp");
	break;
default:
	temp = background;
	//temp = APLoadBitmap ("background.bmp");
break;
}
		if(my_tower[floor][i][j] == Valiant)
		{
			APDcCopy(&hwnd->Dc,i * BLOCK_WIDTH ,j * BLOCK_WIDTH,APCreateCompatibleDCFromBitmap(temp),0,0,BLOCK_WIDTH,BLOCK_WIDTH,RGB(0,0,0));

		}
		else
		{
			APDcCopy(&hwnd->Dc,i * BLOCK_WIDTH ,j * BLOCK_WIDTH,APCreateCompatibleDCFromBitmap(temp),0,0,BLOCK_WIDTH,BLOCK_WIDTH,COLOR_NULL);
	
}//主体

//info
}

bool wndProc(AHwnd hwnd,AMessage msg)
{
	switch(msg.type)
	{
        case MSG_ESC:
            removeWindow(hwnd->id);
            return True;
        case MSG_INIT:
			
		    init(hwnd);
			printf(1,"init finished");
		
		    return False;
		case MSG_KEY_DOWN:
		keyDown(hwnd,msg);
		break;
		case MSG_PAINT:

if (msg.param == 0)
		draw(hwnd);
else
{
    AMessage msg1;
    msg1.type = MSG_WORD;
    msg1.word = (char*)malloc(sizeof(char) * 50);
    sprintf(msg1.word,"Floor:%d,Hp:%d,ATK:%d,DEF:%d,Yellow:%d,Blue:%d,Red:%d",floor+1,hp,atk,def,my_key[0],my_key[1],my_key[2]);
    APSendMessage(hwnd,msg1);
drawone(hwnd,position.x,position.y);
drawone(hwnd,position_old.x,position_old.y);
}
		char info[50];
		AMessage msg1;
	    	msg1.type = MSG_WORD;
            	sprintf(info,"Floor:%d,Hp:%d,ATK:%d,DEF:%d,Yellow:%d,Blue:%d,Red:%d",floor+1,hp,atk,def,my_key[0],my_key[1],my_key[2]);
		msg1.word = info;           	 
		APSendMessage(hwnd,msg1);
		break;
		default:
		break;
	}
	return APWndProc(hwnd,msg);

}


int main(void)
{
	
	AHwnd hwnd = APCreateWindow("magictower",False,0);
	printf(1,"magic tower created.\n");
	APWndExec(hwnd,wndProc);
	exit();
}

