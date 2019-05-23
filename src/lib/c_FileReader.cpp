#include "lib/include/c_FileReader.hpp"
#include <iostream>

/**
 * Constructor
 */
c_FileReader::c_FileReader() {
    _fileStream = new std::ifstream; // Not sure if syntax is correct.
}

/**
 * Deconstructor
 */
c_FileReader::~c_FileReader() {
    delete(_fileStream);
    delete(_fileContent);
}


/**
 * Read the file and load it to memory
 */
void c_FileReader::readFile(char *fileName)
{
    _fileName = fileName;
    loadFileToMemory();
    performIndexing();
}

/**
 * Loads the file to memory
 */
void c_FileReader::loadFileToMemory()
{
    _fileStream->open(_fileName, std::ifstream::ate | std::ifstream::binary);
    _fileSize = _fileStream->tellg();
    _fileStream->seekg(0, _fileStream->beg);
    _fileContent = new char[_fileSize + 1];
    _fileStream->read(_fileContent, _fileSize);
    _fileContent[_fileSize] = 0;
    _fileStream->close();
}


/**
 * Returns file content
 */
char *c_FileReader::fileContent()
{
    char *fileContent = new char[_fileSize + 1];
    memcpy(fileContent, _fileContent, _fileSize);
    fileContent[_fileSize] = 0;
    return fileContent;
}

/**
 * Returns file size
 */
int c_FileReader::fileSize()
{
    return _fileSize;
}

/**
 * Return value from given key:
 */
char *c_FileReader::getValue(char *key)
{
    int i;
    s_Key *keyValue = _keyValue;
    do {
        for (i = 0; key[i] == keyValue->address[i] && key[i] != 0 && keyValue->address[i] != 0; i++) {}
        if (key[i] == keyValue->address[i]) {
            return keyValue->value->address;
        }
        keyValue = keyValue->next;
    } while (keyValue != nullptr);
    return NULL;
}

/**
 * Perform Indexing
 */
void c_FileReader::performIndexing()
{
    char *outputBuffer = new char[2];
    outputBuffer[1] = 0;

    _keyValue = nullptr;
    s_Key *oldKey = nullptr;
    for (int i = 0; i < _fileSize; ++i) {

        if (_fileContent[i] == 0 || _fileContent[i] == '\r' || _fileContent[i] == ' ' || _fileContent[i] == '=') {
            continue;
        }

        s_Key *key = new s_Key;
        if (_keyValue == nullptr) {
            _keyValue = key;
        }
        if (oldKey != nullptr) {
            oldKey->next = key;
        }

        oldKey = key;
        key->address = &_fileContent[i];
        key->length = 0;
        while (_fileContent[i] != '=' && _fileContent[i] != '\n' && _fileContent[i] != '\r' && i < _fileSize) {
            if (_fileContent[i] == ' ') {
                _fileContent[i] = 0;
            }
            i++;
            key->length++;
        }
        if (i >= _fileSize) {
            break;
        }

        _fileContent[i] = 0;
        while (_fileContent[++i] == ' ' || _fileContent[i] == '\n' || _fileContent[i] == '\r') {
            _fileContent[i] = 0;
        }

        s_Value *value = new s_Value;
        key->value = value;
        value->address = &_fileContent[i];
        value->length = 0;
        while(_fileContent[i] != '\n' && i < _fileSize) {
            i++;
            value->length++;
        }
        if (i < _fileSize) {
            _fileContent[i] = 0;
        }
    }
}

