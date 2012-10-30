// Not copyrighted - public domain.
//
// This sample parser implementation was generated by CodeSynthesis XSD,
// an XML Schema to C++ data binding compiler. You may use it in your
// programs without any restrictions.
//

#pragma once

//NOTE: This is a rare example of when relative path lookup is acceptable. ~Seth
#include "../skeleton/geo10-pskel.hpp"

#include "conf/simpleconf.hpp"
#include "geospatial/Point2D.hpp"


namespace sim_mob {
namespace xml {

//Note: Do NOT write constructors for these classes, since we don't want to risk C++'s finnicky constructor
// chaining mechanism. Instead, initialize all your private variables in the pre() function.

//TODO: Once the contents of geo10-pimpl.cpp have been moved into their own classes, consider grouping the header files here
//      into relevant, smaller header files. E.g., all the top-level stuff (Nodes, Links, Segments) can go in one, and the
//      supporting definitions can go in another. ~Seth

///Helper namespace: contains typedefs for particularly verbose items
namespace helper {

//Was: geo_UniNode_Connectors_type
typedef std::set<std::pair<unsigned long,unsigned long> > UniNodeConnectors;

//Was: geo_MultiNode_Connectors_type
typedef std::map<unsigned long, helper::UniNodeConnectors > MultiNodeConnectors;

} //End helper namespace



///TODO: Can we remove this class?
class temp_Segmetair_t_pimpl: public virtual temp_Segmetair_t_pskel {
public:
	virtual void pre () { model = std::make_pair(0, 0); }
	virtual std::pair<unsigned long,unsigned long> post_temp_Segmetair_t () { return model; }

	virtual void first (unsigned long long value) { model.first = value; }
	virtual void second (unsigned long long value) { model.second = value; }

private:
	std::pair<unsigned long,unsigned long> model;
};


class Point2D_t_pimpl: public virtual Point2D_t_pskel {
public:
	virtual void pre ();
    virtual sim_mob::Point2D post_Point2D_t ();

    virtual void xPos (unsigned int);
    virtual void yPos (unsigned int);

private:
    Point2D model;
};



class PolyPoint_t_pimpl: public virtual PolyPoint_t_pskel {
public:
    virtual void pre ();
    virtual sim_mob::Point2D post_PolyPoint_t ();

    virtual void pointID (const ::std::string&);
    virtual void location (sim_mob::Point2D);

private:
    //std::string savedID;
    sim_mob::Point2D model;
};



class PolyLine_t_pimpl: public virtual PolyLine_t_pskel {
public:
    virtual void pre ();
    virtual std::vector<sim_mob::Point2D> post_PolyLine_t ();

    virtual void PolyPoint (sim_mob::Point2D);

private:
    std::vector<sim_mob::Point2D> model;
};



class lane_t_pimpl: public virtual lane_t_pskel {
public:
	virtual void pre ();
	virtual sim_mob::Lane* post_lane_t ();

	virtual void laneID (unsigned long long);
	virtual void width (unsigned int);
	virtual void PolyLine (std::vector<sim_mob::Point2D>);

	virtual void can_go_straight (bool);
	virtual void can_turn_left (bool);
	virtual void can_turn_right (bool);
	virtual void can_turn_on_red_signal (bool);
	virtual void can_change_lane_left (bool);
	virtual void can_change_lane_right (bool);
	virtual void is_road_shoulder (bool);
	virtual void is_bicycle_lane (bool);
	virtual void is_pedestrian_lane (bool);
	virtual void is_vehicle_lane (bool);
	virtual void is_standard_bus_lane (bool);
	virtual void is_whole_day_bus_lane (bool);
	virtual void is_high_occupancy_vehicle_lane (bool);
	virtual void can_freely_park_here (bool);
	virtual void can_stop_here (bool);
	virtual void is_u_turn_allowed (bool);

private:
  sim_mob::Lane model;
};


class connector_t_pimpl: public virtual connector_t_pskel {
public:
	virtual void pre ();
	virtual std::pair<unsigned long,unsigned long> post_connector_t ();

