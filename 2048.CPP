#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>

struct player
{
        int score;
        char name[20];
}p;
struct savestruct
{
        int arr[4][4],score;
        char name[20];
}saves;



int array[4][4],points;
char name[20];

void game(int,int);
void nullify();
void display(int,int,int,int);
void up(int&);
void down(int&);
void left(int&);
void right(int&);
void generator();
void arrangeup(int);
void arrangedown(int);
void arrangeleft(int);
void arrangeright(int);
void checkgameover(int,int);
void gameover(int,int);
void displayname(int,int,char*);
void displayhighscore(int,int,int);
void help(int,int);
void savegame(int,int);
void loadgame(int,int);
int win();
int selectcolor(int);
int check(int);
void readscore();
char *setname(int,int);


void main()
{
        int gdriver=DETECT,gmode;
        initgraph(&gdriver,&gmode,"graphics");
        int maxx=getmaxx(),maxy=getmaxy();

        strcpy(name,setname(maxx,maxy));
        readscore();

        randomize();
        nullify();
        setcolor(RED);
        generator();
        generator();
        game(maxx,maxy);



}
int win()
{
        int ctr=0;
        for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        if(array[i][j]==2048)
                        {
                                ctr=1;
                                break;
                        }
                }
        }
        return ctr;
}
void gamewon(int maxx,int maxy)
{
        cleardevice();
        char ch='a';
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        settextstyle(SANS_SERIF_FONT,0,3);
        setcolor(RED);
        outtextxy(maxx/2,maxy/2-50,"YOU WIN!");

        outtextxy(maxx/2,maxy/2,"DO YOU WANT TO CONTINUE?[y/n]");
        ch=getch();


        if(ch=='y')
        {
                game(maxx,maxy);
        }
        else
        {

                gameover(maxx,maxy);
        }
}


void loadgame(int maxx,int maxy)
{
        cleardevice();
        char n[20];
        int ctr=0;
        strcpy(n,setname(maxx,maxy));
        ifstream save("saves.dat");
        if(!save)
        {
                setcolor(RED);
                settextstyle(DEFAULT_FONT,0,2);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                outtextxy(maxx/2,maxy/2,"NO DATA FOUND");
        }
        else
        {
                savestruct s;
                while(save.read((char*)&s,sizeof(s)))
                {
                        if(!strcmp(s.name,n))
                        {
                                strcpy(name,s.name);
                                for(int i=0;i<4;i++)
                                {
                                        for(int j=0;j<4;j++)
                                        {
                                                array[i][j]=s.arr[i][j];
                                        }
                                }
                                points=s.score;
                                ctr=1;
                                setcolor(RED);
                                settextstyle(DEFAULT_FONT,0,2);
                                settextjustify(CENTER_TEXT,CENTER_TEXT);
                                outtextxy(maxx/2,maxy/2,"LOAD SUCCESSFUL");
                                break;
                        }
                }
                if(ctr!=1)
                {
                        setcolor(RED);
                        settextstyle(DEFAULT_FONT,0,2);
                        settextjustify(CENTER_TEXT,CENTER_TEXT);
                        outtextxy(maxx/2,maxy/2,"NO DATA FOUND");
                }

        }
        getch();
        game(maxx,maxy);
}





