/*
 * File: Q2_pqueue_list.h
 * ----------------------
 * This interface exports the PriorityQueue template class, which implements a queue in which the
 * elements are enqueued in priority order. This version of the interface uses a heap to implement the
 * queue.
 */

#ifndef _q2_pqueue_heap_h
#define _q2_pqueue_heap_h

#include "vector.h"
#include "error.h"

/* Function prototypes */

/*
 * Function: parent
 * Usage: size_t i=parent(n);
 * --------------------------
 * Returns the parent index of an element.
 */

inline size_t parent(const size_t n)
{
    return (n-1)/2;
}

/*
 * Function: leftchild
 * Usage: size_t i=leftchild(n);
 * -----------------------------
 * Returns the left child index of an element.
 */

inline size_t leftchild(const size_t n)
{
    return 2*n+1;
}

/*
 * Function: rightchild
 * Usage: size_t i=rightchild(n);
 * -----------------------------
 * Returns the right child index of an element.
 */

inline size_t rightchild(const size_t n)
{
    return 2*n+2;
}

/*
 * Class: PriorityQueue<pqueuetype>
 * --------------------------------
 * This clss models a linear structure called a priority queue in which values are processed in order
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
 * The heap-based priority queue uses a Vector to store the elements of the priority queue and
 * simulates the operation of a partially ordered tree.
 *
 * The following diagrame illustrates the structure of a priority queue containing 5 elements, A, B, C,
 * D, and E.
 *
 * Vector
 *
 * +---------+---------+---------+---------+---------+
 * |    A    |    B    |    C    |    D    |    E    |
 * +---------+---------+---------+---------+---------+
 * | priority| priority| priority| priority| priority|
 * +---------+---------+---------+---------+---------+
 * |   rank  |   rank  |   rank  |   rank  |   rank  |
 * +---------+---------+---------+---------+---------+
 *
 * partially ordered tree
 *
 * +---------+
 * |    A    |
 * +---------+
 * | priority|
 * +---------+
 * |   rank  |
 * +---------+
 *      |\
 *      | -------------------
 *      |                    \
 * +---------+          +---------+
 * |    B    |          |    C    |
 * +---------+          +---------+
 * | priority|          | priority|
 * +---------+          +---------+
 * |   rank  |          |   rank  |
 * +---------+          +---------+
 *      |\
 *      | -------------------
 *      |                    \
 * +---------+          +---------+
 * |    D    |          |    E    |
 * +---------+          +---------+
 * | priority|          | priority|
 * +---------+          +---------+
 * |   rank  |          |   rank  |
 * +---------+          +---------+
 */

private:

/* Type of heap cell */

    struct cell
    {
        pqueuetype data;                        /* The data value */
        double priority;                        /* The priority of the data */
        clock_t rank;                           /* The rank of the data within one hierarchy */
    };

/* Instance variables */

    Vector<cell> pqueue;                        /* Vector for the cells */
    size_t count;                               /* Number of elements in the priority queue */

/* Private method prototypes */

    void copy(const PriorityQueue<pqueuetype> & src);
};

/*
 * Implementation section
 * ----------------------
 * C++ requires that the implementation for a template class be available to the compiler whenever that
 * type is used. The effect of this restriction is that header files must include the implementation.
 * Clients should not need to look at any of the code beyond this point.
 */

/*
 * Implementation notes: StringMap constructor and destructor
 * ----------------------------------------------------------
 * All dynamic allocation is handled by the Vector class.
 */

template <typename pqueuetype>
PriorityQueue<pqueuetype>::PriorityQueue()
{
    count=0;
}

template <typename pqueuetype>
PriorityQueue<pqueuetype>::~PriorityQueue()
{}

/*
 * Implementation notes: size, isEmpty
 * -----------------------------------
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

/*
 * Implementation notes: enqueue
 * -----------------------------
 * This method creates a new heap cell and insert it to the tail of the Vector and it would be the
 * rightmost element in the lowest level of the partially ordered tree. After inserted, the new cell
 * will be exchanged with its parent continuously until its priority is no bigger than its parent's, or
 * it has been at the root.
 */

template <typename pqueuetype>
void PriorityQueue<pqueuetype>::enqueue(const pqueuetype value,const double priority)
{
    cell c;
    size_t anchor=count;

    c.data=value;
    c.priority=priority;
    c.rank=clock();
    pqueue+=c;
    while ((anchor!=0)&&(pqueue[anchor].priority<pqueue[parent(anchor)].priority))
    {
        cell tmp=pqueue[anchor];

        pqueue[anchor]=pqueue[parent(anchor)];
        pqueue[parent(anchor)]=tmp;
        anchor=parent(anchor);
    }
    count++;
}

