/*
 * File: Q1_pqueue_list.h
 * ----------------------
 * This interface exports the PriorityQueue template class, which implements a queue in which the
 * elements are enqueued in priority order. This version of the interface uses a linked list to
 * implement the queue.
 */

#ifndef _q1_pqueue_list_h
#define _q1_pqueue_list_h

#include "error.h"

/*
 * Class: PriorityQueue<pqueuetype>
 * --------------------------------
 * This class models a linear structure called a priority queue in which values are processed in order
 * of priority. As in conventional English usage, lower priority numbers correspond to higher effective
 * priorities, so that a priority 1 item takes precedence over a priority 2 item.
 */

template <typename pqueuetype>
class PriorityQueue
{
public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<pqueuetype> queue;
 * ---------------------------------------
 * Initializes a new empty priority queue.
 */

    PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * Usage: (usually implicit)
 * -------------------------
 * Frees any heap storage associated with this priority queue.
 */

    ~PriorityQueue();

/*
 * Method: size
 * Usage: size_t n=pqueue.size();
 * ------------------------------
 * Returns the number of values in the priority queue.
 */

    inline size_t size() const;

/*
 * Method: isEmpty
 * Usage: if (pqueue.isEmpty()) . . .
 * ----------------------------------
 * Returns true if the priority queue contains no elements.
 */

    inline bool isEmpty() const;

/*
 * Method: clear
 * Usage: pqueue.clear();
 * ----------------------
 * Removes all elements from this priority queue.
 */

    void clear();

/*
 * Method: enqueue
 * Usage: pqueue.enqueue(value,priority);
 * --------------------------------------
 * Adds value to the end of a hierarchy in the priority queue according to the priority.
 */

    void enqueue(const pqueuetype value,const double priority);

/*
 * Method: dequeue
 * Usage: pqueuetype first=pqueue.dequeue();
 * -----------------------------------------
 * Removes and return the first item in the priority queue. This method signals an error if called on
 * an empty priority queue.
 */

    pqueuetype dequeue();

/*
 * Method: peek
 * Usage: pqueuetype first=pqueue.peek();
 * --------------------------------------
 * Returns the first value in the priority queue without removing it. This method signals an error if
 * called on an empty priority queue.
 */

    inline pqueuetype peek() const;

/*
 * Copy constructor and assignment operator
 * ----------------------------------------
 * These methods implement deep copying for priority queues.
 */

    PriorityQueue(const PriorityQueue<pqueuetype> & src);
    PriorityQueue<pqueuetype> & operator=(const PriorityQueue<pqueuetype> & src);

/* Private section */

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The list-based  priority queue uses a linked list to store the elements of the priority queue. To
 * ensure that adding a new element to the tail of the corresponding hierarchy is fast, the data
 * structure maintains a pointer to the last cell in the priority queue as well as the first. If the
 * priority queue is empty, both the head pointer and the tail pointer are set to NULL.
 *
 * The following diagram illustrates the structure of a priority queue containing 2 elements, A and B.
 *
 *       +---------+          +---------+         +---------+
 *  head |    o----+--------->|    A    |   +--==>|    B    |
 *       +---------+          +---------+   |  |  +---------+
 *  tail |    o----+----+     |    o----+---+  |  |   NULL  |
 *       +---------+    |     +---------+      |  +---------+
 *                      |     | priority|      |  | priority|
 *                      |     +---------+      |  +---------+
 *                      |                      |
 *                      +----------------------+
 */

private:

/* Type for linked list cell */

    struct cell
    {
        pqueuetype data;                        /* The data value */
        cell * link;                            /* Link to the next cell */
        double priority;                        /* The priority of data */
    };

/* Instance variables */

    cell * head;                                /* Pointer to the cell at the head */
    cell * tail;                                /* Pointer to the cell at the tail */
    size_t count;                               /* Number of elements in the priority queue */

/* Private method prototypes */

    void deepCopy(const PriorityQueue<pqueuetype> & src);
};

/*
 * Implementation section
 * ----------------------
 * C++ requires that the implementation for a template class be available to the compiler whenever that
 * type is used. The effect of this restriction is that header files must include the implementation.
 * Clients should not need to look at any of the code beyond this point.
 */

