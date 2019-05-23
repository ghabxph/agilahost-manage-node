//#include "TCPClient.hpp"
#include "ProjectInfo.hpp"
#include <iostream>
#include "lib/include/c_FileReader.hpp"

void showConsoleDescription();
bool getConfigPathFromArgument(int argc, char *argv[], char **configPath);
void connectToServer(char *configPath);
void showError();
void showProperUsage(char *argv[]);
char *convertConstCharPtrToCharPtr(const char *constCharPtr);

/**
 * Program Entry Point
 */
int main(int argc, char *argv[])
{
    char *configPath;

    if (getConfigPathFromArgument(argc, argv, &configPath)) {
        connectToServer(configPath);
    }
    return 0;
}


/**
 * Console Description
 */
void showConsoleDescription()
{
    std::cout
        << "                   _   _                   __          _       " << std::endl
        << "    /\\  / ___  ___| |_(_)_ __   __ _    /\\ \\ \\___   __| | ___  " << std::endl
        << "   / /_/ / _ \\/ __| __| | '_ \\ / _` |  /  \\/ / _ \\ / _` |/ _ \\ " << std::endl
        << "  / __  / (_) \\__ \\ |_| | | | | (_| | / /\\  / (_) | (_| |  __/ " << std::endl
        << "  \\/ /_/ \\___/|___/\\__|_|_| |_|\\__, | \\_\\ \\/ \\___/ \\__,_|\\___| " << std::endl
        << "                               |___/                           " << std::endl
        << "---------------------------------------------------------------" << std::endl
        << "Author: "  << PROJECT_AUTHOR << std::endl
        << "Version: " << PROJECT_VERSION << std::endl
        << std::endl
        << std::endl;
}

/**
 * Gets configuration path from argument
 */
bool getConfigPathFromArgument(int argc, char *argv[], char **configPath)
{
    if (argc < 2) {
        showError();
        showProperUsage(argv);
        return false;
    }
    *configPath = argv[1];
    return true;
}

void showError()
{
    std::cout
        << " ▓█████  ██▀███   ██▀███   ▒█████   ██▀███  " << std::endl
        << " ▓█   ▀ ▓██ ▒ ██▒▓██ ▒ ██▒▒██▒  ██▒▓██ ▒ ██▒" << std::endl
        << " ▒███   ▓██ ░▄█ ▒▓██ ░▄█ ▒▒██░  ██▒▓██ ░▄█ ▒" << std::endl
        << " ▒▓█  ▄ ▒██▀▀█▄  ▒██▀▀█▄  ▒██   ██░▒██▀▀█▄  " << std::endl
        << " ░▒████▒░██▓ ▒██▒░██▓ ▒██▒░ ████▓▒░░██▓ ▒██▒" << std::endl
        << " ░░ ▒░ ░░ ▒▓ ░▒▓░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░" << std::endl
        << " ░ ░  ░  ░▒ ░ ▒░  ░▒ ░ ▒░  ░ ▒ ▒░   ░▒ ░ ▒░" << std::endl
        << " ░     ░░   ░   ░░   ░ ░ ░ ░ ▒    ░░   ░" << std::endl
        << " ░  ░   ░        ░         ░ ░     ░" << std::endl;
}

void showProperUsage(char *argv[])
{
    std::cout
        << std::endl
        << std::endl
        << "Missing config path parameter. Please see proper usage below." << std::endl
        << "Proper Usage:" << std::endl
        << "node [cp]" << std::endl
        << std::endl
        << "cp \t - \t Location of configuration file that contains information" << std::endl
        << "   \t   \t of server where this client program will connect to." << std::endl;
}

void connectToServer(char *configPath)
{
    c_FileReader fileReader;
    fileReader.readFile(configPath);
    char *serverIp = fileReader.getValue(convertConstCharPtrToCharPtr("server"));
    std::cout << serverIp << std::endl;

    // NEXT: Develop TCP Client. I am now able to connect to any server using a config file.
}

char *convertConstCharPtrToCharPtr(const char *constCharPtr)
{
    int length;
    for (length = 0; constCharPtr[length] != 0; length++) {}
    length++;
    return (char *)memcpy(new char[length], constCharPtr, length);
}