	virtual void laneFrom (unsigned long long);
	virtual void laneTo (unsigned long long);

private:
	std::pair<unsigned long,unsigned long> model;
};


class connectors_t_pimpl: public virtual connectors_t_pskel {
public:
	virtual void pre ();
	virtual std::set<std::pair<unsigned long,unsigned long> > post_connectors_t ();

	virtual void Connector (std::pair<unsigned long,unsigned long>);

private:
	std::set<std::pair<unsigned long,unsigned long> > model;
};



class Multi_Connector_t_pimpl: public virtual Multi_Connector_t_pskel {
public:
	virtual void pre ();
	virtual std::pair<unsigned long,std::set<std::pair<unsigned long,unsigned long> > > post_Multi_Connector_t ();

	virtual void RoadSegment (unsigned long long);
	virtual void Connectors (std::set<std::pair<unsigned long,unsigned long> >);

private:
	//std::string RoadSegment_;
	std::pair<unsigned long,std::set<std::pair<unsigned long,unsigned long> > >  model;
};



class Multi_Connectors_t_pimpl: public virtual Multi_Connectors_t_pskel {
public:
	virtual void pre ();
	virtual std::map<unsigned long,std::set<std::pair<unsigned long,unsigned long> > > post_Multi_Connectors_t ();

	virtual void MultiConnectors (const std::pair<unsigned long,std::set<std::pair<unsigned long,unsigned long> > >&);

private:
	helper::MultiNodeConnectors model;
};



class fwdBckSegments_t_pimpl: public virtual fwdBckSegments_t_pskel {
public:
	virtual void pre ();
	virtual std::vector<sim_mob::RoadSegment*> post_fwdBckSegments_t ();

	virtual void Segment (sim_mob::RoadSegment*);

private:
  std::vector<sim_mob::RoadSegment*> model;

};



class RoadSegmentsAt_t_pimpl: public virtual RoadSegmentsAt_t_pskel {
public:
	virtual void pre ();
	virtual std::set<unsigned long> post_RoadSegmentsAt_t ();

	virtual void segmentID (unsigned long long);

private:
  std::set<unsigned long> model;
};



class laneEdgePolyline_cached_t_pimpl: public virtual laneEdgePolyline_cached_t_pskel {
public:
	virtual void pre ();
	virtual std::pair<short,std::vector<sim_mob::Point2D> > post_laneEdgePolyline_cached_t ();

	virtual void laneNumber (short);
	virtual void polyline (std::vector<sim_mob::Point2D>);

private:
  std::pair<short,std::vector<sim_mob::Point2D> > model;
};



class laneEdgePolylines_cached_t_pimpl: public virtual laneEdgePolylines_cached_t_pskel {
public:
	virtual void pre ();
	virtual std::vector<std::vector<sim_mob::Point2D> > post_laneEdgePolylines_cached_t ();

	virtual void laneEdgePolyline_cached (std::pair<short,std::vector<sim_mob::Point2D> >);

  private:
  std::vector<std::vector<sim_mob::Point2D> > model;
};



class segment_t_pimpl: public virtual segment_t_pskel {
public:
	virtual void pre ();
	virtual sim_mob::RoadSegment* post_segment_t ();

	virtual void segmentID (unsigned long long);
	virtual void startingNode (unsigned int);
	virtual void endingNode (unsigned int);
	virtual void maxSpeed (short);
	virtual void Length (unsigned int);
	virtual void Width (unsigned int);
	virtual void originalDB_ID (const ::std::string&);
	virtual void polyline (std::vector<sim_mob::Point2D>);
	virtual void laneEdgePolylines_cached (std::vector<std::vector<sim_mob::Point2D> >);
	virtual void Lanes (std::vector<sim_mob::Lane*>);
	virtual void Obstacles (std::map<sim_mob::centimeter_t,const RoadItem*>);
	virtual void KurbLine (std::vector<sim_mob::Point2D>);

private:
  sim_mob::RoadSegment model;
};



class link_t_pimpl: public virtual link_t_pskel {
public:
	virtual void pre ();
	virtual sim_mob::Link* post_link_t ();

