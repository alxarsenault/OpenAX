/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axFrameworks.
 *
 * axFrameworks is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axFrameworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axFrameworks, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "App.h"
#include "Config.h"
#include "Window.h"
#include "WindowManager.h"
#include "WindowTree.h"

#include "Render.h"
#include "RenderMath.h"
#include "GraphicInterface.h"

#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#ifdef AX_EOS_CORE
#include "axCoreEOS.h"
#endif

namespace ax {
/*
 * ax::Window::Dimension
 */
ax::Window::Dimension::Dimension(ax::Window* win, const ax::Rect& rect)
	: _win(win)
	, _rect(rect)
	, _shownRect(ax::Point(0, 0), rect.size)
	, _scrollDecay(0, 0)
	, _frameBufferObj(rect.size)
{
}

ax::Window::Dimension::Dimension(const ax::Rect& rect)
	: _rect(rect)
	, _shownRect(ax::Point(0, 0), rect.size)
	, _scrollDecay(0, 0)
	, _frameBufferObj(rect.size)
{
}

ax::Rect ax::Window::Dimension::GetAbsoluteRect() const
{
	ax::Point pos = _rect.position;
	Window* win = _win;

	/// @todo This can be faily slow.
	while (win->node.GetParent() != nullptr) {
		pos += win->node.GetParent()->dimension.GetRect().position;
		pos -= win->dimension._scrollDecay;
		win = win->node.GetParent();
	}

	return ax::Rect(pos, _rect.size);
}

void ax::Window::Dimension::SetRect(const ax::Rect& rect)
{
	_rect.position = rect.position;
	_rect.size = rect.size;
	_shownRect.size = rect.size;

	if (_win->property.HasProperty("BackBuffer")) {
		_frameBufferObj.Resize(rect.size);
	}

	_win->event.OnResize(_rect.size);
	_win->Update();
}

void ax::Window::Dimension::SetSize(const ax::Size& size)
{
	_rect.size = size;
	_shownRect.size = size;

	if (_win->property.HasProperty("BackBuffer")) {
		_frameBufferObj.Resize(size);
	}

	_win->event.OnResize(_rect.size);
	_win->Update();
}

void ax::Window::Dimension::SetPosition(const ax::Point& pos)
{
	_rect.position = pos;
	_win->Update();
}

void ax::Window::Dimension::SetShownRect(const ax::Rect& rect)
{
	_shownRect = rect;
	_win->Update();
}

void ax::Window::Dimension::SetSizeNoShowRect(const ax::Size& size)
{
	_rect.size = size;

	if (_win->property.HasProperty("BackBuffer")) {
		_frameBufferObj.Resize(size);
	}

	_win->Update();
}

void ax::Window::Dimension::SetScrollDecay(const ax::Point& decay)
{
	_scrollDecay = decay;
}

ax::Point ax::Window::Dimension::GetScrollDecay() const
{
	return _scrollDecay;
}

/*
 * Window event.
 */
ax::Window::Event::Event(ax::Window* win, ax::Core::WindowManager* win_manager)
	: _win(win)
	, _windowManager(win_manager)
{
}

ax::Window::Event::~Event()
{
	std::cout << "Delete window event." << std::endl;
}

ax::Window::Ptr ax::Window::Event::GetWindow()
{
	return _win->GetWindowPtr();
}

void Window::Event::GrabMouse()
{
	_windowManager->GrabMouse(_win);
}

void Window::Event::UnGrabMouse()
{
	_windowManager->UnGrabMouse();
}

void Window::Event::GrabScroll()
{
	_windowManager->SetScrollCaptureWindow(_win);
}

void Window::Event::UnGrabScroll()
{
	_windowManager->ReleaseScrollCaptureWindow();
}

bool Window::Event::IsGrabbed() const
{
	// Need to change this with this pointer to current ax::Window.
	return _windowManager->IsGrab();
}

bool Window::Event::IsMouseHoverWindow() const
{
	return _windowManager->IsMouseHoverWindow(_win);
}

void Window::Event::GrabKey()
{
	_windowManager->GrabKey(_win);
}

void Window::Event::UnGrabKey()
{
	_windowManager->UnGrabKey();
}

bool Window::Event::IsKeyGrab() const
{
	return _windowManager->IsKeyGrab(_win);
}

void Window::Event::GrabGlobalKey()
{
	_windowManager->AddGlobalGrabedWindow(_win);
}

/*
 * Window node.
 */
 
std::vector<ax::Window::Node::BlockDrawingInfo> ax::Window::Node::_block_drawing_queue;
 
//ax::Window::Ptr ax::Window::Node::Add(ax::Window::Ptr child)
void ax::Window::Node::Add(ax::Window::Ptr child)
{
#ifdef AX_EOS_CORE
	child->dimension.GetFrameBuffer()->AssignCustomFBDrawFunction([child](
		ax::GL::FrameBuffer& fb) {

		ax::App& app(ax::App::GetInstance());
		ax::CoreEOS* core = static_cast<ax::CoreEOS*>(app.GetCore());

		ax::Size global_size = ax::App::GetInstance().GetFrameSize();
		glViewport(0, 0, global_size.x, global_size.y);

		// Bind main frame buffer.
		glBindFramebuffer(GL_FRAMEBUFFER, core->GetMainFrameBufferID());

		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		fb.DrawingFrameBufferBlendFunction();

		ax::Point win_abs_pos = child->dimension.GetAbsoluteRect().position;

		// Projection matrix.
		glm::mat4 projMat = glm::ortho(
			(float)0.0, (float)global_size.x, (float)global_size.y, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(
			glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);
		glm::mat4 model_view_proj = projMat * view * model;

		ax::FloatPoint pos(0.0, 0.0);
		ax::FloatSize size(child->dimension.GetShownRect().size.Cast<float>());

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, fb.GetFrameBufferTexture());

		float vertices[8] = { pos.x, pos.y, pos.x, pos.y + size.y,
			pos.x + size.x, pos.y + size.y, pos.x + size.x, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

		GLuint prog_id = ax::GC::shader_fb.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(
			MatrixID, 1, GL_FALSE, (float*)&model_view_proj[0][0]);

		// Vertex coordinate.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Texture coordinate.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(5);

		glDisable(GL_TEXTURE_2D);
	});
#endif

	child->node._parent = _win;
	_children.push_back(child);
//	return child;
}

void ax::Window::Node::Add(std::shared_ptr<Backbone> backbone)
{
	ax::Window* child = backbone->GetWindow();
	child->backbone = backbone;
	child->node._parent = _win;
	
	_children.push_back(ax::Window::Ptr(child));

//	child->backbone = backbone;

#ifdef AX_EOS_CORE
	child->dimension.GetFrameBuffer()->AssignCustomFBDrawFunction([child](
		ax::GL::FrameBuffer& fb) {

		ax::App& app(ax::App::GetInstance());
		ax::CoreEOS* core = static_cast<ax::CoreEOS*>(app.GetCore());
		//		core->DrawOnMainFBO();
		ax::Size global_size = ax::App::GetInstance().GetFrameSize();
		glViewport(0, 0, global_size.x, global_size.y);
		//																	  glViewport(0, 0,
		//300,
		// 300);

		// Bind main frame buffer.
		glBindFramebuffer(GL_FRAMEBUFFER, core->GetMainFrameBufferID());

		ax::GC::shader_fb.Activate();
		glEnable(GL_TEXTURE_2D);

		fb.DrawingFrameBufferBlendFunction();

		ax::Point win_abs_pos = child->dimension.GetAbsoluteRect().position;
		//																	  ax::Size global_size
		//=
		// ax::App::GetInstance().GetFrameSize();

		// Projection matrix.
		glm::mat4 projMat = glm::ortho(
			(float)0.0, (float)global_size.x, (float)global_size.y, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(
			glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);
		glm::mat4 model_view_proj = projMat * view * model;

		ax::FloatPoint pos(0.0, 0.0);
		ax::FloatSize size(child->dimension.GetShownRect().size.Cast<float>());

		// Bind framebuffer texture.
		glBindTexture(GL_TEXTURE_2D, fb.GetFrameBufferTexture());

		float vertices[8] = { pos.x, pos.y, pos.x, pos.y + size.y,
			pos.x + size.x, pos.y + size.y, pos.x + size.x, pos.y };

		float tex_coords[8] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

		GLuint prog_id = ax::GC::shader_fb.GetProgramId();
		GLuint MatrixID = glGetUniformLocation(prog_id, "mvp_matrix");
		glUniformMatrix4fv(
			MatrixID, 1, GL_FALSE, (float*)&model_view_proj[0][0]);

		// Vertex coordinate.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// Texture coordinate.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, tex_coords);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(5);

		glDisable(GL_TEXTURE_2D);
	});
#endif

//	return *_children.end();
}

void ax::Window::Node::Reparent(Window* parent, const ax::Point& position)
{
	ax::Print("TODO FIX THIS : axWindow.cpp Line 329");
		
		//        _parent = parent;
		//        dimension.SetPosition(position);
		//
		//        ax::Event::ID temp = _parent->GetId();
		//        _parent->ChangeId(GetId());
		//        ChangeId(temp);
		
//	Update();
}

void ax::Window::Node::BeforeDrawing(ax::Window* win)
{
	if (win->property.HasProperty("BlockDrawing")) {
		ax::Window::Dimension& dim = win->dimension;
		ax::Rect shown_rect(dim.GetShownRect());
		shown_rect.position = dim.GetScrollDecay();
		
		ax::Rect abs_rect = dim.GetAbsoluteRect();
		
		ax::Window* tmp = win;
		while(tmp != nullptr) {
			ax::Rect tmp_abs_rect(tmp->dimension.GetAbsoluteRect());
			
			// Find biggest left side position.
			if(tmp_abs_rect.position.x > abs_rect.position.x) {
				abs_rect.position.x = tmp_abs_rect.position.x;
			}
			
			
			
//			// Find right side.
//			if(tmp_abs_rect.position.x > abs_rect.position.x) {
//				abs_rect.position.x = tmp_abs_rect.position.x;
//			}
			
			tmp = tmp->node.GetParent();
		}
		
		// Find smallest size in parent.
//		ax::Window* tmp = win;
//		while(tmp != nullptr) {
//			ax::Rect tmp_abs_rect(tmp->dimension.GetAbsoluteRect());
//			if(tmp_abs_rect.position.x + tmp->dimension.GetShownRect().size.x < abs_rect.position.x + shown_rect.size.x) {
//				shown_rect.size.x = tmp->dimension.GetShownRect().size.x;
//				abs_rect.position.x = tmp_abs_rect.position.x;
//			}
//			tmp = tmp->node.GetParent();
//		}
		
		ax::GL::BlockDrawing(abs_rect, shown_rect,
			ax::App::GetInstance().GetFrameSize());
		
		
		BlockDrawingInfo binfo;
		binfo.abs_rect = abs_rect;
		binfo.shown_rect = shown_rect;
		_block_drawing_queue.push_back(binfo);
	}
}

void ax::Window::Node::EndDrawing(ax::Window* win)
{
	if (win->property.HasProperty("BlockDrawing")) {
		
		_block_drawing_queue.pop_back();
		
		if(_block_drawing_queue.size()) {
			ax::GL::BlockDrawing(_block_drawing_queue.back().abs_rect, _block_drawing_queue.back().shown_rect,
				ax::App::GetInstance().GetFrameSize());
		}
		else {
			ax::GL::UnBlockDrawing();
		}
	}
}

void DrawWindow(ax::Window* win)
{
	//	ax::GL::Math::Matrix4 mview;
	//	mview.Identity().Load();
	//
	//	ax::Window::Dimension& dim = win->dimension;
	////	mview.Translate(dim.GetAbsoluteRect().position -
	/// dim.GetScrollDecay()).Process();
	//	mview.Translate(dim.GetAbsoluteRect().position).Process();

	win->RenderWindow();
}

void Window::Node::Draw()
{
	bool edit_active = false;

	// Don't draw if not shown.
	if (!_win->IsShown()) {
		return;
	}

	if (_win->property.HasProperty("EditingWidget") && edit_active == false) {
		// Don't draw debug editor window and childs.
		return;
	}

	ax::GL::Math::Matrix4 mview_before(ax::GL::Math::GetModelViewMatrixId());

	//	_win->event.OnBeforeDrawing(0);
	BeforeDrawing(_win);

	DrawWindow(_win);

	// Draw all children.
	for (Ptr it : _children) {
		if (it == nullptr) {
			continue;
		}

		bool is_edit_widget = it->property.HasProperty("EditingWidget");

		if (!it->IsShown()) {
			continue;
		}

		// if(is_edit_widget && (!debug_active ||
		// !window->HasProperty("Editable")))
		if (is_edit_widget && edit_active == false) {
			continue;
		}

		it->event.OnBeforeDrawing(0);

		// Save matrix.
		ax::GL::Math::Matrix4 mview_child_before(
			ax::GL::Math::GetModelViewMatrixId());

		// Block the drawging rectangle if window IsBlockDrawing activated.
		BeforeDrawing(it.get());

		// Draw window before nodes.
		DrawWindow(it.get());

		// Draw all child nodes.
		it->node.Draw();

		ax::GL::Math::Matrix4 mview;
		mview.Identity().Load();
		mview.Translate(it->dimension.GetAbsoluteRect().position).Process();

		// @todo This should be remove.
		it->OnPaintStatic();

		// Unblock rectangle.
		EndDrawing(it.get());

		// Reload original matrix.
		mview_child_before.Load();
	}

	EndDrawing(_win);
}

Window::Window(const ax::Rect& rect)
	: ax::Event::Object(ax::App::GetInstance().GetEventManager())
	, _windowManager(ax::App::GetInstance().GetWindowManager())
	, dimension(this, rect) // Members
	, event(this, ax::App::GetInstance().GetWindowManager())
	, state(this)
	, node(this)
{
	state[Hidden] = false;
	state[NeedUpdate] = true;

	property.AddProperty("BackBuffer");
	property.AddProperty("Selectable");
}

Window::~Window()
{
//	ax::Print("ax::Window destructor ", GetId());
}

void Window::DeleteWindow()
{
	//        _windowManager->GetWindowTree()->DeleteWindow(this);
}

ax::Window::Ptr Window::GetWindowPtr()
{
	if (node.GetParent() != nullptr) {
		ax::Window::Ptr win;
		for (auto& n : node.GetParent()->node.GetChildren()) {
			if (n->GetId() == GetId()) {
				win = n;
				return win;
			}
		}
	}

	return nullptr;
}

bool Window::IsShown()
{
	Window* win = this;

	while (win != nullptr) {
		if (win->state[Hidden] == true) {
			return false;
		}

		win = win->node.GetParent();
	}
	return true;
}

void Window::Show()
{
	state.Apply(Hidden, false);
}

void Window::Hide()
{
	state.Apply(Hidden, true);
}



void Window::Update()
{
	state[NeedUpdate] = true;
	ax::App::GetInstance().UpdateAll();
}

void Window::RenderWindow()
{
#if _axBackBufferWindow_ == 1
	if (property.HasProperty("BackBuffer")) {
		if (state[NeedUpdate]) {

			// Draw on framebuffer.
			dimension.GetFrameBuffer()->DrawOnFrameBuffer(
				[this]() {
					event.OnPaint(ax::GC());
					event.OnPaint3D(ax::GC());
				},
				dimension.GetRect().size,
				ax::App::GetInstance().GetFrameSize());

			state[NeedUpdate] = false;
		}

		// Draw the framebuffer.
		ax::Point win_abs_pos = dimension.GetAbsoluteRect().position;
		ax::Size global_size = ax::App::GetInstance().GetFrameSize();

		// Projection matrix.
		glm::mat4 projMat = glm::ortho(
			(float)0.0, (float)global_size.x, (float)global_size.y, (float)0.0);

		// View matrix.
		glm::mat4 view = glm::translate(
			glm::mat4(1.0f), glm::vec3(win_abs_pos.x, win_abs_pos.y, 0.0f));

		glm::mat4 model(1.0f);

		glm::mat4 model_view_proj = projMat * view * model;

		dimension.GetFrameBuffer()->DrawFrameBuffer(
			dimension.GetShownRect().size, ax::Point(0, 0),
			ax::Rect(0, 0, 100, 100), (void*)&model_view_proj[0][0]);

		ax::GC::mvp_matrix = model_view_proj;
		event.OnPaintOverFrameBuffer(ax::GC());
	}
	else {
		event.OnPaint(ax::GC());
		event.OnPaint3D(ax::GC());
	}

#else
	OnPaint();
#endif //_axBackBufferWindow_
}

ax::Rect Window::GetWindowPixelData(unsigned char*& data) const
{
	ax::Rect rect(dimension.GetAbsoluteRect());

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/// @todo MOVE TO axGL lib.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	data = new unsigned char[rect.size.x * rect.size.y * 4];
	ax::Size globalSize(ax::App::GetInstance().GetFrameSize());

	glReadPixels(rect.position.x, globalSize.y - rect.position.y - rect.size.y,
		rect.size.x, rect.size.y,
		GL_RGBA, // Format.
		GL_UNSIGNED_BYTE, // Type.
		(void*)data);

	return rect;
}

void Window::GetWindowPixelData(
	unsigned char*& data, const ax::Rect& rect) const
{
	ax::Point pos(dimension.GetAbsoluteRect().position + rect.position);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/// @todo MOVE TO axGL lib.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	data = new unsigned char[rect.size.x * rect.size.y * 4];
	ax::Size globalSize(ax::App::GetInstance().GetFrameSize());

	glReadPixels(pos.x, globalSize.y - pos.y - rect.size.y, rect.size.x,
		rect.size.y,
		GL_RGBA, // Format.
		GL_UNSIGNED_BYTE, // Type.
		(void*)data);
}
} // namespace ax
