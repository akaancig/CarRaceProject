#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game_player();
void create_enemy(int x,int y,int color);
int random(int range);
void game_Background();
void mycar_Move();
void game_fluidity();
void enemy();
void crash_control();
void crashed();
void game_points();
void main_menu();
void level_menu();
void quit_menu1();
void pause_menu();
void quit_main_menu(),quit_main_menu2();
void quit_windows(),quit_windows2();
void clear_game();
void game_over();
void record_score(long long int point,int level);
void high_scores();
void help_menu();

int C_x,M_Speed=15;
int car_x_1,car_x_2,car_y_1,car_y_2;
int fluidity_value = 0,selected_level = 0;
int enemy_number = 0, create_enemy_value=0, enemy_speed=20,range_bet_enemies=17;
int life_value = 5,enter_value=0;
char points_value_char[15],speed_value_char[3];
long long int points = 0;
long long int scores[30];

struct enemies
{
    int x_1,x_2,y_1,y_2,color;
    int x,y=25;
    int crash_value=0,points_value=0;
}e[20];

int main(int argc, char *argv[])
{
    initwindow(800,800);
    main_menu();
}

void game_player()
{
    int gd=DETECT,gm,i;
    int C_x=0,M_Speed=10;
    int page=0,t_y=-300;
    int a=0;
    while(1)
    {
    setactivepage(page);
    setvisualpage(1-page);
    cleardevice();

    game_Background();
    game_fluidity();
    mycar_Move();
    enemy();
    crash_control();

    page=1-page;
    delay(20);
    }
    getch();
}

int random(int range)
{
    int num;
    num = rand() % range;
    return num;
}

void game_Background()
{
    int ni=5;
    int i,t_y = -300;
    setbkcolor(RED);
    setcolor(BLUE);
    rectangle(0,0,800,800);
    setfillstyle(8,BLUE);
    floodfill(1,1,BLUE);

    for(i=0;i<800;i+=100)
    {
        setcolor(BLACK);
        rectangle(170,0+i,185,50+i);
        setfillstyle(1,BLACK);
        floodfill(171,1+i,BLACK);

        setcolor(WHITE);
        rectangle(170,50+i,185,100+i);
        setfillstyle(1,WHITE);
        floodfill(171,51+i,WHITE);

        setcolor(BLACK);
        rectangle(185,50+i,200,100+i);
        setfillstyle(1,BLACK);
        floodfill(186,51+i,BLACK);

        setcolor(WHITE);
        rectangle(185,0+i,200,50+i);
        setfillstyle(1,WHITE);
        floodfill(186,1+i,WHITE);




        setcolor(BLACK);
        rectangle(600,0+i,615,50+i);
        setfillstyle(1,BLACK);
        floodfill(601,1+i,BLACK);

        setcolor(WHITE);
        rectangle(600,50+i,615,100+i);
        setfillstyle(1,WHITE);
        floodfill(601,51+i,WHITE);

        setcolor(BLACK);
        rectangle(615,50+i,630,100+i);
        setfillstyle(1,BLACK);
        floodfill(616,51+i,BLACK);

        setcolor(WHITE);
        rectangle(615,0+i,630,50+i);
        setfillstyle(1,WHITE);
        floodfill(616,1+i,WHITE);

    }
    setcolor(BLACK);
    rectangle(200,-1,600,800);
    setfillstyle(1,8);
    floodfill(201,0,BLACK);
    setcolor(WHITE);

    t_y+=15;
    if(t_y>500)
        t_y=-500;

    setbkcolor(BLACK);
    settextstyle(10,0,2);
    outtextxy(10,10,"LIFE:");
    outtextxy(5,70,"POINTS :");
    outtextxy(650,10,"SPEED :");
    setfillstyle(1,WHITE);
    for(i=0;i<life_value;i++)
    {
        circle(80+(i*20),20,6);
        floodfill(81+(i*20),21,WHITE);
    }
    settextstyle(10,0,1);
    sprintf(points_value_char,"%lld",points);
    outtextxy(5,100,points_value_char);
    sprintf(speed_value_char,"%d",enemy_speed);
    outtextxy(650,50,speed_value_char);
}

