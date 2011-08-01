#include "Loader.hpp"

#include "soci/soci.h"
#include "soci/postgresql/soci-postgresql.h"

#include "Node.hpp"


using namespace sim_mob::aimsun;


namespace {

void LoadNodes(std::vector<Node>& nodelist)
{
	//Connect
	//NOTE: Our git repository is private (SSH-only) for now, so just storing the password to the DB here.
	soci::session sql(soci::postgresql, "host=localhost port=5432 dbname=SimMobility_DB user=postgres password=S!Mm0bility");

	//Statement
	int count;
	sql <<"select count(*) from get_node();", soci::into(count);

	std::cout <<"Found: " <<count <<" records\n";
}


} //End anon namespace


void sim_mob::aimsun::Loader::LoadNetwork(sim_mob::RoadNetwork& rn)
{
	//Load all nodes
	std::vector<Node> nodelist;
	LoadNodes(nodelist);

}
