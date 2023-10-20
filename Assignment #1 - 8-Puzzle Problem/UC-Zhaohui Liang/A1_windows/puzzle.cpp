#include "puzzle.h"
#include  <cmath>
#include  <assert.h>

using namespace std;


//////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(const Puzzle &p) : path(p.path){
	
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = p.board[i][j];
		    goalBoard[i][j] = p.goalBoard[i][j];
		}
	}	
	
	x0 = p.x0;
	y0 = p.y0;
	//path = p.path;
	pathLength = p.pathLength;
	hCost = p.hCost;
	fCost = p.fCost;	
	strBoard = toString(); //uses the board contents to generate the string equivalent
	depth = p.depth;
	
}

//////////////////////////////////////////////////////////////
//constructor
//inputs:  initial state, goal state
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(string const elements, string const goal){
	
	int n;
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = elements[n] - '0';
		    if(board[i][j] == 0){
			    x0 = j;
			    y0 = i;
			 }
		    n++;
		} 
	}
		
	///////////////////////
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    goalBoard[i][j] = goal[n] - '0';
		    n++;
		} 
	}		
	///////////////////////	
	path = "";
	pathLength=0;
	hCost = 0;
	fCost = 0;
	depth = 0;
	strBoard = toString();	
}


void Puzzle::setDepth(int d){
	depth = d;
}

int Puzzle::getDepth() const {
	return depth;
}

void Puzzle::updateHCost(heuristicFunction hFunction){
	hCost = h(hFunction);
}

void Puzzle::updateFCost(){
	//fCost = ?
}

int Puzzle::getFCost()const{
	return fCost;
}

int Puzzle::getHCost(){
	return hCost;
}

int Puzzle::getGCost()const{
	return pathLength;
}

//Heuristic function implementation
int Puzzle::h(heuristicFunction hFunction){
	
	int sum=0;
	int h=0;
	int numOfMisplacedTiles=0;
	
	switch(hFunction){
		case misplacedTiles:			      
				//place your implementation here	
                h = numOfMisplacedTiles; 					
		        break;
		         
		case manhattanDistance:
		        //place your implementation here
		        
		        h = sum; 					
		        break;         
		           
	};
	
	return h;
	
}


//converts board state into its string representation
string Puzzle::toString(){
  int n;
  string stringPath;
  
  n=0;
  for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){			    
		    stringPath.insert(stringPath.end(), board[i][j] + '0');
		    n++;
		} 
  }
  
//  cout << "toString = " << stringPath << endl;
  
  return stringPath;
}


bool Puzzle::goalMatch() const{
	bool result=false;
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         if (board[i][j] != goalBoard[i][j]) {
            return result; // 有一个方格不匹配，返回false
         }
      }
   }
   return true; // 所有方格匹配，返回true，表示达到目标状态
}


bool Puzzle::canMoveLeft()const{
   return (x0 > 0);
	
}

const string Puzzle::getPath()const{
	return path;
}

bool Puzzle::canMoveRight()const{

   return (x0 < 2);
	
}


bool Puzzle::canMoveUp()const{

   return (y0 > 0);
	
}

bool Puzzle::canMoveDown()const{

   return (y0 < 2);
	
}

///////////////////////////////////////////////
//these functions will be useful for Progressive Deepening Search 

bool Puzzle::canMoveLeft(int maxDepth){
  	
  	bool m=false;
  	//put your implementations here
  	if (x0 > 0 && depth + 1 <= maxDepth) {
  				m=true;
            return m;
        }
  	return m; 
}
bool Puzzle::canMoveRight(int maxDepth){
   
  	bool m=false;
  	//put your implementations here
  	if (x0 < 2 && depth + 1 <= maxDepth) {
  				m=true;
            return m;
        }
  	return m; 
}


bool Puzzle::canMoveUp(int maxDepth){
   
  	bool m=false;
  	//put your implementations here
  	if (y0 > 0 && depth + 1 <= maxDepth) {
  				m=true;
            return m;
        }
  	return m; 
}

bool Puzzle::canMoveDown(int maxDepth){
   
  	bool m=false;
  	//put your implementations here
  	if (y0 < 2 && depth + 1 <= maxDepth) {
  				m=true;
            return m;
        }
  	return m; 
}



///////////////////////////////////////////////

Puzzle *Puzzle::moveLeft()const{
	
	Puzzle *p = new Puzzle(*this);
	
	
   if(x0 > 0){
		
		p->board[y0][x0] = p->board[y0][x0-1];
		p->board[y0][x0-1] = 0;
		
		p->x0--;
		
		p->path = path + "L";
		p->pathLength = pathLength + 1;  
		p->depth = depth + 1; 
		
		
	}
	p->strBoard = p->toString();

	return p;
	
}


Puzzle *Puzzle::moveRight()const{
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(x0 < 2){
		
		p->board[y0][x0] = p->board[y0][x0+1];
		p->board[y0][x0+1] = 0;
		
		p->x0++;
		
		p->path = path + "R";
		p->pathLength = pathLength + 1; 
     	
		p->depth = depth + 1;
		
	}
	
	p->strBoard = p->toString();
	
	return p;
	
}


Puzzle *Puzzle::moveUp()const{
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 > 0){
		
		p->board[y0][x0] = p->board[y0-1][x0];
		p->board[y0-1][x0] = 0;
		
		p->y0--;
		
		p->path = path + "U";
		p->pathLength = pathLength + 1;  
	
		p->depth = depth + 1;
		
	}
	p->strBoard = p->toString();
	
	return p;
	
}

Puzzle *Puzzle::moveDown()const{
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 < 2){
		
		p->board[y0][x0] = p->board[y0+1][x0];
		p->board[y0+1][x0] = 0;
		
		p->y0++;
		
		p->path = path + "D";
		p->pathLength = pathLength + 1;  
		
		p->depth = depth + 1;
		
	}
	p->strBoard = p->toString();	
	
	return p;
	
}
/////////////////////////////////////////////////////


void Puzzle::printBoard(){
	cout << "board: "<< endl;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		  cout << endl << "board[" << i << "][" << j << "] = " << board[i][j];
		}
	}
	cout << endl;
	
}

int Puzzle::getPathLength(){
	return pathLength;
}
