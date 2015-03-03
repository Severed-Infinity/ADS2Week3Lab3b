//
//  main.cpp
//  ADS2Week3Lab3b
//
//  Created by david swift on 23/02/2015.
//  Copyright (c) 2015 david swift. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>

int main(int argc, const char * argv[]) {
    
//    std::map<int, double> moviesInnerMap;
    std::map<std::string, std::multimap<int, double>> movies;
//    std::map<std::string, std::map<int, double>>::iterator it;
//    std::multimap<int, double>::reverse_iterator itIn;
    int number;
    double rating;
    std::string name;
    
    std::ifstream moviesFile;
    moviesFile.open("/Volumes/My Passport for Mac/It-Tallaght/ADS2/ADSWeek3/ADS2Week3Lab3b/ADS2Week3Lab3b/movies");
    
    std::cout << "starting read" << std::endl;
    if (moviesFile.is_open()) {
        std::cout << "opening file\n" << std::endl;
        moviesFile >> number;
        moviesFile.ignore();
        while (!moviesFile.eof()) {
            getline(moviesFile, name);
            moviesFile >> rating;
            moviesFile.ignore();
            if(movies.count(name) == 0){
                movies[name].insert({1, rating});
            } else {
                for (std::map<std::string, std::multimap<int, double>>::iterator it = movies.begin(); it != movies.end(); it++) {
                    if (it->first == name) {
                        for (std::multimap<int, double>::reverse_iterator itIn = it->second.rbegin(); itIn != it->second.rend(); itIn++) {
//                            std::cout << itIn->first << std::endl;
                            int reviewNum = 1;
                            if(itIn->first != 0 && itIn->first <= reviewNum) {
                                movies[name].insert({(itIn->first+1), rating});
//                                std::cout << "additional " << (itIn->first+1) << " " << name << " " << rating << std::endl;
                                break;
                            }
                            reviewNum++;
                        }
                    }
                }
            }
        }
        moviesFile.close();
        std::cout << "file closed" << std::endl;
    } else {
        std::cout << "could not open file" << std::endl;
    }
    std::cout << std::endl;
    for (std::map<std::string, std::multimap<int, double>>::iterator it = movies.begin(); it != movies.end(); it++) {
        double sum = 0, count = 0;
        for (std::multimap<int, double>::iterator itIn = it->second.begin(); itIn != it->second.end(); itIn++) {
            sum += itIn->second;
            count++;
//            std::cout << "review num " << itIn->first << " rating " << itIn->second << std::endl;
        }
        std::cout << "Film: " << it->first << "\n\tnumber of reviews " << count << "\n\tand the average review rating was " << (sum/count) << "." << std::endl;
    }
    return 0;
}