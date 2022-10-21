#include <iostream>
#include <vector>
#include "request.h"
#include "market.h"

void Simulate()
{
    Market TradeMarker;
    Request Req;
    std::vector<Request> AggressorResult;

    while (true) 
    {
        std::cin >> Req;

        AggressorResult = TradeMarker.AddAggressor(Req);

        if (AggressorResult.size())
        {
            for (const auto& Trade : AggressorResult)
            {
                std::cout << Trade << ' ';
            }
            std::cout << '\n';
        }
    }
}

int main() 
{
    Simulate();
}