#include <bits/stdc++.h>
using namespace std;

int CH[4] = {0, 5, 5, 2}; // 0th value is not used
map<int, string> EM;

ifstream Input;
ofstream Output;

int SI, PI, TI, IOI, TSC;
const int TS = 100;

// queues
queue<PCB> rq, ioq, lq, tq;
queue<char *> ebq, ifbq, ofbq;

// Interrupt routines
void IR1();
void IR2();
void IR3();

// utility functions
void move_buffer(queue<char *> &q1, queue<char *> &q2);
void move_pcb(queue<PCB> &q1, queue<PCB> &q2);

class PCB
{
public:
    int jobid, TTC, LLC, TTL, TLL;
    int P_track, N_PC, D_track, N_DC, O_track, N_OL;
    bool P, D;

    PCB()
    {
        jobid = ((ifbq.front()[4] - '0') * 1000) + ((ifbq.front()[5] - '0') * 100) + ((ifbq.front()[6] - '0') * 10) + (ifbq.front()[7] - '0');

        // TTL
        TTL = ((ifbq.front()[8] - '0') * 1000) + ((ifbq.front()[9] - '0') * 100) + ((ifbq.front()[10] - '0') * 10) + (ifbq.front()[11] - '0');

        // TLL
        TLL = ((ifbq.front()[12] - '0') * 1000) + ((ifbq.front()[13] - '0') * 100) + ((ifbq.front()[14] - '0') * 10) + (ifbq.front()[15] - '0');

        // TTC
        TTC = 0;

        // TLC
        LLC = 0;

        D, P = false;
        P_track = -1;
        N_PC = -1;
        D_track = -1;
        N_DC = -1;
        O_track = -1;
        N_OL = -1;
    }
}pcb; //unsure 

class program
{
public:
    char M[300][4];
    char IR[4];
    char R[4];
    int PTR[4];
    bool isAllocated[30];
    bool C;
    int IC;
    int RA;
    int ptc;
    int IC, SI, TI, PI;

    void init();
    int getloc();
    void startExecution(); // correct
    void executeUserProgram();
    int addressMap(int VA);
    int allocate();
    void terminate(vector<int> em);
    void displayPCB(PCB pcb);
    void MOS();
} prog;

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

    RA = -1;
    TI = 0;
    SI = 3;
    PI = 0;
    IOI = 1; // c

    for (int i = 0; i < 30; i++)
    {
        isAllocated[i] = false;
    }
}