	virtual void linkID (unsigned int);
	virtual void roadName (const ::std::string&);
	virtual void StartingNode (unsigned int);
	virtual void EndingNode (unsigned int);
	virtual void Segments (std::pair<std::vector<sim_mob::RoadSegment*>,std::vector<sim_mob::RoadSegment*> >);

private:
	sim_mob::Link model;
};



class separator_t_pimpl: public virtual separator_t_pskel {
public:
	virtual void pre ();
	virtual void post_separator_t ();

	virtual void separator_ID (unsigned short);
	virtual void separator_value (bool);
};



class separators_t_pimpl: public virtual separators_t_pskel {
public:
	virtual void pre ();
	virtual void post_separators_t ();

	virtual void Separator ();
};



class DomainIsland_t_pimpl: public virtual DomainIsland_t_pskel {
public:
	virtual void pre ();
	virtual void post_DomainIsland_t ();

	virtual void domainIsland_ID (unsigned short);
	virtual void domainIsland_value (bool);
};


class DomainIslands_t_pimpl: public virtual DomainIslands_t_pskel {
public:
	virtual void pre ();
	virtual void post_DomainIslands_t ();

	virtual void domainIslands ();
};



class offset_t_pimpl: public virtual offset_t_pskel {
public:
	virtual void pre ();
	virtual void post_offset_t ();

	virtual void offset_ID (unsigned short);
	virtual void offset_value (unsigned int);
};


class offsets_t_pimpl: public virtual offsets_t_pskel {
public:
	virtual void pre ();
	virtual void post_offsets_t ();

	virtual void offset ();
};



class ChunkLength_t_pimpl: public virtual ChunkLength_t_pskel
{
public:
	virtual void pre ();
	virtual void post_ChunkLength_t ();

	virtual void chunklength_ID (unsigned short);
	virtual void chunklength_value (unsigned int);
};


class ChunkLengths_t_pimpl: public virtual ChunkLengths_t_pskel {
public:
	virtual void pre ();
	virtual void post_ChunkLengths_t ();

	virtual void chunklength ();
};


class LanesVector_t_pimpl: public virtual LanesVector_t_pskel {
public:
	virtual void pre ();
	virtual void post_LanesVector_t ();

	virtual void laneID (unsigned long long);
};


class EntranceAngle_t_pimpl: public virtual EntranceAngle_t_pskel {
public:
	virtual void pre ();
	virtual void post_EntranceAngle_t ();

	virtual void entranceAngle_ID (unsigned short);
	virtual void entranceAngle_value (unsigned int);
};



class EntranceAngles_t_pimpl: public virtual EntranceAngles_t_pskel {
public:
	virtual void pre ();
	virtual void post_EntranceAngles_t ();

	virtual void entranceAngle ();
};



class Node_t_pimpl: public virtual Node_t_pskel {
public:
	virtual void pre ();
	virtual sim_mob::Node* post_Node_t ();

	virtual void nodeID (unsigned int);
	virtual void location (sim_mob::Point2D);
	virtual void linkLoc (unsigned long long);
	virtual void originalDB_ID (const ::std::string&);

	static void RegisterLinkLoc(sim_mob::Node* node, unsigned int link);
	static unsigned int GetLinkLoc(sim_mob::Node* node);
	static std::map<sim_mob::Node*, unsigned int>& GetLinkLocList();

private:
	sim_mob::Node model;
	unsigned int linkLocSaved;

	static std::map<sim_mob::Node*, unsigned int> LinkLocCache;
};




class UniNode_t_pimpl: public virtual UniNode_t_pskel, public ::sim_mob::xml::Node_t_pimpl {
public:
	typedef std::set<std::pair<unsigned long,unsigned long> > LaneConnectSet;
	typedef std::pair<unsigned long,unsigned long> SegmentPair;

