#include "OpenAX.h"

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
	});

	app.AddAfterGUILoadFunction(
		[&app]() { app.SetFrameSize(ax::Size(500, 500)); });

	app.MainLoop();

	return 0;
}
