#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string.h>
using namespace std;
void history(char queue[30][100]);
void web_brow(char queue[30][100],char stack[30][100]);
void bookmark(char stack[30][100]);
struct node
{
	char data[100];
	struct node *next;
	struct node *previous;
}*head,*temp;
int front=-1,rear=-1;
int sp=-1;
//cout<<front<<rear;
int main()
{
	int choice;
    char queue[30][100];
    char stack[30][100];
    ifstream file2,file4,file6;
	file2.open("search histories.dat",ios::binary);
	file4.open("pointers.dat",ios::in);
	file6.open("bookmarks.dat",ios::binary);
	while(!file4.eof())
	{
	file4>>front;
	file4>>rear;
	file4>>sp;
    }
	file4.close();
	file2.read((char*)&queue,sizeof(queue));
	file6.read((char*)&stack,sizeof(stack));
	file2.close();
	do
	{
		cout<<"\n\t----------MENU------------";
	    cout<<"\n\t1.SEARCH HISTORY";
		cout<<"\n\t2.WEB BROWSER";
		cout<<"\n\t3.BOOKMARK";
		cout<<"\n\t4.EXIT";
		cout<<"\n\nEnter choice:";
		cin>>choice;
		if(choice==1)
		   history(queue);
		else if(choice==2)
		   web_brow(queue,stack);
		else if(choice==3)
		   bookmark(stack);
		else if(choice==4)
		{
			ofstream file1,file3,file5;
			file1.open("search histories.dat",ios::binary);
			file3.open("pointers.dat",ios::out);
			file5.open("bookmarks.dat",ios::binary);
			file1.write((char*)&queue,sizeof(queue));
			file5.write((char*)&stack,sizeof(stack));
			file3<<front;
			file3<<" ";
			file3<<rear;
			file3<<" ";
			file3<<sp;
			file5.close();
			file3.close();
			file1.close();
		}  
		else
		 cout<<"\nInvalid choice";  
		cout<<"\n\n***************\n\n\n";       
	}while(choice!=4);
	return 0;
}
void history(char queue[30][100])
{
	int i=0;
	cout<<"\n-----Search history-----\n\n";
	if((front==-1)&&(rear==-1))
	    cout<<"\nSearch history is empty\n";
	else
    {
    	i=rear;
    	while(i!=front)
    	{
    		cout<<queue[i];
        	cout<<"\n";
        	if((i==0)&&(front!=0))
        	    i=5-1;
        	else    
        	   i=(i-1)%5;
		}
		cout<<queue[i];
	}
}
void web_brow(char queue[30][100],char stack[30][100])
{
	int choice,choice1;
	cout<<"\nWhat would you like to search:";
	if((front==-1)&&(rear==-1))
	{
	  rear++;
	  front++;
    }
    else 
    {
       if(((((rear+1)%5)==front)))
    	  front=(front+1)%5;
       rear=(rear+1)%5;
    }
    struct node *list,*trav;
	list=(struct node*)malloc(sizeof(struct node)); 
	fflush(stdin); 
	gets(list->data);
	strcpy(queue[rear],list->data);
	cout<<"\nDo you want to bookmark this page:(yes-1/no-2):";
	cin>>choice1;
	if(choice1==1)
	{
		if(sp==-1)
		  sp++;  
		strcpy(stack[sp],list->data);
		sp++;
	    cout<<"\nADDED\n";
	}
	if(head==NULL)
    	head=list;
    else
    {
	   list->previous=temp;
	   temp->next=list;
    }
	temp=list;
	trav=temp; 
	cout<<"\n\t--------------------------";
	if(trav->previous==NULL)
	  cout<<"\n\t1.Search again\n\t4.Exit";
	else
	  cout<<"\n\t1.Search again\n\t2.Previous\n\t4.Exit";
	cout<<"\n\nEnter your choice:";
	cin>>choice;
	if(choice==1)
	   web_brow(queue,stack);
	else if(choice==2)   
	{
		do
		{
			trav=trav->previous;
			cout<<"\n\""<<trav->data<<"\"\n";
			LABEL:
			cout<<"\n\t----------------------";
			if(trav->previous==NULL)
			   cout<<"\n\t3.Next";
			else
			   cout<<"\n\t2.Previous\n\t3.Next";
			cout<<"\n\nEnter choice:";
			cin>>choice1;
			if(choice1==3)
			{
			    trav=trav->next;
			    cout<<"\n\""<<trav->data<<"\"\n";
			    if(trav->next!=NULL)
			       goto LABEL;
			}
		}while(choice1==2);
	 } 
}
void bookmark(char stack[30][100])
{
    int choice=0;
    do
    {
		cout<<"\n\n\n\t-------MENU----------";
		cout<<"\n\t1.Add bookmark\n\t2.Dispaly\n\t3.Exit";
		cout<<"\n\nEnter your choice:";
		cin>>choice;
		if(choice==1)
		{
			cout<<"\nEnter the webpage to make it bookmark:";
			if(sp==-1)
			   sp++;
			fflush(stdin);
			gets(stack[sp]);
			sp++;
		}
		if(choice==2)
		{
			cout<<"\n-------Bookmark-------\n";
			int disp;
			disp=sp;
			if(disp==-1)
			   cout<<"\nBookmark is empty\n";
			else
			{   
				do
				{
					disp--;
					cout<<"\n"<<stack[disp];
				}while(disp!=0);
			}
		}
	}while(choice!=3);
}