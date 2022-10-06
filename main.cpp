#include <bits/stdc++.h>
using namespace std;

class program
{
    char M[100][4];
    char IR[4];
    char R[4];
    int IC, SI;
    char buffer[40];
    bool C = false;

public:
    void init();
    void load();
    void startExecution();
    void executeUserProgram();
    void MOS();
    void read();
    void write();
    void terminate();
    fstream Input;
    fstream Output;
};

void program::init()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }

    IR[4] = {' '};
    R[4] = {' '};
}

void program::load()
{
    int m =0;
    do
    {
        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }
        Input.getline(buffer, 40);
        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            startExecution();
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            break;
        }
        else
        {
            int k = 0;
            for (; m < 100; m++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[m][j] = buffer[k];
                    k++;
                }
                if (k == 40 || buffer[k] == ' ' || buffer[k] == '\0')
                {
                    break;
                }
            }
        }
    } while (!Input.eof());

    int x = 0;
    for (int i = 0; i < 100; i++)
    {       //printing all memory from 00-99
            cout << "M" << x << ":" << M[i][0] << M[i][1] << M[i][2] << M[i][3] << endl;
            x++;
    }
}

void program::startExecution()
{
    IC = 00;
    executeUserProgram();
}

void program::executeUserProgram()
{
    while(IC<10){

        //reading next instruction
        IR[0]=M[IC][0];
        IR[1]=M[IC][1];
        IR[2]=M[IC][2];
        IR[3]=M[IC][3];


        IC++;


        if(IR[0]=='P'){
            SI=2;
            MOS();
        }
        else if(IR[0]=='G'){
            SI=1;
            MOS();
        }
        else if(IR[0]=='L'){

        }
        else if(IR[0]=='S'){
            
        }
        else if(IR[0]=='B'){
            
        }
        else if(IR[0]=='C'){
            
        }
        else if(IR[0]=='H'){
            SI=3;
            MOS();
        }
    }
}

void program::MOS(){
    switch(SI){
        case 1:
            read();
            break;
        case 2:
            write();
            break;
        case 3:
            terminate();
            break;
        default:
            break;
    }
}

void program::read(){
  
    //reading data from data card and putting it into buffer
    Input.getline(buffer, 40);

    //reading OP_CODE from IR and converting it into int data type
    char op_code[2];
    op_code[0] = IR[2];
    op_code[1] = IR[3];

    //mem has the op_code
    int mem = atoi(op_code);    
    
    int k = 0;
            for (int m = mem ; m < mem + 10; m++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[m][j] = buffer[k];
                    k++;
                }
            }

}

void program::write(){
    cout << "write\n";
}
void program::terminate(){
    cout << "terminate\n";
}

int main()
{

    program prog;

    prog.Input.open("input.txt", ios::in);
    if (!prog.Input)
    {
        cout << "File cannot open\n";
    }
    else
    {
        cout << "File Exist \n";
    }
    prog.load();
    return 0;
}