	virtual void pre ();
	virtual sim_mob::UniNode* post_UniNode_t ();

	virtual void firstPair (std::pair<unsigned long,unsigned long>);
	virtual void secondPair (std::pair<unsigned long,unsigned long>);
	virtual void Connectors (LaneConnectSet);

	static void RegisterConnectors(sim_mob::UniNode* lane, const LaneConnectSet& connectors);
	static LaneConnectSet GetConnectors(sim_mob::UniNode* lane);

	static void RegisterSegmentPairs(sim_mob::UniNode* lane, const std::pair<SegmentPair, SegmentPair>& pairs);
	static std::pair<SegmentPair, SegmentPair> GetSegmentPairs(sim_mob::UniNode* lane);

private:
	//NOTE: This parameter name shadows Node::model, but this might be the right way to do things anyway.
	sim_mob::UniNode model;

	//Due to a load cycle, we have to save these as integers.
	LaneConnectSet connectors;
	std::pair<SegmentPair, SegmentPair> segmentPairs;

	static std::map<sim_mob::UniNode*, LaneConnectSet> ConnectCache;
	static std::map<sim_mob::UniNode*, std::pair<SegmentPair, SegmentPair> > SegmentPairCache;
};




//Note: Already done
class intersection_t_pimpl: public virtual intersection_t_pskel, public ::sim_mob::xml::Node_t_pimpl {
public:
	typedef std::map<unsigned long,std::set<std::pair<unsigned long,unsigned long> > > LaneConnectSet;
	typedef std::set<unsigned long> RoadSegmentSet;

	virtual void pre ();
	virtual sim_mob::MultiNode* post_intersection_t ();

	virtual void roadSegmentsAt (RoadSegmentSet);
	virtual void Connectors (const LaneConnectSet&);
	virtual void ChunkLengths ();
	virtual void Offsets ();
	virtual void Separators ();
	virtual void additionalDominantLanes ();
	virtual void additionalSubdominantLanes ();
	virtual void domainIslands ();

	static void RegisterConnectors(sim_mob::MultiNode* intersection, const LaneConnectSet& connectors);
	static LaneConnectSet GetConnectors(sim_mob::MultiNode* intersection);

	static void RegisterSegmentsAt(sim_mob::MultiNode* intersection, const RoadSegmentSet& segmentsAt);
	static RoadSegmentSet GetSegmentsAt(sim_mob::MultiNode* intersection);

private:
	sim_mob::Intersection model;
	LaneConnectSet connectors;
	RoadSegmentSet segmentsAt;

	static std::map<sim_mob::MultiNode*, LaneConnectSet> ConnectCache;
	static std::map<sim_mob::MultiNode*, RoadSegmentSet> SegmentsAtCache;
};



class roundabout_t_pimpl: public virtual roundabout_t_pskel,
  public ::sim_mob::xml::Node_t_pimpl
{
  public:
  virtual void
  pre ();

  virtual void
  roadSegmentsAt (std::set<unsigned long>);

  virtual void
  Connectors (const std::map<unsigned long,std::set<std::pair<unsigned long,unsigned long> > >&);

  virtual void
  ChunkLengths ();

  virtual void
  Offsets ();

  virtual void
  Separators ();

  virtual void
  addDominantLane ();

  virtual void
  roundaboutDominantIslands (float);

  virtual void
  roundaboutNumberOfLanes (int);

  virtual void
  entranceAngles ();

  virtual sim_mob::MultiNode*
  post_roundabout_t ();
};




class RoadItem_t_pimpl: public virtual RoadItem_t_pskel
{
	  unsigned long id_;
	  unsigned short Offset_;
	  sim_mob::Point2D start_,end_;
  public:
  virtual void
  pre ();

  virtual void
  id (unsigned long long);

  virtual void
  Offset (unsigned short);

  virtual void
  start (sim_mob::Point2D);

  virtual void
  end (sim_mob::Point2D);

