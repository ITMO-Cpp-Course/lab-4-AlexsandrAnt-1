#pragma once

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace lab4::resource
{

// 1. Собственный класс исключений
class ResourceError : public std::runtime_error
{
  public:
    explicit ResourceError(const std::string& message) : std::runtime_error(message) {}
};

// 2. Класс-обертка для управления файлом (RAII)
class FileHandle
{
  public:
    // Конструктор (открывает ресурс)
    FileHandle(const std::string& filename, const std::string& mode);

    // Деструктор (закрывает ресурс)
    ~FileHandle();

    // Запрещаем копирование (Правило пяти)
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    // Разрешаем перемещение
    FileHandle(FileHandle&& other) noexcept;
    FileHandle& operator=(FileHandle&& other) noexcept;

    // Доступ к сырому указателю (для чтения/записи)
    std::FILE* get() const noexcept;

  private:
    std::FILE* file_{nullptr};
};

// 3. Менеджер ресурсов (Кеширование)
class ResourceManager
{
  public:
    // Получить доступ к файлу (разделяемое владение)
    std::shared_ptr<FileHandle> getFile(const std::string& filename, const std::string& mode = "r");

  private:
    // Кеш: хранит не сами объекты, а "слабые" ссылки на них
    std::unordered_map<std::string, std::weak_ptr<FileHandle>> cache_;
};

} // namespace lab4::resource
