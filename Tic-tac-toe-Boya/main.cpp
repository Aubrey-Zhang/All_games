#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

enum players { Computer, Human, Draw, None };     //编号 
const int iWin[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };
//可能赢的情况 

//定义游戏类 
class ttt
{
public:
    ttt()            //无参构造函数 
    {
        _p = rand() % 2;          //轮流走，随机顺序 
        reset();              //重置 
    }
    void play()               
    {
        int res = Draw;             //draw为2 
        while( true )
        {
            drawGrid();              //调用函数——给出棋盘 
            while( true )
            {
                if( _p ) getHumanMove();       //_p为1，人走 ，调用人走函数 
    
                else getComputerMove();          //电脑走——电脑走函数 
      
                drawGrid();                    //走完两步之后画出棋盘 
    
                res = checkVictory();          //没有人赢——返回None，即3 
                
                if( res != None )          //能判断输赢 
                    break;                   //跳出循环 
  
                ++_p %= 2;              //没有判断输赢——判断下一步谁走 
            }
    
            if( res == Human )             //判断输赢 
                cout << "CONGRATULATIONS HUMAN --- You won!";
 
            else if( res == Computer )
                cout << "NOT SO MUCH A SURPRISE --- I won!";
      
            else
                cout << "It's a draw!";

            cout << endl << endl;

            string r;
            cout << "Play again( Y / N )? ";
            cin >> r;                               //判断是否再来一局 
            if( r != "Y" && r != "y" )
                return;
                
            ++_p %= 2;
            reset();         //调用函数——重置棋局状态 
        }
    }

private:
    
    void reset()
    {
        for( int x = 0; x < 9; x++ )
            _field[x] = None;            //重置函数——保存棋盘的数组，全部置None 
    }

    void drawGrid()                //画棋盘函数 ——清屏——画棋盘 
    {
	
        system( "cls" );			//清屏 	
		
		COORD c = { 0, 2 };		//定义控制台屏幕初始坐标 ——第一个输出在x，y 
        
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );		//输出光标的位置设定 
        							//输出初始棋盘 
        cout << " 1 | 2 | 3 " << endl;
        cout << "---+---+---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---+---+---" << endl;
        cout << " 7 | 8 | 9 " << endl << endl << endl;
        
        int f = 0;   //棋子计数
        for( short y = 0; y < 5; y += 2 ) //纵坐标 
            for( short x = 1; x < 11; x += 4 ) //横坐标 ，一共11个 
            {
                
                if( _field[f] != None )               //有棋子 
                {

                    COORD c = { x, 2 + y };               //光标设为当前棋盘x，y的相对位置 
                
                    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );//输出光标的额外i之设定 
            
                    string o = _field[f] == Computer ? "X" : "O";    //判断下棋人是否为电脑——是则X，否则0
					 
                    cout << o;      //输出o——“X”或“O” ——在那个位置输出——覆盖原先 
                }
                //棋子个数+1 
                f++;
            }

        c.Y = 9;       //光标y为9 
 
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );    //设置控制台光标位置 
    }
     
    int checkVictory()          //判断输赢的函数 
    {
        for( int i = 0; i < 8; i++ )      //遍历每一种赢法 
        {
            if( _field[iWin[i][0]] != None &&        //该棋子有人下过，且三个位置都为同一个人下的 
                    _field[iWin[i][0]] == _field[iWin[i][1]] && _field[iWin[i][1]] == _field[iWin[i][2]] )    //符合其中一种情况   
            {
                return _field[iWin[i][0]];       //返回赢得是人还是电脑 
            }
        }
        
    //无人赢
        int i = 0;                      //计算当前已下的棋子个数 
        for( int f = 0; f < 9; f++ )    
        {                              
            if( _field[f] != None )		
                i++;
        }
       
       if( i == 9 )               //棋子个数为9个 ——平局 
           return Draw;
            
        return None;            //不然继续下下一个 
    }

    void getHumanMove()           //人类下棋函数 
    {
        int m;
		//int n;
        cout << "Enter your move ( 1 - 9 ) ";
    
        while( true )
        {
            m = 0;
            cin >> m;      //人类输入 

            if( _field[m - 1] != None )                         //已有棋子 
                cout << "Invalid move. Try again!" << endl;

            else                         //正确下棋-退出循环 
                break;
        }
									//标记刚才下的点 
        _field[m - 1] = Human;      //Human为1，表示人类下过 
    }

    void getComputerMove()
    {
        int move = 0;       
        do
        {  
            move = rand() % 9;      //随机取一个点下 
        }
        
        while( _field[move] != None );    //有人下过——继续随机 
//没人下过 
        for( int i = 0; i < 8; i++ )
        {
            int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];  //遍历每一种赢法 
            
            if( _field[try1] != None && _field[try1] == _field[try2] && _field[try3] == None )     
						//有个玩家第三步赢，就下那一步 
            {
                move = try3;                 //下第三步    
                if( _field[try1] == Computer )              //如果那是computer下的，则退出循环 
                    break;
            }
                      //有一个差第二步赢，就下第二步 
            if( _field[try1] != None && _field[try1] == _field[try3] && _field[try2] == None )
            {         
                move = try2;
                if( _field[try1] == Computer )
                    break;
            }
            //差第一步赢，下第一步 
            if( _field[try2] != None && _field[try2] == _field[try3] && _field[try1] == None )
            {
                move = try1;             
                if( _field[try2] == Computer )
                    break;
            }
        }
        _field[move] = Computer;     //标记那一步为computer 
    }


    int _p;

    int _field[9];
};

int main()
{

    srand( GetTickCount() );        //

    ttt tic;          //

    tic.play();

    return 0;
}