/*
 * Implementation notes: PriorityQueue constructor
 * -----------------------------------------------
 * The constructor creates an empty linked list and sets count to 0.
 */

template <typename pqueuetype>
PriorityQueue<pqueuetype>::PriorityQueue()
{
    head=tail=NULL;
    count=0;
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * The destructor frees any heap memory allocated by the priority queue.
 */

template <typename pqueuetype>
PriorityQueue<pqueuetype>::~PriorityQueue()
{
    clear();
}

/*
 * Implementation notes: size, isEmpty, clear
 * ------------------------------------------
 * These methods use the count variable and therefore run in constant time.
 */

template <typename pqueuetype>
size_t PriorityQueue<pqueuetype>::size() const
{
    return count;
}

template <typename pqueuetype>
bool PriorityQueue<pqueuetype>::isEmpty() const
{
    return count==0;
}

template <typename pqueuetype>
void PriorityQueue<pqueuetype>::clear()
{
    while (count!=0)
    {
        dequeue();
    }
}

/*
 * Implementation notes: enqueue
 * -----------------------------
 * This method allocates a new list cell and chains it in at the tail of the corressponding hierarchy
 * in the priority queue. If the priority queue is currently empty, the new cell also becomes the head
 * pointer in the priority queue.
 */

template <typename pqueuetype>
void PriorityQueue<pqueuetype>::enqueue(const pqueuetype value,const double priority)
{
    cell * cp=new cell;

    cp->data=value;
    if (head==NULL)
    {
        cp->link=NULL;
        head=tail=cp;
    } else if (priority<head->priority)
    {
        cp->link=head;
        head=cp;
    } else if (priority>=tail->priority)
    {
        cp->link=NULL;
        tail->link=cp;
        tail=cp;
    } else
    {
        cell * rank=head;

        while (priority>=rank->link->priority)
        {
            rank=rank->link;
        }
        cp->link=rank->link;
        rank->link=cp;
    }
    cp->priority=priority;
    count++;
}

/*
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These methods check for an empty priority queue and report an error if there is no first element.
 * The dequeue method also checks for the case in which the queue becomes empty and sets both the head
 * and tail pointer to NULL.
 */

template <typename pqueuetype>
pqueuetype PriorityQueue<pqueuetype>::dequeue()
{
    if (isEmpty()) error("dequeue: empty priority queue");

    cell * cp=head;
    pqueuetype tmp=cp->data;

    head=cp->link;
    if (head==NULL) tail=NULL;
    count--;
    delete cp;
    return tmp;
}

template <typename pqueuetype>
pqueuetype PriorityQueue<pqueuetype>::peek() const
{
    if (isEmpty()) error("peek: empty priority queue");
    return head->data;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * These methods follow the standard template, leaving the work to deepCopy.
 */

template <typename pqueuetype>
PriorityQueue<pqueuetype>::PriorityQueue(const PriorityQueue<pqueuetype> & src)
{
    deepCopy(src);
}

template <typename pqueuetype>
PriorityQueue<pqueuetype> & PriorityQueue<pqueuetype>::operator=(const PriorityQueue<pqueuetype> & src)
{
    if (this!= & src)
    {
        clear();
        deepCopy(src);
    }
    return * this;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * This function copies the data from the src parameter into the current object. This implementation
 * simply walks down the linked list in the source object and enqueues each value in the destination.
 */

template <typename pqueuetype>
void PriorityQueue<pqueuetype>::deepCopy(const PriorityQueue<pqueuetype> & src)
{
    head=NULL;
    tail=NULL;
    count=0;
    for (cell * cp=src.head;cp!=NULL;cp=cp->link)
    {
        enqueue(cp->data,cp->priority);
    }
}

/*
 * Operator: <<
 * Usage: cout<<pqueue;
 * --------------------
 * Overloads the << operator so that it is able to display the content of the priority queue.
 */

template <typename pqueuetype>
std::ostream & operator<<(std::ostream & os,const PriorityQueue<pqueuetype> pqueue)
{
    PriorityQueue<pqueuetype> tmp=pqueue;

    for (size_t i=0;i<pqueue.size();i++)
    {
        os<<tmp.dequeue()<<" ";
    }
    os<<std::endl;
    return os;
}

#endif
