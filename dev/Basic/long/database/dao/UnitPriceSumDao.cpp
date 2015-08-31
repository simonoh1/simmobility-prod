/*
 * UnitPriceDao.cpp
 *
 *  Created on: Aug 20, 2015
 *      Author: gishara
 */
#include "UnitPriceSumDao.hpp"
#include "DatabaseHelper.hpp"

using namespace sim_mob::db;
using namespace sim_mob::long_term;

UnitPriceSumDao::UnitPriceSumDao(DB_Connection& connection): SqlAbstractDao<UnitPriceSum>(connection, EMPTY_STR ,EMPTY_STR, EMPTY_STR, EMPTY_STR,DB_GETALL_UNIT_PRICE_SUM_PER_PARCEL, EMPTY_STR)
{}

UnitPriceSumDao::~UnitPriceSumDao() {}

void UnitPriceSumDao::fromRow(Row& result, UnitPriceSum& outObj)
{
	outObj.fmParcelId = result.get<BigSerial>("fm_parcel_id", INVALID_ID);
    outObj.unitPriceSum = result.get<double>("unit_price_sum", 0.0);
}

void UnitPriceSumDao::toRow(UnitPriceSum& data, Parameters& outParams, bool update) {}



