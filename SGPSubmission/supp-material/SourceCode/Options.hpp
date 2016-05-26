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

#ifndef __SNL_Options_hpp__
#define __SNL_Options_hpp__

#include "Common.hpp"
#include <sstream>
#include <string>
#include <map>

namespace SNL {

	/** A set of options, specified as key-value pairs. */
	class SNL_API Options : private std::map<std::string, std::string>
	{

	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			// serialize base class information
			ar & boost::serialization::base_object< std::map<std::string, std::string> >(*this);
		}

	public:
		/** Check if an option has been set. */
		bool hasOption(std::string const & option_name) const { return find(option_name) != end(); }

		/** Set the value of an option. */
		template <typename T> void set(std::string const & option_name, T const & value)
		{
			std::ostringstream oss; oss << value;
			(*this)[option_name] = oss.str();
		}

		/** Set the value of an option from a string. */
		void set(std::string const & option_name, std::string const & value) { (*this)[option_name] = value; }

		/** Set the value of an option from a C-style string. It should be read back as a <code>std::string</code>. */
		void set(std::string const & option_name, char const * value) { (*this)[option_name] = std::string(value); }

		/**
		* Get the value of an option. If the option has not been set, the default value specified by the last parameter is
		* returned.
		*/
		template <typename T> T get(std::string const & option_name, T const & default_value) const
		{
			const_iterator existing = find(option_name);
			if (existing != end())
			{
				T value;
				std::istringstream iss(existing->second);
				iss >> value;
				return value;
			}
			else
				return default_value;
		}

		/**
		* Get the value of an option as a string. If the option has not been set, the default value specified by the last parameter
		* is returned.
		*/
		std::string const & get(std::string const & option_name, std::string const & default_value) const
		{
			const_iterator existing = find(option_name);
			if (existing != end())
				return existing->second;
			else
				return default_value;
		}

		/** Merge all options from a second set of options into this set. Values with duplicate keys are overwritten. */
		void merge(Options const & options)
		{
			for (const_iterator ii = options.begin(); ii != options.end(); ++ii)
				set(ii->first, ii->second);
		}

	}; // class Options

} // namespace SNL

#endif
