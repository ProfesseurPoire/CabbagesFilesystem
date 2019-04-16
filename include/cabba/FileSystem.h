#pragma once

/*
 *  The filesystem namespace contains functions meant
 *  to help with file operations.
 *  
 *  Under the hood it's mostly a wraper for std::filesystem
 *  for now, but I might have to get rid of it if I wish to add 
 *  Switch support since it only uses a C++ 11 compiler apparently
 */
namespace cabba { namespace filesystem {

    /*
     * @brief   List the files inside the given directory.
     *
     *          The function parses a directory and stores the path of every
     *          file it encounters inside a dynamically allocated array of
     *          C style strings that will be returned by the function.
     *
     *          The count "out" parameter tells how many files were found.
     *
     *          /!\ Warning. Since the function allocates memory dynamically,
     *          you need to take ownership of the C style strings returned
     *          to avoid memory leaks, and don't forget the char** too
     *
     * @param   directory   Pointer to the C style string that contains the 
     *                      path to the directory that will be inspected
     * @param   count       out parameter that tells how many files where
     *                      found by the function
     *
     * @return  Returns a pointer to a dynamically allocated C style string 
     *          array that contains the directory's files. Returns nullptr
     *          if the directory doesn't exist or can't be inspected.
     */
    char** list_directory(const char* directory, int& count);

    /*
     * @brief   Returns the file's extension
     *
     *          Allocates dynamic memory to create a C Style string
     *          that contains the extension part of the given path
     *
     *          For instance, extension("textures/frog.png"); will returns
     *          "png".
     *
     *          /!\ Warning. Since the function allocates memory dynamically,
     *          you need to take ownership of the returned C style string
     *
     * @param   path    Pointer to the C style string that contains the path
     *                  to the file we want to extract the extension
     *
     * @return  Returns a pointer to a dynamically allocated C Style string
     *          that contains the file's extension
     */
    char* extension(const char* path);

    /*
     * @brief   Returns the filename part of the given path
     *
     *          Allocates dynamic memory to create a C Style string
     *          that contains the filename part of the given path
     *
     *          For instance, filename("textures/frog.png"); will returns
     *          "frog.png"
     *
     *          /!\ Warning. Since the function allocates memory dynamically,
     *          you need to take ownership of the returned C style string
     *
     * @param   path    Pointer to the C style string that contains the path
     *                  to the file we want to extract the filename
     *
     * @return  Returns a pointer to a dynamically allocated array that
     *          contains the file's name
     */
    char* filename(const char* path);

    /*
     * @brief   Returns the path without the file's name
     *
     *          Allocates dynamic memory to create a C Style string
     *          that contains the path minus the filename part of the given
     *          path
     *
     *          For instance, filename("textures/frog.png");will returns
     *          "textures/"
     *
     *          /!\ Warning. Since the function allocates memory dynamically,
     *          you need to take ownership of the returned C style string
     *
     * @param   path    Pointer to the C style string that contains the path
     *                  to the file we want to extract the path minus filename
     *
     * @return  Returns a pointer to a dynamically allocated array that
     *          contains the file's path minus the filename
     */
    char* path_without_name(const char* path);


    /*
     * @brief   Creates an empty file at the given location
     *      
     *          Doesn't work if a file with the same path already
     *          exist
     *
     * @param   Path    Path where the file will be created
     * @return  Returns true if the function managed to create a file
     *          return false otherwise
     */
    bool create_empty_file(const char* path);

    /*
     * @brief   Checks if the file at the given path is a directory
     *
     * @param   path Path to the file we want to check
     *
     * @return  Returns true if the file is a directory, false otherwise
     */
    bool is_directory(const char* path);

    /*
     * @brief   Renames or moves a file or directory 
     *
     *          The function will move or rename the file or directory located
     *          at @ref oldPath to @ref newPath.
     *          The function will fail if newPath already exist
     *
     * @param   oldPath     Pointer to the C style string that contains the 
     *                      path to the file or directory that will be moved
     *                      or renamed
     *
     * @param   newPath     Pointer to the C style string that contains the 
     *                      path to the file or directory where oldPath will
     *                      be moved or renamed
     *
     * @return  Returns true if the operation succeeded 
     */
    bool rename(const char* oldPath, const char* newPath);

    /*
     * @brief   Remove the file or empty directory located at the given path
     *
     *          If the directory isn't empty, the operation will fail. You
     *          should use removeAll instead.
     *
     * @param   path    Pointer to the C style string that contains the 
     *                  path to the file or empty directory to be removed
     *
     * @return  Returns true the operation succeeded, false otherwise
     */
    bool remove(const char* path);

    /*
     * @brief   Remove the file or directory located at the given path
     *
     *          removeAll will work even if the file isn't an empty
     *          directory
     *
     * @param   path    Pointer to the C style string that contains the 
     *                  path to the file or directory to be removed
     *
     * @return  Returns true if the operation succeeded, false otherwise
     */ 
    void remove_all(const char* path);

    /*
     * @brief   Check if a file exist a given path
     * 
     * @param   path    Pointer to the C style string that contains the
     *                  path to the file to be checked for existence
     *
     * @return  Returns true if the file exist, false otherwise
     */
    bool exist(const char* path);

    /*
     * @brief   Creates a new directory at the given path
     * 
     * @param   path    Pointer to the C style string that contains the 
     *                  path to the directory that will be created
     *
     * @return  Returns true if a directory was created, false otherwise
     */
    bool create_directory(const char* path);
}}