void mycar_Move()
{
    int highest_speed,slowest_speed;
    setcolor(BLACK);
    setfillstyle(1,LIGHTBLUE);
    rectangle(358+C_x,680,438+C_x,780);
    floodfill(359+C_x,681,BLACK);

    setcolor(BLACK);
    setfillstyle(11,RED);
    rectangle(368+C_x,690,428+C_x,770);
    floodfill(369+C_x,691,BLACK);

    //Front
    setfillstyle(1,BROWN);
    rectangle(368+C_x,650,428+C_x,680);
    floodfill(369+C_x,651,BLACK);

    //wheels
    setfillstyle(1,BLACK);
    pieslice(370+C_x,665,90,270,6);
    pieslice(428+C_x,665,270,90,6);

    if((car_x_1-M_Speed)>200)
        if(GetAsyncKeyState(VK_LEFT))
            C_x-=M_Speed;
    if((car_x_2+M_Speed)<600)
        if(GetAsyncKeyState(VK_RIGHT))
            C_x+=M_Speed;
    if(selected_level == 1)
    {
        highest_speed = 29;
        slowest_speed = 10;
    }
    else if(selected_level == 2)
    {
        highest_speed = 44;
        slowest_speed = 30;
    }
    else if(selected_level == 3)
    {
        highest_speed = 58;
        slowest_speed = 45;
    }
    if(GetAsyncKeyState(VK_UP) && enemy_speed < highest_speed)
    {
        enemy_speed+=2;
        M_Speed++;
        range_bet_enemies-=5;
        if(enemy_speed >= 8 && enemy_speed <= 10)
            range_bet_enemies = 36;
        if(enemy_speed > 10 && enemy_speed <=12)
            range_bet_enemies = 31;
        if(enemy_speed > 12 && enemy_speed <= 16)
            range_bet_enemies = 24;
        if(enemy_speed > 16 && enemy_speed <= 21)
            range_bet_enemies = 22;
        if(enemy_speed > 21 && enemy_speed <= 25)
            range_bet_enemies = 19;
        if(enemy_speed > 25 && enemy_speed <=30)
            range_bet_enemies = 19;
        if(enemy_speed > 30 && enemy_speed <= 35)
            range_bet_enemies = 17;
		if(enemy_speed > 35 && enemy_speed <= 40)
            range_bet_enemies = 17;
		if(enemy_speed > 40 && enemy_speed <= 45)
            range_bet_enemies = 16;
		if(enemy_speed > 45 && enemy_speed <= 50)
            range_bet_enemies = 15;
		if(enemy_speed > 50 && enemy_speed <= 55)
            range_bet_enemies = 14;
		if(enemy_speed > 55)
            range_bet_enemies = 13;

    }
    if(GetAsyncKeyState(VK_DOWN) && enemy_speed > slowest_speed)
    {
        enemy_speed-=2;
        M_Speed--;
        if(enemy_speed >= 8 && enemy_speed <= 10)
            range_bet_enemies = 36;
        if(enemy_speed > 10 && enemy_speed <=12)
            range_bet_enemies = 31;
        if(enemy_speed > 12 && enemy_speed <= 16)
            range_bet_enemies = 24;
        if(enemy_speed > 16 && enemy_speed <= 21)
            range_bet_enemies = 22;
        if(enemy_speed > 21 && enemy_speed <= 25)
            range_bet_enemies = 19;
        if(enemy_speed > 25 && enemy_speed <=30)
            range_bet_enemies = 19;
        if(enemy_speed > 30 && enemy_speed <= 35)
            range_bet_enemies = 17;
		if(enemy_speed > 35 && enemy_speed <= 40)
            range_bet_enemies = 17;
		if(enemy_speed > 40 && enemy_speed <= 45)
            range_bet_enemies = 16;
		if(enemy_speed > 45 && enemy_speed <= 50)
            range_bet_enemies = 15;
		if(enemy_speed > 50 && enemy_speed <= 55)
            range_bet_enemies = 14;
		if(enemy_speed > 55)
            range_bet_enemies = 13;
    }
    if(GetAsyncKeyState(VK_ESCAPE))
        pause_menu();

    car_x_1 = 358+C_x;
    car_x_2 = 438+C_x;
    car_y_1 = 650;
    car_y_2 = 780;

}

