#pragma once

#include <map>
#include <vector>
#include "request.h"


class Market
{
private:
    std::multimap<unsigned int, Request> BuyOrders;
    std::multimap<unsigned int, Request> SellOrders;

public:
    Market();

    std::vector<Request> AddAggressor(Request Aggressor);

private:
    std::vector<Request> Aggress(Request& Aggressor);

    std::vector<Request> TradesMapToVector(std::map<Request, unsigned int> TradesMap);

    bool ComputeDeal(Request& Req, Request& Aggressor, std::map<Request, unsigned int>& Trades);
    
};