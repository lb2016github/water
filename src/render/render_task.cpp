#include "render_task.h"
#include <functional>
#include <algorithm>
#include <mutex>
#include "render/render_program.h"
#include "render/material.h"
#include "render/render_object.h"

namespace water
{
	namespace render
	{
		RenderTaskManager* RenderTaskManager::m_instance = nullptr;
		std::mutex buffer_mtx;

		void RenderTaskManager::commit()
		{
			buffer_mtx.lock();

			// swap buffer
			int tmp = m_front_buffer;
			m_front_buffer = m_back_buffer;
			m_back_buffer = m_front_buffer;
			// set ready state
			m_task_buffers[m_front_buffer].set_ready(true);
			m_task_buffers[m_back_buffer].clear();

			buffer_mtx.unlock();
		}
		void RenderTaskManager::add_task(RenderTaskPtr task)
		{
			m_task_buffers[m_back_buffer].add_task(task);
		}
		void RenderTaskManager::get_front_buffer(RenderTaskBuffer& dst_buffer)
		{
			buffer_mtx.lock();
			dst_buffer = m_task_buffers[m_front_buffer];
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
		RenderTaskManager::RenderTaskManager()
		{
			m_render = new RenderThread();
			std::thread th(&RenderThread::render, m_render);
			if (th.joinable()) th.detach();
		}
		RenderTaskManager::~RenderTaskManager()
		{
			for (int i = 0; i < 2; ++i)
			{
				m_task_buffers[i].clear();
			}
			delete m_render;
		}
		RenderTaskBuffer::RenderTaskBuffer(): m_ready(false)
		{
		}
		RenderTaskBuffer::RenderTaskBuffer(RenderTaskBuffer&& buffer)
		{
			std::move(buffer.m_tasks.begin(), buffer.m_tasks.end(), m_tasks.begin());
			m_ready = buffer.m_ready;
			buffer.m_ready = false;
		}
		RenderTaskBuffer::RenderTaskBuffer(RenderTaskBuffer& buffer)
		{
			std::copy(buffer.m_tasks.begin(), buffer.m_tasks.end(), m_tasks.begin());
			m_ready = buffer.m_ready;
		}
		RenderTaskBuffer& RenderTaskBuffer::operator=(RenderTaskBuffer&& buffer)
		{
			if (&buffer == this) return *this;
			clear();
			std::move(buffer.m_tasks.begin(), buffer.m_tasks.end(), m_tasks.begin());
			m_ready = buffer.m_ready;
			buffer.m_ready = false;
			return *this;
		}
		RenderTaskBuffer& RenderTaskBuffer::operator=(const RenderTaskBuffer& buffer)
		{
			if (&buffer == this) return *this;
			clear();
			std::copy(buffer.m_tasks.begin(), buffer.m_tasks.end(), m_tasks.begin());
			m_ready = buffer.m_ready;
			return *this;
		}
		void RenderTaskBuffer::add_task(RenderTaskPtr task)
		{
			// add dependent tasks
			RenderTaskList dependents = task->get_depend_tasks();
			for each (RenderTaskPtr d_task in dependents)
			{
				add_task(d_task);
			}
			// add task
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
		void RenderThread::render()
		{
			while (true)
			{
				// get buffer data
				RenderTaskManager::get_instance()->get_front_buffer(m_task_buffer);
				if (!m_task_buffer.is_ready())
				{
					continue;
				}
				// todo sort tasks to decrease drawcall 
				// do render jobs
				for each (RenderTaskPtr task in m_task_buffer.m_tasks)
				{
					task->render();
				}
				// render end
			}
		}
		RenderThread::RenderThread()
		{
		}
		RenderTask::RenderTask(MeshPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map, RenderTaskPtr dependent):
			mesh_ptr(mesh), program_ptr(program), render_state(render_state), param_map(param_map)
		{
		}
		RenderTask::~RenderTask()
		{
		}
		void RenderTask::render()
		{
			// use program and apply parameters
			program_ptr->use_program();
			program_ptr->apply_parameters(param_map);
			// draw meshes
			mesh_ptr->render();
		}
		RenderTaskList RenderTask::get_depend_tasks()
		{
			return RenderTaskList();
		}
	}
}