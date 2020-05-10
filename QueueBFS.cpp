/*
 * File: QueueBFS.cpp
 * ------------------
 * This program implements the breadth-first search algorithm using an explicit queue.
 */

#include "graphtypes.h"
#include "queue.h"

/*
 * Function: breadthFirstSearch
 * Usage: breadthFirstSearch(start)
 * --------------------------------
 * Implements the breadth-first search algorithm using an explict queue.
 */

void breadthFirstSearch(Node * start)
{
    Queue<Node *> cities;
    Set<Node *> visited;

    cities.enqueue(start);
    while (!cities.isEmpty())
    {
        Node * city=cities.dequeue();

        visited.add(city);
        for (Arc * link:city->arcs)
        {
            if (!visited.contains(link->finish))
            {
                cities.enqueue(link->finish);
                visited.add(link->finish);
            }
        }
        std::cout<<city->name<<std::endl;
    }
}
