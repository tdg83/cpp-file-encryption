#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

void encrFile(std::string path){
	std::fstream file, temp;
	std::string tempPath = "temp.txt";

	file.open(path, std::ios::in);
	temp.open(tempPath, std::ios::out);

	char byte;
	while (file >> std::noskipws >> byte){
		byte += 1;
		temp << byte;
	}

	file.close();
	temp.close();

	file.open(path, std::ios::out);
	temp.open(tempPath, std::ios::in);

	while (temp >> std::noskipws >> byte){
		file << byte;
	}

	file.close();
	temp.close();

	remove(tempPath.c_str());
}

void encrDir(std::string dirPath){
	DIR* dir;
	struct dirent* entry;
	struct stat status;
	std::string path;

	if ((dir = opendir(dirPath.c_str())) != NULL){
		while ((entry = readdir(dir)) != NULL){
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
				path = dirPath + "/" + entry->d_name;
				stat(path, &status);
				if (S_ISDIR(status.st_mode)){
					encrDir(path);
				}
				else {
					encrFile(path);
				}
			}
		}
	}
}

int main(){
	std::string inpPath;
	std::cout<<"file encryption program\ninput a valid file path";
	std::cin>>inpPath;
	encrDir(inpPath);
	return 0;
}
