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
			dst_buffer = m_task_buffers[m_front_buffer];
			buffer_mtx.unlock();
		}
		void RenderTaskManager::tick()
		{
			commit();
			if (!m_render)
			{
				m_render = new RenderThread();
				std::thread th(&RenderThread::render, m_render);
				if (th.joinable()) th.detach();
			}
			//m_render->do_render();
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
		RenderTaskBuffer::RenderTaskBuffer(const RenderTaskBuffer& buffer)
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
		void RenderThread::render()
		{
			auto window = world::World::get_instance()->get_window();
			auto size = window->get_window_size();
			auto this_window = glfwCreateWindow(size.x, size.y, "tmp", NULL, nullptr);

			glfwMakeContextCurrent(this_window);
			// int glad
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				log_error("[GLAD]Failed to initialize glad");
				return;
			}
			while (true)
			{
				get_device()->clear();
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
				glfwSwapBuffers(this_window);
				glfwPollEvents();
			}
		}
		void RenderThread::do_render()
		{
			get_device()->clear();
			// get buffer data
			RenderTaskManager::get_instance()->get_front_buffer(m_task_buffer);
			if (!m_task_buffer.is_ready())
			{
				return;
			}
			// todo sort tasks to decrease drawcall 
			// do render jobs
			for each (RenderTaskPtr task in m_task_buffer.m_tasks)
			{
				task->render();
			}
		}
		RenderThread::RenderThread()
		{
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