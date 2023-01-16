#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_LINE 255
typedef struct
{
	char name[20];
	char pass[20];
	int score;
}user;
user u;
int checkUser(char *source);
void createUser(char *source);
int fcheck(const char *filecheck);
void newstrncpy(char *dest,char *source,int max);
int msleep(long tms);
void countdown(int repeat, long msecond);
void lifeCheck(int current);
int login();
void title();
int random(int min, int max);
int countLine(char *source);
void getLine(char**dest,int in_line);
int play();
void appendScore();
void swap (user* i,user* f);
int sort();
void scoreboard();

//todo: difficulties

int main()
{
	srand(time(0));
	login();
	title();
}







int fcheck(const char *filecheck)
{
	if (access(filecheck, F_OK) != 0)
	{
		FILE* fp = fopen(filecheck,"w");
		fclose(fp);
	}
}



int msleep(long tms)
{
    struct timespec ts;
    int ret;

    if (tms < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;

    do {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);

    return ret;
}



void countdown(int repeat, long msecond)
{
	int i;
	for(i=repeat;i>0;i--)
	{
		printf("Wait...%d\n",i);
		msleep(msecond);
	}
	system("cls");
}



void createUser(char *newname)
{
	FILE* fp = fopen("lib/user.txt","a");
	strcpy(u.name,newname);
	char tpass[20];
	printf("Enter your new password: ");
	scanf("%s",u.pass);fflush(stdin);
	u.score = 0;
	fprintf(fp,"%s#%s#%d\n",u.name,u.pass,u.score);
	fclose(fp);
}




int checkUser(char *source)
{
	FILE* fp = fopen("lib/user.txt","r");
	bool stop = false;
	int create_new;
	char buffer[MAX_LINE];
	char pass_buffer[MAX_LINE];
	int int_buffer;
	char *text[100] = {0};
	while(stop==false)
	{
		fscanf(fp,"%[^#]#%[^#]#%d\n",&u.name,&u.pass,&u.score);
		//if found
		if(strcmp(u.name,source)==0)
		{
			stop = true;
			fclose(fp);
			return 0;
		}
		//if not found
		else if(feof(fp))
		{
			fflush(stdin);
			printf("Create new account?\n1.yes\n2.no\ninput: ");
			scanf("%d",&create_new);fflush(stdin);
			if(create_new==1)//y
			{
				stop = true;
				fclose(fp);
				createUser(source);
			}
			else if(create_new==2)//n
			{
				stop = true;
				fclose(fp);
				exit(0);
			}
			else
			{
				printf("Wrong input!\n\n");
			}
		}
	}
	fclose(fp);
}



int login()
{
	char tname[10];
	char tpass[10];
	int tscore;
	fcheck("lib/user.txt");
	printf(
	"\n"
	"  _                 _       \n"
	" | |               (_)      \n"
	" | |     ___   __ _ _ _ __  \n"
	" | |    / _ \\ / _` | | '_ \\ \n"
	" | |___| (_) | (_| | | | | |\n"
	" |______\\___/ \\__, |_|_| |_|\n"
	"               __/ |        \n"
	"              |___/         \n"
	"\n"
	"Enter your username(no space): "
	);
	scanf("%s",&tname);fflush(stdin);
	//if found:
    if (checkUser(tname)==0)
    {
    	printf("Hello, %s .",tname);
    	printf(" Please input your password: ");
    	scanf("%s",&tpass);fflush(stdin);
		if (strcmp(tpass,u.pass)!=0)
		{
			exit(0);
		}
	}
}



void lifeCheck(int current)
{
	if (current <= 5)
	{
		switch(current)
		{
			case 0:
				printf(
				"  +---+\n"
				"  |   |\n"
				"  O   |\n"
				" /|\\  |\n"
				" / \\  |\n"
				"      |\n"
				"=========\n"
				);
			case 1:
				printf(
				"  +---+\n"
				"  |   |\n"
				"  O   |\n"
				" /|\\  |\n"
				" /    |\n"
				"      |\n"
				"=========\n"
				);
				break;
			case 2:
				printf(
				"  +---+\n"
				"  |   |\n"
				"  O   |\n"
				" /|\\  |\n"
				"      |\n"
				"      |\n"
				"=========\n"
				);
				break;
			case 3:
				printf(
				"  +---+\n"
				"  |   |\n"
				"  O   |\n"
				"  |   |\n"
				"      |\n"
				"      |\n"
				"=========\n"
				);
				break;
			case 4:
				printf(
				"  +---+\n"
				"  |   |\n"
				"  O   |\n"
				"      |\n"
				"      |\n"
				"      |\n"
				"=========\n"
				);
				break;
			case 5:
				printf(
				"  +---+\n"
				"  |   |\n"
				"      |\n"
				"      |\n"
				"      |\n"
				"      |\n"
				"=========\n"
				);
				break;
		}
	}
	
	printf("Your life(s): %d\n",current);
}



void newstrncpy(char *dest,char *source,int max)
{
	int i;
	int j=0;
	for(i=0;i<max;i++)
	{
		if((source[i]=='\b') || (source[i]=='\f') || (source[i]=='\n') || (source[i]=='\r') || (source[i]=='\t') || (source[i]=='\v') || (source[i]=='\0'))
		{
//			return dest;
			break;
		}
		if(source[i]>64 && source[i]<91)
		{
			dest[j] = source[i];
			j++;
		}
		else if(source[i]>96 && source[i]<123)
		{
			dest[j] = source[i];
			j++;
		}
	}
//	return dest;
}



void title()
{
	int main_selection=0;
	int sscore=u.score;
	int max_lives = 5;//set
	do 
	{ 	
		//title
		printf(
		"---------------------------------------------------------------------------------\n"
		"  __    __       ___      .__   __.   _______ .___  ___.      ___      .__   __. \n"
		" |  |  |  |     /   \\     |  \\ |  |  /  _____||   \\/   |     /   \\     |  \\ |  | \n"
		" |  |__|  |    /  ^  \\    |   \\|  | |  |  __  |  \\  /  |    /  ^  \\    |   \\|  | \n"
		" |   __   |   /  /_\\  \\   |  . `  | |  | |_ | |  |\\/|  |   /  /_\\  \\   |  . `  | \n"
		" |  |  |  |  /  _____  \\  |  |\\   | |  |__| | |  |  |  |  /  _____  \\  |  |\\   | \n"
		" |__|  |__| /__/     \\__\\ |__| \\__|  \\______| |__|  |__| /__/     \\__\\ |__| \\__| \n"
		"                                                                                 \n"
		"---------------------------------------------------------------------------------\n"
		"Current Session score: %d\n"
		"Selection:\n"
		"1.Play\n"
		"2.Scoreboard\n"
		"3.Exit\n",u.score
		);
		printf("Input: ");
		scanf("%d",&main_selection);getchar();
		switch (main_selection)
		{
			case 1:
				system("cls");
				u.score += play(max_lives);
				countdown(5, 750);
				break;
			case 2:
				system("cls");
				scoreboard();
				countdown(3, 750);
				break;
			case 3:
				countdown(3, 750);
				break;
			default:
				printf("Wrong input!\n");
				countdown(3, 750);
				break;
		}
	}while(main_selection!=3);
}



int random(int min, int max)
{
	int out;
	out = (rand() % (max - min + 1)) + min;
	return out;
}



int countLine(char *source)
{
	FILE* fp = fopen(source,"r");
	int count = 0;
	while(!feof(fp))
	{
		if(fgetc(fp) == '\n')
		{
			count++;
		}
	}
	fclose(fp);
	return count;
}



void getLine(char **dest,int in_line)
{
	FILE*fp=fopen("lib/database.txt","r"); 
	bool stop = false;
	int curr_line=0;
	char buffer[MAX_LINE];
	char text[100] = {0};
	do
	{
		fgets(buffer,MAX_LINE,fp);
		if(feof(fp))
		{
			stop = true;
			strcpy(text,"err");
		}
		else if(curr_line == in_line)
		{
			stop = true;
			newstrncpy(text,buffer,100);
		}
		curr_line++;
	}while(stop==false);
	fclose(fp);
	*dest = text;
}



int play(int max_lives)
{
	int score=0;
	//standard usage
	int i;
	//setup
	bool game_ongoing = true;//bool for game start
	int input_check;//integer for how many mismatch characters from user input and answer
	int lives = max_lives;//starting lives
	int max=countLine("lib/database.txt");//temp how many answer in answer sheet
	char input;//single character input from user
	char ansheet[100]={0};//max length of words
	char *tempLine=(char *)malloc(100);//set allocation for string var
	int randresult = random(0,max-1);//get the random value
	printf("ID: %d\n",randresult);//id debug
	getLine(&tempLine, randresult);
	newstrncpy(ansheet,tempLine,100);//copy from getline random value to ansheet
	const int anslength = strlen(ansheet);//for some reason having multiple strlen causes error / different output. Solution: use a single var
	char answer[anslength];//create var from ansheet
	char used[255]={0};//for used letters
	char input_temp[anslength];//create the _ _ _ _
	newstrncpy(answer,ansheet,100);//copy from ith answsheet
	for(i=0;i<anslength;i++)//assign the _ _ _ _
	{
		input_temp[i] = '_';
	}
	//start
	while(game_ongoing==true)
	{
		input_check = 0;
		lifeCheck(lives);
//		printf("ans:%s\n",answer);//debug
//		printf("Start!\nans:%s   lives:%d\nstrlen ans: %d   strlen ansheet: %d    strlen input_temp: %d\n",answer,lives,strlen(answer),strlen(ansheet),strlen(input_temp));//debug
		printf("\n");
		for(i=0;i<anslength;i++)
		{
			printf("%c ",input_temp[i]);
		}
		printf("\n");
		
		
		//used letters:
		printf("Used letters: ");
		for(i=0;i<255;i++)
		{
			if((used[i]>64 && used[i]<91)||(used[i]>96 && used[i]<123))
			{
				printf("%c ",used[i]);
			}
		}
		
		
		//input from user
		printf("\nInput: ");
		scanf("%c",&input);fflush(stdin);//for better input buffer cleaning
		
		//for loop the entire answer length
		for(i=0;input_temp[i]!='\0' && input_temp[i]!='\n';i++)
		{
			//if input is same as current character
			if(input == answer[i])
			{
				input_temp[i] = input;
			}
			//if input is capital
			else if(input == answer[i]-32)
			{
				input_temp[i] = input+32;
			}
			//if input is not same as current character
			else
			{
				input_check++;
			}
		}
		
		//if wrong answer
		if (input_check>=strlen(answer))
		{
			used[input] = input;
			lives--;
		}
		
		//strcmp but better :)
		int second_check = 0;
		for(i=0;i<anslength;i++)
		{
			if(input_temp[i]==answer[i])
			{
				second_check++;
			}
		}
		system("cls");
		//final win lose condition
		if (lives<=0)
		{
			lifeCheck(lives);
			printf(
			"\n"
			" __     __           _                    _ \n"
			" \\ \\   / /          | |                  | |\n"
			"  \\ \\_/ /__  _   _  | |     ___  ___  ___| |\n"
			"   \\   / _ \\| | | | | |    / _ \\/ __|/ _ \\ |\n"
			"    | | (_) | |_| | | |___| (_) \\__ \\  __/_|\n"
			"    |_|\\___/ \\__,_| |______\\___/|___/\\___(_)\n"
			"                                            \n"
			"                                            \n"
			"\n"
			"Correct answer is: %s\n",answer
			);
			score-=1000;//scoring
			game_ongoing=false;
		}
		if (second_check==anslength)
		{
			for(i=0;i<anslength;i++)
			{
				printf("%c",input_temp[i]);
			}
			printf(
			"\n"
			"\n"
			" __     __          __          ___       _ \n"
			" \\ \\   / /          \\ \\        / (_)     | |\n"
			"  \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __ | |\n"
			"   \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\| |\n"
			"    | | (_) | |_| |    \\  /\\  /  | | | | |_|\n"
			"    |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_(_)\n"
			"                                            \n"
			"                                            \n"
			"\n"
		    "\n");
			score+=1000-(max_lives-lives)*200;//scoring
			game_ongoing=false;
		}
	}
	return score;
}



void swap (user* i,user* f)
{
    //swap score
    int temps = i->score;
    i->score = f->score;
    f->score = temps;

    //swap name
    char tempn[255];
    strcpy(tempn, i->name);
    strcpy(i->name, f->name);
    strcpy(f->name, tempn);
    
    //swap pass
    char tempp[255];
    strcpy(tempp, i->pass);
    strcpy(i->pass, f->pass);
    strcpy(f->pass, tempp);
}



int sort()
{
    int i,j,n;
    FILE *fp = fopen("lib/user.txt","r");
    n = countLine("lib/user.txt");
    user u[n];
    // scanning si u
    for (i = 0; i<n; i++)
    {
        fscanf (fp,"%[^#]#%[^#]#%d\n", &u[i].name, &u[i].pass, &u[i].score);
    }

    //sort descending by score
    for (i = 0; i < n - 1; i++)
    {
    	for (j = i; j < n; j++)
    	{
    		if (u[i].score < u[j].score)
    		{
    			swap(&u[i], &u[j]);
			}
		}
	}
    //sort ascending by name if score is same
    for (i = 0; i < n - 1; i++)
    {
    	for (j = i; j < n; j++)
    	{
    		if ((u[i].score == u[j].score) && (strcmp(u[i].name, u[j].name) > 0))
    		{
    			swap(&u[i], &u[j]);
			}
		}
	}
        
    system("cls");
    printf
	(
		"\n"
		"  _                    _             ____                      _ \n"
		" | |                  | |           |  _ \\                    | |\n"
		" | |     ___  __ _  __| | ___ _ __  | |_) | ___   __ _ _ __ __| |\n"
		" | |    / _ \\/ _` |/ _` |/ _ \\ '__| |  _ < / _ \\ / _` | '__/ _` |\n"
		" | |___|  __/ (_| | (_| |  __/ |    | |_) | (_) | (_| | | | (_| |\n"
		" |______\\___|\\__,_|\\__,_|\\___|_|    |____/ \\___/ \\__,_|_|  \\__,_|\n"
		"                                                                 \n"
		"                                                                 \n"
		"\n"
	);
    printf("------------------------------------\n");
    for (i = 0; i < n; i++)
    {
    	printf("%s\t\t|\t\t%d\n", u[i].name, u[i].score);
	}
	printf("------------------------------------\n");
    fclose(fp); 
    printf("press anything to continue...");
    char temp;
    getch(temp);
    printf("\n");
}



void appendScore()
{
	FILE *fp1=fopen("lib/user.txt","r");
	FILE *fp2=fopen("lib/temp.txt","w");
	char temp[20];
	char temp2[20];
	int temp3;
	while(!feof(fp1))
	{
		fscanf(fp1,"%[^#]#%[^#]#%d\n",&temp,&temp2,&temp3);
		if(strcmp(temp,u.name)==0)//if sama
		{
			fprintf(fp2,"%s#%s#%d\n",temp,temp2,u.score);
		}
		else
		{
			fprintf(fp2,"%s#%s#%d\n",temp,temp2,temp3);
		}
	}
	fclose(fp1);
	fclose(fp2);
	remove("lib/user.txt");
    rename("lib/temp.txt", "lib/user.txt");
}



void scoreboard()
{
	int menu_selection = 0;
	while(menu_selection!=3)
	{
		printf(
		"\n"
		"   _____                    _                         _ \n"
		"  / ____|                  | |                       | |\n"
		" | (___   ___ ___  _ __ ___| |__   ___   __ _ _ __ __| |\n"
		"  \\___ \\ / __/ _ \\| '__/ _ \\ '_ \\ / _ \\ / _` | '__/ _` |\n"
		"  ____) | (_| (_) | | |  __/ |_) | (_) | (_| | | | (_| |\n"
		" |_____/ \\___\\___/|_|  \\___|_.__/ \\___/ \\__,_|_|  \\__,_|\n"
		"                                                        \n"
		"                                                        \n"
		"\n"
		"1.Save progress\n"
		"2.View scores\n"
		"3.Back to main\n\n"
		"Input: "
		);
		scanf("%d",&menu_selection);fflush(stdin);
		switch(menu_selection)
		{
			case 1:
				appendScore();
				countdown(3, 750);
				printf("Successful save!\n");
				break;
			case 2:
				sort();
				countdown(3, 750);
				break;
			case 3:
				break;
				return;
			default:
				printf("Wrong input!\n");
				break;
		}
	}
}