void savegame(int maxx,int maxy)
{
        cleardevice();
        int ctr=0,num=0;
        savestruct s;
        strcpy(s.name,name);
        s.score=points;
        for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        s.arr[i][j]=array[i][j];
                }
        }
        char ch;
        setcolor(RED);
        fstream save("saves.dat",ios::in|ios::out);
        while(save.read((char*)&saves,sizeof(saves)))
        {
                if(!strcmp(saves.name,name))
                {

                        settextjustify(CENTER_TEXT,CENTER_TEXT);
                        settextstyle(SANS_SERIF_FONT,0,3);
                        setcolor(RED);
                        outtextxy(maxx/2,maxy/2-50,"DATA WITH YOUR NAME ALREADY EXISTS!");

                        outtextxy(maxx/2,maxy/2,"DO YOU WANT TO REPLACE?[y/n]");
                        ch=getch();


                        if(ch=='y')
                        {

                                cleardevice();

                                save.seekg(num*sizeof(s),ios::beg);

                                save.write((char*)&s,sizeof(s));
                                settextjustify(CENTER_TEXT,CENTER_TEXT);
                                outtextxy(maxx/2,maxy/2,"SAVE SUCCESSFUL");
                        }
                        ctr=1;
                        break;
                }
                num++;
        }
        save.close();

        if(ctr!=1)
        {

                  fstream file("saves.dat",ios::out|ios::ate);

                  file.write((char*)&s,sizeof(s));
                  file.close();
                  settextjustify(CENTER_TEXT,CENTER_TEXT);
                  outtextxy(maxx/2,maxy/2,"SAVE SUCCESSFUL");
        }

        getch();
        game(maxx,maxy);



}


void nullify()
{
        for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        array[i][j]=0;
                }
        }
}

void displayname(int x,int y,char *name)
{
        setcolor(YELLOW);
        settextstyle(GOTHIC_FONT,0,2);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(x,y,"Player:");
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        setcolor(WHITE);
        outtextxy(x+40,y,name);
}


char *setname(int maxx,int maxy)
{
        cleardevice();
        setcolor(WHITE);
        setfillstyle(CLOSE_DOT_FILL,RED);

        rectangle(0,0,maxx,maxy);
        rectangle(10,10,maxx-10,maxy-10);
        floodfill(2,2,WHITE);

        settextstyle(GOTHIC_FONT,0,4);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        setcolor(RED);
        outtextxy(maxx/2,maxy/2-50,"Enter Name:");
        //settextjustify(CENTER_TEXT,CENTER_TEXT);
        char name[20],ch;
        int i=0;
        name[0]='\0';
        while(1)
        {
                setcolor(BLUE);
                outtextxy(maxx/2,maxy/2,name);
                ch=getch();
                setcolor(BLACK);
                outtextxy(maxx/2,maxy/2,name);
                if(ch!=13)
                {
                        if(ch==8&&i!=0)
                        {
                                name[i-1]='\0';
                                i--;
                        }
                        else if(ch!=8)
                        {
                                name[i++]=ch;
                                name[i]='\0';
                        }
                }
                else
                {
                        break;
                }
        }
        cleardevice();
        return name;

}




void display(int maxx,int maxy,int color,int points)
{

        int begx=maxx/2-100,begy=maxy/2-100,i,j,fillcolor;

        settextstyle(SANS_SERIF_FONT,0,2);
        setcolor((color==BLACK)?BLACK:YELLOW);
        char chpoints[10],ch[20];
        strcpy(ch,"SCORE: ");
        itoa(points,chpoints,10);
        strcat(ch,chpoints);
        settextjustify(LEFT_TEXT,TOP_TEXT);
        outtextxy(maxx/2+100,20,ch);

        setcolor((color==BLACK)?BLACK:RED);

        setlinestyle(SOLID_LINE,1,3);

        for(i=0;i<=4;i++)
        {
                line(begx-25,begy-25+(i*50),begx+175,begy-25+(i*50));
        }



        for(j=0;j<=4;j++)
        {
                line(begx-25+(j*50),begy-25,begx-25+(j*50),begy+175);
        }





        settextstyle(SANS_SERIF_FONT,0,3);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        char temp[10];

        for(i=0;i<4;i++)
        {
                for(j=0;j<4;j++)
                {
                        if(array[i][j]!=0)
                        {
                                fillcolor=(color==BLACK)?BLACK:selectcolor(array[i][j]);
                                if(array[i][j]>64)
                                {
                                        settextstyle(SANS_SERIF_FONT,0,2);
                                }
                                setcolor(fillcolor);
                                itoa(array[i][j],temp,10);
                                outtextxy(begx+(j*50),begy+(i*50),temp);
                                if(array[i][j]>64)
                                {
                                        settextstyle(SANS_SERIF_FONT,0,3);
                                }

                        }
                        else
                        {
                                outtextxy(begx+(j*50),begy+(i*50)," ");
                        }
                }

        }
}

