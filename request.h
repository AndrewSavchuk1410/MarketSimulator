#pragma once

#include <string>
#include <iostream>

enum class RequestSide
{
    Sell,
    Buy
};

class Request 
{
private:
    std::string Identifier;
    RequestSide Side;
    unsigned int Quantity;
    unsigned int Price;

public:
    Request();
    Request(std::string _Identifier, RequestSide _Side, unsigned int _Quantity, unsigned int _Price);

    friend std::istream& operator>> (std::istream& is, Request& Req);
    friend std::ostream& operator<< (std::ostream& os, const Request& Req);
    friend bool operator< (const Request& Req1, const Request& Req2);

    friend class Market;
};
