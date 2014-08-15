/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012-2014 University of California, Los Angeles
 *
 * This file is part of ChronoSync, synchronization library for distributed realtime
 * applications for NDN.
 *
 * ChronoSync is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * ChronoSync is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ChronoSync, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Alexander Afanasyev <http://lasr.cs.ucla.edu/afanasyev/index.html>
 * @author Yingdi Yu <yingdi@cs.ucla.edu>
 */

#ifndef CHRONOSYNC_COMMON_HPP
#define CHRONOSYNC_COMMON_HPP

#include "config.hpp"

#ifdef _TESTS
#define VIRTUAL_WITH_TESTS virtual
#define PUBLIC_WITH_TESTS_ELSE_PROTECTED public
#define PUBLIC_WITH_TESTS_ELSE_PRIVATE public
#define PROTECTED_WITH_TESTS_ELSE_PRIVATE protected
#else
#define VIRTUAL_WITH_TESTS
#define PUBLIC_WITH_TESTS_ELSE_PROTECTED protected
#define PUBLIC_WITH_TESTS_ELSE_PRIVATE private
#define PROTECTED_WITH_TESTS_ELSE_PRIVATE private
#endif

#include <cstddef>
#include <list>
#include <set>
#include <queue>
#include <vector>

#include <ndn-cxx/common.hpp>
#include <ndn-cxx/interest.hpp>
#include <ndn-cxx/data.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/scoped_ptr.hpp>

namespace chronosync {

using std::size_t;

using boost::noncopyable;
using boost::scoped_ptr;

using ndn::shared_ptr;
using ndn::weak_ptr;
using ndn::enable_shared_from_this;
using ndn::make_shared;
using ndn::static_pointer_cast;
using ndn::dynamic_pointer_cast;
using ndn::const_pointer_cast;
using ndn::function;
using ndn::bind;
using ndn::ref;
using ndn::cref;

using ndn::Interest;
using ndn::Data;
using ndn::Name;
using ndn::Exclude;
using ndn::Block;

namespace tlv {
using namespace ndn::Tlv;
}

namespace name = ndn::name;
namespace time = ndn::time;

} // namespace chronosync

#endif // CHRONOSYNC_COMMON_HPP
