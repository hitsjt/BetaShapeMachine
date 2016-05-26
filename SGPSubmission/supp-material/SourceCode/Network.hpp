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
#ifndef __SNL_Network_hpp__
#define __SNL_Network_hpp__

#include "Common.hpp"
#include "Node.hpp"
#include "Options.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>

namespace SNL {

/** Generic interface for all implemented probabilistic networks. */
class SNL_API Network
{
  private:
    typedef std::vector<Node *> NodeSet;

  public:
    typedef NodeSet::const_iterator NodeConstIterator;  ///< Const iterator over nodes.
    typedef NodeSet::iterator NodeIterator;  ///< Iterator over nodes.

    /** Destructor. */
    virtual ~Network() {}

    /** Initialize the probabilistic network with the supplied options. */
    virtual void init(Options const & options = SNL::Options() ) = 0;

    /** Train the probabilistic network with the supplied options. */
    virtual void train(Options const & options) = 0;

    /** Extend the probabilistic network to include additional data, as specified in the supplied options. */
    //virtual void extend(Options const & options) = 0;

    /**
     * Set the observed value of a node. If the node represents a discrete variable, the coordinates of the argument are rounded
     * to the nearest integers.
     */
    virtual void setObservation(Node * node, std::vector<double> const & value) = 0;

    /** Clear the observation at a node, marking it as unobserved. */
    virtual void clearObservation(Node * node) = 0;

    /** Clear the observations at all nodes. */
    virtual void clearAllObservations() = 0;

    /**
     * Perform inference on the probabilistic network, based on the current set of observations. The probability distributions
     * assigned to the query nodes can be recovered using the Node::prob() function.
     */
    virtual void doInference() = 0;

    /** Get a sample from the probabilistic network, conditioned on the current set of observations. */
    // virtual Sample getSample() = 0;

    /** Load the probabilistic network from a disk file. */
    virtual void load(std::string const & in_path) = 0;

    /** Save the probabilistic network to a disk file. */
    virtual void save(std::string const & out_path) const = 0;

    /** Print probabilistic network statistics. */
    virtual void printStats(std::ostream & os = std::cout) = 0;

    /** Get the number of nodes in the network. */
    long numNodes() const { return (long)nodes->size(); }

    /** Get an iterator to the beginning of the set of nodes. */
    NodeConstIterator nodesBegin() const { return nodes->begin(); }

    /** Get an iterator to the beginning of the set of nodes. */
    NodeIterator nodesBegin() { return nodes->begin(); }

    /** Get an iterator to the end of the set of nodes. */
    NodeConstIterator nodesEnd() const { return nodes->end(); }

    /** Get an iterator to the end of the set of nodes. */
    NodeIterator nodesEnd() { return nodes->end(); }

  protected:
    NodeSet * nodes;  ///< The set of nodes in the network. Edges are implicitly coded by parent/child pointers. OLD VERSION
}; // class Network

/** An interface for a network factory. Should be implemented and registered by each actual network. */
class SNL_API NetworkFactory
{
  public:
    /** Destructor. */
    virtual ~NetworkFactory() {}

    /** Create a network with the given name. The network must be destroyed using destroyNetwork(). */
    virtual Network * createNetwork(std::string const & name) = 0;

    /** Destroy a network created with createNetwork(). */
    virtual void destroyNetwork(Network * render_system) = 0;

}; // class NetworkFactory

/** Manages available network factories. */
class SNL_API NetworkManager
{
  public:
    /**
     * <b>[Internal]</b> Initialization routine. Don't call this directly unless absolutely necessary, use PluginManager::init()
     * instead.
     */
    static bool _init();

    /**
     * <b>[Internal]</b> Termination routine. Don't call this directly unless absolutely necessary, use PluginManager::finish()
     * instead.
     */
    static bool _finish();

    /**
     * Install a factory for a particular network type. The factory pointer should not be null.
     *
     * @return True if the factory was successfully installed, false if a factory of the specified type (with case-insensitive
     *   matching) is already installed.
     */
    static bool installFactory(std::string const & type, NetworkFactory * factory);

    /** Uninstall a factory for a particular renderystem type. The match is case-insensitive. */
    static void uninstallFactory(std::string const & type);

    /** Get a factory for network of a given type. An error is thrown if no such factory has been installed. */
    static NetworkFactory * getFactory(std::string const & type);

  private:
    typedef std::map<std::string, NetworkFactory *> FactoryMap;  ///< Maps network types to factory instances.

    static FactoryMap installed_factories;  ///< Set of installed factories, one for each network type.

}; // class NetworkManager

} // namespace SNL

#endif
