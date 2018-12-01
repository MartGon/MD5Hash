#include <openssl/md5.h>

#include <iostream>
#include <fstream>
#include <iomanip>

const uint64_t CHUNK_SIZE = INT32_MAX / 2;

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cout << "Need a filename to hash\n";
		std::cin.get();
		return -1;
	}

	// Initialize MD5

	MD5_CTX md5;

	if (!MD5_Init(&md5))
	{
		std::cout << "Fail when trying to init MD5\n";
		std::cin.get();
		return -1;
	}

	// Open file
	std::string filename(argv[1]);
	std::fstream file(filename, std::fstream::binary | std::fstream::in | std::fstream::ate);

	// Get file size and reset index
	uint64_t file_size = file.tellg();
	file.seekg(0);

	// Read proccess
	unsigned char* chunk = new unsigned char[CHUNK_SIZE];
	std::cout << "File progress 00%";
	while (true)
	{
		// Get current index position
		uint64_t index = file.tellg();
		uint64_t diff = file_size - index;

		// Print progress
		std::cout << "\rFile progress " << (int)((float)index / (float)file_size * 100) << "%";

		// Set size to read and hash
		uint32_t size_to_read = CHUNK_SIZE;
		if (!diff)
			break;
		else if (diff < CHUNK_SIZE)
			size_to_read = diff;

		// Read from file
		file.read((char*)chunk, size_to_read);

		// Feed data to md5 object
		if (!MD5_Update(&md5, chunk, size_to_read))
		{
			std::cout << "Fail during update process\n";
			std::cin.get();
			return -1;
		}
	} 

	// Finishing md5
	unsigned char hash[16];
	unsigned char pos = 0;
	if (!MD5_Final(hash, &md5))
	{
		std::cout << "Fail during finalizing process\n";
		std::cin.get();
		return -1;
	}

	// Result
	std::cout << "\nThe final result is ";
	for (const auto& elem : hash)
	{
		std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)elem;
	}

	std::cout << "\n";

	std::cin.get();
	return 0;
}