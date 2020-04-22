#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <initializer_list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class BehaviourTree
{
public:
	class Node
	{
	public:
		virtual bool run() = 0;
	};

	class CompositeNode : public Node
	{
	public:
		const std::vector<Node*>& getChildren() const
		{
			return m_children;
		}

		void addChild(Node* t_child)
		{
			m_children.emplace_back(t_child);
		}

		void addChildren(std::list<Node*> t_child)
		{
			for (Node* child : t_child)
			{
				addChild(child);
			}
		}

	private: 
		std::vector<Node*> m_children;
	};

	class Selector : public CompositeNode
	{
	public:
		virtual bool run() override
		{
			for (Node* child : getChildren())
			{
				if (child->run())
				{
					return true;
				}
			}
			return false;
		}
	};

	class Sequence : public CompositeNode
	{
	public:
		virtual bool run() override
		{
			for (Node* child : getChildren())
			{
				if (!child->run())
				{
					return false;
				}
			}
			std::cout << "root success" << std::endl;
			//m_eStatus == BH_SUCCESS; 
			return true;
		}
	};

	class Root : public Node
	{
	public:
		Node* m_child;
		class BehaviourTree;
		void setChild(Node* t_newChild)
		{
			m_child = t_newChild;
		}
		virtual bool run() override
		{
			return m_child->run();
		}
	};
private:
	Root* m_root;
	//Status m_eStatus;
public:
	BehaviourTree() :	//m_eStatus(BH_INVALID),
		m_root(new Root()) {};
	~BehaviourTree() {};
	void setRootChild(Node* rootChild)
	{
		m_root->setChild(rootChild);
	}
	bool run() const
	{
		/*if (t_true)
		{
			std::cout << "root success" << std::endl;
			m_eStatus == BH_SUCCESS;
		}
		else
		{
			std::cout << "root failure" << std::endl;
			m_eStatus == BH_FAILURE;
		}*/
		return m_root->run();
	}
};

class Action : public BehaviourTree::Node
{
public:
	Action(const std::string newName, int prob) : action(newName), statusSuccess(prob) {}
	virtual bool run () override
	{
		if (std::rand() % 100 < statusSuccess)
		{
			std::cout << action << " success" << std::endl;
			return true;
		}
		std::cout << action << " failure" << std::endl;
		return false;
	}
private:
	std::string action;
	int statusSuccess;
};