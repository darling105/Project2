#ifndef __ENTITY_INFO_H__
#define __ENTITY_INFO_H__

#include <iostream>


class EntityInfo
{
public:
	int _level;
	std::string _entityName;

	EntityInfo(std::string name)
	{
		this->_entityName = name;

	}
};

#endif // !__ENTITY_INFO_H__