  virtual std::pair<unsigned long,sim_mob::RoadItem*>
  post_RoadItem_t ();
};

class BusStop_t_pimpl: public virtual BusStop_t_pskel,
  public ::sim_mob::xml::RoadItem_t_pimpl
{
	  sim_mob::BusStop *bs;

  public:
  virtual void
  pre ();

  virtual void
  xPos (double);

  virtual void
  yPos (double);

  virtual void
  lane_location (unsigned long long);

  virtual void
  is_terminal (bool);

  virtual void
  is_bay (bool);

  virtual void
  has_shelter (bool);

  virtual void
  busCapacityAsLength (unsigned int);

  virtual void
  busstopno (const ::std::string&);

  virtual std::pair<unsigned long,sim_mob::BusStop*>
  post_BusStop_t ();
};

class ERP_Gantry_t_pimpl: public virtual ERP_Gantry_t_pskel,
  public ::sim_mob::xml::RoadItem_t_pimpl
{
  public:
  virtual void
  pre ();

  virtual void
  ERP_GantryID (const ::std::string&);

  virtual void
  post_ERP_Gantry_t ();
};

class FormType_pimpl: public virtual FormType_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  TextBox (int);

  virtual void
  TextArea (int);

  virtual void
  Header (int);

  virtual void
  post_FormType ();
};

class PointPair_t_pimpl: public virtual PointPair_t_pskel
{
	  std::pair<sim_mob::Point2D,sim_mob::Point2D> pointPair;
  public:
  virtual void
  pre ();

  virtual void
  first (sim_mob::Point2D);

  virtual void
  second (sim_mob::Point2D);

  virtual std::pair<sim_mob::Point2D,sim_mob::Point2D>
  post_PointPair_t ();
};

class crossing_t_pimpl: public virtual crossing_t_pskel,
  public ::sim_mob::xml::RoadItem_t_pimpl
{
	  sim_mob::Crossing *crossing;
  public:
  virtual void
  pre ();

  virtual void
  nearLine (std::pair<sim_mob::Point2D,sim_mob::Point2D>);

  virtual void
  farLine (std::pair<sim_mob::Point2D,sim_mob::Point2D>);

  virtual std::pair<unsigned long,sim_mob::Crossing*>
  post_crossing_t ();
};

class RoadBump_t_pimpl: public virtual RoadBump_t_pskel,
  public ::sim_mob::xml::RoadItem_t_pimpl
{
  public:
  virtual void
  pre ();

  virtual void
  roadBumpID (const ::std::string&);

  virtual void
  segmentID (unsigned long long);

  virtual void
  post_RoadBump_t ();
};

class RoadNetwork_t_pimpl: public virtual RoadNetwork_t_pskel
{
	  sim_mob::RoadNetwork &rn;
  public:
	  RoadNetwork_t_pimpl();
  virtual void
  pre ();

  virtual void
  Nodes ();

  virtual void
  Links (std::vector<sim_mob::Link*>);

  virtual void
  post_RoadNetwork_t ();
};

class RoadItems_t_pimpl: public virtual RoadItems_t_pskel
{
	  std::map<centimeter_t,const RoadItem*> RoadItems;
  public:
  virtual void
  pre ();

  virtual void
  BusStop (std::pair<unsigned long,sim_mob::BusStop*>);

  virtual void
  ERP_Gantry ();

  virtual void
  Crossing (std::pair<unsigned long,sim_mob::Crossing*>);

  virtual void
  RoadBump ();

  virtual std::map<sim_mob::centimeter_t,const RoadItem*>
  post_RoadItems_t ();
};

class TripchainItemType_pimpl: public virtual TripchainItemType_pskel,
  public ::xml_schema::string_pimpl
{
  public:
  virtual void
  pre ();

  virtual std::string
  post_TripchainItemType ();
};

class TripchainItemLocationType_pimpl: public virtual TripchainItemLocationType_pskel,
  public ::xml_schema::string_pimpl
{
  public:
  virtual void
  pre ();

  virtual std::string
  post_TripchainItemLocationType ();
};

class TripChainItem_t_pimpl: public virtual TripChainItem_t_pskel
{
	  std::string itemType_;
	  long personID_;
	  unsigned int sequenceNumber_;
	  std::string startTime_,endTime_;
	  sim_mob::TripChainItem *tcItem;
  public:
  virtual void
  pre ();

