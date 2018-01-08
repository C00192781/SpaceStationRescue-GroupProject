#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>

using namespace std;









template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;




// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    This is the graph class, it contains all the
//                  nodes.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph {
private:

    // typedef the classes to make our lives easier.
    typedef GraphArc<NodeType, ArcType> Arc;
    typedef GraphNode<NodeType, ArcType> Node;

// ----------------------------------------------------------------
//  Description:    An array of all the nodes in the graph.
// ----------------------------------------------------------------
    Node** m_pNodes;

// ----------------------------------------------------------------
//  Description:    The maximum number of nodes in the graph.
// ----------------------------------------------------------------
    int m_maxNodes;


// ----------------------------------------------------------------
//  Description:    The actual number of nodes in the graph.
// ----------------------------------------------------------------
    int m_count;


public:           
    // Constructor and destructor functions
    Graph( int size );
    ~Graph();

    // Accessors
    Node** nodeArray() const {
       return m_pNodes;
    }

    // Public member functions.
    bool addNode( NodeType data, int index );
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void depthFirst( Node* pNode, void (*pProcess)(Node*) );
    void breadthFirst( Node* pNode, void (*pProcess)(Node*) );
	void adaptedBreadthFirst(Node* pNode, void(*pProcess)(Node*),Node* destNode);
	void ucs(Node* pStart, Node* pDest, std::vector<Node *>& path);//void(*pVisitFunc)(Node*)
	void aStar(Node* pStart, Node* pDest,std::vector<Node *>& path);
};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph( int size ) : m_maxNodes( size ) {
   int i;
   m_pNodes = new Node * [m_maxNodes];
   // go through every index and clear it to null (0)
   for( i = 0; i < m_maxNodes; i++ ) {
        m_pNodes[i] = 0;
   }

   // set the node count to 0.
   m_count = 0;
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
   int index;
   for( index = 0; index < m_maxNodes; index++ ) {
        if( m_pNodes[index] != 0 ) {
            delete m_pNodes[index];
        }
   }
   // Delete the actual array
   delete m_pNodes;
}

// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index ) {
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if ( m_pNodes[index] == 0) {
      nodeNotPresent = true;
      // create a new node, put the data in it, and unmark it.
      m_pNodes[index] = new Node;
      m_pNodes[index]->setData(data);
      m_pNodes[index]->setMarked(false);

      // increase the count and return success.
      m_count++;
    }
        
    return nodeNotPresent;
}

// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode( int index ) {
     // Only proceed if node does exist.
     if( m_pNodes[index] != 0 ) {
         // now find every arc that points to the node that
         // is being removed and remove it.
         int node;
         Arc* arc;

         // loop through every node
         for( node = 0; node < m_maxNodes; node++ ) {
              // if the node is valid...
              if( m_pNodes[node] != 0 ) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_pNodes[node]->getArc( m_pNodes[index] );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
              }
         }
        

        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_pNodes[index];
        m_pNodes[index] = 0;
        m_count--;
    }
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) {
     bool proceed = true; 
     // make sure both nodes exist.
     if( m_pNodes[from] == 0 || m_pNodes[to] == 0 ) {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if( m_pNodes[from]->getArc( m_pNodes[to] ) != 0 ) {
         proceed = false;
     }

     if (proceed == true) {
        // add the arc to the "from" node.
        m_pNodes[from]->addArc( m_pNodes[to], weight );
     }
     
     return proceed;
}

// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc( int from, int to ) {
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( m_pNodes[from] == 0 || m_pNodes[to] == 0 ) {
         nodeExists = false;
     }

     if (nodeExists == true) {
        // remove the arc.
        m_pNodes[from]->removeArc( m_pNodes[to] );
     }
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
// Dev-CPP doesn't like Arc* as the (typedef'd) return type?
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) {
     Arc* pArc = 0;
     // make sure the to and from nodes exist
     if( m_pNodes[from] != 0 && m_pNodes[to] != 0 ) {
         pArc = m_pNodes[from]->getArc( m_pNodes[to] );
     }
                
     return pArc;
}


// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() {
     int index;
     for( index = 0; index < m_maxNodes; index++ ) {
          if( m_pNodes[index] != 0 ) {
              m_pNodes[index]->setMarked(false);
          }
     }
}


// ----------------------------------------------------------------
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst( Node* pNode, void (*pProcess)(Node*) ) {
     if( pNode != 0 ) {
           // process the current node and mark it
           pProcess( pNode );
           pNode->setMarked(true);

           // go through each connecting node
           list<Arc>::iterator iter = pNode->arcList().begin();
           list<Arc>::iterator endIter = pNode->arcList().end();
        
		   for( ; iter != endIter; ++iter) {
			    // process the linked node if it isn't already marked.
                if ( (*iter).node()->marked() == false ) {
                   depthFirst( (*iter).node(), pProcess);
                }            
           }
     }
}


// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst( Node* pNode, void (*pProcess)(Node*) ) {
   if( pNode != 0 ) {
	  queue<Node*> nodeQueue;        
	  // place the first node on the queue, and mark it.
      nodeQueue.push( pNode );
      pNode->setMarked(true);

      // loop through the queue while there are nodes in it.
      while( nodeQueue.size() != 0 ) 
	  {
         // process the node at the front of the queue.
         pProcess( nodeQueue.front() );

         // add all of the child nodes that have not been 
         // marked into the queue
         list<Arc>::const_iterator iter = nodeQueue.front()->arcList().begin();
         list<Arc>::const_iterator endIter = nodeQueue.front()->arcList().end();
		 //list<Arc>::const_iterator prevIter = nodeQueue.front()->arcList().begin();
         
		 for( ; iter != endIter; iter++ ) 
		 {
              if ( (*iter).node()->marked() == false) 
			  {
				 // mark the node and add it to the queue.
				 (*iter).node()->setPrevious((nodeQueue.front()));
				 std::cout << (*iter).node()->data() << " Previous:" << (*iter).node()->getPrevious()->data() << std::endl;
                 (*iter).node()->setMarked(true);
                 nodeQueue.push( (*iter).node() );
              }
         }

         // dequeue the current node.
         nodeQueue.pop();
      }
   }  
}

template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::adaptedBreadthFirst(Node* pNode, void(*pProcess)(Node*),Node* destNode) {


	if (pNode != 0) {
		queue<Node*> nodeQueue;
		// place the first node on the queue, and mark it.
		nodeQueue.push(pNode);
		pNode->setMarked(true);
		bool goalReached = false;
		// loop through the queue while there are nodes in it.
		while (nodeQueue.size() != 0 && goalReached == false)
		{
			// process the node at the front of the queue.
			pProcess(nodeQueue.front());

			// add all of the child nodes that have not been 
			// marked into the queue
			list<Arc>::const_iterator iter = nodeQueue.front()->arcList().begin();
			list<Arc>::const_iterator endIter = nodeQueue.front()->arcList().end();

			for (; iter != endIter; iter++)
			{
				if ((*iter).node() == destNode)
				{
					goalReached == true;
					Node* temp = (*iter).node();
					destNode->setPrevious(nodeQueue.front());
					std::cout << std::endl;
					std::cout << "Destination Node: "+destNode->data() << std::endl;
					while (temp !=pNode)
					{
						temp = temp->getPrevious();
						std::cout << "Path Node :" + temp->data() <<std::endl;
					}
					std::cout << std::endl;
				}
				if ((*iter).node()->marked() == false)
				{
					// mark the node and add it to the queue.
					(*iter).node()->setPrevious((nodeQueue.front()));
					//std::cout << (*iter).node()->data() << " Previous:" << (*iter).node()->getPrevious()->data() << std::endl;
					(*iter).node()->setMarked(true);
					nodeQueue.push((*iter).node());
				}
			}
			// dequeue the current node.
			nodeQueue.pop();
		}
	}
}

