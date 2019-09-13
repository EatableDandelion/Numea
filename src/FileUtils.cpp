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
}