  virtual void
  personID (long long);

  virtual void
  itemType (std::string);

  virtual void
  sequenceNumber (unsigned int);

  virtual void
  startTime (const ::std::string&);

  virtual void
  endTime (const ::std::string&);

  virtual sim_mob::TripChainItem*
  post_TripChainItem_t ();
};

class Trip_t_pimpl: public virtual Trip_t_pskel,
  public ::sim_mob::xml::TripChainItem_t_pimpl
{
	  sim_mob::Trip * trip;
  public:
  virtual void
  pre ();

  virtual void
  tripID (long long);

  virtual void
  fromLocation (unsigned int);

  virtual void
  fromLocationType (std::string);

  virtual void
  toLocation (unsigned int);

  virtual void
  toLocationType (std::string);

  virtual void
  subTrips (std::vector<sim_mob::SubTrip>);

  virtual sim_mob::TripChainItem*
  post_Trip_t ();
};

class SubTrip_t_pimpl: public virtual SubTrip_t_pskel,
  public ::sim_mob::xml::Trip_t_pimpl
{
	  sim_mob::SubTrip subTrip;
  public:
  virtual void
  pre ();

  virtual void
  mode (const ::std::string&);

  virtual void
  isPrimaryMode (bool);

  virtual void
  ptLineId (const ::std::string&);

  virtual sim_mob::SubTrip
  post_SubTrip_t ();
};

class SubTrips_t_pimpl: public virtual SubTrips_t_pskel
{
	  std::vector<sim_mob::SubTrip> subTrips;
  public:
  virtual void
  pre ();

  virtual void
  subTrip (sim_mob::SubTrip);

  virtual std::vector<sim_mob::SubTrip>
  post_SubTrips_t ();
};

class Activity_t_pimpl: public virtual Activity_t_pskel,
  public ::sim_mob::xml::TripChainItem_t_pimpl
{
	  sim_mob::Activity *activity;
  public:
  virtual void
  pre ();

  virtual void
  description (const ::std::string&);

  virtual void
  location (unsigned int);

  virtual void
  locationType (std::string);

  virtual void
  isPrimary (bool);

  virtual void
  isFlexible (bool);

  virtual void
  isMandatory (bool);

  virtual sim_mob::TripChainItem*
  post_Activity_t ();
};

class TripChain_t_pimpl: public virtual TripChain_t_pskel
{
	  std::pair<unsigned long, std::vector<sim_mob::TripChainItem*> > personID_Tripchain_Pair;
  public:
  virtual void
  pre ();

  virtual void
  personID (long long);

  virtual void
  Trip (sim_mob::TripChainItem*);

  virtual void
  Activity (sim_mob::TripChainItem*);

  virtual std::pair<unsigned long, std::vector<sim_mob::TripChainItem*> >
  post_TripChain_t ();
};

class TripChains_t_pimpl: public virtual TripChains_t_pskel
{
	  std::map<unsigned int, std::vector<sim_mob::TripChainItem*> > tripchains;
  public:
  virtual void
  pre ();

  virtual void
  TripChain (std::pair<unsigned long, std::vector<sim_mob::TripChainItem*> >);

  virtual void
  post_TripChains_t ();
};

class linkAndCrossing_t_pimpl: public virtual linkAndCrossing_t_pskel
{
	  struct LinkAndCrossing LAC;
  public:
  virtual void
  pre ();

  virtual void
  ID (unsigned char);

  virtual void
  linkID (unsigned int);

  virtual void
  crossingID (unsigned int);

  virtual void
  angle (unsigned char);

  virtual sim_mob::LinkAndCrossing
  post_linkAndCrossing_t ();
};

class linkAndCrossings_t_pimpl: public virtual linkAndCrossings_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  linkAndCrossing (sim_mob::LinkAndCrossing);

