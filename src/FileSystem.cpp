#include <cabba/FileSystem.h>

#include <windows.h>
#include <strsafe.h>
#include <filesystem>
#include <string>

#include <fstream>

namespace cabba { namespace filesystem {

    bool create_empty_file(const char* path)
    {
        if (exist(path))
            return false;

        std::ofstream file(path, std::ofstream::trunc);

        if (file.is_open())
        {
            return true;
        }
        return false;
    }

    char** list_directory(const char* directory, int& count)
    {
        // Ok so that might be a little bit shitty here
        char** files;
        std::vector<std::string> sfiles;

        for (auto& p : std::filesystem::directory_iterator(directory))
        {
            sfiles.push_back(p.path().string());
        }

        count = sfiles.size();
        files = new char*[sfiles.size()];

        for (int i = 0; i < sfiles.size(); ++i)
        {
            files[i] = new char[sfiles[i].size() + 1];
            strcpy(files[i], sfiles[i].data());
        }
       
        return files;
    }

    bool cabba::filesystem::remove(const char* path)
    {
        std::error_code error;

        std::filesystem::remove(path, error);
        // 0 being a success here
        return (error.value() == 0);
    }

    bool cabba::filesystem::create_directory(const char* path)
    {
        return std::filesystem::create_directory(path);
    }

    void cabba::filesystem::remove_all(const char* path)
    {
        std::filesystem::remove_all(path);
    }

    bool cabba::filesystem::exist(const char* path)
    {
        return std::filesystem::exists(path);
    }

    /*
     * @brief  Find the last occurrence of character c in str
     */
    int find_last(const char* str, char c...)
    {
        int size = strlen(str);
        for (int i = size - 1; i >= 0; i--)
        {
            va_list args;
            va_start(args, c);
            if (str[i] == c)
            {
                va_end(args);
                return i;
            }
            va_end(args);
        }
        return-1;
    }

    bool rename(const char* path, const char* newPath)
    {
        std::error_code errorCode;
        std::filesystem::rename(path, newPath, errorCode);
        return true;
    }


    // WARNING : '\\' didn't worked weirdly

    char* path_without_name(const char* path)
    {
        // we look for the first "/" or "\" if the path from the end
        int index = find_last(path, '/', '\\');

        // If index equals -1 it means there's nothing before the filename
        if (index == -1)
            return "";

        std::string str = path;
        str = str.substr(0, index + 1);

        char* newStr = new char[str.size() + 1];
        std::strcpy(newStr, str.data());

        return newStr;
    }

    char* filename(const char* path)
    {
        std::string str(path);

        // There's probably a "find last token somewhere in the STL"

        int index = 0;
        for (int i = str.size() - 1; i > 0; --i)
        {
            if (str[i] == '/' || str[i] == '\\')
            {
                std::string cut = str.substr(i + 1);
                char* newStr = new char[cut.size()+1];
                std::strcpy(newStr, cut.data());
                return newStr;
            }
        }
        return "";
    }

    char* extension(const char* path)
    {
        std::string str(path);
        std::string ext = "";
        bool start_ext = false;

        for (size_t i = 0; i < str.size(); ++i)
        {
            if (start_ext)
            {
                ext += str[i];
            }
            if (str[i] == '.')
            {
                start_ext = true;
            }
        }
        char* newStr = new char[ext.size() + 1];
        std::strcpy(newStr, ext.data());
        return newStr;
    }

    bool is_directory(const char* str)
    {
        return std::filesystem::is_directory(str);
    }
}}