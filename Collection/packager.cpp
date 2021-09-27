#include "packager.h"

using namespace IMU_Tools;

IMU_Tools::Packager::Packager(std::string destination, int port) {
  _dest = destination;
  _port = port;
  _count = 0;
  struct sockaddr_in server;
  // Create socket
  _descriptor = socket(AF_INET, SOCK_DGRAM, 0);
  if (_descriptor == -1)
    printf("Could not create socket");

  server.sin_addr.s_addr = inet_addr(_dest.c_str()); // Destination address
  server.sin_family = AF_INET;
  server.sin_port = htons(_port); // Destination port

  // Connect to remote server
  if (connect(_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0) {
    puts("connect error");
  } else {
    puts("Connected\n");
  }
}

IMU_Tools::Packager::~Packager() { 1; }

std::string IMU_Tools::Packager::_float_to_string(float value) {

  std::stringstream stream;
  stream << std::fixed << std::setprecision(6) << value;
  std::string s = stream.str();

  return s;
}

int IMU_Tools::Packager::send_packet(float *data) {
  std::string arr = "";

  int len = 4;
  // Convert floats to string
  for (int i = 0; i < len; i++) {
    arr += _float_to_string(data[i]);
    if (i != len - 1) {
      arr += ", ";
    }
  }

  puts(arr.c_str());
  // Send some data
  if (send(_descriptor, arr.c_str(), strlen(arr.c_str()), 0) < 0) {
    puts("Send failed");
    return 1;
  }
  printf("%7d - Sent", _count++);
  return 0;
}