void create_enemy(int x,int y,int color,int car_number)
{
    setcolor(BLACK);
    ellipse(x,y,180,360,36,30);
    line(x-36,y,x-36,y-80);
    line(x+36,y,x+36,y-80);
    ellipse(x,y-78,0,180,36,17);
    ellipse(x,y-16,180,360,36,16);
    //on - capraz
    line(x-36,y-16,x-26,y-26);
    line(x+36,y-16,x+26,y-26);
    ellipse(x,y-26,180,360,27,5);
    //ust-duz
    line(x-26,y-26,x-26,y-76);
    line(x+26,y-26,x+26,y-75);
    ellipse(x,y-74,0,180,27,5);
    //arka - capraz
    line(x-36,y-80,x-26,y-75);
    line(x+36,y-80,x+26,y-75);
    //tekerlek
    ellipse(x+36,y-4,270,90,4,7);
    ellipse(x+36,y-69,270,90,4,7);
    ellipse(x-35,y-4,90,270,4,7);
    ellipse(x-35,y-69,90,270,4,7);
    //farlar
    ellipse(x-31,y+25,0,90,15,12);
    ellipse(x+31,y+26,90,180,15,12);

    setfillstyle(1,BLACK);
    floodfill(x-35,y-75,BLACK);
    floodfill(x+35,y-75,BLACK);
    floodfill(x,y-5,BLACK);
    //tekerlek boyama
    setfillstyle(1,LIGHTGRAY);
    setcolor(LIGHTGRAY);
    floodfill(x+37,y-2,BLACK);
    floodfill(x+37,y-67,BLACK);
    floodfill(x-37,y-2,BLACK);
    floodfill(x-37,y-67,BLACK);

    setfillstyle(1,YELLOW);
    setcolor(YELLOW);
    floodfill(x-25,y+20,BLACK);
    floodfill(x+25,y+18,BLACK);
    setfillstyle(1,color);
    setcolor(color);
    floodfill(x,y,BLACK);
    floodfill(x,y-65,BLACK);
    floodfill(x,y-82,BLACK);

    e[car_number].x_1 = x - 38; //left
    e[car_number].x_2 = x+38;   //right
    e[car_number].y_1 = y+15;   //bottom
    e[car_number].y_2 = y-89;   //top

    //x1=x-38 left
    //x2=x+38 right
    //y1=y+15 bottom
    //y2=y-89 top
}

void game_fluidity()
{
    int i;
    if(fluidity_value%6==0 || fluidity_value%6 == 1 || fluidity_value%6 ==2)
    {
        for(i=0;i<800;i+=100)
    {
        setcolor(BLACK);
        rectangle(170,0+i,185,50+i);
        setfillstyle(1,BLACK);
        floodfill(171,1+i,BLACK);

        setcolor(WHITE);
        rectangle(170,50+i,185,100+i);
        setfillstyle(1,WHITE);
        floodfill(171,51+i,WHITE);

        setcolor(BLACK);
        rectangle(185,50+i,200,100+i);
        setfillstyle(1,BLACK);
        floodfill(186,51+i,BLACK);

        setcolor(WHITE);
        rectangle(185,0+i,200,50+i);
        setfillstyle(1,WHITE);
        floodfill(186,1+i,WHITE);




        setcolor(BLACK);
        rectangle(600,0+i,615,50+i);
        setfillstyle(1,BLACK);
        floodfill(601,1+i,BLACK);

        setcolor(WHITE);
        rectangle(600,50+i,615,100+i);
        setfillstyle(1,WHITE);
        floodfill(601,51+i,WHITE);

        setcolor(BLACK);
        rectangle(615,50+i,630,100+i);
        setfillstyle(1,BLACK);
        floodfill(616,51+i,BLACK);

        setcolor(WHITE);
        rectangle(615,0+i,630,50+i);
        setfillstyle(1,WHITE);
        floodfill(616,1+i,WHITE);

    }
    for(i=0;i<800;i+=80)
    {
        setcolor(WHITE);
        rectangle(320,10+i,340,50+i);
        setfillstyle(1,WHITE);
        floodfill(321,11+i,WHITE);

        rectangle(460,10+i,480,50+i);
        setfillstyle(1,WHITE);
        floodfill(461,11+i,WHITE);

    }
    }
    else if(fluidity_value%6==3 || fluidity_value%6==4 || fluidity_value%6==5)
    {
        for(i=0;i<800;i+=100)
    {
        setcolor(WHITE);
        rectangle(170,0+i,185,50+i);
        setfillstyle(1,WHITE);
        floodfill(171,1+i,WHITE);

        setcolor(BLACK);
        rectangle(170,50+i,185,100+i);
        setfillstyle(1,BLACK);
        floodfill(171,51+i,BLACK);

        setcolor(WHITE);
        rectangle(185,50+i,200,100+i);
        setfillstyle(1,WHITE);
        floodfill(186,51+i,WHITE);

        setcolor(BLACK);
        rectangle(185,0+i,200,50+i);
        setfillstyle(1,BLACK);
        floodfill(186,1+i,BLACK);




        setcolor(WHITE);
        rectangle(600,0+i,615,50+i);
        setfillstyle(1,WHITE);
        floodfill(601,1+i,WHITE);

        setcolor(BLACK);
        rectangle(600,50+i,615,100+i);
        setfillstyle(1,BLACK);
        floodfill(601,51+i,BLACK);

        setcolor(WHITE);
        rectangle(615,50+i,630,100+i);
        setfillstyle(1,WHITE);
        floodfill(616,51+i,WHITE);

        setcolor(BLACK);
        rectangle(615,0+i,630,50+i);
        setfillstyle(1,BLACK);
        floodfill(616,1+i,BLACK);

    }
    for(i=0;i<800;i+=80)
    {
        setcolor(WHITE);
        rectangle(320,50+i,340,90+i);
        setfillstyle(1,WHITE);
        floodfill(323,53+i,WHITE);

        rectangle(460,50+i,480,90+i);
        setfillstyle(1,WHITE);
        floodfill(463,53+i,WHITE);

    }
    }
    fluidity_value++;
}

