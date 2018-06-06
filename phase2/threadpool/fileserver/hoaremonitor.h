#ifndef HOAREMONITOR_H
#define HOAREMONITOR_H


class HoareMonitor{
protected:
class Condition
{
friend HoareMonitor;
public:
Condition();
private:
QSemaphore waitingSem;
int nbWaiting;
};
HoareMonitor();
void monitorIn();
void monitorOut();
void wait(Condition &cond);
void signal(Condition &cond);
private:
QSemaphore monitorMutex;
QSemaphore monitorSignale;
int monitorNbSignale;
};

#endif // HOAREMONITOR_H
