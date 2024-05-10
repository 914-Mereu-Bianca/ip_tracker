#ifndef _PARSER_H_
#define _PARSER_H_

#include "../build/proto_generated/data.grpc.pb.h"

class Parser {
public:

    std::vector<data::Device> parseData(const std::string &file);

private:

    // this function will parse each 95 values from each field
    std::vector<std::string> parseUniqueField(const std::string &data);

};

#endif // _PARSER_H_