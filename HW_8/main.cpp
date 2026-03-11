#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

void convertPostsFile() {
    // Make sure your original file is named posts.txt
    std::ifstream ifs("posts.txt");
    std::ofstream ofs("posts_new.txt");

    if (!ifs.is_open() || !ofs.is_open()) {
        std::cout << "Error opening files!" << std::endl;
        return;
    }

    int numPosts;
    ifs >> numPosts;
    ofs << numPosts << "\n";

    std::srand(std::time(nullptr)); // Seed random number generator

    for (int i = 0; i < numPosts; ++i) {
        int mId, pId, aId, oldLikes;
        std::string message, url;

        ifs >> mId;
        ifs.ignore();
        std::getline(ifs, message);

        // Trim leading whitespace from old message
        size_t start = message.find_first_not_of(" \t\r\n");
        if(start != std::string::npos) message = message.substr(start);

        // Read old IDs and the old single integer like count
        ifs >> pId >> aId >> oldLikes;
        ifs.ignore();
        std::getline(ifs, url);

        start = url.find_first_not_of(" \t\r\n");
        if(start != std::string::npos) url = url.substr(start);

        // Write new format
        ofs << mId << "\n\t" << message << "\n\t" << pId << "\n\t" << aId << "\n\t";

        // Generate 3 to 5 random likes from your 148 users
        int numLikes = 3 + (std::rand() % 3);
        for(int l = 0; l < numLikes; l++) {
            int randomUserId = std::rand() % 148;
            ofs << randomUserId << (l == numLikes - 1 ? "" : " ");
        }
        ofs << "\n";

        // Handle URL or blank line
        if (url.empty()) {
            ofs << "\n";
        } else {
            ofs << "\t" << url << "\n";
        }
    }

    ifs.close();
    ofs.close();
    std::cout << "Successfully converted " << numPosts << " posts to posts_new.txt!" << std::endl;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //convertPostsFile();
    MainWindow w;
    w.show();
    return a.exec();
}
