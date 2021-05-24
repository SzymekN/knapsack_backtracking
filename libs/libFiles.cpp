#include "libFiles.h"

void CreateFile(std::ofstream& createFile, std::string passedName)
{
	//name of a file that is being created
	char fileName[30];

	if (passedName.length() != 0)
		strcpy_s(fileName, passedName.c_str());
	else {
		std::cin >> fileName;
		CheckFileName(fileName);
	}
	createFile.open(fileName);

	if (!createFile.is_open()) {
		throw MyRuntimeExceptions::FileException("Create file ERROR");
	}

}

void OpenFile(std::ifstream& openFile, std::string passedName)
{
	//name of a file that is being opened
	char fileName[30];
	if (passedName.length() != 0)
		strcpy_s(fileName, passedName.c_str());
	else {
		std::cin >> fileName;
		CheckFileName(fileName);
	}
	openFile.open(fileName);

	if (!openFile.is_open()) {
		throw  MyRuntimeExceptions::FileException("Open file ERROR");
	}
}

void CheckFileName(char fileName[30])
{
	for (int i = 0; i <30; i++) {
		if (fileName[i] == '.')
		{
			if (fileName[i + 4] != NULL)
				for (int j = i + 4; j < 30; j++)
					fileName[j] = NULL;
			if (fileName[i + 1] == 't' and fileName[i + 2] == 'x' and fileName[i + 3] == 't') {
				return;
			}
			else if (fileName[i + 1] != 't' or fileName[i + 2] != 'x' or fileName[i + 3] != 't') {
				fileName[i + 1] = 't';
				fileName[i + 2] = 'x';
				fileName[i + 3] = 't';
				fileName[i + 4] = NULL;
				std::cout << "corrected file name: " << fileName << std::endl; 
				return;
			}
		}
		else if (fileName[i] == NULL) {
			fileName[i] = '.';
			fileName[i + 1] = 't';
			fileName[i + 2] = 'x';
			fileName[i + 3] = 't';
			fileName[i + 4] = NULL;
			std::cout << "corrected file name: " << fileName << std::endl;
			return;
		}
	}
}

void CopyDataSet(int cursor, std::ifstream& readFromFile, std::ofstream& writeToFile)
{
	//coordinates of a vector 0=y, 1=x
	int secondCoord = 0;
	//one value that is being read from a file
	double valueRead{};
	//one line read from a file
	std::string line{};
	readFromFile.seekg(cursor, std::ios::beg);

	writeToFile<< "\n\nY, X vector with a best match:\n";
	while (secondCoord < 2)
	{
		std::getline(readFromFile, line);

		std::istringstream iss(line);

		while (iss.peek()!=EOF) {
			iss>>valueRead;
			writeToFile << std::setprecision(15)<<valueRead<<" ";
		}
		writeToFile<< std::endl << std::endl;
		secondCoord++;
	}
}

void WriteToFileAllDivisions(int* division, int* quantityOfANumber, int divisionLength, std::ofstream& writeToFile)
{
	for (int i = 1; i < divisionLength + 1; i++)
	{
		int temp = quantityOfANumber[i];
		while (temp > 1) {
			writeToFile<< division[i] << " ";
			temp--;
		}
		writeToFile<< division[i] << " ";
	}
	writeToFile << std::endl;
}

int CountLines(std::ifstream& readFromFile)
{
	std::string line{};
	int lines{};
	while (std::getline(readFromFile, line))
		lines++;

	readFromFile.clear();
	readFromFile.seekg(0);
	return lines;
}

void SetValuesToArray(long long* values, int numberOfValues, std::ifstream& readFromFile)
{

	int i = 0;
	//one line read from a file
	std::string line{};
	long long value;
		
	std::getline(readFromFile, line);
	if(line=="")
		std::getline(readFromFile, line);

	std::istringstream iss(line);

	while (iss.peek() != EOF) {
		iss >> values[i];
		//std::cout << values[i] << " ";
		i++;
	}

}