void enemy()
{
    int i,random_number;
    int flag=0;
    srand(time(NULL));

    if(enemy_number>=20)
    {
        enemy_number = 0;
        for(i=0;i<20;i++)
            e[i].crash_value = 0;
    }

    e[enemy_number].color = random(15);

    while(e[enemy_number-1].color == e[enemy_number].color || e[enemy_number].color == 0 || e[enemy_number].color == 8)
    {
        e[enemy_number].color = random(15);
    }


    while(create_enemy_value % range_bet_enemies == 0 && flag != 1)
    {
        random_number = random(3);

        if(random_number == 0 && e[enemy_number-1].x != 260)
        {
            e[enemy_number].points_value = 0;
            e[enemy_number].x = 260;
            e[enemy_number].y = 26;;
            create_enemy(e[enemy_number].x,e[enemy_number].y,e[enemy_number].color,enemy_number);
            enemy_number++;
            flag++;
        }
        else if(random_number == 1 && e[enemy_number-1].x != 400)
        {
            e[enemy_number].points_value = 0;
            e[enemy_number].x = 400;
            e[enemy_number].y = 26;
            create_enemy(e[enemy_number].x,e[enemy_number].y,e[enemy_number].color,enemy_number);
            enemy_number++;
            flag++;
        }
        else if(random_number == 2 && e[enemy_number-1].x != 540)
        {
            e[enemy_number].points_value = 0;
            e[enemy_number].x = 540;
            e[enemy_number].y = 26;
            create_enemy(e[enemy_number].x,e[enemy_number].y,e[enemy_number].color,enemy_number);
            enemy_number++;
            flag++;
        }

    }
    for(i=0;i<20;i++)
    {
        if(e[i].y>25 && e[i].y<950)
        {
            create_enemy(e[i].x,e[i].y,e[i].color,i);
            e[i].y+=enemy_speed;
        }
    }
    create_enemy_value++;
}

void crash_control()
{
    int i;
    for(i=0;i<20;i++)
    {
        if(car_y_1 <= e[i].y_2 && car_y_2 >= e[i].y_2)
        {
            if(e[i].x_2 <= car_x_2 && e[i].x_2 >= car_x_1 && e[i].crash_value == 0)
            {
                crashed();
                e[i].crash_value++;

            }
            else if(e[i].x_1 >= car_x_1 && e[i].x_1<=car_x_2 && e[i].crash_value == 0)
            {
                crashed();
                e[i].crash_value++;
            }
        }
        if(car_y_1 < e[i].y_2 && e[i].points_value == 0)
        {
            points+=M_Speed;
            e[i].points_value++;
        }
    }
}

void crashed()
{
    life_value--;
    if(life_value == 0)
    {
        record_score(points,selected_level);
        game_over();
    }
}

