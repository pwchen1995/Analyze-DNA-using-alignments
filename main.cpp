#include "tasks.h"
#include <iostream>
#include <fstream>
#include <string>
#include<algorithm>
#include <cstdlib>

using namespace std;

int main() {

    string inputFile;
    tasks stree;
//    inputFile= "F:\\Abhyas\\WSU\\Sem 2\\Computational Genomics\\Homework\\dataCoding\\project3\\demo1.fasta";
//    stree.inputReader(inputFile);
//    inputFile= "F:\\Abhyas\\WSU\\Sem 2\\Computational Genomics\\Homework\\dataCoding\\project3\\demo2.fasta";
//    stree.inputReader(inputFile);





    inputFile= "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/Covid_Wuhan.fasta";
    stree.inputReader(inputFile);
    inputFile= "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/Covid_USA-CA4.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/Covid_Australia.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/Covid_India.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/Covid_Brazil.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/SARS_2013_GU553363.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/SARS_2017_MK062179.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/MERS_2012_KF600620.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/MERS_2014_KY581694.fasta";
    stree.inputReader(inputFile);
    inputFile = "/Users/kevinchen/Desktop/WSU_Spring2020/Computational Genomics/Program3_PinakBhalerao_Ping-WenChen/DATASET/MERS_2014_USA_KP223131.fasta";
    stree.inputReader(inputFile);

//    stree.buildGST();
//    stree.buildLCS(8,9); //2 parameters between 0-9
}
