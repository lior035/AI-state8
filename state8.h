#ifndef STATE8_H
#define STATE8_H

class State8
{
	//object components

	int** arr ; //Demonstrat the state as a mathrizion
	int i, j; //index to the empty space

	//values of the f(n) g(n) and h(n)
	int fVal;
	int gVal;
	int hVal;

	void computeHn (State8* goal);//h(n) from goal - using manhatten mathod
	void computeFn (); // using the g(n) and h(n) of the cureent state to compute f(n)

public:

	State8 (int ** arr = NULL) ; //constructor

	int compareStates(State8 * s); // comparing method between to states
	
	State8** createSonsState (int * numOfSons, State8* goal); // givinig all the state available from the current state (influenced by the blank space), and returns the num of state created
								                // note that - maximum sons will be 4


	//update methodes of g(n) and h(n) of the current state
	void updateGn (State8* s); //increase g(n) of state by one  - TO BE USED ONLY ONCE AT A STATE
	int giveGn ();

	void updateFn ();
	int giveFn (); //gives methods to extract f(n) of the state

	void updateHn (State8* goal); //update the h(n) val of this state
	int computeDis(State8* goal,int k,int m,int num);
	int giveHn();
	

	void createMat(State8 * curr);
	void copyMat (State8 * curr, int ** arr);
	void printState();//printing the state

	~State8();

};

#endif