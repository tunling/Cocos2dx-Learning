#ifndef __MyCallBackReader__
#define __MyCallBackReader__
#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
class MyCallBackReader : public cocostudio::NodeReader
{
public:
	MyCallBackReader() {};
	~MyCallBackReader() {};
	static MyCallBackReader* getInstance();
	static void purge();
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};
#endif
