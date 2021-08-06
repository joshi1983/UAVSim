#include "RenderTasks.hpp"
#include <iostream>
using namespace std;

RenderTasks* RenderTasks::singleton = nullptr;

RenderTasks* RenderTasks::getInstance()
{
	if (RenderTasks::singleton == nullptr)
		RenderTasks::singleton = new RenderTasks();

	return RenderTasks::singleton;
}

RenderTasks::RenderTasks(): root(nullptr)
{
}

RenderTask* RenderTasks::getById(unsigned int id)
{
	if (tasks.find(id) == tasks.end()) {
		cerr << "Unable to find task with id: " << id << endl;
		return nullptr;
	}
	return tasks[id];
}

void RenderTasks::add(RenderTask* task)
{
	tasks[task->getId()] = task;
}

void RenderTasks::remove(RenderTask* task)
{
	tasks.erase(task->getId());
	// if removing root, update root accordingly.
	if (task->getId() == root->getId())
		root = nullptr;
}

void RenderTasks::updateAnimationStateForCurrentTask(AnimationState & state) const
{
	if (root != nullptr)
	{
		root->updateAnimationStateForCurrentTask(state);
	}
}

void RenderTasks::getViewport(RenderViewport & result) const
{
	if (root != nullptr)
	{
		root->getViewport(result);
	}
	else
	{
		result.widthRatio = 1;
		result.heightRatio = 1;
		result.leftRatio = 0;
		result.topRatio = 0;
	}
}
