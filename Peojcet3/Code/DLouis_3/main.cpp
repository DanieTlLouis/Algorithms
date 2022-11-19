/*
Daniel Louis
Algorithms 
Project 3:
	seam carving
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void createImage(std::vector<std::vector<int>> &v, std::string imageName, std::pair<int, int> &sizeOfPic, int &number);
void printImageCode(std::vector<std::vector<int>> &image, std::pair<int,int> const &sizeOfPic);
void genEnergyTable(std::vector<std::vector<int>> &image, std::vector<std::vector<int>> &energy, std::pair<int, int>  const &sizeOfPic);
void geerateCumTable(std::vector<std::vector<int>> &energy, std::vector<std::vector<int>> &cumulatedEnergy, std::pair<int, int> const &sizeOfPic);
void seamHor(std::vector<std::vector<int>> &image, std::vector<std::vector<int>> &cumulatedEnergy, std::pair<int, int>  &sizeOfPic);
void seamVert(std::vector<std::vector<int>> &image, std::vector<std::vector<int>> &cumulatedEnergy, std::pair<int, int> &sizeOfPic); 
void outPutPic(std::vector<std::vector<int>> image , std::pair<int, int> const sizeOfPic, int const & number, std::string imageName);
void seamHorControl(std::vector<std::vector<int>> &image, std::pair<int, int>  &sizeOfPic);
void seamVertControl(std::vector<std::vector<int>> &image, std::pair<int, int>  &sizeOfPic);

int main(int argc, char *argv[])
{
	//need to remove the .pgm form file
	//need to add this through argument
	//could also have menue if there is no argument found 
	if(argc < 3)
	{
		/*
		std::cout << "This is for seam carving please follow the menue to see what to do\n";
		std::cout << "1. Provide file name to seam.\n" << "2. Seam vertical line\n" << "3. seam horizontal line\n"
			<< "4. close";
		int selection; 
		std::cin >> selection;
		std::string imageName = "../bug";
		std::vector<std::vector<int>> image;
		std::pair<int, int> sizeOfPic;
		int number;

		createImage(image, imageName, sizeOfPic, number);

		seamHorControl(image,sizeOfPic);

		outPutPic(image, sizeOfPic, number, imageName);
		*/
		std::cout << "this was called wrong. Please provide the filename.pgm followed by the number of vertical seams to cut and finally the horizontal lines to cut.\n"
			<< "such as \"a.eve bug.pgm 5 3\" in order to seam 5 vertical and 3 horizontal lines from bug.pgm.\n";
	}
	else
	{
		std::string imageName = argv[1];
		std::string ver = argv[2];
		std::string hor = argv[3];
		int hori = std::stoi(hor);
		int vert = std::stoi(ver);

		imageName = imageName.substr(0, imageName.size() - 4);
		std::vector<std::vector<int>> image;
		std::pair<int, int> sizeOfPic;
		int number;

		createImage(image, imageName, sizeOfPic, number);

		for(int i = 0; i < hori; i ++)
			seamHorControl(image,sizeOfPic);
		for(int i = 0; i < vert; i++)
			seamVertControl(image, sizeOfPic);

		outPutPic(image, sizeOfPic, number, imageName);
	}

	return 1;

}
void seamHorControl(std::vector<std::vector<int>> &image, std::pair<int, int>  &sizeOfPic)
{
	std::vector<std::vector<int>> energy = image;

	genEnergyTable(image, energy, sizeOfPic);
	std::vector<std::vector<int>> cumulatedEnergy = energy;
	seamHor(image, cumulatedEnergy, sizeOfPic);
}
void seamVertControl(std::vector<std::vector<int>> &image, std::pair<int, int>  &sizeOfPic)
{
	std::vector<std::vector<int>> energy = image;

	genEnergyTable(image, energy, sizeOfPic);
	std::vector<std::vector<int>> cumulatedEnergy = energy;
	seamVert(image, cumulatedEnergy, sizeOfPic);
}

void outPutPic(std::vector<std::vector<int>> image , std::pair<int, int> const sizeOfPic, int const &number, std::string imageName)
{
	std::ofstream out (std::string ("./" + imageName + "_processed.pgm"));
	out << "P2" << '\n';
	out << sizeOfPic.first << ' ' << sizeOfPic.second << '\n';
	out << number << '\n';
	for(int i = 0; i < sizeOfPic.second; i++)
	{
		for(int j = 0; j < sizeOfPic.first; j++)
		{
			out << image[i][j] << ' ';
		}
		out << '\n';
	} 
	out.close();
}

