#pragma once
#include <string.h>
#include <fstream>
#include "lib/include/s_Key.hpp"
#include "lib/include/s_Value.hpp"

/**
 * File Reader
 *
 * @author ghabxph <me@ghabxph.info>
 */
class c_FileReader
{
public:

    /**
     * Constructor
     */
    c_FileReader();

    /**
     * Copy constructor
     */
    c_FileReader(const c_FileReader &other);

    /**
     * Move constructor
     */
    c_FileReader(c_FileReader &&other) noexcept;

    /**
     * Destructor
     */
    virtual ~c_FileReader() noexcept;

    /**
     * Copy assignment operator
     */
    c_FileReader& operator=(const c_FileReader &other);

    /**
     * Move assignment operator
     */
    c_FileReader& operator=(c_FileReader &&other) noexcept;

    /**
     * Read the file and load it to memory
     */
    void readFile(char *fileName);

    /**
     * Returns file content
     */
    char *fileContent();

    /**
     * Returns file size
     */
    int fileSize();

    /**
     * Return value from given key
     */
    char *getValue(char *key);


protected:
private:

    /**
     * File Stream
     */
    std::ifstream *_fileStream;

    /**
     * Size of file
     */
    int _fileSize;

    /**
     * Filename of file to read
     */
    char *_fileName;

    /**
     * Key-value structure
     */
    s_Key *_keyValue;

    /**
     * File content in memory, based on the given file name
     */
    char *_fileContent;

    /**
     * Loads the file to memory
     */
    void loadFileToMemory();

    /**
     * Perform indexing
     */
    void performIndexing();


};
