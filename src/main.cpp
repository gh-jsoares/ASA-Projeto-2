#include "Parser.hpp"
#include "Network.hpp"
#include "Writer.hpp"

int main()
{
    Parser parser;
    Writer writer;

    Network network = parser.factory();

    writer.write(network);

    return 0;
}