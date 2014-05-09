#ifndef __Action_H__
#define __Action_H__

class Action{
	int x_;
	int y_;

public:
	Action(int x, int y);
	int x();
	int y();
    virtual void execute() = 0;
	virtual ~Action(){};
};

#endif /* __Action_H__ */

