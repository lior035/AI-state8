#include <iostream>
using namespace std;
#include <string.h>
#include "state8.h"

State8::State8(int ** arr) //constructor 
{	
	hVal = 0;
	fVal = 0;
	gVal = 0;

	if (arr ==NULL)
		createMat(this);

	else 
		copyMat(this, arr); // will duplicate the same mat to this object
}

//==========================================================================

void State8::createMat(State8 * curr)
{
	curr->arr = new int* [3];
	
	int u ;
	int col;

	for (u=0; u<3; u++)
		curr->arr[u] = new int [3];
	
	cout<<"Please choose a blank place in the pazzal, in the format of [row, col] where row and col between 1-3"<<endl;
	cin>>u;
	curr->i = u-1;

	cin>>u;
	curr->j = u-1;

	cout<<"please enter numbers between 1-8 in order to fill the mathrician, input as [row,col], no duplications"<<endl;

	for (u=0; u<3; u++)
	{
		for (col=0; col<3;col++)
		{
			if ((curr->i==u)&&(curr->j==col))
			{
				cout<<"Place : [" <<u+1<<" , "<<col+1<<"] : blank spot - no input here"<<endl;
				curr->arr[u][col] = 0; // in order to indicate a blank spot the number will be 0 at this position
			}

			else
			{
				cout<<"Place : [" <<u+1<<" , "<<col+1<<"] :"<<endl;
				cin>>curr->arr[u][col];
			}
		}
	}
}

void State8::copyMat (State8 * curr, int ** arr)
{
	curr->arr = new int* [3];

	int u ;
	int col;

	for (u=0; u<3; u++)
		curr->arr[u] = new int [3];

	for (u=0; u<3; u++)
	{
		for (col=0; col<3;col++)
		{
			if (arr[u][col] == 0) 
			{
				curr->i = u;
				curr->j = col;
			}

			else
			{
				curr->arr[u][col] = arr[u][col];
			}
		}
	}
}

//==========================================================================

void State8:: updateHn (State8* goal) 
{
	this->computeHn(goal);
}

void State8::computeHn (State8* goal)
{
	//asumption - the array is not empty
	
	int k;
	int m ;
	int Hn = 0;

	for (k=0; k<3; k++)
	{
		for (m=0; m<3; m++)
		{
			int num = this->arr[k][m];
			if (num!=0)
				Hn += computeDis(goal,k,m,num);
		}
	}

	this->hVal = Hn;
}

int State8::computeDis(State8* goal,int k,int m,int num)
{
	int col;
	int row;
	int n1 =0;
	int n2 = 0;
	
	for (row = 0; row<3; row++)
	{
		for(col=0; col<3; col++)
		{
			if (num == goal->arr[row][col])
			{
				 n1 = k-row;
				 n2 = m-col;

				if (n1<0)
					n1=n1*(-1);
				if (n2<0)
					n2 = n2*(-1);
				return n1+n2;
			}
		}
	}
	return n1+n2;
}


int State8::giveHn()
{
	return this->hVal;
}

//==========================================================================

void State8::updateGn (State8* g)
{
	this->gVal = g->giveGn()+1;
}

int State8::giveGn()
{
	return this->gVal;
}
//==========================================================================

void State8::updateFn ()
{
	//compute f(n) assuming that h(n) and g(n) are update to the correct vals
	this->computeFn();
}

void State8::computeFn ()
{
	//compute f(n) assuming that h(n) and g(n) are update to the correct vals
	this->fVal = this->gVal+this->hVal;
}

int State8::giveFn ()
{
	return this->fVal;
}