void seamHor(std::vector<std::vector<int>> &image, std::vector<std::vector<int>> &cumulatedEnergy, std::pair<int, int> &sizeOfPic) 
{
	int indexY = 0;
	int least = cumulatedEnergy[0][0];
	for(int y = 0; y < sizeOfPic.second; y++)
	{
		if(least > cumulatedEnergy[y][0])
		{
			least = cumulatedEnergy[y][0];
			indexY = y;
		}
	}
	for(int x = 0; x <= (sizeOfPic.first - 1); x++)
	{
		for(int y = indexY; y < sizeOfPic.second-1; y++)
		{
			image[y][x] = image[y+1][x];
		}
		if(x == sizeOfPic.first - 1)
			break;
		if(indexY == 0)
		{
			if(cumulatedEnergy[0][x+1] > cumulatedEnergy[1][x+1])
			{
				indexY += 1;
			}
		}
		else if(indexY == sizeOfPic.second - 1)
		{
			if(cumulatedEnergy[indexY][x+1] > cumulatedEnergy[indexY-1][x+1])
			{
				indexY -= 1;
			}
		}
		else
		{
			if(cumulatedEnergy[indexY][x+1] < cumulatedEnergy[indexY-1][x+1] 
				&& cumulatedEnergy[indexY][x+1] < cumulatedEnergy[indexY+1][x+1])
			{
				indexY = indexY;
			}
			else if(cumulatedEnergy[indexY-1][x+1] < cumulatedEnergy[indexY+1][x+1])
			{
				indexY -= 1;
			}
			else
			{
				indexY += 1;
			}
		}
	}
	sizeOfPic.second -= 1;

	
}
void seamVert(std::vector<std::vector<int>> &image, std::vector<std::vector<int>> &cumulatedEnergy, std::pair<int, int> &sizeOfPic) 
{
	int indexX = 0;
	int least = cumulatedEnergy[0][0];	
	for(int x  = 0; x < sizeOfPic.first; x++)
	{
		if(least > cumulatedEnergy[sizeOfPic.second -1][x])
		{
			least = cumulatedEnergy[sizeOfPic.second -1][x];
			indexX = x;
		}
	}

	for(int y = (sizeOfPic.second - 1); y >= 0; y--)
	{ 
		for(int x = indexX; x < sizeOfPic.first - 1; x++)
		{
			image[y][x] = image[y][x + 1]; 
		}
		if(y == 0)
			break;
		if(indexX == 0)
		{
			if(cumulatedEnergy[y-1][0] > cumulatedEnergy[y-1][1])
			{
				indexX += 1;
			}
		}
		else if(indexX == sizeOfPic.first - 1)
		{
			if(cumulatedEnergy[y-1][indexX] > cumulatedEnergy[y - 1][indexX - 1])
			{
				indexX -= 1;
			}
		}
		else
		{
			if(cumulatedEnergy[y-1][indexX] < cumulatedEnergy[y-1][indexX - 1] 
				&& cumulatedEnergy[y-1][indexX] < cumulatedEnergy[y-1][indexX + 1])
			{
				indexX = indexX;
			}
			else if(cumulatedEnergy[y-1][indexX-1] < cumulatedEnergy[y-1][indexX + 1])
			{
				indexX -= 1;
			}
			else
			{
				indexX += 1;
			}
		}
	}
	
	
	sizeOfPic.first -= 1;
}

void geerateCumTable(std::vector<std::vector<int>> &energy, std::vector<std::vector<int>> &cumulatedEnergy, std::pair<int, int> const &sizeOfPic)
{
	for(int i = 0; i < sizeOfPic.second; i++)
	{
		for(int x = 0; x < sizeOfPic.first; x++)
		{
			if(i == 0)
			{
				cumulatedEnergy[i][x] = energy[i][x];
			}
			else
			{
				//corner case to left
				if(x == 0)
				{
					if(cumulatedEnergy[i-1][x] < cumulatedEnergy[i-1][x+1])
					{
						cumulatedEnergy[i][x] = cumulatedEnergy[i-1][x] + energy[i][x];
					}
					else
					{
						cumulatedEnergy[i][x] = cumulatedEnergy[i-1][x+1] + energy[i][x]; 
					}
				}
				//corner case to right
				else if(x == sizeOfPic.first -1)
				{
					if (cumulatedEnergy[i][x] < cumulatedEnergy[i][x-1])
					{
						cumulatedEnergy[i][x] = cumulatedEnergy[i-1][x] + energy[i][x];
					}
					else
					{
						cumulatedEnergy[i][x] = cumulatedEnergy[i-1][x-1] + energy[i][x];
					}
				}
				else
				{
					if (cumulatedEnergy[i-1][x-1] < cumulatedEnergy[i-1][x] && cumulatedEnergy[i-1][x-1] < cumulatedEnergy[i-1][x+1])
					{
						cumulatedEnergy[i][x] = energy[i][x] + cumulatedEnergy[i-1][x-1];
					}
					else if (cumulatedEnergy[i-1][x] < cumulatedEnergy[i-1][x+1])
					{
						cumulatedEnergy[i][x] = energy[i][x] + cumulatedEnergy[i-1][x];
					}
					else
					{
						cumulatedEnergy[i][x] = energy[i][x] + cumulatedEnergy[i-1][x+1];
					}
				}

			}
		}
	}
}

