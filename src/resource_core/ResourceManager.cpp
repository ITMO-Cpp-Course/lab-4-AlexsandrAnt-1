#include "ResourceManager.hpp"
#include "FileHandle.hpp"
namespace lab4::resource {

std::shared_ptr<FileHandle> ResourceManager::getFile(const std::string& filename,
                                                       const std::string& mode) {
    std::string key = filename + ":" + mode;

    // Ищем в кеше
    auto it = cache_.find(key);
    if (it != cache_.end()) {
        if (auto shared = it->second.lock()) {
            return shared;
        }
    }

    auto new_shared = std::make_shared<FileHandle>(filename, mode);

    cache_[key] = new_shared;

    return new_shared;
}

} // namespace lab4::resource