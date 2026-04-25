#include "FileHandle.hpp"
#include "ReourceError.hpp"
#include <utility>

namespace lab4::resource
{

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

FileHandle::FileHandle(FileHandle&& other) noexcept : file_(std::exchange(other.file_, nullptr)) {}

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

} // namespace lab4::resource