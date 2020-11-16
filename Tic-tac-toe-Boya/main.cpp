#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

enum players { Computer, Human, Draw, None };     //��� 
const int iWin[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };
//����Ӯ����� 

//������Ϸ�� 
class ttt
{
public:
    ttt()            //�޲ι��캯�� 
    {
        _p = rand() % 2;          //�����ߣ����˳�� 
        reset();              //���� 
    }
    void play()               
    {
        int res = Draw;             //drawΪ2 
        while( true )
        {
            drawGrid();              //���ú��������������� 
            while( true )
            {
                if( _p ) getHumanMove();       //_pΪ1������ ���������ߺ��� 
    
                else getComputerMove();          //�����ߡ��������ߺ��� 
      
                drawGrid();                    //��������֮�󻭳����� 
    
                res = checkVictory();          //û����Ӯ��������None����3 
                
                if( res != None )          //���ж���Ӯ 
                    break;                   //����ѭ�� 
  
                ++_p %= 2;              //û���ж���Ӯ�����ж���һ��˭�� 
            }
    
            if( res == Human )             //�ж���Ӯ 
                cout << "CONGRATULATIONS HUMAN --- You won!";
 
            else if( res == Computer )
                cout << "NOT SO MUCH A SURPRISE --- I won!";
      
            else
                cout << "It's a draw!";

            cout << endl << endl;

            string r;
            cout << "Play again( Y / N )? ";
            cin >> r;                               //�ж��Ƿ�����һ�� 
            if( r != "Y" && r != "y" )
                return;
                
            ++_p %= 2;
            reset();         //���ú��������������״̬ 
        }
    }

private:
    
    void reset()
    {
        for( int x = 0; x < 9; x++ )
            _field[x] = None;            //���ú��������������̵����飬ȫ����None 
    }

    void drawGrid()                //�����̺��� ������������������ 
    {
	
        system( "cls" );			//���� 	
		
		COORD c = { 0, 2 };		//�������̨��Ļ��ʼ���� ������һ�������x��y 
        
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );		//�������λ���趨 
        							//�����ʼ���� 
        cout << " 1 | 2 | 3 " << endl;
        cout << "---+---+---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---+---+---" << endl;
        cout << " 7 | 8 | 9 " << endl << endl << endl;
        
        int f = 0;   //���Ӽ���
        for( short y = 0; y < 5; y += 2 ) //������ 
            for( short x = 1; x < 11; x += 4 ) //������ ��һ��11�� 
            {
                
                if( _field[f] != None )               //������ 
                {

                    COORD c = { x, 2 + y };               //�����Ϊ��ǰ����x��y�����λ�� 
                
                    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );//������Ķ���i֮�趨 
            
                    string o = _field[f] == Computer ? "X" : "O";    //�ж��������Ƿ�Ϊ���ԡ�������X������0
					 
                    cout << o;      //���o������X����O�� �������Ǹ�λ�������������ԭ�� 
                }
                //���Ӹ���+1 
                f++;
            }

        c.Y = 9;       //���yΪ9 
 
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );    //���ÿ���̨���λ�� 
    }
     
    int checkVictory()          //�ж���Ӯ�ĺ��� 
    {
        for( int i = 0; i < 8; i++ )      //����ÿһ��Ӯ�� 
        {
            if( _field[iWin[i][0]] != None &&        //�����������¹���������λ�ö�Ϊͬһ�����µ� 
                    _field[iWin[i][0]] == _field[iWin[i][1]] && _field[iWin[i][1]] == _field[iWin[i][2]] )    //��������һ�����   
            {
                return _field[iWin[i][0]];       //����Ӯ�����˻��ǵ��� 
            }
        }
        
    //����Ӯ
        int i = 0;                      //���㵱ǰ���µ����Ӹ��� 
        for( int f = 0; f < 9; f++ )    
        {                              
            if( _field[f] != None )		
                i++;
        }
       
       if( i == 9 )               //���Ӹ���Ϊ9�� ����ƽ�� 
           return Draw;
            
        return None;            //��Ȼ��������һ�� 
    }

    void getHumanMove()           //�������庯�� 
    {
        int m;
		//int n;
        cout << "Enter your move ( 1 - 9 ) ";
    
        while( true )
        {
            m = 0;
            cin >> m;      //�������� 

            if( _field[m - 1] != None )                         //�������� 
                cout << "Invalid move. Try again!" << endl;

            else                         //��ȷ����-�˳�ѭ�� 
                break;
        }
									//��Ǹղ��µĵ� 
        _field[m - 1] = Human;      //HumanΪ1����ʾ�����¹� 
    }

    void getComputerMove()
    {
        int move = 0;       
        do
        {  
            move = rand() % 9;      //���ȡһ������ 
        }
        
        while( _field[move] != None );    //�����¹������������ 
//û���¹� 
        for( int i = 0; i < 8; i++ )
        {
            int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];  //����ÿһ��Ӯ�� 
            
            if( _field[try1] != None && _field[try1] == _field[try2] && _field[try3] == None )     
						//�и���ҵ�����Ӯ��������һ�� 
            {
                move = try3;                 //�µ�����    
                if( _field[try1] == Computer )              //�������computer�µģ����˳�ѭ�� 
                    break;
            }
                      //��һ����ڶ���Ӯ�����µڶ��� 
            if( _field[try1] != None && _field[try1] == _field[try3] && _field[try2] == None )
            {         
                move = try2;
                if( _field[try1] == Computer )
                    break;
            }
            //���һ��Ӯ���µ�һ�� 
            if( _field[try2] != None && _field[try2] == _field[try3] && _field[try1] == None )
            {
                move = try1;             
                if( _field[try2] == Computer )
                    break;
            }
        }
        _field[move] = Computer;     //�����һ��Ϊcomputer 
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
