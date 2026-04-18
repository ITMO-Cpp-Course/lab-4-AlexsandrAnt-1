#include <catch2/catch_test_macros.hpp>

#include "resource_core.hpp"
#include <cstdio>
#include <fstream>

using namespace lab4::resource;
// Вспомогательная функция для создания временного файла
void createDummyFile(const std::string& name)
{
    std::ofstream out(name);
    out << "initial content";
    out.close();
}

TEST_CASE("FileHandle Basic RAII", "[resource]")
{
    const std::string testFile = "test_raii.txt";
    createDummyFile(testFile);

    SECTION("Successful open")
    {
        REQUIRE_NOTHROW(FileHandle(testFile, "r"));
    }

    SECTION("Throw on missing file")
    {
        REQUIRE_THROWS_AS(FileHandle("non_existent.txt", "r"), ResourceError);
    }

    std::remove(testFile.c_str());
}

TEST_CASE("ResourceManager Caching", "[resource]")
{
    const std::string testFile = "test_cache.txt";
    createDummyFile(testFile);
    ResourceManager manager;

    SECTION("Shared access to same file")
    {
        auto h1 = manager.getFile(testFile, "r");
        auto h2 = manager.getFile(testFile, "r");

        REQUIRE(h1.get() == h2.get());
        REQUIRE(h1.use_count() == 2);
    }

    SECTION("Resource cleanup when not used")
    {
        std::weak_ptr<FileHandle> tracker;
        {
            auto h = manager.getFile(testFile, "r");
            tracker = h;
            REQUIRE(!tracker.expired());
        }
        REQUIRE(tracker.expired());
    }

    std::remove(testFile.c_str());
}