int program::getloc()
{
    cout << "GETLOC()" << endl
         << endl;

    int mem = ((IR[2] - '0') * 10) + (IR[3] - '0');
    return mem;
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
    // checking for invalid page fault error
    if (!isAllocated[RA / 10])
    {
        PI = 3;
        MOS();
    }

    return RA;
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

void move_pcb(queue<PCB> &q1, queue<PCB> &q2)
{
    // q1->q2
    PCB pcb = q1.front();
    q1.pop();
    q2.push(pcb);
}

void move_buffer(queue<char *> &q1, queue<char *> &q2)
{

    // q1->q2
    char *buffer = q1.front();
    q1.pop();
    q2.push(buffer);
}

void displayPCB(PCB pcb)
{
    // printing the PCB
    cout << "\nPCB: " << endl;
    cout << "jobid:\t" << pcb.jobid << endl;
    cout << "TTL:\t" << pcb.TTL << endl;
    cout << "TLL:\t" << pcb.TLL << endl;
    cout << "TTC:\t" << pcb.TTC << endl;
    cout << "LLC:\t" << pcb.LLC << endl
         << endl;
    cout << "D:\t" << pcb.D << endl;
    cout << "P:\t" << pcb.P << endl;
    cout << "P_track:\t" << pcb.P_track << endl;
    cout << "N_PC:\t" << pcb.N_PC << endl;
    cout << "D_track:\t" << pcb.D_track << endl;
    cout << "N_DC:\t" << pcb.N_DC << endl;
    cout << "O_track:\t" << pcb.O_track << endl;
    cout << "N_OL:\t" << pcb.N_OL << endl;
}

void em_init()
{
    EM[0] = "No Error";
    EM[1] = "Out of Data";
    EM[2] = "Line Limit Exceeded";
    EM[3] = "Time Limit Exceeded";
    EM[4] = "Operation Code Error";
    EM[5] = "Operand Error";
    EM[6] = "Invalid Page Fault";
}

void program::terminate(vector<int> em)
{

    int n = em.size();
    Output << endl
           << endl;
    for (int i = 0; i < n; i++)
    {
        Output << EM[em[i]] << endl;
    }
}

void program::MOS()
{

    // TI and SI
    if ((TI == 0 | TI == 1) && (SI == 1))
    {
        move_pcb(rq, ioq);
        // read();
    }
    else if ((TI == 0 | TI == 1) && (SI == 2))
    {
        move_pcb(rq, ioq);
        // write();
    }
    else if ((TI == 0 | TI == 1) && (SI == 3))
    {
        move_pcb(rq, tq);
        terminate({0});
    }
    else if (TI == 2 && SI == 1)
    {
        move_pcb(rq, tq);
        terminate({3});
    }
    else if (TI == 2 && SI == 2)
    {
        move_pcb(rq, ioq);
        // write();
        move_pcb(ioq, tq);
        terminate({3});
    }
    else if (TI == 2 && SI == 3)
    {
        move_pcb(rq, tq);
        terminate({0});
    }

    // TI and PI
    if ((TI == 0 | TI == 1) && PI == 1)
    {
        move_pcb(rq, tq);
        terminate({4});
    }
    else if ((TI == 0 | TI == 1) && PI == 2)
    {
        move_pcb(rq, tq);
        terminate({5});
    }
    else if ((TI == 0 | TI == 1) && PI == 3)
    {
        // check if valid
        if (IR[0] == 'G' && IR[1] == 'D' || IR[0] == 'S' && IR[1] == 'R')
        {
            int block = allocate();

            int PTE = ((PTR[1] * 100) + (PTR[2] * 10) + PTR[3]) + ptc;
            isAllocated[block] = true;
            ptc++;
            M[PTE][2] = (block / 10) + '0';

            M[PTE][3] = (block % 10) + '0';

            IC--;
            pcb.TTC++;
        }
        else
        {
            move_pcb(rq, tq);
            terminate({0});
        }
    }
    else if (TI == 2 && PI == 1)
    {
        move_pcb(rq, tq);
        terminate({3, 4});
    }
    else if (TI == 2 && PI == 2)
    {
        move_pcb(rq, tq);
        terminate({3, 5});
    }
    else if (TI == 2 && PI == 3)
    {
        move_pcb(rq, tq);
        terminate({3});
    }

    // IOI
    if (IOI == 1)
    {
        IR1();
    }
    else if (IOI == 2)
    {
        IR2();
    }
    else if (IOI == 3)
    {
        IR2();
        IR1();
    }
    else if (IOI == 4)
    {
        IR3();
    }
    else if (IOI == 5)
    {
        IR1();
        IR3();
    }
    else if (IOI == 6)
    {
        IR3();
        IR2();
    }
    else if (IOI == 7)
    {
        IR2();
        IR1();
        IR3();
    }

    SI = 0, PI = 0, TI = 0, IOI = 1; // unsure
}

void IR1()
{
    // Read next card in given eb, change status to ifb, place on ifb (q)

    char *buffer = ebq.front();
    ebq.pop();

    // reading from input file line by line
    Input.getline(buffer, 41);
    ifbq.push(buffer);

    // If not e-o-f and eb(q) not empty
    if (!Input.eof() && ebq.empty() == false)
    {

        // Get next eb
        buffer = ebq.front();
        ebq.pop();

        // start Channel 1
        start_ch1();
    }

    // Examine ifbq
    if (ifbq.front()[0] == '$' && ifbq.front()[1] == 'A' && ifbq.front()[2] == 'M' && ifbq.front()[3] == 'J')
    {
        // Create and initialize PCB

        PCB pcb;
        displayPCB(pcb);
        prog.init();

        // Allocate frame for Page Table
        //  generating PTR
        Output << "------jobID: " << pcb.jobid << " initiated------\n\n";
        int ptr = prog.allocate() * 10;

        // allocating PTR
        prog.PTR[0] = ptr / 1000;
        prog.PTR[1] = (ptr / 100) % 10;
        prog.PTR[2] = (ptr / 10) % 10;
        prog.PTR[3] = ptr % 10;
        cout << "PTR: " << ptr << endl;

        // Initialize Page Table and PTR
        for (int i = ptr; i < ptr + 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                prog.M[i][j] = '*';
            }
        }

        prog.isAllocated[ptr / 10] = true;

        // Set F <- P (Program cards to follow)
        pcb.P = true;

        // Change Status from ifb to eb
        char *buffer1 = ifbq.front();

        ifbq.pop();

        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        // Return buffer to eb(q)
        ebq.push(buffer1);
    }
    else if (ifbq.front()[0] == '$' && ifbq.front()[1] == 'D' && ifbq.front()[2] == 'T' && ifbq.front()[3] == 'A')
    {
        // Change Status from ifb to eb
        char *buffer1 = ifbq.front();

        ifbq.pop();

        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        // Return buffer to eb(q)
        ebq.push(buffer1);
    }
    else if (ifbq.front()[0] == '$' && ifbq.front()[1] == 'E' && ifbq.front()[2] == 'N' && ifbq.front()[3] == 'D'){
        
        //Place PCB on LQ
        lq.push(pcb); //unsure

        // Change Status from ifb to eb
        char *buffer1 = ifbq.front();

        ifbq.pop();

        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        // Return buffer to eb(q)
        ebq.push(buffer1);

    }
    else{
        
    }
}