int selectcolor(int x)
{
        if(x>4)
        {
                switch (x)
                {
                        case 32:
                        case 128:

                             return YELLOW;

                        case 64:
                        case 256:
	                case 4096:

                             return RED;

                        case 16:
                        case 512:
                        case 2048:
                             return WHITE;

                        case 8:
                        case 1024:

                             return MAGENTA;
                }
        }
        else
        {
                return GREEN;
        }
}

void generator()
{
        int x,i,j,ctr=0;

        do
        {
                x=random(5);
        }while(x!=2&&x!=4);


        do
        {
                i=random(4);
                j=random(4);
                if(array[i][j]==0)
                {
                        ctr++;
                        array[i][j]=x;
                }
        }while(ctr==0);
}

void up(int &points)
{
        for(int i=0;i<4;i++)
        {
                arrangeup(i);
                for(int j=0;j<4;j++)
                {
                        if(array[j][i]==array[j+1][i])
                        {
                                array[j][i]*=2;
                                array[j+1][i]=0;
                                points+=array[j][i];

                        }
                }
                arrangeup(i);

        }

}
void down(int &points)
{

        for(int i=0;i<4;i++)
        {
                arrangedown(i);
                for(int j=3;j>=0;j--)
                {
                        if(array[j][i]==array[j-1][i])
                        {
                                array[j][i]*=2;
                                array[j-1][i]=0;
                                points+=array[j][i];

                        }
                }
                arrangedown(i);
        }

}
void left(int &points)
{

        for(int i=0;i<4;i++)
        {
                arrangeleft(i);
                for(int j=0;j<3;j++)
                {
                        if(array[i][j]==array[i][j+1])
                        {
                                array[i][j]*=2;
                                array[i][j+1]=0;
                                points+=array[i][j];

                        }
                }
                arrangeleft(i);

        }

}

void right(int &points)
{

        for(int i=0;i<4;i++)
        {
                arrangeright(i);
                for(int j=3;j>=1;j--)
                {
                        if(array[i][j]==array[i][j-1])
                        {
                                array[i][j]*=2;
                                array[i][j-1]=0;
                                points+=array[i][j];

                        }
                }
                arrangeright(i);
        }


}

void arrangeup(int x)
{
        int temp;

        for(int i=0;i<4;i++)
        {
                if(array[i][x]!=0)
                {
                        for(int j=i-1;j>=0;j--)
                        {
                                if(array[j][x]!=0)
                                {
                                        temp=array[i][x];
                                        array[i][x]=array[j+1][x];
                                        array[j+1][x]=temp;

                                        break;


                                }
                                else if(j==0)

                                {
                                        temp=array[i][x];
                                        array[i][x]=array[j][x];
                                        array[j][x]=temp;

                                        break;
                                }


                        }

                }


        }

}
void arrangedown(int x)
{
        int temp;

        for(int i=3;i>=0;i--)
        {
                if(array[i][x]!=0)
                {
                        for(int j=i+1;j<4;j++)
                        {
                                if(array[j][x]!=0)
                                {
                                        temp=array[i][x];
                                        array[i][x]=array[j-1][x];
                                        array[j-1][x]=temp;

                                        break;


                                }
                                else if(j==3)

                                {
                                        temp=array[i][x];
                                        array[i][x]=array[j][x];
                                        array[j][x]=temp;

                                        break;
                                }


                        }

                }


        }


}

void arrangeleft(int x)
{
        int temp;

        for(int i=0;i<4;i++)
        {
                if(array[x][i]!=0)
                {
                        for(int j=i-1;j>=0;j--)
                        {
                                if(array[x][j]!=0)
                                {
                                        temp=array[x][i];
                                        array[x][i]=array[x][j+1];
                                        array[x][j+1]=temp;

                                        break;


                                }
                                else if(j==0)

                                {
                                        temp=array[x][i];
                                        array[x][i]=array[x][j];
                                        array[x][j]=temp;

                                        break;
                                }


                        }

                }


        }

}


