#include <iostream>
#include <fstream>
using namespace std;
#include <cstdlib>
#include <typeinfo.h>


#include "state8.h"

void main()
{
	int num = 0;
	State8** sons;
	State8** sons0;

	cout<<"Enter start state: "<<endl;
	State8 * s = new State8();
	cout<<"Enter goal state: "<<endl;
	State8 * goal = new State8();

	cout<<"start state:"<<endl;
	s->printState();
	cout<<"goal state:"<<endl;
	goal->printState();

	//int i = s->compareStates(goal);
	sons = s->createSonsState(&num, goal);
	
	/*if (i==0)
		cout<<"false"<<endl;
	else
		cout<<"true"<<endl;
		*/

	cout<<"Num of sons: "<<num<<endl;
	for (int i=0; i<num; i++)
	{
		cout<<"son state number: "<<i+1<<endl;
		sons[i]->printState();
		cout<<"g(n): " <<sons[i]->giveGn()<<"\t h(n): "<<sons[i]->giveHn()<<"\t f(n): "<<sons[i]->giveFn()<<endl;
	}

	num = 0;
	sons0 = sons[0]->createSonsState(&num, goal);

	cout<<"sons of son number"<<0<<endl;
	for (int i=0; i<num; i++)
	{
		cout<<"son state number: "<<i+1<<endl;
		sons0[i]->printState();
		cout<<"g(n): " <<sons0[i]->giveGn()<<"\t h(n): "<<sons0[i]->giveHn()<<"\t f(n): "<<sons0[i]->giveFn()<<endl;
	}

	for (int i=0; i<num; i++)
	{
		delete sons0[i];
	}
	delete sons0;
}