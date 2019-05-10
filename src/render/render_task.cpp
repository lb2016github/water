#include "render_task.h"
#include <functional>

namespace water
{
	namespace render
	{
		RenderTaskManager* RenderTaskManager::m_instance = nullptr;
		void RenderTaskManager::render()
		{
			std::vector<IRenderTask*> finished_task;
			for (std::vector<IRenderTask*>::iterator iter = m_tasks[cur_index].begin(); iter != m_tasks[cur_index].end(); ++iter)
			{
				IRenderTask* cur_task = (*iter);
			}
		}
		void RenderTaskManager::add_task(IRenderTask * task)
		{
			m_tasks[cur_index].push_back(task);
		}
		RenderTaskManager * RenderTaskManager::get_instance()
		{
			if (m_instance == nullptr)
			{
				m_instance = new RenderTaskManager();
			}
			return m_instance;
		}
		void RenderTaskManager::before_render()
		{
			// swap
			cur_index = (cur_index + 1) % 2;
			// todo sort tasks
			RenderTaskList copy;
			std::function<void(IRenderTask* task)> sort_task;
			sort_task = [&copy, &sort_task](IRenderTask* task)
			{
				RenderTaskList tmp = task->get_depend_tasks();
				for (RenderTaskList::iterator iter = tmp.begin(); iter != tmp.end(); ++iter)
				{
					sort_task(task);
				}
				copy.push_back(task);
			};
			for each (IRenderTask* task in m_tasks[cur_index])
			{
				sort_task(task);
			}
			m_tasks[cur_index].clear();
			m_tasks[cur_index] = std::move(copy);
		}
		void RenderTaskManager::do_render()
		{
			for each(IRenderTask* task in m_tasks[cur_index])
			{
				task->render();
			}
		}
		void RenderTaskManager::end_render()
		{
			m_tasks[cur_index].clear();
		}
		RenderTaskManager::RenderTaskManager()
		{
		}
		RenderTaskManager::~RenderTaskManager()
		{
			for (int i = 0; i < 2; ++i)
			{
				for (std::vector<IRenderTask*>::iterator iter = m_tasks[i].begin(); iter != m_tasks[i].end(); ++iter)
				{
					delete (*iter);
				}
				m_tasks[i].clear();
			}
		}
	}
}