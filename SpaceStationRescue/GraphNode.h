#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <list>
#include <memory>
//#include "NodeGraphics.h"

// Forward references
template <typename NodeType, typename ArcType> class GraphArc;

// -------------------------------------------------------
// Name:        GraphNode
// Description: This is the node class. The node class 
//              contains data, and has a linked list of 
//              arcs.
// -------------------------------------------------------
template<class NodeType, class ArcType>
class GraphNode {
private:    
// typedef the classes to make our lives easier.
    typedef GraphArc<NodeType, ArcType> Arc;
    typedef GraphNode<NodeType, ArcType> Node;
// -------------------------------------------------------
// Description: data inside the node
// -------------------------------------------------------
    NodeType m_data;

// -------------------------------------------------------
// Description: list of arcs that the node has.
// -------------------------------------------------------
    list<Arc> m_arcList;

// -------------------------------------------------------
// Description: This remembers if the node is marked.
// -------------------------------------------------------
    bool m_marked;

// -------------------------------------------------------
// Description: pointer to previous node
// -------------------------------------------------------
	GraphNode *m_previous;

// -------------------------------------------------------
// Description: estimated distance to get to destination from this node
// -------------------------------------------------------
	int estimatedDistToDest = std::numeric_limits<int>::max() - 10000;

// -------------------------------------------------------
// Description: This remebers if the node has been removed from the proirity queue
// -------------------------------------------------------
	bool m_removed;

public:
    // Accessor functions
    list<Arc> const & arcList() const {
        return m_arcList;              
    }

    bool marked() const {
        return m_marked;
    }

    NodeType const & data() const {
        return m_data;
    }
    // Manipulator functions
    void setData(NodeType data) {
        m_data = data;
    }
    
    void setMarked(bool mark) {
        m_marked = mark;
    }

	bool getRemoved()
	{
		return m_removed;
	}

	void setRemoved(bool removed) {
		m_removed = removed;
	}

	GraphNode* getPrevious()
	{
		return m_previous;
	}

	void setPrevious(GraphNode *prev)
	{
		m_previous = prev;
	}

	//NodeGraphics& getGraphics()
	//{
	//	return m_graphics;
	//}

	//void setGraphics(NodeGraphics graphics)
	//{
	//	m_graphics = graphics;
	//}

	void setEstimatedDistToDest(int newDistance)
	{
		estimatedDistToDest = newDistance;
	}

	int getEstimatedDistToDest()
	{
		return estimatedDistToDest;
	}
    Arc* getArc( Node* pNode );    
    void addArc( Node* pNode, ArcType pWeight );
    void removeArc( Node* pNode );

};

// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    This finds the arc in the current node that
//                  points to the node in the parameter.
//  Arguments:      The node that the arc connects to.
//  Return Value:   A pointer to the arc, or 0 if an arc doesn't
//                  exist from this to the specified input node.
// ----------------------------------------------------------------
template<typename NodeType, typename ArcType>
GraphArc<NodeType, ArcType>* GraphNode<NodeType, ArcType>::getArc(Node* pNode) {

	list<Arc>::iterator iter = m_arcList.begin();
	list<Arc>::iterator endIter = m_arcList.end();
	Arc* pArc = 0;
	m_previous = nullptr;
	// find the arc that matches the node
	for (; iter != endIter && pArc == 0; ++iter) {
		if ((*iter).node() == pNode) {
			pArc = &((*iter));
		}
	}

	// returns null if not found
	return pArc;
}


// ----------------------------------------------------------------
//  Name:           addArc
//  Description:    This adds an arc from the current node pointing
//                  to the first parameter, with the second parameter 
//                  as the weight.
//  Arguments:      First argument is the node to connect the arc to.
//                  Second argument is the weight of the arc.
//  Return Value:   None.
// ----------------------------------------------------------------
template<typename NodeType, typename ArcType>
void GraphNode<NodeType, ArcType>::addArc(Node* pNode, ArcType weight) {
	// Create a new arc.
	Arc a;
	a.setNode(pNode);
	a.setWeight(weight);
	// Add it to the arc list.
	m_arcList.push_back(a);
}


// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This finds an arc from this node to input node 
//                  and removes it.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<typename NodeType, typename ArcType>
void GraphNode<NodeType, ArcType>::removeArc(Node* pNode) {
	list<Arc>::iterator iter = m_arcList.begin();
	list<Arc>::iterator endIter = m_arcList.end();

	int size = m_arcList.size();
	// find the arc that matches the node
	for (; iter != endIter && m_arcList.size() == size;
		++iter) {
		if ((*iter).node() == pNode) {
			m_arcList.remove((*iter));
		}
	}
}

#include "GraphArc.h"

#endif
