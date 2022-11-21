#include <bits/stdc++.h>
using namespace std;

// Process Control Block
struct PCB
{
    int jobid;
    int TTL;
    int TLL;
    int TTC;
    int LLC;
} pcb;

class program
{
    char M[300][4];
    char IR[4];
    char R[4];
    int PTR[4];
    int IC, SI, TI, PI;
    char buffer[40];
    bool isAllocated[30];
    bool C;
    int flag;
    int EM;
    int RA;
    int ptc; // 0-9

public:
    void init();
    void load();
    int getloc();
    void startExecution();
    void executeUserProgram();
    void MOS();
    void read();
    void write();           // correct
    void terminate(int EM); // correct
    int addressMap(int VA); // correct
    int allocate();         // correct
    fstream Input;
    fstream Output;
};

void program::init()
{
    cout << "INIT()" << endl
         << endl;

    srand(time(0)); // c
    ptc = 0;        // counter for page table

    for (int i = 0; i < 300; i++) // c
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }

    C = false;

    IR[4] = {' '};

    R[4] = {' '};

    PTR[4] = {-1}; // c

    EM = 0;  // c
    RA = -1; // c
    TI = 0;  // c
    SI = 3;  // c
    PI = 0;  // c

    for (int i = 0; i < 30; i++) // CHANGES
    {
        isAllocated[i] = false;
    }

    // creating a PCB object and initializing the values

    // jobid
    pcb.jobid = ((buffer[4] - '0') * 1000) + ((buffer[5] - '0') * 100) + ((buffer[6] - '0') * 10) + (buffer[7] - '0');

    // TTL
    pcb.TTL = ((buffer[8] - '0') * 1000) + ((buffer[9] - '0') * 100) + ((buffer[10] - '0') * 10) + (buffer[11] - '0');

    // TLL
    pcb.TLL = ((buffer[12] - '0') * 1000) + ((buffer[13] - '0') * 100) + ((buffer[14] - '0') * 10) + (buffer[15] - '0');

    // TTC
    pcb.TTC = 0;

    // TLC
    pcb.LLC = 0;

    // printing the PCB
    cout << "\nPCB: " << endl;
    cout << "jobid:\t" << pcb.jobid << endl;
    cout << "TTL:\t" << pcb.TTL << endl;
    cout << "TLL:\t" << pcb.TLL << endl;
    cout << "TTC:\t" << pcb.TTC << endl;
    cout << "LLC:\t" << pcb.LLC << endl
         << endl;
}

int program::getloc()
{
    cout << "GETLOC()" << endl
         << endl;

    int mem = ((IR[2] - '0') * 10) + (IR[3] - '0');
    return mem;
}

int program::allocate()
{
    cout << "ALLOCATE()" << endl
         << endl;

    int block = rand() % 30;

    while (isAllocated[block])
    {
        block = rand() % 30;
    }

    cout << "BLOCK: " << block << endl;
    return block;
}

