//Copyright (c) 2013 Singapore-MIT Alliance for Research and Technology
//Licensed under the terms of the MIT License, as described in the file:
//   license.txt   (http://opensource.org/licenses/MIT)

/**
 * \file partitions/Serialization.cpp
 * Chain-load any files to make a class boost::serialize-able.
 * Use this class to avoid adding #ifdef's directly into classes like Agent, etc.
 *
 * \author Seth N. Hetu
 */

#pragma once

#include "conf/settings/DisableMPI.h"

#ifndef SIMMOB_DISABLE_MPI
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#endif