  virtual sim_mob::LinkAndCrossingC
  post_linkAndCrossings_t ();
};

class signalAlgorithm_t_pimpl: public virtual signalAlgorithm_t_pskel,
  public ::xml_schema::string_pimpl
{
  public:
  virtual void
  pre ();

  virtual void
  post_signalAlgorithm_t ();
};

class Plan_t_pimpl: public virtual Plan_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  planID (unsigned char);

  virtual void
  PhasePercentage (double);

  virtual void
  post_Plan_t ();
};

class Plans_t_pimpl: public virtual Plans_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  Plan ();

  virtual void
  post_Plans_t ();
};

class TrafficColor_t_pimpl: public virtual TrafficColor_t_pskel,
  public ::xml_schema::string_pimpl
{
  public:
  virtual void
  pre ();

  virtual void
  post_TrafficColor_t ();
};

class ColorDuration_t_pimpl: public virtual ColorDuration_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  TrafficColor ();

  virtual void
  Duration (unsigned char);

  virtual std::pair<sim_mob::TrafficColor,std::size_t>
  post_ColorDuration_t ();
};

class ColorSequence_t_pimpl: public virtual ColorSequence_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  TrafficLightType (const ::std::string&);

  virtual void
  ColorDuration (std::pair<sim_mob::TrafficColor,std::size_t>);

  virtual std::pair<std::string,std::vector<std::pair<TrafficColor,std::size_t> > >
  post_ColorSequence_t ();
};

class links_maps_t_pimpl: public virtual links_maps_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  links_map (std::pair<sim_mob::Link*,sim_mob::linkToLink>);

  virtual std::multimap<sim_mob::Link*,sim_mob::linkToLink>
  post_links_maps_t ();
};

class links_map_t_pimpl: public virtual links_map_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  linkFrom (unsigned int);

  virtual void
  linkTo (unsigned int);

  virtual void
  SegmentFrom (unsigned int);

  virtual void
  SegmentTo (unsigned int);

  virtual void
  ColorSequence (std::pair<std::string,std::vector<std::pair<TrafficColor,std::size_t> > >);

  virtual std::pair<sim_mob::Link*,sim_mob::linkToLink>
  post_links_map_t ();
};

class Phase_t_pimpl: public virtual Phase_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  phaseID (unsigned char);

  virtual void
  name (const ::std::string&);

  virtual void
  links_map (std::multimap<sim_mob::Link*,sim_mob::linkToLink>);

  virtual void
  post_Phase_t ();
};

class Phases_t_pimpl: public virtual Phases_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  Phase ();

  virtual void
  post_Phases_t ();
};

class SplitPlan_t_pimpl: public virtual SplitPlan_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  splitplanID (unsigned int);

  virtual void
  signalAlgorithm ();

  virtual void
  cycleLength (unsigned char);

  virtual void
  offset (unsigned char);

  virtual void
  ChoiceSet ();

  virtual void
  Phases ();

  virtual sim_mob::SplitPlan
  post_SplitPlan_t ();
};

class Signal_t_pimpl: public virtual Signal_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  signalID (unsigned char);

  virtual void
  nodeID (unsigned int);

  virtual void
  signalAlgorithm ();

  virtual void
  linkAndCrossings (sim_mob::LinkAndCrossingC);

  virtual void
  SplitPlan (sim_mob::SplitPlan);

  virtual sim_mob::Signal*
  post_Signal_t ();
};

class Signals_t_pimpl: public virtual Signals_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  signal (sim_mob::Signal*);

  virtual void
  post_Signals_t ();
};



///NOTE: Already done.
class GeoSpatial_t_pimpl: public virtual GeoSpatial_t_pskel {
public:
	virtual void pre ();
	virtual void post_GeoSpatial_t ();

	virtual void RoadNetwork ();
};



class SimMobility_t_pimpl: public virtual SimMobility_t_pskel
{
  public:
  virtual void
  pre ();

