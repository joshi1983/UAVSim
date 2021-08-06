#include "RenderTask.hpp"
#include "RenderTasks.hpp"
using namespace std;

unsigned int RenderTask::nextId = 0;

RenderTask::RenderTask(RenderTask * parent):
	 id(++RenderTask::nextId), parent(parent)
{
	RenderTasks * tasks = RenderTasks::getInstance();
	tasks->add(this);
}

unsigned int RenderTask::getId() const
{
	return id;
}

void RenderTask::processScreenshot()
{
    RenderTask* currentTask = getCurrentRenderTask();
    if (this != currentTask)
        currentTask->processScreenshot();
}

RenderTask* RenderTask::getCurrentRenderTask()
{
	if (children.size() == 0)
		return this;
	else
		return children.front();
}

const RenderTask* RenderTask::getCurrentRenderTask() const
{
	if (children.size() == 0)
		return this;
	else
		return children.front();
}

void RenderTask::removeFirstLeafChild()
{
	if (children.size() > 0)
		children.front()->removeFirstLeafChild();
	else if (parent != nullptr)
	{
		// remove this.
		parent->children.pop_front();
	}
}

RenderTask::~RenderTask()
{
	RenderTasks * tasks = RenderTasks::getInstance();
	tasks->remove(this);
}

void RenderTask::updateAnimationStateForCurrentTask(AnimationState & state) const
{
    const RenderTask* currentTask = getCurrentRenderTask();
    if (this != currentTask)
        currentTask->updateAnimationStateForCurrentTask(state);
}

void RenderTask::getViewport(RenderViewport & result) const
{
    const RenderTask* currentTask = getCurrentRenderTask();
    if (this != currentTask)
        currentTask->getViewport(result);
}