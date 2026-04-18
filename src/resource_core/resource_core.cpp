#include "resource_core.hpp"
#include <utility>

namespace lab4::resource
{

// --- Реализация FileHandle ---

FileHandle::FileHandle(const std::string& filename, const std::string& mode)
{
    file_ = std::fopen(filename.c_str(), mode.c_str());
    if (!file_)
    {
        throw ResourceError("Failed to open file: " + filename);
    }
}

FileHandle::~FileHandle()
{
    if (file_)
    {
        std::fclose(file_);
    }
}

// Конструктор перемещения
FileHandle::FileHandle(FileHandle&& other) noexcept : file_(std::exchange(other.file_, nullptr)) {}

// ИСПРАВЛЕНО: добавлено FileHandle:: перед именем метода
FileHandle& FileHandle::operator=(FileHandle&& other) noexcept
{
    if (this != &other)
    {
        // Сначала освобождаем свой текущий ресурс, если он был
        if (file_)
        {
            std::fclose(file_);
        }
        // Забираем чужой
        file_ = std::exchange(other.file_, nullptr);
    }
    return *this;
}

std::FILE* FileHandle::get() const noexcept
{
    return file_;
}

// --- Реализация ResourceManager ---

std::shared_ptr<FileHandle> ResourceManager::getFile(const std::string& filename, const std::string& mode)
{
    // Создаем уникальный ключ для кеша (имя + режим)
    std::string key = filename + ":" + mode;

    // Ищем в кеше
    auto it = cache_.find(key);
    if (it != cache_.end())
    {
        // Пробуем получить shared_ptr из weak_ptr
        if (auto shared = it->second.lock())
        {
            return shared; // Файл уже открыт, возвращаем существующий
        }
    }

    // Если файла нет в кеше или он уже был уничтожен
    auto new_shared = std::make_shared<FileHandle>(filename, mode);

    // Сохраняем "слабую" ссылку в кеш
    cache_[key] = new_shared;

    return new_shared;
}

} // namespace lab4::resource