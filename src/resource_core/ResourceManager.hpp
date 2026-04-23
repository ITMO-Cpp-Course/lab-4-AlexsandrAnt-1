#pragma once
#include "FileHandle.hpp"
#include <string>
#include <memory>
#include <unordered_map>

namespace lab4::resource {

class ResourceManager {
public:
    std::shared_ptr<FileHandle> getFile(const std::string& filename,
                                         const std::string& mode = "r");

private:
    std::unordered_map<std::string, std::weak_ptr<FileHandle>> cache_;
};

} // namespace lab4::resource