#pragma once
#include <string>
#include <cstdio>

namespace lab4::resource {

class FileHandle {
public:
    FileHandle(const std::string& filename, const std::string& mode);
    ~FileHandle();

    // Запрещаем копирование
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    // Разрешаем перемещение
    FileHandle(FileHandle&& other) noexcept;
    FileHandle& operator=(FileHandle&& other) noexcept;

    std::FILE* get() const noexcept;

private:
    std::FILE* file_;
};

} // namespace lab4::resource