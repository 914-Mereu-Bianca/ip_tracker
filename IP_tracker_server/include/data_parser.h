#ifndef _PARSER_H_
#define _PARSER_H_

#include "../build/proto_generated/data.grpc.pb.h"
#include <string>
#include <fstream>

class Parser {
public:

    void parseData(const std::string &input_file);
    void parseData2(const std::string &string);
    inline std::vector<data::Device> getDevices() { return devices_; }

private:

    void jumpOver(std::ifstream &file, int lines_to_be_skipped);

    void parseIP(const std::string &string);
    void parseMAC(const std::string &string);
    void parseOnline(const std::string &string);
    void parseBlocked(const std::string &string);

    std::vector<data::Device> devices_;

};

#endif // _PARSER_H_