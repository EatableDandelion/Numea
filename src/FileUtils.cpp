#include "FileUtils.h"

namespace Numea
{
	DataFileWriter::DataFileWriter(const std::string& name):fileName(name)
	{
		
	}
	
	DataFileWriter::~DataFileWriter()
	{
		if(file.is_open())
		{
			file.close();
		}
	}
	
	std::ofstream& DataFileWriter::getOfstream()
	{
		return file;
	}
	
	std::ifstream& Numea::operator>>(std::ifstream& stream, DataFileWriter& file)
	{
		stream >> file.getOfstream();
		return stream;
	}
}
