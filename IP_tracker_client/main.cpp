#include <QApplication>
#include "include/client_modelview.h"
#include "include/client.h"
#include <grpc++/grpc++.h>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv); 

    ClientModelView client_;

    client_.runClient();

    return app.exec();

    return 0;
}