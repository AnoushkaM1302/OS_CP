#include <bits/stdc++.h>
using namespace std;
class PCB{
    public:
    int a1,a2;
    PCB(){
        a1 = 1;
        a2 = 2;
    }
}pcb;

queue<PCB> rq, tq, ioq, lq;
void move_pcb( queue<PCB>& q1, queue<PCB>& q2){
    // q1->q2
    PCB pcb = q1.front();
    q1.pop();
    q2.push(pcb);

}
int main(){

PCB pcb1;
pcb1.a1 = 4;
pcb1.a2 = 8;
rq.push(pcb);
rq.push(pcb1);

move_pcb(rq, tq);

cout << rq.size();
cout << tq.front().a2 << endl;

move_pcb(tq, ioq);

cout << tq.size();
cout << ioq.front().a1;



return 0;
}