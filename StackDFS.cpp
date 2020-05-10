/*
 * File: StackDFS.cpp
 * ------------------
 * This program reimplements the depth-first search algorithm using an explicit stack.
 */

#include "graphtypes.h"
#include "stack.h"

/*
 * Function: depthFirstSearch
 * Usage: depthFirstSearch(start)
 * ------------------------------
 * Implements the depth-first search algorithm using an explicit stack.
 */

void depthFirstSearch(Node * start)
{
    Stack<Node *> cities;
    Set<Node *> visited;

    cities.push(start);
    while(!cities.isEmpty())
    {
        Node * city = cities.pop();

        visited.add(city);
        for (Arc * link:city->arcs)
        {
            if (!visited.contains(link->finish))
            {
                cities.push(link->finish);
                visited.add(link->finish);
            }
        }
        std::cout<<city->name<<std::endl;
    }
}