void main_menu()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setbkcolor(LIGHTBLUE);

        setcolor(RED);
        settextstyle(2,0,50);
        outtextxy(220,100,"CAR  RACE  GAME");
        setcolor(WHITE);
        settextstyle(8,0,6);
        outtextxy(250,200,"New Game");
        settextstyle(8,0,6);
        outtextxy(250,280,"High Scores");
        settextstyle(8,0,6);
        outtextxy(250,360,"Help");
        settextstyle(8,0,6);
        outtextxy(250,440,"Quit");

        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        if(select_number == 2 || select_number == 3 || select_number == 4)
        {
            if(GetAsyncKeyState(VK_UP))
            {
                select_number--;
            }
        }
        if(select_number == 1 || select_number == 2 || select_number == 3)
        {
            if(GetAsyncKeyState(VK_DOWN))
            {
                select_number++;
            }
        }
        if(select_number == 1)
        {
            setfillstyle(1,RED);
            pieslice(225,230,90,270,25);
            floodfill(224,229,WHITE);
        }
        else if(select_number == 2)
        {
            setfillstyle(1,RED);
            pieslice(225,313,90,270,25);
            floodfill(224,312,WHITE);
        }
        else if(select_number == 3)
        {
            setfillstyle(1,RED);
            pieslice(225,392,90,270,25);
            floodfill(224,391,WHITE);
        }
        else if(select_number == 4)
        {
            setfillstyle(1,RED);
            pieslice(225,472,90,270,25);
            floodfill(224,471,WHITE);
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 0)
            {
                clear_game();
                level_menu();
            }
            else if(select_number == 2 && enter_value %2 == 0)
                high_scores();
            else if(select_number == 3 && enter_value %2 == 0)
                help_menu();
            else if(select_number == 4)
                quit_menu1();
            enter_value++;
        }


        page = 1-page;
        delay(90);
    }
}

void level_menu()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        if(select_number == 1)
        {
            setbkcolor(RED);
            setcolor(WHITE);
            settextstyle(10,0,6);
            outtextxy(295,200,"E A S Y");
            setcolor(BLACK);
            outtextxy(235,350,"M E D Ý U M");
            outtextxy(295,500,"H A R D");

        }
        else if(select_number == 2)
        {
            setbkcolor(RED);
            setcolor(BLACK);
            settextstyle(10,0,6);
            outtextxy(295,200,"E A S Y");
            outtextxy(295,500,"H A R D");
            setcolor(WHITE);
            outtextxy(235,350,"M E D Ý U M");


        }
        else if(select_number == 3)
        {
            setbkcolor(RED);
            setcolor(BLACK);
            settextstyle(10,0,6);
            outtextxy(295,200,"E A S Y");
            outtextxy(235,350,"M E D Ý U M");
            setcolor(WHITE);
            outtextxy(295,500,"H A R D");

        }

        if(select_number == 1 || select_number == 2)
            if(GetAsyncKeyState(VK_DOWN))
            select_number++;
        if(select_number == 2 || select_number == 3)
            if(GetAsyncKeyState(VK_UP))
            select_number--;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 1)
            {
                enemy_speed = 14;
                M_Speed = 14;
                range_bet_enemies = 24;
                selected_level = 1;
                game_player();
            }
            else if(select_number == 2 && enter_value % 2 == 1)
            {
                enemy_speed = 30;
                M_Speed = 21;
                range_bet_enemies = 14;
                selected_level = 2;
                game_player();
            }
            else if(select_number == 3 && enter_value % 2 == 1)
            {
                enemy_speed = 47;
                M_Speed = 28;
                range_bet_enemies = 13;
                selected_level = 3;
                game_player();
            }
            enter_value++;
        }
        if(GetAsyncKeyState(VK_ESCAPE))
            main_menu();
        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        page = 1-page;
        delay(85);
    }
}

void quit_menu1()
{
    int page=0,i,select_number=1;
    int enter_value2;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(10,0,8);
        outtextxy(270,200,"Y E S");
        outtextxy(320,420,"N O");
        if(select_number == 1)
        {
            setfillstyle(1,BLUE);
            pieslice(240,245,90,270,30);
            floodfill(239,244,RED);
        }
        else if(select_number == 2)
        {
            setfillstyle(1,BLUE);
            pieslice(240,465,90,270,30);
            floodfill(239,464,RED);
        }
        if(GetAsyncKeyState(VK_UP) && select_number == 2)
            select_number = 1;
        else if(GetAsyncKeyState(VK_DOWN) && select_number == 1)
            select_number = 2;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 1)
                exit(0);
            else if(select_number == 2 && enter_value % 2 == 1)
                main_menu();
            enter_value++;
        }
        if(GetAsyncKeyState(VK_ESCAPE))
            main_menu();
        page = 1-page;
        delay(90);
    }
}