void program::load()
{

    cout << "LOAD()" << endl
         << endl;
    if (Input.eof())
    {
        exit(0);
    }
    while (!Input.eof())
    {
        // initialising buffer
        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        // reading from input file line by line
        Input.getline(buffer, 41);

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            cout << "$AMJ" << endl
                 << endl;

            init();
            flag = 0;
            // c
            // generating PTR
            Output << "------jobID: " << pcb.jobid << " initiated------\n\n";
            int ptr = allocate() * 10;

            // allocating PTR
            PTR[0] = ptr / 1000;
            PTR[1] = (ptr / 100) % 10;
            PTR[2] = (ptr / 10) % 10;
            PTR[3] = ptr % 10;
            cout << "PTR: " << ptr << endl;

            // initializing page table
            for (int i = ptr; i < ptr + 10; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[i][j] = '*';
                }
            }

            isAllocated[ptr / 10] = true; // CHANGES
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            cout << "$DTA" << endl
                 << endl;

            startExecution();
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            flag = 1;
            cout << "$END" << endl
                 << endl;
            int x = 0;
            for (int i = 0; i < 300; i++)
            {
                cout << "M" << x << ": " << M[i][0] << M[i][1] << M[i][2] << M[i][3] << endl;
                x++;
            }

            // printing the PCB
            cout << "\nPCB: " << endl;
            cout << "jobid:\t" << pcb.jobid << endl;
            cout << "TTL:\t" << pcb.TTL << endl;
            cout << "TLL:\t" << pcb.TLL << endl;
            cout << "TTC:\t" << pcb.TTC << endl;
            cout << "LLC:\t" << pcb.LLC << endl
                 << endl;

            Output << "\nPCB: " << endl;
            Output << "jobid:\t" << pcb.jobid << endl;
            Output << "TTL:\t" << pcb.TTL << endl;
            Output << "TLL:\t" << pcb.TLL << endl;
            Output << "TTC:\t" << pcb.TTC << endl;
            Output << "LLC:\t" << pcb.LLC << endl
                   << endl;

            cout << "---job ID: " << pcb.jobid << " ENDED!!---" << endl
                 << endl;
            Output << "---job ID: " << pcb.jobid << " ENDED!!---" << endl
                   << endl;

            init();
            break;
        }
        else
        {
            if (flag == 0)
            {
                // reading from the program card
                cout << "READING FROM THE PROGRAM CARD" << endl
                     << endl;

                // get frame for program page
                int block = allocate(); // returns block [0-29] //c
                cout << "block: " << block << endl;
                int loc = block * 10;
                cout << "loc: " << loc << endl;

                // updating page table

                int PTE = ((PTR[1] * 100) + (PTR[2] * 10) + PTR[3]) + ptc;
                isAllocated[block] = true; // CHANGES
                ptc++;                     // c
                cout << "PTE: " << PTE << endl;

                M[PTE][2] = (block / 10) + '0';

                M[PTE][3] = (block % 10) + '0';
                cout << "M[PTE] : " << M[PTE][2] << M[PTE][3] << endl;

                int k = 0;
                for (int i = loc; i < loc + 10; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        // error handling for when the OP_CODE is 'H'
                        if (buffer[k] == 'H')
                        {
                            M[i][j] = buffer[k];
                            k++;
                            break;
                        }
                        else
                        {
                            M[i][j] = buffer[k];
                            k++;
                        }
                    }

                    if (k == 40 || buffer[k] == ' ' || buffer[k] == '\0')
                    {
                        break;
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }

    cout << "END LOAD" << endl
         << endl;
}

void program::startExecution()
{
    cout << "STARTEXECUTION()" << endl
         << endl;
    IC = 00;
    executeUserProgram();
}

int program::addressMap(int VA)
{
    cout << "ADDRESSMAP()" << endl
         << endl;
    // checking for operand error
    if (VA < 0 || VA > 99)
    {
        PI = 2;
        MOS();
    }

    int PTE = (VA / 10) + ((PTR[1] * 100) + (PTR[2] * 10) + (PTR[3]));
    cout << "PTE :" << PTE << endl;

    RA = ((M[PTE][2] - '0') * 10 + (M[PTE][3] - '0')) * 10 + (VA % 10); // CHANGES
    cout << "VA :" << VA << endl;
    cout << "RA : " << RA << endl
         << endl;
    // -----PROBLEM HERE------
    // checking for page fault error
    if (!isAllocated[RA / 10]) // CHANGES
    {
        PI = 3;
        MOS();
    }

    return RA;
}

void program::executeUserProgram()
{
    cout << "EXECUTEUSERPROGRAM()" << endl
         << endl;
    while (PI == 0 && TI == 0)
    {

        RA = addressMap(IC);
        if (PI != 0)
        {
            break;
        }

        IR[0] = M[RA][0]; // CHANGES
        IR[1] = M[RA][1];
        IR[2] = M[RA][2];
        IR[3] = M[RA][3];
        IC++;

        if (IR[0] == 'H')
        {
            SI = 3;
            pcb.TTC++;
            MOS();
            break;
        }
        else
        {

            RA = addressMap(((IR[2] - '0') * 10 + (IR[3] - '0')));

            if (PI != 0)
            {
                break;
            }

            cout << "NO PI ERROR " << endl
                 << endl;
            if (IR[0] == 'P' && IR[1] == 'D')
            {
                SI = 2;
                MOS();
                pcb.TTC++;
            }
            else if (IR[0] == 'G' && IR[1] == 'D')
            {
                cout << "GD here" << endl
                     << endl;
                SI = 1;
                MOS();
            }
            else if (IR[0] == 'L' && IR[1] == 'R')
            {

                for (int i = 0; i < 4; i++)
                {
                    R[i] = M[RA][i];
                }

                pcb.TTC++;
            }
            else if (IR[0] == 'S' && IR[1] == 'R')
            {

                for (int i = 0; i < 4; i++)
                {
                    M[RA][i] = R[i];
                }

                pcb.TTC += 2;
            }
            else if (IR[0] == 'B' && IR[1] == 'T')
            {
                if (C)
                {
                    int loc = getloc();

                    IC = loc;
                }

                pcb.TTC++;
            }
            else if (IR[0] == 'C' && IR[1] == 'R')
            {

                if (R[0] == M[RA][0] && R[1] == M[RA][1] && R[2] == M[RA][2] && R[3] == M[RA][3])
                {
                    C = true;
                }
                else
                {
                    C = false;
                }

                pcb.TTC++;
            }
            else
            {
                PI = 1;
                MOS();
            }
        }

        // checking for TLE
        if (pcb.TTC > pcb.TTL)
        {
            TI = 2;
            MOS();
        }
    }
}

void program::MOS()
{
    cout << "MOS()" << endl
         << endl;
    // Output << "MOS() called....\n";
    // Output << "INTERRUPT VALUES:\n";
    // Output << "SI: " << SI <<endl;
    // Output << "PI: " << PI <<endl;
    // Output << "TI: " << TI <<endl << endl;

    // TI and PI
    if (TI == 0 && PI == 1)
    {
        terminate(4);
    }
    else if (TI == 0 && PI == 2)
    {
        terminate(5);
    }
    else if (TI == 0 && PI == 3)
    {

        // check if valid
        if (IR[0] == 'G' && IR[1] == 'D' || IR[0] == 'S' && IR[1] == 'R')
        {
            cout << "INSIDE MOS() : VALID PAGE FAULT" << endl;
            Output << "Error: VALID PAGE FAULT, REALLOCATING....\n";

            // ---PROBLEM HERE----
            int block = allocate();

            int PTE = ((PTR[1] * 100) + (PTR[2] * 10) + PTR[3]) + ptc;
            isAllocated[block] = true; // CHANGES
            ptc++;                     // c
            cout << "PTE: " << PTE << endl;

            M[PTE][2] = (block / 10) + '0';

            M[PTE][3] = (block % 10) + '0';
            cout << "M[PTE] : " << M[PTE][2] << M[PTE][3] << endl;

            IC--;
            PI = 0; // c

            // incrementing the TTC
            pcb.TTC++;
            executeUserProgram(); // CHANGES
            return;
        }
        else
        {
            terminate(6);
        }
    }
    else if (TI == 2 && PI == 1)
    {
        Output << "Operation Code Error" << endl;
        terminate(3);
    }
    else if (TI == 2 && PI == 2)
    {
        Output << "Operand Error" << endl;
        terminate(3);
    }
    else if (TI == 2 && PI == 3)
    {
        terminate(3);
    }

    // TI and SI
    if (TI == 0 && SI == 1)
    {
        read();
    }
    else if (TI == 0 && SI == 2)
    {
        write();
    }
    else if (TI == 0 && SI == 3)
    {
        terminate(0);
    }
    else if (TI == 2 && SI == 1)
    {
        terminate(3);
    }
    else if (TI == 2 && SI == 2)
    {
        write();
        terminate(3);
    }
    else if (TI == 2 && SI == 3)
    {
        terminate(0);
    }

    // PI = 0, SI = 0, TI = 0;
}

void program::read()
{
    cout << "READ()" << endl
         << endl;
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }
    // reading data from data card and putting it into buffer
    Input.getline(buffer, 41);

    if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
    {
        terminate(1); // c
    }

    // // reading OP_CODE from IR and converting it into int data type

    int k = 0;
    for (int l = RA; l < RA + 10; l++) // c
    {
        for (int j = 0; j < 4; j++)
        {
            M[l][j] = buffer[k];
            k++;
        }
    }
    // incrementing the TTC
    pcb.TTC++;
    // executeUserProgram();
    return;
}

