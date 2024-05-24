#include "notepad.h"
#include "/Users/isaiahmac/Downloads/json-develop/single_include/nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <QDebug>

void notepad::deleteLine(std::string fileDirectory){
	std::fstream myFile; 
	myFile.open(fileDirectory, std::ios::in);
	std::string buffer;
	std::vector<std::string> lines;

	while (std::getline(myFile, buffer)){
		lines.push_back(buffer+'\n');
	}
	myFile.close();
	myFile.open(fileDirectory, std::ios::out);
    lines[lines.size()-1]="";
    for(std::string line: lines){
		myFile<< line;	
	}
	myFile.close();
    return;
}

void notepad::initilizeNotePad(std::string time){
	std::ofstream myFile;
    myFile.open("/Users/isaiahmac/Documents/code/QT/chess/chess/moveFiles/"+time.append(".json"));
	myFile<<"{\n}";
	myFile.close();
}



void notepad::writeMove(std::string time, int turn, std::string startMove, std::string endMove, char promotionPiece){

	std::ofstream myFile;
	std::string comma="";
    if (turn!=1){
		comma=",";
	}
    std::string fileDirectory="/Users/isaiahmac/Documents/code/QT/chess/chess/moveFiles/"+time.append(".json");
	myFile.open(fileDirectory, std::fstream::app);
	deleteLine(fileDirectory);
    myFile << comma<<" \"turn" << turn << "\": {\"startMove\": \""<< startMove<< "\", \"endMove\": \""<< endMove <<"\", \"promotionPiece\": \""<<promotionPiece<<"\" }\n}";
	myFile.close();
    return;
}


int notepad::getTotalTurn(std::string fileDirectory){
	std::fstream myFile; 
    myFile.open(fileDirectory, std::ios::in);
	std::string buffer;
	std::vector<std::string> lines;

	while (std::getline(myFile, buffer)){
		lines.push_back(buffer+'\n');
	}
	myFile.close();
	return lines.size()-2;

}
std::string notepad::getStartMove(std::string fileDirectory, int turn){
	std::ifstream myFile;
    myFile.open(fileDirectory);
	nlohmann::json myJson = nlohmann::json::parse(myFile);
	return myJson["turn"+ std::to_string(turn)]["startMove"].get<std::string>();
}
std::string notepad::getEndMove(std::string fileDirectory, int turn){
	std::ifstream myFile;
    myFile.open(fileDirectory);
	nlohmann::json myJson = nlohmann::json::parse(myFile);
	return myJson["turn"+ std::to_string(turn)]["endMove"].get<std::string>();
}
std::string notepad::getPromotionPiece(std::string fileDirectory, int turn){
    std::ifstream myFile;
    myFile.open(fileDirectory);
    nlohmann::json myJson = nlohmann::json::parse(myFile);
    return myJson["turn"+ std::to_string(turn)]["promotionPiece"].get<std::string>();
}


std::string notepad::returnGameList(){
	DIR *directory;
	struct dirent *entry;
	std::string buffer="";
	directory=opendir("moveFiles");
	while ((entry =readdir(directory)) != NULL){
		buffer.append(entry->d_name);
		buffer+='\n';
	}
	closedir(directory);
	return buffer;
}

