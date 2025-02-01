// parse the inp.cpp using simdjson

#include "simdjson.h"
#include <fstream>
#include <iostream>

int main() {
  const std::string filename = "inp.json";
  printf("size of the string filename is : %zu\n", sizeof(std::string));

  simdjson::ondemand::parser parser;

  try {
    simdjson::padded_string json = simdjson::padded_string::load(filename);

    simdjson::ondemand::document doc = parser.iterate(json);

    bool classMaster = doc["classMaster"].get_bool();
    std::cout << "classMaster: " << (classMaster ? "true" : "false")
              << std::endl;

    simdjson::ondemand::object timeTable = doc["timeTable"].get_object();

    for (auto subject : timeTable) {
      std::string_view subjectName = subject.unescaped_key();
      std::cout << "Subject: " << subjectName << std::endl;

      simdjson::ondemand::object days = subject.value().get_object();

      for (auto day : days) {
        std::string_view dayName = day.unescaped_key();
        std::cout << "  " << dayName << ": ";

        simdjson::ondemand::array timings = day.value().get_array();
        for (auto time : timings) {
          std::cout << time.get_string() << " ";
        }
        std::cout << std::endl;
      }
    }
  } catch (const simdjson::simdjson_error &e) {
    std::cerr << "simdjson error: " << e.what() << std::endl;
    return 1;
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
