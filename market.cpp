#include "market.h"
#include <algorithm>


Market::Market() {}


std::vector<Request> Market::AddAggressor(Request Aggressor)
{

    std::vector<Request> Trades = Aggress(Aggressor);
    std::sort(Trades.begin(), Trades.end());

    if (Aggressor.Quantity > 0U)
    {
        if (Aggressor.Side == RequestSide::Buy)
        {
            BuyOrders.insert({ Aggressor.Price, Aggressor });
        }
        else
        {
            SellOrders.insert({ Aggressor.Price, Aggressor });
        }
    }

    return Trades;
}

std::vector<Request> Market::Aggress(Request& Aggressor)
{
    std::map<Request, unsigned int> Trades;
    std::multimap<unsigned int, Request>::iterator RequestIt;

    if (Aggressor.Side == RequestSide::Buy)
    {
        for (RequestIt = SellOrders.begin(); 
            RequestIt != SellOrders.end() && RequestIt->second.Price <= Aggressor.Price && Aggressor.Quantity > 0U;)
        {
            if (!ComputeDeal(RequestIt->second, Aggressor, Trades))
            {
                RequestIt++;
                continue;
            }

            if (!RequestIt->second.Quantity)
            {
                RequestIt++;
                SellOrders.erase(std::prev(RequestIt));
            }
        }
    }
    else
    {
        for (RequestIt = BuyOrders.lower_bound(Aggressor.Price); 
            RequestIt != BuyOrders.end() && RequestIt->second.Price >= Aggressor.Price && Aggressor.Quantity > 0U;)
        {
            if (!ComputeDeal(RequestIt->second, Aggressor, Trades))
            {
                RequestIt++;
                continue;
            }

            if (!RequestIt->second.Quantity)
            {
                RequestIt++;
                BuyOrders.erase(std::prev(RequestIt));
            }
        }

    }

    return TradesMapToVector(Trades);
}


bool Market::ComputeDeal(Request& Req, Request& Aggressor, std::map<Request, unsigned int>& Trades)
{
    if (Req.Identifier == Aggressor.Identifier)
    {
        return false;
    }

    unsigned int Quantity = std::min(Aggressor.Quantity, Req.Quantity);
    Aggressor.Quantity -= Quantity;
    Req.Quantity -= Quantity;

    Trades[Request(Req.Identifier, Req.Side, 0U, Req.Price)] += Quantity;
    Trades[Request(Aggressor.Identifier, Aggressor.Side, 0U, Req.Price)] += Quantity;

    return true;
}


std::vector<Request> Market::TradesMapToVector(std::map<Request, unsigned int> TradesMap)
{
    std::vector<Request> TradesVector;
    for (auto Trade : TradesMap)
    {
        TradesVector.push_back(Request(Trade.first.Identifier, Trade.first.Side, Trade.second, Trade.first.Price));
    }

    return TradesVector;
}
