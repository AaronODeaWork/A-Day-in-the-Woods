/// <summary>
/// @author: Jack Fennell
/// @date 06/02/2020
/// </summary>

#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H
#include <Player.h>



//Template that each command will take
class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Entity& t_entity) = 0;
	
protected:
	Command() {};
	
};

#endif // !COMMANDINTERFACE_H