void arrangeright(int x)
{
        int temp;

        for(int i=3;i>=0;i--)
        {
                if(array[x][i]!=0)
                {
                        for(int j=i+1;j<4;j++)
                        {
                                if(array[x][j]!=0)
                                {
                                        temp=array[x][i];
                                        array[x][i]=array[x][j-1];
                                        array[x][j-1]=temp;

                                        break;


                                }
                                else if(j==3)

                                {
                                        temp=array[x][i];
                                        array[x][i]=array[x][j];
                                        array[x][j]=temp;

                                        break;
                                }


                        }

                }


        }


}

void checkgameover(int maxx,int maxy)
{
        int ctr=0,i,j;
        for(i=0;i<4;i++)
        {
                for(j=0;j<4;j++)
                {
                        if(array[i][j]==0)
                        {
                                ctr=1;
                                break;
                        }
                }
        }

        if(ctr!=1)
        {
                for(i=0;i<4;i++)
                {
                        for(j=0;j<3;j++)
                        {
                                if(array[i][j]==array[i][j+1] || array[j][i]==array[j+1][i])
                                {
                                        ctr=2;
                                }
                        }
                }
                if(ctr!=2)
                {


                        gameover(maxx,maxy);
                }
        }
}


void gameover(int maxx,int maxy)
{

                ofstream file("highscores.dat",ios::trunc);
                file.write((char*)&p,sizeof(p));
                file.close();

                settextstyle(DEFAULT_FONT,0,7);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                setcolor(WHITE);
                outtextxy(maxx/2,maxy/2-20,"GAME OVER!");
                getch();
                closegraph();
                exit(0);
}

int check(int x)
{
        int i,j,ctr;

        switch (x)
        {
                case 1:                 // up
                     for(i=0;i<4;i++)
                     {
                        for(j=0;j<3;j++)
                        {
                                if(array[j+1][i]!=0&&array[j][i]==0)
                                {
                                        ctr=0;
                                }
                                if((array[j][i]==array[j+1][i])&&array[j][i]!=0)
                                {
                                        ctr=0;
                                }

                        }
                     }
                     return ctr;


                case 2:        //down
                     for(i=0;i<4;i++)
                     {
                        for(j=0;j<3;j++)
                        {
                                if(array[j][i]!=0&&array[j+1][i]==0)
                                {
                                        ctr=0;
                                }
                                if((array[j][i]==array[j+1][i])&&array[j][i]!=0)
                                {
                                        ctr=0;
                                }

                        }
                     }
                     return ctr;

                case 3:                 //left

                     for(i=0;i<4;i++)
                     {
                        for(j=1;j<4;j++)
                        {
                                if(array[i][j]!=0&&array[i][j-1]==0)
                                {
                                        ctr=0;
                                }
                                if((array[i][j-1]==array[i][j])&&array[i][j]!=0)
                                {
                                        ctr=0;
                                }

                        }
                     }
                     return ctr;

                case 4:                 //right

                     for(i=0;i<4;i++)
                     {
                        for(j=0;j<3;j++)
                        {
                                if(array[i][j]!=0&&array[i][j+1]==0)
                                {
                                        ctr=0;
                                }
                                if((array[i][j]==array[i][j+1])&&array[i][j]!=0)
                                {
                                        ctr=0;
                                }

                        }
                     }
                     return ctr;

        }
}

void readscore()
{
        ifstream file("highscore.dat");
        if(!file)
        {
                p.score= 0;
                strcpy(p.name,'\0');
        }
        else
        {
                file.read((char *)&p,sizeof(p));
                file.close();
        }
}

void displayhighscore(int maxx,int maxy,int color)
{

        settextstyle(GOTHIC_FONT,0,3);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        setcolor(BROWN);
        outtextxy(maxx-100,maxy/2-80,"Highscore");
        settextstyle(DEFAULT_FONT,0,2);
        setcolor((color==BLACK)?BLACK:WHITE);
        outtextxy(maxx-100,maxy/2-20,p.name);
        setcolor((color==BLACK)?BLACK:YELLOW);
        char ch[10];
        itoa(p.score,ch,10);
        outtextxy(maxx-100,maxy/2,ch);
}

