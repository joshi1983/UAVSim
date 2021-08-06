#ifndef RENDER_TASKS_HEADER_INCLUDED
#define RENDER_TASKS_HEADER_INCLUDED
#include <map>
#include "RenderTask.hpp"
#include "../AnimationState.hpp"

class RenderTasks
{
	private:
		std::map<unsigned int, RenderTask*> tasks;
		RenderTask* root;
		RenderTasks();
		static RenderTasks* singleton;
	public:
		RenderTask* getById(unsigned int id);
		void updateAnimationStateForCurrentTask(AnimationState & state) const;
		void getViewport(RenderViewport & result) const;
		void add(RenderTask* task);
		void remove(RenderTask* task);
		static RenderTasks* getInstance();
};

#endif
