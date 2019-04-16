#include <cabba/test/test.h>
#include <cabba/FileSystem.h>

#include <ostream>

using namespace cabba::test;
using namespace cabba;

class FileSystemTesting : public Test
{
public:

    // For the tests I'm kinda assuming that this folder
    // is always created and these two functions works :eyes:
    void set_up()
    {
        filesystem::create_directory("cabbages");
        filesystem::create_empty_file("cabbages/test.txt");
    }

    void tear_down()
    {
        filesystem::remove_all("cabbages");
    }
};

TEST_F(FileSystemTesting, file_exist)
{
    assert_that(filesystem::exist("cabbages"), 
        equals(true));

    assert_that(filesystem::exist("cabbages/test.txt"),
        equals(true));

    assert_that(filesystem::exist("NotCabbages"),
        equals(false));
}

TEST_F(FileSystemTesting, is_directory)
{
    assert_that(filesystem::is_directory("cabbages"), 
        equals(true));

    assert_that(filesystem::is_directory("cabbages/test.txt"), 
        equals(false));

    assert_that(filesystem::is_directory("notCabbages"), 
        equals(false));
}

TEST_F(FileSystemTesting, filename)
{
    char* filename = filesystem::filename("cabbages/test.txt");
    assert_that(strcmp(filename, "test.txt"), equals(0));
    delete[]filename;
}

TEST_F(FileSystemTesting, path_without_name)
{
    char* path_w_name = filesystem::path_without_name("cabbages/test.txt");

    assert_that(
        strcmp(path_w_name, "cabbages/"), equals(0));
    delete[] path_w_name;
}

TEST_F(FileSystemTesting, extension)
{
    char* ext = filesystem::extension("cabbages/test.txt");

    assert_that(
        strcmp(ext, "txt"), equals(0));
    delete[] ext;
}

TEST_F(FileSystemTesting, create_empty_file)
{
    filesystem::create_empty_file("cabbages/empty_file.txt");

    assert_that(filesystem::exist("cabbages/empty_file.txt"),
        equals(true));

    filesystem::remove("cabbages/empty_file.txt");
}

TEST_F(FileSystemTesting, list_directory)
{
    filesystem::create_empty_file("cabbages\\empty_file.txt");

    int size;
    char** paths = filesystem::list_directory("cabbages", size);
    
    assert_that(size,   equals(2));
    assert_that(strcmp(paths[0], "cabbages\\empty_file.txt"), equals(0));
    assert_that(strcmp(paths[1], "cabbages\\test.txt"), equals(0));

    delete[]paths[0];
    delete[]paths[1];
    delete[]paths;

    filesystem::remove("cabbages/empty_file.txt");
}

TEST_F(FileSystemTesting, rename)
{
    filesystem::create_empty_file("test");

    filesystem::rename("test", "test2");

    assert_that(filesystem::exist("test2"),
        equals(true));

    assert_that(filesystem::exist("test"),
        equals(false))

    filesystem::rename("cabbages", "cabbagesTest");

    assert_that(filesystem::exist("cabbagesTest"),
        equals(true));

    assert_that(filesystem::exist("cabbagesTest\\test.txt"),
        equals(true));

    assert_that(filesystem::exist("cabbages"),
        equals(false));

    filesystem::rename("cabbagesTest", "cabbages");
}

TEST_F(FileSystemTesting, remove)
{
    assert_that(filesystem::remove("cabbages"),
        equals(false));

    assert_that(filesystem::remove("cabbages\\test.txt"),
        equals(true));

    assert_that(filesystem::exist("cabbages\\test.txt"),
        equals(false));
}