void pause_menu()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        if(select_number == 1)
        {
            setbkcolor(RED);
            settextstyle(10,0,4);
            setcolor(WHITE);
            outtextxy(250,200,"RESUME GAME");
            setcolor(BLACK);
            outtextxy(205,320,"QUIT TO MAIN MENU");
            outtextxy(215,440,"QUIT TO WINDOWS");
        }
        if(select_number == 2)
        {
            setbkcolor(RED);
            settextstyle(10,0,4);
            setcolor(BLACK);
            outtextxy(250,200,"RESUME GAME");
            setcolor(WHITE);
            outtextxy(205,320,"QUIT TO MAIN MENU");
            setcolor(BLACK);
            outtextxy(215,440,"QUIT TO WINDOWS");
        }
        if(select_number == 3)
        {
            setbkcolor(RED);
            setcolor(BLACK);
            settextstyle(10,0,4);
            setcolor(BLACK);
            outtextxy(250,200,"RESUME GAME");
            outtextxy(205,320,"QUIT TO MAIN MENU");
            setcolor(WHITE);
            outtextxy(215,440,"QUIT TO WINDOWS");
        }
        if(GetAsyncKeyState(VK_UP) && select_number > 1)
            select_number--;
        if(GetAsyncKeyState(VK_DOWN) && select_number < 3)
            select_number++;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1)
                game_player();
            else if(select_number == 2)
                quit_main_menu();
            else if(select_number == 3)
                quit_windows();
        }

        page = 1 - page;
        delay(85);
    }
}
void quit_main_menu()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(10,0,8);
        outtextxy(270,200,"Y E S");
        outtextxy(320,420,"N O");
        settextstyle(10,0,2);
        outtextxy(205,575,"ATTENTION ! IF YOU CHOOSE");
        outtextxy(205,625,"YES, YOUR PROGRESS WILL");
        outtextxy(205,675,"BE DISAPPEARED !!");
        if(select_number == 1)
        {
            setfillstyle(1,BLUE);
            pieslice(240,245,90,270,30);
            floodfill(239,244,RED);
        }
        else if(select_number == 2)
        {
            setfillstyle(1,BLUE);
            pieslice(240,465,90,270,30);
            floodfill(239,464,RED);
        }
        if(GetAsyncKeyState(VK_UP) && select_number == 2)
            select_number = 1;
        else if(GetAsyncKeyState(VK_DOWN) && select_number == 1)
            select_number = 2;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 1)
                main_menu();
            else if(select_number == 2 && enter_value % 2 == 1)
                pause_menu();
            enter_value++;
        }
        page = 1-page;
        delay(90);
    }
}

void quit_main_menu2()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(10,0,8);
        outtextxy(270,200,"Y E S");
        outtextxy(320,420,"N O");
        if(select_number == 1)
        {
            setfillstyle(1,BLUE);
            pieslice(240,245,90,270,30);
            floodfill(239,244,RED);
        }
        else if(select_number == 2)
        {
            setfillstyle(1,BLUE);
            pieslice(240,465,90,270,30);
            floodfill(239,464,RED);
        }
        if(GetAsyncKeyState(VK_UP) && select_number == 2)
            select_number = 1;
        else if(GetAsyncKeyState(VK_DOWN) && select_number == 1)
            select_number = 2;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 1)
                main_menu();
            else if(select_number == 2 && enter_value % 2 == 1)
                game_over();
            enter_value++;
        }

        page = 1-page;
        delay(90);
    }
}

void quit_windows()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(10,0,8);
        outtextxy(270,200,"Y E S");
        outtextxy(320,420,"N O");
        settextstyle(10,0,2);
        outtextxy(205,575,"ATTENTION ! IF YOU CHOOSE");
        outtextxy(205,625,"YES, YOUR PROGRESS WILL");
        outtextxy(205,675,"BE DISAPPEARED !!");
        if(select_number == 1)
        {
            setfillstyle(1,BLUE);
            pieslice(240,245,90,270,30);
            floodfill(239,244,RED);
        }
        else if(select_number == 2)
        {
            setfillstyle(1,BLUE);
            pieslice(240,465,90,270,30);
            floodfill(239,464,RED);
        }
        if(GetAsyncKeyState(VK_UP) && select_number == 2)
            select_number = 1;
        else if(GetAsyncKeyState(VK_DOWN) && select_number == 1)
            select_number = 2;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 0)
                exit(0);
            else if(select_number == 2 && enter_value % 2 == 0)
                pause_menu();
            enter_value++;
        }
        page = 1-page;
        delay(90);
    }
}