void genEnergyTable(std::vector<std::vector<int>>  &image, std::vector<std::vector<int>> &energy, std::pair<int, int> const &sizeOfPic)
{
	for(int y = 0; y < sizeOfPic.second; y++)
	{
		for(int x = 0; x < sizeOfPic.first; x++)
		{
			//left side case
			if(y == 0)
			{
				//top left corner case
				if(x == 0)
				{
					energy[y][x] = abs(image[y+1][x] - image[y][x]) + abs(image[y][x+1] - image[y][x]);
				}
				//bottom left
				else if (x == sizeOfPic.first - 1)
				{	
					energy[y][x] = abs(image[y+1][x] - image[y][x]) + abs(image[y][x-1] - image[y][x]);
				}
				else
				{
					energy[y][x] = abs(image[y+1][x] - image[y][x]) + abs(image[y][x-1] - image[y][x]) + abs(image[y][x+1] - image[y][x]);
				}
			}
			//right side case	
			else if(y == sizeOfPic.second - 1)
			{
				//top right
				if(x == 0)
				{
					energy[y][x] = abs(image[y-1][x] - image[y][x]) + abs(image[y][x+1] - image[y][x]);
				}
				//bottom right corner case
				else if (x == sizeOfPic.first - 1)
				{
					energy[y][x] = abs(image[y-1][x] - image[y][x]) + abs(image[y][x-1] - image[y][x]);
				}
				else
				{
					energy[y][x] = abs(image[y-1][x] - image[y][x]) + abs(image[y][x+1] - image[y][x]) + abs(image[y][x-1] - image[y][x]);
				}

			}
			//top case
			else if(y != 0 && y != sizeOfPic.second && x == 0)
			{
				energy[y][x] = abs(image[y-1][x] - image[y][x]) + abs(image[y+1][x] - image[y][x]) + abs(image[y][x+1] - image[y][x]); 
			}
			//bottom case
			else if(y != sizeOfPic.second - 1 && x == sizeOfPic.first - 1)
			{
				energy[y][x] = abs(image[y-1][x] - image[y][x]) + abs(image[y+1][x] - image[y][x]) + abs(image[y][x-1]- image[y][x]); 
			}
			//normal case
			else
			{
				energy[y][x] = abs(image[y][x-1] - image[y][x]) + abs(image[y][x+1] - image[y][x]) 
					+ abs(image[y+1][x] - image[y][x]) + abs(image[y-1][x] - image[y][x]);
			}
		}
	}
} 

void createImage(std::vector<std::vector<int>> &image, std::string imageName, std::pair<int, int> &sizeOfPic, int &number)
//[[pre: image.size() != 0]]
{
	std::ifstream in("../" + imageName + ".pgm");
	if(in.fail())
	{
		std::cout << "The file failed to open. This file should not be in the build folder, however needs to be one above the build folder.\n";
	}
	int tempint = 0;

	std::string temp;
	getline(in, temp);
	//need to figure out if it starts with # before this 
	getline(in, temp);

	in >> sizeOfPic.first;
	in >> sizeOfPic.second;
	in >> number;

	std::vector<int> tempvec{};
	
	for(int y = 0; y < sizeOfPic.second; y ++)
	{
		for(int x = 0; x < sizeOfPic.first; x++)
		{
			in >> tempint;
			tempvec.push_back(tempint);
		}
		image.push_back(tempvec);
		tempvec.clear();
	}		

	in.close();
}

void printImageCode(std::vector<std::vector<int>>  &image, std::pair<int,int> const &sizeOfPic)
{
	//std::cout << "size of pic: " << sizeOfPic.first << ' ' << sizeOfPic.second << '\n';
	for(int i = 0; i < sizeOfPic.second; i++)
	{
		for(int j = 0; j < sizeOfPic.first; j++)
		{
			std::cout << image[i][j] << ' ';
		}
		std::cout << '\n';
	}
}
