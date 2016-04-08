#include "NumberScroll.h"
#include "OpenAX.h"
#include "Slider.h"
#include "TextBox.h"

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

		ax::Slider::Info sld_info;
		sld_info.img_path = "";
		sld_info.btn_size = ax::Size(0, 0);
		sld_info.slider_width = 8;
		sld_info.contour_round_radius = 0;
		sld_info.bgColorNormal = ax::Color(0.5);
		sld_info.bgColorHover = ax::Color(0.5);
		sld_info.bgColorClicked = ax::Color(0.5);
		sld_info.sliderColorNormal = ax::Color(255, 0, 0);
		sld_info.sliderColorHover = ax::Color(255, 0, 0);
		sld_info.sliderColorClicked = ax::Color(255, 0, 0);
		sld_info.sliderContourColor = ax::Color(255, 0, 0);
		sld_info.contourColor = ax::Color(0.0);
		sld_info.backSliderColor = ax::Color(0.0);
		sld_info.backSliderContourColor = ax::Color(0.0);

		auto constrate_sld = ax::shared<ax::Slider>(ax::Rect(ax::Point(100, 100), ax::Size(300, 20)),
			ax::Slider::Events(), sld_info, ax::Slider::Flags::CLICK_ANYWHERE);
		win->node.Add(constrate_sld);

		ax::TextBox::Info txtInfo;
		txtInfo.normal = ax::Color(0.97);
		txtInfo.hover = txtInfo.normal;
		txtInfo.selected = txtInfo.normal;
		txtInfo.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
		txtInfo.contour = ax::Color(0.88);
		txtInfo.cursor = ax::Color(1.0f, 0.0f, 0.0f);
		txtInfo.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
		txtInfo.font_color = ax::Color(0.0);

		ax::TextBox::Events txt_evts;
		auto txt_box(ax::shared<ax::TextBox>(
			ax::Rect(ax::Point(10, 10), ax::Size(120, 24)), txt_evts, txtInfo, "", "Banana"));

		win->node.Add(txt_box);

		win->node.Add(ax::shared<ax::NumberScroll>(ax::Rect(300, 300, 70, 25), ax::NumberScroll::Events(),
			ax::NumberScroll::Info(), 12, ax::Utils::Control::Type::INTEGER,
			ax::Utils::Range<double>(1.0, 10000.0), 1.0));

	});

	app.AddAfterGUILoadFunction([&app]() { app.SetFrameSize(ax::Size(500, 500)); });

	app.MainLoop();

	return 0;
}