/*
 * Implement notes: dequeue, peek
 * ------------------------------
 * These methods check for an empty priority queue and report an error if there is no first element.
 * The dequeue method moves the last cell in the Vector to the front if the vector is not empty after
 * removing the first element. A duplicated cell of the moved cell will be inserted to the tail of the
 * Vector if the remaining count is an even number to ensure no cell has only one child. After moving,
 * the moved cell will be exchanged with the child cell with a smaller priority if its priority is not
 * the smallest among its children and itself. Else, if it encounters children with the same priority,
 * the exchange will still happen if its rank is higher than its child's. If the moved cell has
 * children with the same priority, the child with lower rank will be exchanged. This procedure will
 * continue until the moved cell's priority is no smaller than both of its children's and the rank is
 * smaller than children with the same priority. The duplicated cell will be removed at last.
 */

template <typename pqueuetype>
pqueuetype PriorityQueue<pqueuetype>::dequeue()
{
    if (isEmpty()) error("dequeue: empty priority queue");

    pqueuetype result=pqueue[0].data;
    size_t anchor=0;                            /* The index of the moved cell */
    bool completed=0;                           /* Record if a duplicated child is inserted */

    if (count==1)
    {
        pqueue.removeBack();
        count--;
    } else
    {
        pqueue[0]=pqueue[--count];
        pqueue.removeBack();
        if (count%2==0)
        {
            pqueue+=pqueue[0];
            count++;
            completed=1;
        }
        while (count>=2*anchor+2)
        {
            if ((pqueue[anchor].priority<pqueue[leftchild(anchor)].priority)
                    &&(pqueue[anchor].priority<pqueue[rightchild(anchor)].priority)) break;
            if ((pqueue[anchor].priority==pqueue[leftchild(anchor)].priority)
                    &&(pqueue[anchor].rank<=pqueue[leftchild(anchor)].rank)
                    &&(pqueue[anchor].priority<pqueue[rightchild(anchor)].priority)) break;
            if ((pqueue[anchor].priority<pqueue[leftchild(anchor)].priority)
                    &&(pqueue[anchor].priority==pqueue[rightchild(anchor)].priority)
                    &&(pqueue[anchor].rank<=pqueue[rightchild(anchor)].rank)) break;
            if ((pqueue[anchor].priority==pqueue[leftchild(anchor)].priority)
                    &&(pqueue[anchor].priority==pqueue[rightchild(anchor)].priority)
                    &&(pqueue[anchor].rank<=pqueue[leftchild(anchor)].rank)
                    &&(pqueue[anchor].rank<=pqueue[rightchild(anchor)].rank)) break;
            if ((pqueue[anchor].priority>pqueue[leftchild(anchor)].priority)
                    ||(pqueue[anchor].priority>pqueue[rightchild(anchor)].priority))
            {
                if (pqueue[leftchild(anchor)].priority<pqueue[rightchild(anchor)].priority)
                {
                    cell tmp=pqueue[anchor];

                    pqueue[anchor]=pqueue[leftchild(anchor)];
                    pqueue[leftchild(anchor)]=tmp;
                    anchor=leftchild(anchor);
                } else if (pqueue[leftchild(anchor)].priority>pqueue[rightchild(anchor)].priority)
                {
                    cell tmp=pqueue[anchor];

                    pqueue[anchor]=pqueue[rightchild(anchor)];
                    pqueue[rightchild(anchor)]=tmp;
                    anchor=rightchild(anchor);
                } else
                {
                    if (pqueue[leftchild(anchor)].rank<pqueue[rightchild(anchor)].rank)
                    {
                        cell tmp=pqueue[anchor];

                        pqueue[anchor]=pqueue[leftchild(anchor)];
                        pqueue[leftchild(anchor)]=tmp;
                        anchor=leftchild(anchor);
                    } else
                    {
                        cell tmp=pqueue[anchor];

                        pqueue[anchor]=pqueue[rightchild(anchor)];
                        pqueue[rightchild(anchor)]=tmp;
                        anchor=rightchild(anchor);
                    }
                }
            } else
            {
                if (pqueue[leftchild(anchor)].rank<pqueue[rightchild(anchor)].rank)
                {
                    cell tmp=pqueue[anchor];

                    pqueue[anchor]=pqueue[leftchild(anchor)];
                    pqueue[leftchild(anchor)]=tmp;
                    anchor=leftchild(anchor);
                } else
                {
                    cell tmp=pqueue[anchor];

                    pqueue[anchor]=pqueue[rightchild(anchor)];
                    pqueue[rightchild(anchor)]=tmp;
                    anchor=rightchild(anchor);
                }
            }
        }
        if (completed)
        {
            pqueue.removeBack();
            count--;
        }
    }
    return result;
}

template <typename pqueuetype>
pqueuetype PriorityQueue<pqueuetype>::peek() const
{
    if (isEmpty()) error("peek: empty priority queue");
    return pqueue[0].data;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * These methods follow the standard template, copy the Vector and the count.
 */

template <typename pqueuetype>
PriorityQueue<pqueuetype>::PriorityQueue(const PriorityQueue<pqueuetype> & src)
{
    pqueue=src.pqueue;
    count=src.count;
}

template <typename pqueuetype>
PriorityQueue<pqueuetype> & PriorityQueue<pqueuetype>::operator=(const PriorityQueue<pqueuetype> & src)
{
    pqueue=src.pqueue;
    count=src.count;
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
