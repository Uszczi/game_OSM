#include "DataInfo.h"
#include <cmath>

DataInfo::DataInfo(unsigned maxSize) :
	maxSize(maxSize)
{
	buffer = new float[maxSize];
	clear();
}

DataInfo::~DataInfo()
{
	delete[] buffer;
}

void DataInfo::add(float value)
{
	buffer[index] = value;
	index = (index + 1) % maxSize;
	bufferSize = (bufferSize < index) ? index : bufferSize;

	minValue = std::fmin(minValue, value);
	maxValue = std::fmax(maxValue, value);
}

void DataInfo::clear()
{
	index = 0;
	bufferSize = 0;

	minValue = 1e12;
	maxValue = -1e12;
}

float DataInfo::averange() const
{
	float sum = 0;
	for(unsigned i = 0; i < bufferSize; ++i)
		sum += buffer[i];

	return sum / bufferSize;
}

float DataInfo::minimum() const
{
	return minValue;
}

float DataInfo::maximum() const
{
	return maxValue;
}