void quit_windows2()
{
    int page=0,i,select_number=1;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(10,0,8);
        outtextxy(270,200,"Y E S");
        outtextxy(320,420,"N O");
        if(select_number == 1)
        {
            setfillstyle(1,BLUE);
            pieslice(240,245,90,270,30);
            floodfill(239,244,RED);
        }
        else if(select_number == 2)
        {
            setfillstyle(1,BLUE);
            pieslice(240,465,90,270,30);
            floodfill(239,464,RED);
        }
        if(GetAsyncKeyState(VK_UP) && select_number == 2)
            select_number = 1;
        else if(GetAsyncKeyState(VK_DOWN) && select_number == 1)
            select_number = 2;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1 && enter_value % 2 == 0)
                exit(0);
            else if(select_number == 2 && enter_value % 2 == 0)
                game_over();
            enter_value++;
        }
        page = 1-page;
        delay(90);
    }
}

void clear_game()
{
    int i;
    for(i=0;i<20;i++)
    {
        e[i].x_1 = NULL;
        e[i].x_2 = NULL;
        e[i].y_1 = NULL;
        e[i].y_2 = NULL;
        e[i].x = NULL;
        e[i].y = 25;
        e[i].crash_value = 0;
        e[i].points_value = 0;
        e[i].color = NULL;
        points = 0;
        life_value = 5;
        selected_level = 0;
    }
}

void game_over()
{
    int page=0,i,select_number=1;
    clear_game();
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setbkcolor(RED);
        setcolor(BLUE);
        settextstyle(10,0,4);
        outtextxy(210,100,"G A M E   O V E R !");

        if(select_number == 1)
        {
            setbkcolor(RED);
            settextstyle(10,0,4);
            setcolor(WHITE);
            outtextxy(290,200,"NEW GAME");
            setcolor(BLACK);
            outtextxy(205,320,"QUIT TO MAIN MENU");
            outtextxy(210,440,"QUIT TO WINDOWS");
        }
        if(select_number == 2)
        {
            setbkcolor(RED);
            settextstyle(10,0,4);
            setcolor(BLACK);
            outtextxy(210,200,"NEW GAME");
            setcolor(WHITE);
            outtextxy(215,320,"QUIT TO MAIN MENU");
            setcolor(BLACK);
            outtextxy(210,440,"QUIT TO WINDOWS");
        }
        if(select_number == 3)
        {
            setbkcolor(RED);
            setcolor(BLACK);
            settextstyle(10,0,4);
            setcolor(BLACK);
            outtextxy(210,200,"NEW GAME");
            outtextxy(205,320,"QUIT TO MAIN MENU");
            setcolor(WHITE);
            outtextxy(235,440,"QUIT TO WINDOWS");
        }
        if(GetAsyncKeyState(VK_UP) && select_number > 1)
            select_number--;
        if(GetAsyncKeyState(VK_DOWN) && select_number < 3)
            select_number++;
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(select_number == 1)
                level_menu();
            else if(select_number == 2)
                quit_main_menu2();
            else if(select_number == 3)
                quit_windows2();
        }

        page = 1 - page;
        delay(85);
    }
}

