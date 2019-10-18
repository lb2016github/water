#include "render_task.h"
#include <functional>
#include <algorithm>
#include <mutex>
#include "render/render_program.h"
#include "render/material.h"
#include "render/render_object.h"
#include "render/device.h"
#include "render_state.h"
#include "world/gameobjects/world.h"
#include "glad/glad.h"
#include "glfw3/glfw3.h"
#include "common/log.h"

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
			m_back_buffer = tmp;
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
			dst_buffer = std::move(m_task_buffers[m_front_buffer]);
			buffer_mtx.unlock();
		}
		bool RenderTaskManager::is_front_ready()
		{
			return m_task_buffers[m_front_buffer].m_ready;
		}
		void RenderTaskManager::tick()
		{
			commit();
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
		}
		RenderTaskManager::~RenderTaskManager()
		{
			for (int i = 0; i < 2; ++i)
			{
				m_task_buffers[i].clear();
			}
		}
		RenderTaskBuffer::RenderTaskBuffer(): m_ready(false)
		{
		}
		RenderTaskBuffer::RenderTaskBuffer(RenderTaskBuffer&& buffer)
		{
			m_tasks = std::move(buffer.m_tasks);
			m_ready = buffer.m_ready;
			buffer.m_ready = false;
		}
		RenderTaskBuffer::RenderTaskBuffer(const RenderTaskBuffer& buffer)
		{
			std::copy(buffer.m_tasks.begin(), buffer.m_tasks.end(), m_tasks.begin());
			m_ready = buffer.m_ready;
		}
		RenderTaskBuffer& RenderTaskBuffer::operator=(RenderTaskBuffer&& buffer)
		{
			if (&buffer == this) return *this;
			clear();
			m_ready = buffer.m_ready;
			m_tasks = std::move(buffer.m_tasks);
			buffer.m_ready = false;
			return *this;
		}
		RenderTaskBuffer& RenderTaskBuffer::operator=(const RenderTaskBuffer& buffer)
		{
			if (&buffer == this) return *this;
			clear();
			m_tasks.resize(buffer.m_tasks.size());
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
		RenderTask::RenderTask(MeshDataPtr mesh, ProgramPtr program, RenderStateInfo render_state, ParameterMap param_map, RenderTaskPtr dependent):
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
			// update render state
			auto device = get_device();
			device->get_render_state_manager()->apply(render_state);
			// draw meshes
			device->draw(mesh_ptr);
		}
		RenderTaskList RenderTask::get_depend_tasks()
		{
			return RenderTaskList();
		}
		RenderTargetTask::RenderTargetTask(Command cmd, IRenderTargetPtr ptr): m_cmd(cmd), m_rtpr(ptr)
		{
		}
		void RenderTargetTask::render()
		{
			switch (m_cmd)
			{
			case CMD_BIND_FOR_WIRTE:
				m_rtpr->bind_for_writing();
				break;
			case CMD_RESET:
				m_rtpr->reset();
				break;
			default:
				break;
			}
		}
		RenderTaskList RenderTargetTask::get_depend_tasks()
		{
			return RenderTaskList();
		}
	}
}