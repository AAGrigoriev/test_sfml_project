#pragma once

#include <assert.h>
#include <filesystem>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>

namespace utility {

template <typename Resource, typename Identifier>
class resource_holder {
 public:
  void load(Identifier id, const std::filesystem::path& path_to_source);
  template <typename SecondParametr>
  void load(Identifier id,
            const std::filesystem::path& path_to_source,
            SecondParametr addition_param);

  Resource& get_resource(Identifier id);
  const Resource& get_resource(Identifier id) const;

 private:
  void insert_resource(Identifier id, std::unique_ptr<Resource> resource);

 private:
  std::map<Identifier, std::unique_ptr<Resource>> resource_storage;
};

template <typename Resource, typename Identifier>
void resource_holder<Resource, Identifier>::load(
    Identifier id,
    const std::filesystem::path& path_to_source) {
  std::unique_ptr<Resource> resource(new Resource());
  if (!resource->loadFromFile(path_to_source.string())) {
    throw std::runtime_error("Resource not load" + path_to_source.string());
  }
  insert_resource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename SecondParametr>
void resource_holder<Resource, Identifier>::load(
    Identifier id,
    const std::filesystem::path& path_to_source,
    SecondParametr addition_param) {
  std::unique_ptr<Resource> resource(new Resource());
  if (!resource->loadFromFile(path_to_source.string(), addition_param)) {
    throw std::runtime_error("Resource not load" + path_to_source.string());
  }
  insert_resource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
const Resource& resource_holder<Resource, Identifier>::get_resource(
    Identifier id) const {
  auto found = resource_storage.find(id);
  assert(found != resource_storage.end());
  return *found->second;
}

template <typename Resource, typename Identifier>
Resource& resource_holder<Resource, Identifier>::get_resource(Identifier id) {
  auto found = resource_storage.find(id);
  assert(found != resource_storage.end());
  return *found->second;
}

template <typename Resource, typename Identifier>
void resource_holder<Resource, Identifier>::insert_resource(
    Identifier id,
    std::unique_ptr<Resource> resource) {
  auto inserted =
      resource_storage.insert(std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}

}  // namespace utility
