#include <iostream>

using namespace std;

//
// A Queue Class with For_Each and Delete_If functions
//


// An element for the Queue.
struct Event
{
    Event(int x):mx(x),next(NULL){};
    int mx;
    Event * next;
};



struct Queue
{
    Queue():m_qHead(NULL),m_qTail(NULL){}

    // Insert at tail of list
    void qPush(Event* e);

    // Pop from head of list
    Event * qPop();

    // Apply function to each element
    template <class T> void qFor_Each(T& f); 

    // Delete element if f returns true
    template <class T> void qDelete_If(T& f);


    Event* m_qHead;
    Event* m_qTail;
};



// Call f(element) for each element
// Note: f cannot delete e or change the next pointer
template <class T>
void Queue::qFor_Each( T& f) 
{
    Event * e = m_qHead;
    while (e) {
        f(e);
        e=e->next;
    }
}


// Insert el at tail of list
void Queue::qPush(Event* el)
{
    if ( m_qTail ){
        m_qTail->next = el;
    }else{
        m_qHead = el;
    }
    m_qTail = el;
    el->next=NULL;
}


// Pop element from head of list
Event * Queue::qPop()
{
    Event *e = m_qHead;
    if ( m_qHead )
    {
        m_qHead = m_qHead->next;
        if ( m_qHead == NULL )
            m_qTail = NULL;
    }
    return e;
}


// Delete elements for which f returns true
template <class T>
void Queue::qDelete_If(T& f)
{
    Event* e = m_qHead;
    Event* n = NULL;
    m_qHead=m_qTail=NULL;
    while (e) {
        n = e->next;
        if (f(e)){
            delete (e);
        }else{
            qPush(e);
        }
        e=n;
    }
}




struct EvPrint
{
    void operator()(Event* e){
        cout << e->mx << " ";
    }
};

struct EvDel
{
    bool operator()(Event* e) {
        return (e->mx % 2);
    }
};
    
            


int main (int argc, char** argv)
{
    Queue c;
    for (int i=0; i<10; ++i){
        c.qPush(new Event(i));
    }

    // Print out
    cout << "For_Each:"<< endl;
    EvPrint pr;
    c.qFor_Each(pr);
    cout << endl;

    // Delete all odd numbers
    cout << "Delete_if:"<< endl;
    EvDel dl;
    c.qDelete_If(dl);
    c.qFor_Each(pr);
    cout << endl;

    // Check push and pop in list
    Queue q2;
    cout << "Adding:"<< endl;
    for (int i=20; i>0; i--){
        cout << i << " ";
        q2.qPush(new Event(i));
    }
    cout << endl;

    Event* e = NULL;
    cout << "Extracting:"<< endl;
    while (e=q2.qPop()){
        cout << e->mx << " ";
    }
    cout << endl;
}


    