  virtual void
  GeoSpatial ();

  virtual void
  TripChains ();

  virtual void
  Signals ();

  virtual void
  post_SimMobility_t ();
};


//NOTE: Done already.
class Lanes_pimpl: public virtual Lanes_pskel {
public:
	virtual void pre ();
	virtual std::vector<sim_mob::Lane*> post_Lanes ();

	virtual void Lane (sim_mob::Lane*);

	static sim_mob::Lane* LookupLane(unsigned int id);
	static void RegisterLane(unsigned int id, sim_mob::Lane* lane);

private:
	std::vector<sim_mob::Lane*> model;

	static std::map<unsigned int,sim_mob::Lane*> Lookup;
};



//NOTE: Already done.
class Segments_pimpl: public virtual Segments_pskel {
public:
	typedef std::vector<sim_mob::RoadSegment*> SegmentList;

	virtual void pre ();
	virtual std::pair<SegmentList, SegmentList> post_Segments (); //Fwd, back segments

	virtual void FWDSegments (std::vector<sim_mob::RoadSegment*>);
	virtual void BKDSegments (std::vector<sim_mob::RoadSegment*>);

	static sim_mob::RoadSegment* LookupSegment(unsigned int id);
	static void RegisterSegment(unsigned int id, sim_mob::RoadSegment* seg);

private:
	SegmentList fwd;
	SegmentList rev;
	//SegmentList unique;

	static std::map<unsigned int, sim_mob::RoadSegment*> Lookup;
};



//NOTE: Need to clean up reference to the singleton ConfigParams instance!
class Nodes_pimpl: public virtual Nodes_pskel {
public:
	Nodes_pimpl():rn(sim_mob::ConfigParams::GetInstance().getNetworkRW()){
		std::cout << "RoadNetworkRW hooked\nTODO: This is not the correct way to do things!";
	}

	virtual void pre ();
	virtual void post_Nodes ();

	virtual void UniNodes (std::set<sim_mob::UniNode*>&);
	virtual void Intersections (std::vector<sim_mob::MultiNode*>&);
	virtual void roundabouts (std::vector<sim_mob::MultiNode*>&);

	static sim_mob::Node* LookupNode(unsigned int id);
	static void RegisterNode(unsigned int id, sim_mob::Node* node);

private:
	sim_mob::RoadNetwork &rn;

	static std::map<unsigned int,sim_mob::Node*> Lookup;
};


//NOTE: Need to clean up reference to the singleton ConfigParams instance!
class Links_pimpl: public virtual Links_pskel {
public:
	virtual void pre ();
	virtual std::vector<sim_mob::Link*> post_Links ();

	virtual void Link (sim_mob::Link*);

	static sim_mob::Link* LookupLink(unsigned int id);
	static void RegisterLink(unsigned int id, sim_mob::Link* node);

private:
	std::vector<sim_mob::Link*> model;
	static std::map<unsigned int,sim_mob::Link*> Lookup;
};

class UniNodes_pimpl: public virtual UniNodes_pskel
{
	  std::set<sim_mob::UniNode*> uniNodes;
  public:
  virtual void
  pre ();

  virtual void
  UniNode (sim_mob::UniNode*);

  virtual std::set<sim_mob::UniNode*>&
  post_UniNodes ();
};

class Intersections_pimpl: public virtual Intersections_pskel
{
	  std::vector<sim_mob::MultiNode*> intersections;
  public:
  virtual void
  pre ();

  virtual void
  Intersection (sim_mob::MultiNode*);

  virtual std::vector<sim_mob::MultiNode*>&
  post_Intersections ();
};

class roundabouts_pimpl: public virtual roundabouts_pskel
{
	  std::vector<sim_mob::MultiNode*> roundabouts;
  public:
  virtual void
  pre ();

  virtual void
  roundabout (sim_mob::MultiNode*);

  virtual std::vector<sim_mob::MultiNode*>&
  post_roundabouts ();
};


}} //End namespace sim_mob::xml

