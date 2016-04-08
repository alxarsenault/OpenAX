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
		
		ax::NumberScroll::Info scroll_info;
		scroll_info.up_btn = "drop_up.png";
		scroll_info.down_btn = "drop_down.png";
		
		// Txt box.
		scroll_info.txt_info.normal = ax::Color(1.0);
		scroll_info.txt_info.hover = ax::Color(1.0);
		scroll_info.txt_info.selected = ax::Color(1.0);
		scroll_info.txt_info.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
		scroll_info.txt_info.contour = ax::Color(0.7);
		scroll_info.txt_info.cursor = ax::Color(1.0f, 0.0f, 0.0f);
		scroll_info.txt_info.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
		scroll_info.txt_info.font_color = ax::Color(0.0);
		
		// Button.
		scroll_info.btn_info.normal = ax::Color(0.85);
		scroll_info.btn_info.hover = ax::Color(0.86);
		scroll_info.btn_info.clicking = ax::Color(0.83);
		scroll_info.btn_info.selected = scroll_info.btn_info.normal;
		scroll_info.btn_info.contour = ax::Color(0.7);
		scroll_info.btn_info.font_color = ax::Color(0.0, 0.0);
		
		win->node.Add(ax::shared<ax::NumberScroll>(ax::Rect(300, 300, 70, 20), ax::NumberScroll::Events(),
			scroll_info, 12, ax::Utils::Control::Type::INTEGER,
			ax::Utils::Range<double>(1.0, 10000.0), 1.0));

	});

	app.AddAfterGUILoadFunction([&app]() { app.SetFrameSize(ax::Size(500, 500)); });

	app.MainLoop();

	return 0;
}
