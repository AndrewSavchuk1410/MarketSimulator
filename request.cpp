#include "request.h"

Request::Request() {}


Request::Request(std::string _Identifier, RequestSide _Side, unsigned int _Quantity, unsigned int _Price)
    : Identifier(_Identifier), Side(_Side), Quantity(_Quantity), Price(_Price) {}


std::istream& operator>> (std::istream& is, Request& Req)
{
    char Side = ' ';
    long long Quantity = 0, Price = 0;
    
    is >> Req.Identifier >> Side >> Quantity >> Price;
    
    if (Quantity <= 0)
    {
        std::cerr << "Ivalid input; Quantity must be > 0\n";
        Quantity = 0;
    }
    if (Price < 0)
    {
        std::cerr << "Ivalid input; Price must be >= 0\n";
        Quantity = 0;
        Price = 0;
    }

    Req.Side = (Side == 'B' ? RequestSide::Buy : RequestSide::Sell);
    Req.Quantity = Quantity;
    Req.Price = Price;

    return is;
}


std::ostream& operator<< (std::ostream& os, const Request& Req)
{
    char Side = (Req.Side == RequestSide::Buy ? '+' : '-');
    os << Req.Identifier  << Side << Req.Quantity << '@' << Req.Price;
    return os;
}


bool operator< (const Request& Req1, const Request& Req2)
{
    if (Req1.Identifier.size() < Req2.Identifier.size()) { return true; }
    if (Req1.Identifier.size() > Req2.Identifier.size()) { return false; }

    if (Req1.Identifier < Req2.Identifier) { return true; }
    if (Req1.Identifier > Req2.Identifier) { return false; }

    if (Req1.Side < Req2.Side) { return true; }
    if (Req1.Side > Req2.Side) { return false; } 

    if (Req1.Quantity < Req2.Quantity) { return true; }
    if (Req1.Quantity > Req2.Quantity) { return false; }

    if (Req1.Price < Req2.Price) { return true; }
    if (Req1.Price > Req2.Price) { return false; }

    return false;
}