void IR2()
{
    // Print given ofb, change status from ofb to eb

    char *buffer = ofbq.front();
    ofbq.pop();
    string output = "";
    for (int i = 0; i < 40; i++)
    {
        output += buffer[i];
    }

    // initializing the buffer
    Output << output << endl;
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }

    // Return buffer to eb(q)
    ebq.push(buffer);

    // If ofb(q) not empty,
    if (ofbq.empty() == false)
    {

        // Get next ofb
        buffer = ofbq.front();
        ofbq.pop();

        // start Channel 2
        start_ch2();
    }
}

class super_mem
{

public:
    // int cebq, cifbq, cofbq; // counters for queues

    super_mem()
    {
        // cebq = 10;
        // cifbq = 0;
        // cofbq = 0;

        for (int i = 0; i < 10; i++)
        {
            char buffer[40];

            for (int j = 0; j < 40; j++)
            {
                buffer[j] = '\0';
            }

            ebq.push(buffer);
        }
    }

} super;

class CH1
{
public:
    bool flag;
    int timer;

    CH1()
    {
        flag = false;
        timer = 0;
    }
} ch1;

class CH2
{
public:
    bool flag;
    int timer;

    CH2()
    {
        flag = false;
        timer = 0;
    }
} ch2;

class CH3
{
public:
    bool flag;
    int timer;

    CH3()
    {
        flag = false;
        timer = 0;
    }
} ch3;

void start_ch1()
{
    IOI -= 1;
    ch1.timer = 0;
    ch1.flag = true;
}

void start_ch2()
{
    IOI -= 2;
    ch2.timer = 0;
    ch2.flag = true;
}

void ch3_start()
{
    IOI -= 4;
    ch3.timer = 0;
    ch3.flag = true;
}

void simulation()
{

    // incrementing TTC
    pcb.TTC++;

    if (pcb.TTC == pcb.TTL)
    {
        TI = 2;
    }

    // incrementing TSC
    TSC++;

    if (TSC == TS)
    {
        TI = 1;
    }

    if (ch1.flag = true)
    {
        ch1.timer++;

        if (ch1.timer == CH[1])
        {
            IOI += 1;
        }
    }

    if (ch2.flag = true)
    {
        ch2.timer++;

        if (ch2.timer == CH[1])
        {
            IOI += 2;
        }
    }

    if (ch3.flag = true)
    {
        ch3.timer++;

        if (ch3.timer == CH[1])
        {
            IOI += 4;
        }
    }

    // checking for interrupts
    if (SI != 0 || PI != 0 || TI != 0 || IOI != 0)
    {
        MOS();
    }
}

int main()
{

    Input.open("input.txt", ios::in);
    Output.open("output.txt", ios::app);

    if (!Input)
    {
        cout << "File cannot open\n";
    }
    else
    {
        cout << "File Exist \n";
    }
    em_init();
    prog.load();
    Input.close();
    Output.close();

    return 0;
}