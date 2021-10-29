#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define size 100
void screen(int a[21][19],int score,int b[21][19]);
void ai(int *x,int *y,int *st,int *fn,int *wx,int *wy,int a[21][19],int b[21][19],int *val,int *c);
void cherry(int a[21][19],int b[21][19],int *ghx,int *ghy,int *plx,int *ply,int *cld,int *pdirx,int *pdiry,int *fx,int *fy ,int *vl,int *s);
int main(){
	srand(time(0));
	int b[21][19];
	int zero;
	char replay;
	int a[21][19]={	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	           	    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
			   		{1,20,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,20,1},
              		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			 		{1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
			   		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
			   		{1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
			   		{-1,-1,-1,1,0,1,-1,-1,-1,-1,-1,-1,-1,1,0,1,-1,-1,-1},
			  		{1,1,1,1,0,1,-1,1,1,-1,1,1,-1,1,0,1,1,1,1},
			  		{-1,-1,-1,-1,0,-1,-1,1,-1,-1,-1,1,-1,-1,0,-1,-1,-1,-1},
			        {1,1,1,1,0,1,-1,1,1,1,1,1,-1,1,0,1,1,1,1},
			        {-1,-1,-1,1,0,1,-1,-1,-1,-1,-1,-1,-1,1,0,1,-1,-1,-1},
			        {1,1,1,1,0,1,-1,1,1,1,1,1,-1,1,0,1,1,1,1},
			        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
			        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
			        {1,20,0,1,0,0,0,0,0,10,0,0,0,0,0,1,0,20,1},
			        {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
			        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
			        {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
			        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
	int i,j;
	for(i=0;i<21;i++){
    	for(j=0;j<19;j++){
    		b[i][j]=0;
    	}
    }
	int score=0;
	int gx1=9,gy1=8,gx2=9,gy2=9,gx3=9,gy3=10,gx4=8,gy4=9;
	int fx1=9,fy1=8,fx2=9,fy2=9,fx3=9,fy3=10,fx4=9,fy4=9;
	b[gx1][gy1]=1;
	b[gx2][gy2]=2;
	b[gx3][gy3]=3;
	b[gx4][gy4]=4;
    int s1=1,s2=1,s3=1,s4=1;
    int dx1=-1,dy1=0,dx2=-1,dy2=0,dx3=-1,dy3=0,dx4=-1,dy4=0;
	screen(a,score,b);
	int v1=1,v2=2,v3=3,v4=4;
	int c1=0,c2=0,c3=0,c4=0;
	int end=0;
	int state=1;
	int dirx=0;
	int diry=-1;
	int px=15,py=9;
	int timer=0;
	char way;
	//////////////////////////////////////////////////////////
	//STEP EVENTS
	while(end==0){
		if(kbhit()){
			way=getch();
			if(way=='w' && a[px-1][py]!=1){
				dirx=-1;
				diry=0;
			}
			if(way=='a' && a[px][py-1]!=1){
				dirx=0;
				diry=-1;
			}
			if(way=='s' && a[px+1][py]!=1){
				dirx=1;
				diry=0;
			}
			if(way=='d' && a[px][py+1]!=1){
				dirx=0;
				diry=1;
			}
		}
		if(a[px+dirx][py+diry]!=1){
			if(a[px+dirx][py+diry]==0){
				a[px+dirx][py+diry]=-1;
				score+=10;
		    }
			if(a[px+dirx][py+diry]==20){
				a[px+dirx][py+diry]=-1;
				score+=200;
				state=2;
				timer=50;
			}
            if(b[px+dirx][py+diry]!=1 && b[px+dirx][py+diry]!=2 &&
				b[px+dirx][py+diry]!=3 && b[px+dirx][py+diry]!=4){
				a[px][py]=-1;
	    		px+=dirx;
		    	py+=diry;
				a[px][py]=10;	
			}
		}
		if(py==0 || py==18){
			a[px][py]=-1;
			py=18-py;
			a[px][py]=10;
		}
		//////////////////////////////////////////////////
		// GHOSTS
		if(state==2){
			s1=2;
			s2=2;
			s3=2;
			s4=2;
			cherry(a,b,&gx1,&gy1,&px,&py,&c1,&dirx,&diry,&fx1,&fy1,&v1,&score);
			cherry(a,b,&gx2,&gy2,&px,&py,&c2,&dirx,&diry,&fx2,&fy2,&v2,&score);
			cherry(a,b,&gx3,&gy3,&px,&py,&c3,&dirx,&diry,&fx3,&fy3,&v3,&score);
			cherry(a,b,&gx4,&gy4,&px,&py,&c4,&dirx,&diry,&fx4,&fy4,&v4,&score);
		}
		if(timer>0 && state==2){
			timer-=1;
		}
		if(timer<=0 && state==2){
			s1=1;
			s2=1;
			s3=1;
			s4=1;
			state=1;
			timer=1;
		}
		ai(&gx1,&gy1,&s1,&end,&dx1,&dy1,a,b,&v1,&c1);
		ai(&gx2,&gy2,&s2,&end,&dx2,&dy2,a,b,&v2,&c2);
		ai(&gx3,&gy3,&s3,&end,&dx3,&dy3,a,b,&v3,&c3);
		ai(&gx4,&gy4,&s4,&end,&dx4,&dy4,a,b,&v4,&c4);
		//////////////////////////////////////////////////
		screen(a,score,b);
		zero=0;
        for(i=0;i<21;i++){
        	for(j=0;j<19;j++){
        	    if(a[i][j]==0 || a[i][j]==20){
        	    	zero+=1;
				}
	    	}
		}
		if(zero==0){
			end=1;
		}
	}
	if(zero==0){
		printf("you win\n");
	}else{
		printf("you lose\n");
	}
	printf("do you want to play again?\n");
	printf("y       n\n");
	end=0;
	while(end==0){
		replay=getch();
		if(replay=='y' || replay=='n'){
			end=1;
		}
	}
	if(replay=='y'){
		main();
	}else if(replay=='n'){
		return 0;
	}
}
	
	
	
	
	
	
void screen( int a[21][19],int score,int b[21][19]){
	int i,j;
	system("cls");
    for(i=0;i<21;i++){
    	for(j=0;j<19;j++){
    		if(b[i][j]==0){
    			if(a[i][j]==1){
    		    	printf("[]");
		    	}else if(a[i][j]==0){
			    	printf(" .");
			    }else if(a[i][j]==10){
			    	printf(" O");
		    	}else if(a[i][j]==20){
				    printf("8>");
		    	}else{
			    	printf("  ");
		    	}
			}else{
				printf("G%d",b[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	printf("SCORE:    %d\n",score);
}

void cherry(int a[21][19],int b[21][19],int *ghx,int *ghy,int *plx,int *ply,int *cld,int *pdirx,int *pdiry,int *fx,int *fy, int *vl,int *s){
	if(*plx==*ghx && *ply==*ghy){
		b[*ghx][*ghy]=0;
		*ghx=*fx;
		*ghy=*fy;
		*cld=10;
		b[*ghx][*ghx]=*vl;
		*s+=100;
	}else if(*plx+*pdirx==*ghx && *ply+*pdiry==*ghy){
		b[*ghx][*ghy]=0;
		*ghx=*fx;
		*ghy=*fy;
		*cld=10;
		b[*ghx][*ghx]=*vl;
		*s+=100;
	}
}

void ai(int *x,int *y,int *st,int *fn, int *wx,int *wy ,int a[21][19],int b[21][19],int *val,int *c){
	int dist,mindist;
	int empty=0;
	int check=0;
	if(*y==0 || *y==18){
		b[*x][*y]=0;
		*y=18-*y;
		b[*x][*y]=*val;
	}
	if(a[*x+1][*y]!=1){
		empty+=1;
	}
	if(a[*x-1][*y]!=1){
		empty+=1;
	}
	if(a[*x][*y+1]!=1){
		empty+=1;
	}
	if(a[*x][*y-1]!=1){
		empty+=1;
	}
	if(*st==1 || *st==2){
		if(a[*x+*wx][*y+*wy]==10 && *st!=2){
		    *fn=1;
		}
		if(a[*x+*wx][*y+*wy]==1 || empty>2){
			while(check==0){
				*wx=(rand() % 3)-1;
				*wy=(rand() % 3)-1;
				if(abs(*wx+*wy)==1){
					check=1;
				}
			}
		}
		if(a[*x+*wx][*y+*wy]!=1 && *c<=0 && a[*x+*wx][*y+*wy]!=10){
			b[*x][*y]=0;
		    *x+=*wx;
		    *y+=*wy;
		    b[*x][*y]=*val;
		}
	}
	if(*c<=0){
		*c=(rand() % 2)+1;
		if(*st==2){
			*c+=3;
		}
	}
	*c-=1;
}