void record_score(long long int point,int level)
{
    int x=0;
    FILE *fptr;
    int i,j;
    fptr = fopen("C:\\car_game\\high_scores.txt","r");
    if(fptr == NULL)
    {
        fptr = fopen("C:\\car_game\\high_scores.txt","w");
        for(i=0;i<30;i++)
        {
            fprintf(fptr,"1000000000000 ");
        }
    }
    fclose(fptr);
    fptr = fopen("C:\\car_game\\high_scores.txt","r");
    for(i=0;i<30;i++)
    {
        fscanf(fptr,"%lld",&scores[i]);
        scores[i]-=1000000000000;
    }
    if(level == 1)
    {
        for(i=0;i<10;i++)
        {
            if(scores[i] == point)
                x = 1;
            if(point > scores[i] && i!= 9 && x == 0)
            {
                for(j=9;j>=i;j--)
                   scores[j] = scores[j-1];
                scores[i] = point;
                break;
            }
            else if(point > scores[i] && i==9 && x == 0)
                scores[9] = point;
        }
    }
    else if(level == 2)
    {
        for(i=10;i<20;i++)
        {
            if(scores[i] == point)
                x = 1;
            if(point > scores[i] && i!= 9)
            {
                for(j=19;j>=i;j--)
                   scores[j] = scores[j-1];
                scores[i] = point;
                break;
            }
            else if(point > scores[i] && i==9)
                scores[19] = point;
        }
    }
    else if(level == 3)
    {
        for(i=20;i<30;i++)
        {
            if(scores[i] == point)
                x = 1;
            if(point > scores[i] && i!= 9)
            {
                for(j=29;j>=i;j--)
                   scores[j] = scores[j-1];
                scores[i] = point;
                break;
            }
            else if(point > scores[i] && i==9)
                scores[29] = point;
        }
    }
    fclose(fptr);
    fptr = fopen("C:\\car_game\\high_scores.txt","w");
    for(i=0;i<30;i++)
    {
        scores[i]+=1000000000000;
        fprintf(fptr,"%lld ",scores[i]);
    }
    fclose(fptr);
}

void high_scores()
{
    FILE *fptr;
    int i,j,page=0;
    char point_char[12];
    fptr = fopen("C:\\car_game\\high_scores.txt","r");
    if(fptr == NULL)
    {
        fptr = fopen("C:\\car_game\\high_scores.txt","w");
        for(i=0;i<30;i++)
        {
            fprintf(fptr,"1000000000000 ");
        }
    }
    fclose(fptr);
    fptr = fopen("C:\\car_game\\high_scores.txt","r");
    for(i=0;i<30;i++)
    {
        fscanf(fptr,"%lld",&scores[i]);
        scores[i]-=1000000000000;
    }
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(10,0,4);
        outtextxy(125,50,"E A S Y");
        outtextxy(335,50,"M E D I U M");
        outtextxy(610,50,"H A R D");
        settextstyle(10,0,3);
        for(i=0;i<10;i++)
        {
            setcolor(BLACK);
            sprintf(point_char,"%d",(i+1));
            outtextxy(30,140+(i*60),point_char);
            setcolor(WHITE);
            sprintf(point_char,"%lld",scores[i]);
            outtextxy(125,140+(i*60),point_char);
        }
        for(i=10;i<20;i++)
        {
            sprintf(point_char,"%lld",scores[i]);
            outtextxy(335,140+((i-10)*60),point_char);
        }
        for(i=20;i<30;i++)
        {
            sprintf(point_char,"%lld",scores[i]);
            outtextxy(610,140+((i-20)*60),point_char);
        }
        if(GetAsyncKeyState(VK_ESCAPE))
            main_menu();
        page = 1 - page;
        delay(70);
    }
    fclose(fptr);
}

void help_menu()
{
    int page=0,i;
    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();

        setbkcolor(GREEN);
        setcolor(DARKGRAY);
        rectangle(0,0,190,800);
        setfillstyle(1,DARKGRAY);
        floodfill(1,1,DARKGRAY);
        rectangle(610,0,800,800);
        floodfill(799,799,DARKGRAY);

        for(i=0;i<900;i+=50)
        {
            setcolor(WHITE);
            setfillstyle(1,WHITE);
            rectangle(90,10+i,100,35+i);
            floodfill(91,11+i,WHITE);
            rectangle(700,10+i,710,35+i);
            floodfill(701,11+i,WHITE);
        }

        setcolor(RED);
        settextstyle(2,0,50);
        outtextxy(220,100,"CAR  RACE  GAME");
        setcolor(WHITE);
        settextstyle(10,0,2);
        outtextxy(210,180,"-> You can move the car right");
        outtextxy(210,220,"and left with the arrow keys.");
        outtextxy(210,280,"-> If you press the up and down");
        outtextxy(210,320,"arrow keys your car accelerates");
        outtextxy(210,350,"and slows down.");
        outtextxy(210,420,"-> There is a specific speed");
        outtextxy(210,460,"range for each level.");
        outtextxy(210,520,"-> Your points are determined by");
        outtextxy(210,570,"your speed.");


        if(GetAsyncKeyState(VK_ESCAPE))
            main_menu();

        page = 1 - page;
        delay(70);
    }
}
