#include <QApplication>
#include "include/client_view.h"
#include "include/client.h"
#include <grpc++/grpc++.h>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv); 

    ClientView client_;

    client_.runClient();

    return app.exec();

    return 0;
}