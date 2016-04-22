#include <OpenAX/Button.h>
#include <OpenAX/OpenAX.h>
#include <OpenAX/Slider.h>
#include <OpenAX/TextBox.h>

#include "ColorPicker.h"

#include "atSaveWorkDialog.h"

int main()
{
	ax::App& app(ax::App::GetInstance());

	app.AddMainEntry([&app]() {
		// Main window.
		ax::Window* win = ax::Window::Create(ax::Rect(0, 0, 500, 500));

		win->event.OnPaint = ax::WFunc<ax::GC>([win](ax::GC gc) {
			const ax::Rect rect(win->dimension.GetRect());
			gc.SetColor(ax::Color(1.0));
			gc.DrawRectangle(rect);
		});

		app.AddTopLevel(ax::Window::Ptr(win));

//		win->node.Add(
//			ax::shared<ax::Button>(ax::Rect(0, 0, 50, 50), ax::Button::Events(), ax::Button::Info()));

//		win->node.Add(ax::shared<ax::ColorPicker>(ax::Rect(100, 100, 205, 272), ax::Color(255, 0, 0)));
		
		win->node.Add(ax::shared<at::SaveWorkDialog>(ax::Rect(10, 10, 300, 170)));

	});

	app.AddAfterGUILoadFunction([&app]() { app.SetFrameSize(ax::Size(500, 500)); });

	app.MainLoop();

	return 0;
}