//==========================================================================
State8** State8::createSonsState (int * numOfSons, State8* goal)
{
	int u;
	int tSons;
	State8** sons;
	//-------case of the blank at (0,0)-------------------------

	if ((this->i==0) &&(this->j ==0))
	{
		tSons = 2;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[0][0] = this->arr[0][1];
		sons[0]->j = 1; // i remain at 0

		sons[1]->arr[0][0] = this->arr[1][0];
		sons[1]->i = 1; // j remain at 0
	}

	//-------case of the blank at (0,1)-------------------------

	else  if ((this->i == 0)&&(this->j == 1))
	{
		tSons = 3;
	    sons = new State8* [tSons];
		
		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[0][1] = this->arr[0][0];
		sons[0]->j = 0;//i remain at 0

		sons[1]->arr[0][1] = this->arr[1][1];
		sons[1]->i = 1; // j remain at 0

		sons[2]->arr[0][1] = this->arr[0][2];
		sons[2]->j = 2; //i remain at 0
	}

	//-------case of the blank at (0,2)-------------------------

	else  if ((this->i == 0)&&(this->j == 2))
	{
		tSons = 2;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[0][2] = this->arr[0][1];
		sons[0]->j = 1;// i reamin at 0;

		sons[1]->arr[0][2] = this->arr[1][2];
		sons[1]->i = 1;// j reamin at 2;
	}

	//-------case of the blank at (1,0)-------------------------

	else  if ((this->i == 1)&&(this->j == 0))
	{
		tSons = 3;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[1][0] = this->arr[0][0];
		sons[0]->i = 0;// j reamin at 0;

		sons[1]->arr[1][0] = this->arr[1][1];
		sons[1]->j = 1;// i reamin at 1;

		sons[2]->arr[1][0] = this->arr[2][0];
		sons[2]->i =2;// j reamin at 0;
	}

	//-------case of the blank at (1,1)-------------------------

	else  if ((this->i == 1)&&(this->j == 1))
	{
		tSons = 4;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[1][1] = this->arr[0][1];
		sons[0]->i = 0;// j reamin at 1;

		sons[1]->arr[1][1] = this->arr[2][1];
		sons[1]->i = 2;// j reamin at 1;

		sons[2]->arr[1][1] = this->arr[1][0];
		sons[2]->j = 0;// i reamin at 1;

		sons[3]->arr[1][1] = this->arr[1][2];
		sons[3]->j =2;// i reamin at 1;
	}

	//-------case of the blank at (1,2)-------------------------

	else  if ((this->i == 1)&&(this->j == 2))
	{
		tSons = 3;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[1][2] = this->arr[0][2];
		sons[0]->i = 0;// j reamin at 2;

		sons[1]->arr[1][2] = this->arr[2][2];
		sons[1]->i = 2;// j reamin at 2;

		sons[2]->arr[1][2] = this->arr[1][1];
		sons[2]->j = 1;// i reamin at 1;
	}

	//-------case of the blank at (2,0)-------------------------

	else  if ((this->i == 2)&&(this->j == 0))
	{
		tSons = 2;
		sons = new State8* [tSons];
	
		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[2][0] = this->arr[1][0];
		sons[0]->i = 1;// j reamin at 0;

		sons[1]->arr[2][0] = this->arr[2][1];
		sons[1]->j = 1;// i reamin at 2;
	}

	//-------case of the blank at (2,1)-------------------------

	else  if ((this->i == 2)&&(this->j == 1))
	{
		tSons = 3;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[2][1] = this->arr[2][0];
		sons[0]->j = 0;// i reamin at 2;

		sons[1]->arr[2][1] = this->arr[1][1];
		sons[1]->i = 1;// j  reamin at 1;

		sons[2]->arr[2][1] = this->arr[2][2];
		sons[2]->j = 2;// i  reamin at 2;
	}

	//-------case of the blank at (2,2)------------------------

	else 
	{
		tSons = 2;
		sons = new State8* [tSons];

		for (u=0;u<tSons;u++)
			sons[u]= new State8 (this->arr);

		sons[0]->arr[2][2] = this->arr[1][2];
		sons[0]->i = 1;//j  reamin at 2;

		sons[1]->arr[2][2] = this->arr[2][1];
		sons[1]->j = 1;//i  reamin at 2;
	}

	//===========================================================

	for (u=0;u<tSons;u++)
	{
		sons[u]->arr[sons[u]->i][sons[u]->j] = 0;
		sons[u]->updateGn (this);
		sons[u]->updateHn (goal);
		sons[u]->updateFn ();

		
	}

	*numOfSons = tSons;

	return sons;
}

//==========================================================================


int State8:: compareStates(State8 * s)
{
	int row, col;

	for (row = 0; row<3; row++)
	{
		for (col = 0; col<3; col++)
		{
			if (this->arr[row][col] != s->arr[row][col])
				return 0; // meaning that the state's mathritions are diffrent
		}
	}

	return 1; // same array in both state
}

//==========================================================================

void State8::printState()
{
	int row, col;

	for (row = 0; row<3; row++)
	{
		for(col= 0 ; col<3; col++)
		{
			if (this->arr[row][col] == 0)
				cout<<"\tE";
			else
				cout<<"\t"<<this->arr[row][col];
		}
		cout<<endl;
	}
}

//===========================================================================

State8::~State8()
{
	int i;
	for (i=0;i<3;i++)
		delete this->arr[i];
	delete this->arr;
}