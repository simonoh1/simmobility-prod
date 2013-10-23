/*
 * MULTICAST_Message.h
 *
 *  Created on: May 9, 2013
 *      Author: vahid
 */

#ifndef RR_ANDROID_MULTICAST_MESSAGE_HPP_
#define RR_ANDROID_MULTICAST_MESSAGE_HPP_
//#include "entities/commsim/message/derived/roadrunner-androidRoadrunnerMessage.hpp"
#include "entities/commsim/message/base/Message.hpp"
namespace sim_mob {
namespace roadrunner {

//class MSG_MULTICAST : public sim_mob::roadrunner::RoadrunnerMessage {
class MSG_MULTICAST : public sim_mob::comm::Message<msg_data_t> {
	//...
public:
	Handler * newHandler();
	MSG_MULTICAST(msg_data_t data_);
};


//Handler for the above message
class HDL_MULTICAST : public Handler {

public:
	void handle(msg_ptr message_,Broker*);
};

}/* namespace roadrunner */
} /* namespace sim_mob */
#endif /* MULTICAST_MESSAGE_H_ */
