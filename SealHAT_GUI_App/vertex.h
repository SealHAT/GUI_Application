/*
 * classes.h
 *
 *  Created on: Feb 29, 2016
 *      Author: krystine
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <map>

using namespace std;

template <class Type>
class Vertex
{
public:
    //Constructors
    Vertex();
    Vertex(int newValue, Type newData, bool newVisited);

    //Desctructor
    ~Vertex();

    void createGraph(list<Restaurant*> restaurantsToTravelTo,  bool startAtSaddleback);

    //Mutators
    void setVertexValue(int newValue);
    void setData(Type newData);
    void setVisited(bool newVisited);
    void setVertexOfClosestUnvisitedNeighbor(int newVertex);

    //Accessors
    int  getVertexValue()const;
    Type getData()const;
    bool getVisited()const;
    int  getVertexOfClosestUnvisitedNeighbor()const;

private:
    int  vertexValue;
    Type data;
    bool visited;
    int  vertexOfClosestUnvisitedNeighbor;

    double** _graph;
    QString *_locations;
    int _size;
};

//Constructors
template <class Type>
Vertex<Type>::Vertex()
{
    vertexValue = -1;
    //data        = NULL;
    visited     = false;
    vertexOfClosestUnvisitedNeighbor = -1;
    _size = 0;

}

template <class Type>
Vertex<Type>::Vertex(int newValue, Type newData, bool newVisited)
{
    vertexValue = newValue;
    data        = newData;
    visited     = newVisited;
    vertexOfClosestUnvisitedNeighbor = -1;
    _size = 0;
}

//Desctructor
template <class Type>
Vertex<Type>::~Vertex() {

    /** Deallocates memory of the dynamic 2D maps */
    for(int i = 0; i < _size; i++) {
        delete[] _graph[i];
    }

    if(_size != 0) {
    delete [] _graph;
    }
}


template <class Type>
void Vertex<Type>::createGraph(list<Restaurant*> restaurantsToTravelTo, bool startAtSaddleback) {

    int rowCount;

    rowCount = restaurantsToTravelTo.size() + 1;

    _size = rowCount;
    int colCount = rowCount;

    _graph = new double*[rowCount];
    _locations = new QString[rowCount];


    for(int row = 0; row < rowCount; row++) {
        _graph[row] = new double[colCount];
    }

    int row = 0;
    int col = 0;


    _locations[row] = "Saddleback";
    _graph[row][col] = 0.0;

    col++;

    for(list<Restaurant*>::const_iterator it = restaurantsToTravelTo.begin();
            it != restaurantsToTravelTo.end(); it++) {

        double distanceFromSaddleback = (*it)->getDistance();
        _graph[row][col] = distanceFromSaddleback;
        col++;

    }

    for(list<Restaurant*>::const_iterator it = restaurantsToTravelTo.begin();
        it != restaurantsToTravelTo.end(); it++) {
        col = 0;
        _locations[row] = (*it)->getRestaurantName();

        map<QString, double> current = (*it)->getDistancesToRestaurants();

        for(map<QString, double>::const_iterator i = current.begin(); i != current.end(); i++) {
            QString distanceToName = i->first;

            /** need to check if the certain restaurant in the map is the one that needs to be visited to */
            bool found = false;
            list<Restaurant*>::const_iterator j = restaurantsToTravelTo.begin();

            while(!found && j != restaurantsToTravelTo.end()) {

                if(distanceToName == (*it)->getRestaurantName()) {
                    found = true;
                }

            }

            if(found) {
                double distance = i->second;
                _graph[row][col] = distance;
            }

            col++;
        }

    }

}


//Mutators
template <class Type>
void Vertex<Type>::setVertexValue(int newValue)
{
    vertexValue = newValue;
}

template <class Type>
void Vertex<Type>::setData(Type newData)
{
    data = newData;
}

template <class Type>
void Vertex<Type>::setVisited(bool newVisited)
{
    visited = newVisited;
}

template <class Type>
void Vertex<Type>::setVertexOfClosestUnvisitedNeighbor(int newVertex)
{
    vertexOfClosestUnvisitedNeighbor = newVertex;
}

//Accessors
template <class Type>
int Vertex<Type>::getVertexValue()const
{
    return vertexValue;
}

template <class Type>
Type Vertex<Type>::getData()const
{
    return data;
}

template <class Type>
bool Vertex<Type>::getVisited()const
{
    return visited;
}

template <class Type>
int Vertex<Type>::getVertexOfClosestUnvisitedNeighbor()const
{
    return vertexOfClosestUnvisitedNeighbor;
}



#endif /* VERTEX_H_ */