template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::ucs(Node* pStart, Node* pDest, std::vector<Node *>& path) //void(*pProcess)(Node*), 
{

	if (pStart != 0)
	{
		for (int index = 0; index < m_maxNodes; index++) {
			if (m_pNodes[index] != 0) {
				m_pNodes[index]->setData(pair<string, int>(m_pNodes[index]->data().first, std::numeric_limits<int>::max() - 10000));

			}
		}
		bool foundPath = false;
		priority_queue<Node*, vector<Node*>, NodeSearchCostComparer<NodeType, ArcType>> nodeQueue;
		nodeQueue.push(pStart);
		pStart->setMarked(true);
		pStart->setData(pair<string, int>(pStart->data().first, 0));
		while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
		{
			list<Arc>::const_iterator iter = nodeQueue.top()->arcList().begin();
			list<Arc>::const_iterator endIter = nodeQueue.top()->arcList().end();
			for (; iter != endIter; iter++)
			{
				if ((*iter).node() != nodeQueue.top())
				{
					int dist = nodeQueue.top()->data().second + iter->weight();

					if ((*iter).node()->marked() == false)
					{
						// mark the node and add it to the queue.
						(*iter).node()->setPrevious((nodeQueue.top()));
						if (dist < (*iter).node()->data().second)
						{
							(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, dist));
						}
						(*iter).node()->setMarked(true);
						nodeQueue.push((*iter).node());
					}
					if (dist < (*iter).node()->data().second)
					{
						(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, dist));
						(*iter).node()->setPrevious((nodeQueue.top()));
					}
					if ((*iter).node() == pDest)
					{
						if (dist <= (*iter).node()->data().second)
						{
							(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, dist));
							(*iter).node()->setPrevious((nodeQueue.top()));
							if (foundPath == true)
							{
								path.clear();
							}
							Node* temp = (*iter).node();
							path.push_back((*iter).node());
							while (temp != pStart)
							{
								temp = temp->getPrevious();
								path.push_back(temp);
							}
							foundPath = true;
						}
					}

				}
			}
			nodeQueue.pop();
		}
	}
}
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::aStar(Node* pStart, Node* pDest, std::vector<Node *>& path)
{
	//g(n) = nodeQueue.top()->data().second
	//h(n) = estimated cost
	//f(n) = g(n)+h(n)

	if (pStart != 0)
	{
		//run UCS in opposite direction
		std::vector<Node*> ucsPath;
		//ucs(pDest, pStart, ucsPath);
		ucs(pDest, pStart, ucsPath);

		for (int index = 0; index < m_maxNodes; index++) 
		{
			if (m_pNodes[index] != 0) 
			{
				m_pNodes[index]->setEstimatedDistToDest(m_pNodes[index]->data().second*0.9);
				m_pNodes[index]->setData(pair<string, int>(m_pNodes[index]->data().first, std::numeric_limits<int>::max() - 10000));
				std::cout << m_pNodes[index]->data().first << " " << m_pNodes[index]->getEstimatedDistToDest() << std::endl;

				//make sure marked is set to false
				m_pNodes[index]->setMarked(false);
				//set bool
				m_pNodes[index]->setRemoved(false);
			}
		}
		priority_queue<Node*, vector<Node*>, NodeSearchEstimateComparer<NodeType, ArcType>> nodeQueue;

		//Add starting node to queue and set its distance and that it has been visited
		nodeQueue.push(pStart);
		pStart->setMarked(true);
		pStart->setData(pair<string, int>(pStart->data().first, 0));

		while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
		{
			list<Arc>::const_iterator iter = nodeQueue.top()->arcList().begin();
			list<Arc>::const_iterator endIter = nodeQueue.top()->arcList().end();
			for (; iter != endIter; iter++)
			{
				if ((*iter).node()->getPrevious() != nodeQueue.top())
				{
					int dist = nodeQueue.top()->data().second + iter->weight();

					//Checks if distance is shorter than current shortest distance to this node
					if (dist < (*iter).node()->data().second)
					{
						//sets new distance
						(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, dist));
						//sets pointer for previous node to the node at the top of the queue
						(*iter).node()->setPrevious((nodeQueue.top()));
					}

					//Checks to see if the node has been visited
					if ((*iter).node()->marked() == false)
					{
						//sets pointer for previous node to the node at the top of the queue
						(*iter).node()->setPrevious((nodeQueue.top()));
						// mark the node and add it to the queue.
						(*iter).node()->setMarked(true);
						nodeQueue.push((*iter).node());
					}

					if ((*iter).node() == pDest)
					{
						if (dist <= (*iter).node()->data().second)
						{
							//sets new distance
							(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, dist));
							//sets pointer for previous node to the node at the top of the queue
							(*iter).node()->setPrevious((nodeQueue.top()));
							//Clears contents of vector
							path.clear();
							Node* temp = (*iter).node();
							path.push_back((*iter).node());
							//Gets pointer to the previous node and adds it to the path vector
							while (temp != pStart)
							{
								temp = temp->getPrevious();
								path.push_back(temp);
							}
						}
					}
				}
			}
			nodeQueue.pop();
		}
	}
}


template<class NodeType, class ArcType>
class NodeSearchEstimateComparer 
{
public:
	typedef GraphNode<NodeType, ArcType> Node;
	//Compares nodes f(n) values
	bool operator()(Node * n1, Node * n2) 
	{
		//f(n) = h(n) + g(n)
		int p1 = n1->getEstimatedDistToDest() + n1->data().second;
		int p2 = n2->getEstimatedDistToDest() + n2->data().second;
		return p1 > p2;
	}
};


template<class NodeType, class ArcType>
class NodeSearchCostComparer 
{
public:
	typedef GraphNode<NodeType, ArcType> Node;
	//Compares nodes weight/distance values
	bool operator()(Node * n1, Node * n2) 
	{
		pair<string, int> p1 = n1->data();
		pair<string, int> p2 = n2->data();
		return p1.second > p2.second;
	}
};


#include "GraphNode.h"
#include "GraphArc.h"


#endif
