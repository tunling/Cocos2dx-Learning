#include "MyCallBackReader.h"
#include "MyCallBack.h"
USING_NS_CC;
static MyCallBackReader* _instanceMyCallBackReader = nullptr;
MyCallBackReader* MyCallBackReader::getInstance()
{
	if (!_instanceMyCallBackReader)
	{
		_instanceMyCallBackReader = new MyCallBackReader();
	}
	return _instanceMyCallBackReader;
}

void MyCallBackReader::purge()
{
	CC_SAFE_DELETE(_instanceMyCallBackReader);
}

Node* MyCallBackReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	MyCallBack* node = MyCallBack::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
}