void program::write()
{
    cout << "WRITE()" << endl
         << endl;
    // incrementing LLC
    pcb.LLC++; // c

    // checking for LLE
    if (pcb.LLC > pcb.TLL)
    { // c
        terminate(2);
    }

    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }

    // reading data from Memory and putting it into buffer
    int k = 0;
    for (int l = RA; l < RA + 10; l++) // c
    {
        for (int j = 0; j < 4; j++)
        {
            buffer[k] = M[l][j];
            k++;
        }
    }

    // printing buffer data to output.txt
    string output = "";
    for (int i = 0; i < 40; i++)
    {
        if (buffer[i] != '\0')
        {
            output += buffer[i];
        }
    }

    cout << "output: " << output << endl;

    Output << "Output: " << output;
    Output << "\n";
    SI = 0;
}

void program::terminate(int EM)
{
    if (flag == 0)
    {
        cout << "TERMINATE()" << endl
             << endl;
        // Output << "terminating....\n";
        if (EM == 0) // c
        {
            Output << "jobID: " << pcb.jobid << " No Error\n\n";
            cout << "jobID: " << pcb.jobid << " No Error\n";
        }
        else if (EM == 1)
        {
            Output << "jobID: " << pcb.jobid << " Out of Data\n\n";
            cout << "jobID: " << pcb.jobid << " Out of Data\n";

            Output << "\nPCB: " << endl;
            Output << "jobid:\t" << pcb.jobid << endl;
            Output << "TTL:\t" << pcb.TTL << endl;
            Output << "TLL:\t" << pcb.TLL << endl;
            Output << "TTC:\t" << pcb.TTC << endl;
            Output << "LLC:\t" << pcb.LLC << endl
                   << endl;
        }
        else if (EM == 2)
        {
            Output << "jobID: " << pcb.jobid << " Line Limit Exceeded\n\n";
            cout << "jobID: " << pcb.jobid << " Line Limit Exceeded\n";
        }
        else if (EM == 3)
        {
            Output << "jobID: " << pcb.jobid << " Time Limit Exceeded\n\n";
            cout << "jobID: " << pcb.jobid << " Time Limit Exceeded\n";
        }
        else if (EM == 4)
        {
            Output << "jobID: " << pcb.jobid << " Operation Code Error\n\n";
            cout << "jobID: " << pcb.jobid << " Operation Code Error\n";
        }
        else if (EM == 5)
        {
            Output << "jobID: " << pcb.jobid << " Operand Error\n\n";
            cout << "jobID: " << pcb.jobid << " Operand Error\n";
        }
        else if (EM == 6)
        {
            Output << "jobID: " << pcb.jobid << " Invalid Page Fault\n\n";
            cout << "jobID: " << pcb.jobid << " Invalid Page Fault\n";
        }
    }

    flag = 1;
    load();
    // return;
}

int main()
{

    cout << "MAIN()" << endl
         << endl;
    program prog;

    prog.Input.open("input.txt", ios::in);
    prog.Output.open("output.txt", ios::app);

    if (!prog.Input)
    {
        cout << "File cannot open\n";
    }
    else
    {
        cout << "File Exist \n";
    }
    prog.load();
    prog.Input.close();
    prog.Output.close();
    return 0;
}