void help(int maxx,int maxy)
{
        cleardevice();
        int y=100;
        char word[20],ch[2];
        ch[1]='\0';

        setcolor(WHITE);
        rectangle(0,0,maxx,maxy);
        rectangle(10,10,maxx-10,maxy-10);
        setfillstyle(SOLID_FILL,RED);
        floodfill(3,3,WHITE);
        settextstyle(GOTHIC_FONT,0,3);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(maxx/2,50,"2048");
        moveto(15,y);
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        ifstream help("help.txt");
        settextstyle(SANS_SERIF_FONT,0,2);

        if(!help)
        {
                gotoxy(20,20);
                cout<<"CANNOT OPEN!";
        }
        else
        while(!help.eof())
        {
                help>>word;
                if(getx()>=maxx-50)
                {
                        y+=20;
                        moveto(15,y);
                }
                outtext(word);
                help.get(ch[0]);
                outtext(ch);

        }
        help.close();
        getch();
        game(maxx,maxy);


}
void menubar(int maxx,int maxy)
{
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,BLUE);
        rectangle(0,maxy-20,maxx,maxy);
        floodfill(3,maxy-17,WHITE);


        settextstyle(DEFAULT_FONT,0,1);
        moveto(20,maxy-10);
        setcolor(WHITE);
        outtext("HELP:");
        setcolor(GREEN);
        outtext("F1   ");
        setcolor(WHITE);
        outtext("EXIT:");
        setcolor(GREEN);
        outtext("Esc   ");
        setcolor(WHITE);
        outtext("SAVE:");
        setcolor(GREEN);
        outtext("F2   ");
        setcolor(WHITE);
        outtext("LOAD:");
        setcolor(GREEN);
        outtext("F3   ");
        setcolor(WHITE);
        outtext("RESTART:");
        setcolor(GREEN);
        outtext("F5");

}

int ctrwin=0;
void game(int maxx,int maxy)
{
        cleardevice();
        setcolor(RED);
        rectangle(0,0,maxx,maxy);
        rectangle(10,10,maxx-10,maxy-10);
        setfillstyle(SOLID_FILL,BLUE);
        floodfill(4,4,RED);

        char ch;
        displayname(100,20,name);
        menubar(maxx,maxy);
        while(!kbhit())
        {


                if(win()&&ctrwin!=1)
                {
                        ctrwin=1;
                        gamewon(maxx,maxy);
                }
                display(maxx,maxy,BLUE,points);
                displayhighscore(maxx,maxy,10);
                checkgameover(maxx,maxy);
                ch=getch();
                if(ch==0)
                {
                        ch=getch();

                        display(maxx,maxy,BLACK,points);
                        switch(ch)
                        {
                                case 72:

                                     if(!check(1))
                                     {
                                        up(points);
                                        generator();
                                     }


                                     break;
                                case 75:
                                     if(!check(3))
                                     {
                                        left(points);
                                        generator();
                                     }
                                     break;
                                case 77:
                                     if(!check(4))
                                     {
                                        right(points);
                                        generator();
                                     }
                                     break;

                                case 80:

                                     if(!check(2))
                                     {
                                        down(points);
                                        generator();
                                     }
                                     break;

                                case 59:
                                     help(maxx,maxy);
                                     break;
                                case 60:
                                     savegame(maxx,maxy);
                                     break;
                                case 61:
                                     loadgame(maxx,maxy);
                                     break;
                                case 63:
                                     nullify();
                                     points=0;
                                     generator();
                                     generator();
                                     break;
                                default:
                                        break;

                        }
                }
                else if(ch==27)
                {
                        break;
                }
                if(points>p.score)
                {
                        displayhighscore(maxx,maxy,BLACK);
                        strcpy(p.name,name);
                        p.score=points;

                }


        }
        gameover(maxx,maxy);
}