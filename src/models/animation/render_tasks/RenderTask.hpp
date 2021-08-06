#ifndef RENDER_TASK_HEADER_INCLUDED
#define RENDER_TASK_HEADER_INCLUDED
#include <list>
#include <string>
#include "../AnimationState.hpp"
#include "../../../RenderViewport.hpp"
#include "AnimationStateUpdater.hpp"

class RenderTask: public AnimationStateUpdater
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
		virtual void updateAnimationStateForCurrentTask(AnimationState & state) const override;
		RenderTask* getCurrentRenderTask();
		const RenderTask* getCurrentRenderTask() const;
		virtual void getViewport(RenderViewport & result) const;
		virtual void processScreenshot();
		virtual std::string getTypeName() const = 0;
		virtual ~RenderTask();
};

#endif
