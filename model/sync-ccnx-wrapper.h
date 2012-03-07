/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Zhenkai Zhu <zhenkai@cs.ucla.edu>
 *         卞超轶 Chaoyi Bian <bcy@pku.edu.cn>
 *	   Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef SYNC_CCNX_WRAPPER_H
#define SYNC_CCNX_WRAPPER_H

extern "C" {
#include <ccn/ccn.h>
#include <ccn/charbuf.h>
#include <ccn/keystore.h>
#include <ccn/uri.h>
#include <ccn/bloom.h>
#include <ccn/signing.h>
}

#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>
#include <string>

/**
 * \defgroup sync SYNC protocol
 *
 * Implementation of SYNC protocol
 */
namespace Sync {

/**
 * \ingroup sync
 * @brief A wrapper for ccnx library; clients of this code do not need to deal
 * with ccnx library
 */
class CcnxWrapper {
private:
	ccn* m_handle;
	ccn_keystore *m_keyStore;
	ccn_charbuf *m_keyLoactor;
	// to lock, use "boost::recursive_mutex::scoped_lock scoped_lock(mutex);
	boost::recursive_mutex m_mutex;
	boost::thread m_thread;

private:
	void createKeyLocator();
	void initKeyStore();
	const ccn_pkey *getPrivateKey();
	const unsigned char *getPublicKeyDigest();
	ssize_t getPublicKeyDigestLength();
	void ccnLoop();
	bool running;

public:

  /**
   * @brief initialize the wrapper; a lot of things needs to be done. 1) init
   * keystore 2) init keylocator 3) start a thread to hold a loop of ccn_run
   *
   */
   CcnxWrapper();
   ~CcnxWrapper();

  /**
   * @brief send Interest; need to grab lock m_mutex first
   *
   * @param strInterest the Interest name
   * @param dataCallback the callback function to deal with the returned data
   * @return the return code of ccn_express_interest
   */
   int sendInterest(std::string strInterest, boost::function<void (std::string)>
   dataCallback);

  /**
   * @brief set Interest filter (specify what interest you want to receive
   *
   * @param prefix the prefix of Interest
   * @param interestCallback the callback function to deal with the returned data
   * @return the return code of ccn_set_interest_filter
   */
   int setInterestFilter(std::string prefix, boost::function<void (std::string)>
   interestCallback);

  /**
   * @brief publish data and put it to local ccn content store; need to grab
   * lock m_mutex first
   *
   * @param name the name for the data object
   * @param dataBuffer the data to be published
   * @param freshness the freshness time for the data object
   * @return code generated by ccnx library calls, >0 if success
   */
   int publishData(std::string name, std::string dataBuffer, int freshness);

};

} // Sync

#endif // SYNC_CCNX_WRAPPER_H
