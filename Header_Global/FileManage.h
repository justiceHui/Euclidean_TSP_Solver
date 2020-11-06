//
// Created by jhnah on 2020-11-06.
//

#include "./General.h"

#ifndef EUCLIDEAN_TSP_SOLVER_FILEMANAGE_H
#define EUCLIDEAN_TSP_SOLVER_FILEMANAGE_H

FILE *INPUT, *OUTPUT, *ERROR;
string FILE_NAME, INPUT_FILE, OUTPUT_FILE, ERROR_FILE;

void setFileName(const int TEST_NO){
    FILE_NAME = (TEST_NO < 10 ? "../TSP_data/0" : "../TSP_data/") + to_string(TEST_NO);
    INPUT_FILE = FILE_NAME + ".in";
    OUTPUT_FILE = FILE_NAME + ".out";
    ERROR_FILE = FILE_NAME + ".err";
}
void openInputFile(){
    INPUT = freopen(INPUT_FILE.c_str(), "r", stdin);
}
void openOutputFile(){
    OUTPUT = freopen(OUTPUT_FILE.c_str(), "w", stdout);
}
void openErrorFile(){
    ERROR = freopen(ERROR_FILE.c_str(), "w", stderr);
}
void closeInputFile(){ fclose(INPUT); }
void closeOutputFile(){ fclose(OUTPUT); }
void closeErrorFile(){ fclose(ERROR); }

#endif //EUCLIDEAN_TSP_SOLVER_FILEMANAGE_H
