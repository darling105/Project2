#ifndef _DEFINE_BITMASK_H__

class DefineBitmask
{
public:
	static const int NON = 0x00;
	static const int GROUND = 0x01;
	static const int CHARACTER = 0x08;
	static const int ENEMY = 0x03;
	static const int VOID_ENEMY = 0x04;
	static const int BULLET = 0x10;
	static const int STAIR = 0x09;
	static const int FINISH = 0x40;
};
#endif // !_DEFINE_BITMASK_H__
