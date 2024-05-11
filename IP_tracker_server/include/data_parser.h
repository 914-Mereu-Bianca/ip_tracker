#ifndef _PARSER_H_
#define _PARSER_H_

#include "../build/proto_generated/data.grpc.pb.h"
#include "../build/proto_generated/data.pb.h"
#include <string>
#include <fstream>

class Parser {
public:

    void parseData(const std::string &string);
    inline std::vector<data::Device> getDevices() { return devices_; }

private:

    void parseIP(const std::string &string);
    void parseName(const std::string &string);
    void parseMAC(const std::string &string);
    void parseOnline(const std::string &string);
    void parseBlocked(const std::string &string);

    std::vector<data::Device> devices_; // a list of devices of type proto

};

#endif // _PARSER_H_