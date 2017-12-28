#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <queue>

#include "Command.h"

class CommandQueue
{
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:
	std::queue<Command> mQueue;
};

#endif
