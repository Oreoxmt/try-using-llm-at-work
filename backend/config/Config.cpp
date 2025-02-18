#include "Config.h"

#include <fstream>
#include <istream>
#include <string>

#include <capnp/compat/json.h>
#include <capnp/message.h>

namespace muton::playground::llm {

Config::ConfigType Config::Read() {
  Config::ConfigType config;
  std::ifstream config_file("config.json");
  if (!config_file.good()) {
    throw std::runtime_error("failed to open config.json");
  }
  std::string config_str{std::istreambuf_iterator<char>(config_file), std::istreambuf_iterator<char>()};
  capnp::JsonCodec().decode(kj::ArrayPtr<const char>(config_str.data(), config_str.size()), config.Root());
  return config;
}

}  // namespace muton::playground::llm
