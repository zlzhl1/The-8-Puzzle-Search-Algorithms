#ifndef PUZZLE_H
#define PUZZLE_H
#include <string>
#include <iostream>

using namespace std;


enum heuristicFunction{misplacedTiles, manhattanDistance};


class Puzzle{
        
private:

    string path="";
    int pathLength;
    int hCost;
    int fCost;
    int depth; 
        
    int goalBoard[3][3];
    
    int x0, y0; //coordinates of the blank or 0-tile
    
    int board[3][3];
    
public:
    
    string strBoard;
     
    Puzzle(const Puzzle &p); //Constructor
    Puzzle(string const elements, string const goal);
    int getGCost() const;
    void printBoard();
    
    int h(heuristicFunction hFunction);   
    void updateFCost(); 
    void updateHCost(heuristicFunction hFunction);
    void updateDepth(){
         depth++;
    }        
          
     
    bool goalMatch()const;
     string toString();
    
    string getString()const {
        return strBoard;
     }
    
    bool canMoveLeft()const;
    bool canMoveRight()const;
    bool canMoveUp()const;
    bool canMoveDown()const;  

//----------------------------------------
//these functions will be useful for Progressive Deepening Search    
     bool canMoveLeft(int maxDepth);
     bool canMoveDown(int maxDepth);
     bool canMoveRight(int maxDepth);
     bool canMoveUp(int maxDepth);   
//----------------------------------------
      
    Puzzle * moveUp()const;
    Puzzle * moveRight()const;
    Puzzle * moveDown()const;
    Puzzle * moveLeft()const;
     
     
    const string getPath()const;
    
    void setDepth(int d);
    int getDepth() const;
    
    int getPathLength();
    int getFCost()const;
    int getHCost();
    // 在 Puzzle 类中添加 operator> 比较运算符
struct PuzzleComparator {
    bool operator()(const Puzzle& p1, const Puzzle& p2) const {
        return p1.getGCost() > p2.getGCost();
    }
};
    bool operator<(const Puzzle& other) const {
        // 根据需要定义比较逻辑，例如，比较两个 Puzzle 对象的某个属性
        // 这里使用示例逻辑，比较 Puzzle 对象的路径长度
        return path.size() < other.path.size();
    }


};
#endif // PUZZLE_H