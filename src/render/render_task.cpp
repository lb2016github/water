#include "render_task.h"
#include <functional>
#include <mutex>

namespace water
{
	namespace render
	{
		RenderTaskManager* RenderTaskManager::m_instance = nullptr;
		std::mutex buffer_mtx;

		void RenderTaskManager::render()
		{
			// swap buffer
			swap_buffer(m_front_buffer, m_back_buffer);
		}
		void RenderTaskManager::add_task(IRenderTask * task)
		{
			buffer_mtx.lock();
			m_task_buffers[m_back_buffer].add_task(task);
			buffer_mtx.unlock();
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
		inline void water::RenderTaskManager::swap_buffer(int & a, int & b)
		{
			buffer_mtx.lock();
			int tmp = a;
			a = b;
			b = tmp;
			buffer_mtx.unlock();
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
		void RenderTaskBuffer::add_task(IRenderTask * task)
		{
			m_tasks.push_back(task);
		}
		void RenderTaskBuffer::clear()
		{
			m_ready = false;
			m_tasks.clear();
		}
		void RenderTaskBuffer::set_ready(bool is_ready)
		{
			m_ready = is_ready;
		}
	}
}