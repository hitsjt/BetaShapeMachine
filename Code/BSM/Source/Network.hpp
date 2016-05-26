//============================================================================
//
// This file is part of the SNL library.
//
// This software is covered by the following BSD license, except for portions
// derived from other works which are covered by their respective licenses.
// For full licensing information including reproduction of these external
// licenses, see the file LICENSE.txt provided in the documentation.
//
// Copyright (c) 2012, Stanford University
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holders nor the names of contributors
// to this software may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
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
