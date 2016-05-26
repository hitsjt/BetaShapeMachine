//============================================================================
//
// This file is part of the Shapes Generative Model Library (SGML) project.
//
// Copyright (c) 2010-2014 - Evangelos Kalogerakis, Siddhartha Chaudhuri (authors of the code) / Stanford University, UMass-Amherst
//
// SGML is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// SGML is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with SGML.  If not, see <http://www.gnu.org/licenses/>.
//
//============================================================================

#ifndef __SNL_Node_hpp__
#define __SNL_Node_hpp__

#include "Common.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace SNL {

	/** %Node of a probabilistic graphical model, representing a random variable in the model. */
	class SNL_API Node
	{
	private:
		typedef std::vector<Node *> NodeArray;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & deactivate_neighbors;
			ar & type;
			ar & id;
			ar & parents;
			ar & children;
			ar & siblings;
			ar & neighbors;
		}
	public:
		typedef NodeArray::const_iterator NodeConstIterator;  ///< Iterator over nodes.
		typedef NodeArray::iterator NodeIterator;  ///< Iterator over nodes.

		/** Destructor. */
		virtual ~Node()
		{
			clearNeighbors();
			clearParents();
			clearChildren();
			clearSiblings();
		}

		Node(int _type, long _id, bool _deactivate_neighbors = false): type(_type), id(_id), deactivate_neighbors(_deactivate_neighbors) { }

		/** Does the node represent a variable that takes discrete values? */
		virtual bool isDiscrete() const = 0;

		/** Does the node represent a variable that takes continuous values? */
		bool isContinuous() const { return !isDiscrete(); }

		/** Get the type of the node. */
		virtual int getType() const = 0;

		/** Get the ID of the node. */
		virtual long getID() const = 0;

		/** Get the string description of the node. */
		virtual std::string getName() const = 0;    

		/** Get the number of dimensions of the values taken by this variable. */
		virtual size_t dim() const = 0;

		/**
		* Get the probability assigned to this node for a particular value by the inference procedure. If the node represents a
		* discrete variable, the argument is rounded to the nearest integer.
		*/
		//virtual double prob(std::vector<double> const & value) const = 0;

		/** Get the number of parent nodes of this node. */
		long numParents() const { return (long)parents.size(); }

		/** Get an iterator to the beginning of the set of parents. */
		NodeConstIterator parentsBegin() const { return parents.begin(); }

		/** Get an iterator to the beginning of the set of parents. */
		NodeIterator parentsBegin() { return parents.begin(); }

		/** Get an iterator to the end of the set of parents. */
		NodeConstIterator parentsEnd() const { return parents.end(); }

		/** Get an iterator to the end of the set of parents. */
		NodeIterator parentsEnd() { return parents.end(); }

		/** Get the number of children nodes of this node. */
		long numChildren() const { return (long)children.size(); }

		/** Get an iterator to the beginning of the set of children. */
		NodeConstIterator childrenBegin() const { return children.begin(); }

		/** Get an iterator to the beginning of the set of children. */
		NodeIterator childrenBegin() { return children.begin(); }

		/** Get an iterator to the end of the set of children. */
		NodeConstIterator childrenEnd() const { return children.end(); }

		/** Get an iterator to the end of the set of children. */
		NodeIterator childrenEnd() { return children.end(); }

		/** Get the number of siblings nodes of this node. */
		long numSiblings() const { return (long)siblings.size(); }

		/** Get an iterator to the beginning of the set of siblings. */
		NodeConstIterator siblingsBegin() const { return siblings.begin(); }

		/** Get an iterator to the beginning of the set of siblings. */
		NodeIterator siblingsBegin() { return siblings.begin(); }

		/** Get an iterator to the end of the set of siblings. */
		NodeConstIterator siblingsEnd() const { return siblings.end(); }

		/** Get an iterator to the end of the set of siblings. */
		NodeIterator siblingsEnd() { return siblings.end(); }

		/** Get the number of neighboring nodes of this node. */
		long numNeighbors() const { return (long)neighbors.size(); }

		/** Get an iterator to the beginning of the set of neighbors. */
		NodeConstIterator neighborsBegin() const { return neighbors.begin(); }

		/** Get an iterator to the beginning of the set of neighbors. */
		NodeIterator neighborsBegin() { return neighbors.begin(); }

		/** Get an iterator to the end of the set of neighbors. */
		NodeConstIterator neighborsEnd() const { return neighbors.end(); }

		/** Get an iterator to the end of the set of neighbors. */
		NodeIterator neighborsEnd() { return neighbors.end(); }

		/** Check if this node is a parent of another node. */
		bool isParentOf(Node const * node) const
		{
			for (size_t i = 0; i < children.size(); ++i)
				if (children[i] == node)
					return true;

			return false;
		}

		/** Check if this node is a child of another node. */
		bool isChildOf(Node const * node) const
		{
			for (size_t i = 0; i < parents.size(); ++i)
				if (parents[i] == node)
					return true;

			return false;
		}

		/** Check if this node is a sibling of another node. */
		bool isSiblingOf(Node const * node) const
		{
			for (size_t i = 0; i < siblings.size(); ++i)
				if (siblings[i] == node)
					return true;

			return false;
		}

		/** Check if this node is a neighbor of another node. */
		bool isNeighborOf(Node const * node) const
		{
			for (size_t i = 0; i < neighbors.size(); ++i)
				if (neighbors[i] == node)
					return true;

			return false;
		}

		/** Add a parent node. */
		void addParent(Node * parent)
		{
			if (!isChildOf(parent))
			{
				parents.push_back(parent);
				parent->children.push_back(this);
				if (!deactivate_neighbors)
				{
					neighbors.push_back( parent );
					parent->neighbors.push_back(this);
				}
			}
		}

		/** Add a parent node without checking if it already exists. */
		void addParentNoCheck(Node * parent)
		{
			parents.push_back(parent);
			parent->children.push_back(this);
			if (!deactivate_neighbors)
			{
				neighbors.push_back( parent );
				parent->neighbors.push_back(this);
			}
		}

		/** Remove a parent node. */
		void removeParent(Node * parent)
		{
			if (!deactivate_neighbors)
				removeNeighbor(parent);
			for (size_t i = 0; i < parents.size(); ++i)
				if (parents[i] == parent)
				{
					parents.erase(parents.begin() + i);
					parent->removeChildOneWay(this);
					return;
				}
		}

		/** Remove all parents of the node. */
		void clearParents()
		{
			while ( !parents.empty() )
			{
				removeParent( *( parents.begin() ) );
			}
		}


		/** Add a child node. */
		void addChild(Node * child)
		{
			if (!isParentOf(child))
			{
				children.push_back(child);
				child->parents.push_back(this);
				if (!deactivate_neighbors)
				{
					neighbors.push_back(child);
					child->neighbors.push_back(this);
				}
			}
		}

		/** Add a child node without checking if it already exists. */
		void addChildNoCheck(Node * child)
		{
			children.push_back(child);
			child->parents.push_back(this);
			if (!deactivate_neighbors)
			{
				neighbors.push_back(child);
				child->neighbors.push_back(this);
			}
		}

		/** Remove a child node, given a pointer to it. Assumes duplicates do not exist. */
		void removeChild(Node * child)
		{
			if (!deactivate_neighbors)
				removeNeighbor(child);
			for (size_t i = 0; i < children.size(); ++i)
				if (children[i] == child)
				{
					children.erase(children.begin() + i);
					child->removeParentOneWay(this);
					return;
				}
		}

		/** Remove all children of the node. */
		void clearChildren()
		{
			while ( !children.empty() )
			{
				removeChild( *( children.begin() ) );
			}
		}


		/** Add a sibling node. */
		void addSibling(Node * sibling)
		{
			if (!isSiblingOf(sibling))
			{
				siblings.push_back(sibling);
				sibling->siblings.push_back(this);
				if (!deactivate_neighbors)
				{
					neighbors.push_back( sibling );
					sibling->neighbors.push_back(this);
				}
			}
		}

		/** Add a sibling node without checking if it already exists. */
		void addSiblingNoCheck(Node * sibling)
		{
			siblings.push_back(sibling);
			sibling->siblings.push_back(this);
			if (!deactivate_neighbors)
			{
				neighbors.push_back( sibling );
				sibling->neighbors.push_back(this);
			}
		}

		/** Remove a sibling node. */
		void removeSibling(Node * sibling)
		{
			if (!deactivate_neighbors)
				removeNeighbor(sibling);
			for (size_t i = 0; i < siblings.size(); ++i)
				if (siblings[i] == sibling)
				{
					siblings.erase(siblings.begin() + i);
					sibling->removeSiblingOneWay(this);
					return;
				}
		}

		/** Remove all siblings of the node. */
		void clearSiblings()
		{
			while ( !siblings.empty() )
			{
				removeSibling( *( siblings.begin() ) );
			}
		}

		/** Add a neighbor (undirected) node. */
		void addNeighbor(Node * neighbor)
		{
			if (deactivate_neighbors)
			{
				std::cerr << "SNL::Node constructor was called to deactivate the neighbors member. You cannot now use addNeighbor()!" << std::endl;
				return;
			}
			if (!isNeighborOf(neighbor))
			{
				neighbors.push_back( neighbor );
				neighbor->neighbors.push_back(this);
			}
		}

		/** Add a neighbor (undirected) node without checking if it already exists. */
		void addNeighborNoCheck(Node * neighbor)
		{
			if (deactivate_neighbors)
			{
				std::cerr << "SNL::Node constructor was called to deactivate the neighbors member. You cannot now use addNeighborNoCheck()!" << std::endl;
				return;
			}
			neighbors.push_back( neighbor );
			neighbor->neighbors.push_back(this);
		}

		/** Remove a neighboring node. */
		void removeNeighbor(Node * neighbor)
		{
			for (size_t i = 0; i < neighbors.size(); ++i)
				if (neighbors[i] == neighbor)
				{
					neighbors.erase(neighbors.begin() + i);
					neighbor->removeNeighborOneWay(this);
					break;
				}
		}

		/** Remove all neighbors of the node. */
		void clearNeighbors()
		{
			clearParents();
			clearChildren();
			clearSiblings();

			while ( !neighbors.empty() )
			{
				removeNeighbor( *( neighbors.begin() ) );
			}
		}

		void clearNeighborsUnsafeOneWay()
		{
			parents.clear();
			children.clear();
			siblings.clear();
			neighbors.clear();
		}

	public:
		int type;
		long id;
		NodeArray parents;   ///< The set of parents of the node.
		NodeArray children;  ///< The set of children of the node.
		NodeArray siblings;  ///< The set of siblings of the node.
		NodeArray neighbors;  ///< The set of all neighbors of the node (parents+children+siblings)

	private:
		bool deactivate_neighbors; 

		void removeParentOneWay(Node * parent)
		{
			for (size_t i = 0; i < parents.size(); ++i)
				if (parents[i] == parent)
				{
					parents.erase(parents.begin() + i);
					break;
				}
		}

		void removeChildOneWay(Node * child)
		{
			for (size_t i = 0; i < children.size(); ++i)
				if (children[i] == child)
				{
					children.erase(children.begin() + i);
					return;
				}
		}

		void removeSiblingOneWay(Node * sibling)
		{
			for (size_t i = 0; i < siblings.size(); ++i)
				if (siblings[i] == sibling)
				{
					siblings.erase(siblings.begin() + i);
					return;
				}
		}

		void removeNeighborOneWay(Node * neighbor)
		{
			for (size_t i = 0; i < neighbors.size(); ++i)
				if (neighbors[i] == neighbor)
				{
					neighbors.erase(neighbors.begin() + i);
					break;
				}
		}


	}; // class Node

} // namespace SNL

#endif
