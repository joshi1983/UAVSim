#ifndef RENDER_TASK_HEADER_INCLUDED
#define RENDER_TASK_HEADER_INCLUDED
#include <list>
#include "../AnimationState.hpp"
#include <string>

class RenderTask
{
	private:
		static unsigned int nextId;
		unsigned int id;
	protected:
		RenderTask * parent;
		std::list<RenderTask*> children;
		void removeFirstLeafChild();
	public:
		RenderTask(RenderTask * parent);
		unsigned int getId() const;
		virtual void updateAnimationStateForCurrentTask(AnimationState & state) const;
		RenderTask* getCurrentRenderTask();
		const RenderTask* getCurrentRenderTask() const;
		virtual std::string getTypeName() const = 0;
		virtual ~RenderTask();
};

#endif
