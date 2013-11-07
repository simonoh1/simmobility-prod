//Copyright (c) 2013 Singapore-MIT Alliance for Research and Technology
//Licensed under the terms of the MIT License, as described in the file:
//   license.txt   (http://opensource.org/licenses/MIT)

/*
 * UNICAST_Message.h
 *
 *  Created on: May 9, 2013
 *      Author: vahid
 */

#pragma once

#include "entities/commsim/message/Types.hpp"
#include "entities/commsim/message/base/Message.hpp"
#include "entities/commsim/message/base/UnicastHandler.hpp"

namespace sim_mob {
namespace roadrunner {

class UnicastMessage : public sim_mob::comm::Message {
public:
	UnicastMessage(sim_mob::comm::MsgData& data_, bool useNs3) : Message(data_), useNs3(useNs3)
	{}

	sim_mob::Handler* newHandler() {
		return new sim_mob::roadrunner::UnicastHandler(useNs3);
	}

private:
	bool useNs3;
};

}}

