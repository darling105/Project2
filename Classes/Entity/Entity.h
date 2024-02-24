#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "EntityInfo.h"
//#include "EntityStat.h"

USING_NS_CC;

class Entity : public Node
{
public:
	static Entity* create(EntityInfo* info);
	virtual bool init(EntityInfo* info);
	Sprite* getModel() { return _model; }
	EntityInfo* getEntityInfo() { return _info; }
protected:
	virtual bool loadAnimations();

protected:
	EntityInfo* _info;
	Sprite* _model;
};

#endif // !__ENTITY_H__
