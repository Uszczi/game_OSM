#ifndef SRC_DATAINFO_H_
#define SRC_DATAINFO_H_

class DataInfo {
	float *buffer;
	float minValue, maxValue;

	unsigned bufferSize;
	unsigned index;
	unsigned maxSize;

public:
	DataInfo(unsigned maxSize);
	virtual ~DataInfo();

	void add(float value);
	void clear();

	float averange() const;
	float minimum() const;
	float maximum() const;
};

#endif /* SRC_DATAINFO_H_ */
