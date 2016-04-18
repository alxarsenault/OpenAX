#include "DropMenu.h"
#include "NumberScroll.h"
#include "OpenAX.h"
#include "Slider.h"
#include "TextBox.h"

#include "WindowManager.h"
#include "axCocoaInterfaceMac.h"

class DropInfo : public ax::Window::Backbone {
public:
	DropInfo(const ax::Rect& rect)
		: _is_droped(false)
		, _drop_menu(nullptr)
	{
		// Create window.
		win = ax::Window::Create(rect);
		win->event.OnPaint = ax::WBind<ax::GC>(this, &DropInfo::OnPaint);

		ax::Button::Info btn_info;
		btn_info.normal = ax::Color(0.95);
		btn_info.hover = ax::Color(0.97);
		btn_info.clicking = ax::Color(0.93);
		btn_info.selected = btn_info.normal;
		btn_info.contour = ax::Color(0.80);
		btn_info.font_color = ax::Color(0.0);

		auto btn = ax::shared<ax::Button>(
			ax::Rect(0, 0, rect.size.x, rect.size.y), GetOnButtonClick(), btn_info, "", "Banana");
		_drop_btn = btn.get();
		win->node.Add(btn);
	}

private:
	bool _is_droped;
	ax::Button* _drop_btn;
	ax::DropMenu* _drop_menu;

	int FindSelectedIndex()
	{
		const ax::StringVector& items = _drop_menu->GetItems();

		for (int i = 0; i < items.size(); i++) {
			if (items[i] == _drop_btn->GetLabel()) {
				return i;
				break;
			}
		}

		return -1;
	}

	axEVENT_ACCESSOR(ax::Button::Msg, OnButtonClick);
	void OnButtonClick(const ax::Button::Msg& msg)
	{
		if (_is_droped) {
			RemoveMenu();
			_is_droped = false;
		}
		else {
			ax::Button* sender = msg.GetSender();
			const ax::Point pos(sender->GetWindow()->dimension.GetAbsoluteRect().GetNextPosDown(0));

			ax::StringVector drop_options = { "Banana", "Potato" };

			CreateMenu(ax::Rect(pos, ax::Size(175, 300)), drop_options);
			_is_droped = true;
		}
	}

	void CreateMenu(const ax::Rect& rect, const ax::StringVector& drop_options)
	{
		ax::DropMenu::Info menu_info;
		menu_info.normal = ax::Color(240, 240, 240);
		menu_info.hover = ax::Color(246, 246, 246);
		menu_info.font_color = ax::Color(0.0);
		menu_info.selected = ax::Color(41, 222, 255);
		menu_info.selected_hover = ax::Color(41, 226, 255);
		menu_info.selected_font_color = ax::Color(0.0);
		menu_info.contour = ax::Color(0.86);
		menu_info.separation = ax::Color(0.86);
		menu_info.up_down_arrow = ax::Color(0.35);
		menu_info.right_arrow = ax::Color(0.70);
		menu_info.item_height = 25;

		auto menu = ax::shared<ax::DropMenu>(rect, GetOnMenuChoice(), menu_info, drop_options);

		_drop_menu = menu.get();

		// Find selected index.
		int selected_index = FindSelectedIndex();

		if (selected_index != -1) {
			_drop_menu->SetSelectedItem(selected_index);
		}

		auto pop_man = ax::App::GetInstance().GetPopupManager();
		auto pop_win_tree = pop_man->GetWindowTree();
		std::vector<ax::Window::Ptr>& pop_top_node_vector = pop_win_tree->GetNodeVector();

		if (pop_top_node_vector.size() == 0) {
			// Add to top level.
			menu->GetWindow()->backbone = menu;
			pop_top_node_vector.push_back(ax::Window::Ptr(menu->GetWindow()));
		}
		else {
			// Add beside top level.
			menu->GetWindow()->backbone = menu;
			pop_top_node_vector.push_back(ax::Window::Ptr(menu->GetWindow()));
		}
	}

	void RemoveMenu()
	{
		if (_drop_menu != nullptr) {
			auto pop_man = ax::App::GetInstance().GetPopupManager();
			auto pop_win_tree = pop_man->GetWindowTree();
			std::vector<ax::Window::Ptr>& pop_top_node_vector = pop_win_tree->GetNodeVector();

			int index = -1;

			for (int i = 0; i < pop_top_node_vector.size(); i++) {
				if (pop_top_node_vector[i]->GetId() == _drop_menu->GetWindow()->GetId()) {
					index = i;
					break;
				}
			}

			if (index != -1) {
				ax::Window::Ptr tmp_menu = pop_top_node_vector[index];
				pop_man->SetPastWindow(nullptr);
				pop_man->UnGrabKey();
				pop_man->UnGrabMouse();
				pop_top_node_vector.erase(pop_top_node_vector.begin() + index);
				tmp_menu->backbone.reset();
				_drop_menu = nullptr;
			}
		}
	}

	axEVENT_ACCESSOR(ax::DropMenu::Msg, OnMenuChoice);
	void OnMenuChoice(const ax::DropMenu::Msg& msg)
	{
//		ax::Print(msg.GetItem());
		_drop_btn->SetLabel(msg.GetItem());
		RemoveMenu();
		_is_droped = false;
	}

	void OnPaint(ax::GC gc)
	{
		const ax::Rect rect(win->dimension.GetDrawingRect());
		gc.SetColor(ax::Color(0.95));
		gc.DrawRectangle(rect);
	}
};

class PreferencePanel : public ax::Window::Backbone {
public:
	PreferencePanel(const ax::Rect& rect)
		: _font(0)
		, _audio_rect(10, 10, rect.size.x - 20, 100)
	{
		_audio_label_rect = ax::Rect(_audio_rect.position, ax::Size(_audio_rect.size.x, 23));

		_midi_rect = ax::Rect(_audio_rect.GetNextPosDown(10), ax::Size(_audio_rect.size.x, 65));
		_midi_label_rect = ax::Rect(_midi_rect.position, ax::Size(_midi_rect.size.x, 23));

		// Create window.
		win = ax::Window::Create(rect);
		win->event.OnPaint = ax::WBind<ax::GC>(this, &PreferencePanel::OnPaint);

		// Audio input device.
		auto btn_in = ax::shared<DropInfo>(
			ax::Rect(ax::Point(_audio_label_rect.position.x + 95, _audio_label_rect.position.y + 30),
				ax::Size(175, 25)));

		win->node.Add(btn_in);

		// Audio output device.
		ax::Point o_pos(btn_in->GetWindow()->dimension.GetRect().GetNextPosDown(10));
		auto btn_out = ax::shared<DropInfo>(ax::Rect(o_pos, ax::Size(175, 25)));
		win->node.Add(btn_out);

		// Midi input device.
		auto btn_midi_in = ax::shared<DropInfo>(
			ax::Rect(ax::Point(_midi_label_rect.position.x + 95, _midi_label_rect.position.y + 30),
				ax::Size(175, 25)));
		win->node.Add(btn_midi_in);
	}

	virtual ~PreferencePanel()
	{
	}

private:
	ax::Font _font;
	ax::Rect _audio_rect;
	ax::Rect _audio_label_rect;

	ax::Rect _midi_rect;
	ax::Rect _midi_label_rect;

	axEVENT_ACCESSOR(ax::Button::Msg, OnButtonAudioInputDevice);
	void OnButtonAudioInputDevice(const ax::Button::Msg& msg)
	{
		ax::StringVector drop_options = { "Banana", "Potato" };

		ax::DropMenu::Info menu_info;
		menu_info.normal = ax::Color(240, 240, 240);
		menu_info.hover = ax::Color(246, 246, 246);
		menu_info.font_color = ax::Color(0.0);
		menu_info.selected = ax::Color(41, 222, 255);
		menu_info.selected_hover = ax::Color(41, 226, 255);
		menu_info.selected_font_color = ax::Color(0.0);
		menu_info.contour = ax::Color(0.86);
		menu_info.separation = ax::Color(0.86);
		menu_info.up_down_arrow = ax::Color(0.35);
		menu_info.right_arrow = ax::Color(0.70);
		menu_info.item_height = 25;

		ax::DropMenu::Events drop_evts;

		ax::Size size(175, 300);

		ax::Button* sender = msg.GetSender();
		const ax::Point pos(sender->GetWindow()->dimension.GetRect().GetNextPosDown(0));

		auto menu = ax::shared<ax::DropMenu>(ax::Rect(pos, size), drop_evts, menu_info, drop_options);

		win->node.Add(menu);
	}

	axEVENT_ACCESSOR(ax::Button::Msg, OnButtonAudioOutputDevice);
	void OnButtonAudioOutputDevice(const ax::Button::Msg& msg)
	{
	}

	void OnPaint(ax::GC gc)
	{
		const ax::Rect rect(win->dimension.GetDrawingRect());
		gc.SetColor(ax::Color(0.95));
		gc.DrawRectangle(rect);

		// Audio rectangle.
		gc.SetColor(ax::Color(0.80));
		gc.DrawRectangleContour(_audio_rect);

		// Audio label.
		gc.SetColor(ax::Color(0.80));
		gc.DrawRectangle(_audio_label_rect);

		gc.SetColor(ax::Color(0.0));
		gc.DrawStringAlignedCenter(_font, "Audio", _audio_label_rect);

		// Audio input device.
		gc.SetColor(ax::Color(0.0));
		const ax::Point in_dev_pos(_audio_label_rect.position.x + 8, _audio_label_rect.position.y + 35);
		gc.DrawString(_font, "Input device    : ", in_dev_pos);

		// Audio output device.
		const ax::Point out_dev_pos(in_dev_pos + ax::Point(0, 34));
		gc.DrawString(_font, "Output device : ", out_dev_pos);

		// Midi rectangle.
		gc.SetColor(ax::Color(0.80));
		gc.DrawRectangleContour(_midi_rect);

		// Midi label.
		gc.SetColor(ax::Color(0.80));
		gc.DrawRectangle(_midi_label_rect);

		gc.SetColor(ax::Color(0.0));
		gc.DrawStringAlignedCenter(_font, "Midi", _midi_label_rect);
		
		// Audio input device.
		gc.SetColor(ax::Color(0.0));
		const ax::Point midi_in_dev_pos(_midi_label_rect.position.x + 8, _midi_label_rect.position.y + 35);
		gc.DrawString(_font, "Input device    : ", midi_in_dev_pos);

		// Preference contour.
		gc.SetColor(ax::Color(0.80));
		gc.DrawRectangleContour(rect);
	}
};

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

		//		ax::Slider::Info sld_info;
		//		sld_info.img_path = "";
		//		sld_info.btn_size = ax::Size(0, 0);
		//		sld_info.slider_width = 8;
		//		sld_info.contour_round_radius = 0;
		//		sld_info.bgColorNormal = ax::Color(0.5);
		//		sld_info.bgColorHover = ax::Color(0.5);
		//		sld_info.bgColorClicked = ax::Color(0.5);
		//		sld_info.sliderColorNormal = ax::Color(255, 0, 0);
		//		sld_info.sliderColorHover = ax::Color(255, 0, 0);
		//		sld_info.sliderColorClicked = ax::Color(255, 0, 0);
		//		sld_info.sliderContourColor = ax::Color(255, 0, 0);
		//		sld_info.contourColor = ax::Color(0.0);
		//		sld_info.backSliderColor = ax::Color(0.0);
		//		sld_info.backSliderContourColor = ax::Color(0.0);
		//
		//		auto constrate_sld = ax::shared<ax::Slider>(ax::Rect(ax::Point(100, 100), ax::Size(300, 20)),
		//			ax::Slider::Events(), sld_info, ax::Slider::Flags::CLICK_ANYWHERE);
		//		win->node.Add(constrate_sld);
		//
		//		ax::TextBox::Info txtInfo;
		//		txtInfo.normal = ax::Color(0.97);
		//		txtInfo.hover = txtInfo.normal;
		//		txtInfo.selected = txtInfo.normal;
		//		txtInfo.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
		//		txtInfo.contour = ax::Color(0.88);
		//		txtInfo.cursor = ax::Color(1.0f, 0.0f, 0.0f);
		//		txtInfo.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
		//		txtInfo.font_color = ax::Color(0.0);
		//
		//		ax::TextBox::Events txt_evts;
		//		auto txt_box(ax::shared<ax::TextBox>(
		//			ax::Rect(ax::Point(10, 10), ax::Size(120, 24)), txt_evts, txtInfo, "", "Banana"));
		//
		//		win->node.Add(txt_box);
		//
		//		ax::NumberScroll::Info scroll_info;
		//		scroll_info.up_btn = "drop_up.png";
		//		scroll_info.down_btn = "drop_down.png";
		//
		//		// Txt box.
		//		scroll_info.txt_info.normal = ax::Color(1.0);
		//		scroll_info.txt_info.hover = ax::Color(1.0);
		//		scroll_info.txt_info.selected = ax::Color(1.0);
		//		scroll_info.txt_info.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
		//		scroll_info.txt_info.contour = ax::Color(0.7);
		//		scroll_info.txt_info.cursor = ax::Color(1.0f, 0.0f, 0.0f);
		//		scroll_info.txt_info.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
		//		scroll_info.txt_info.font_color = ax::Color(0.0);
		//
		//		// Button.
		//		scroll_info.btn_info.normal = ax::Color(0.85);
		//		scroll_info.btn_info.hover = ax::Color(0.86);
		//		scroll_info.btn_info.clicking = ax::Color(0.83);
		//		scroll_info.btn_info.selected = scroll_info.btn_info.normal;
		//		scroll_info.btn_info.contour = ax::Color(0.7);
		//		scroll_info.btn_info.font_color = ax::Color(0.0, 0.0);
		//
		//		win->node.Add(ax::shared<ax::NumberScroll>(ax::Rect(300, 300, 70, 20),
		// ax::NumberScroll::Events(),
		//			scroll_info, 12, ax::Utils::Control::Type::INTEGER,
		//			ax::Utils::Range<double>(1.0, 10000.0), 1.0));

		win->node.Add(ax::shared<PreferencePanel>(ax::Rect(10, 10, 300, 194)));
		
		ax::Print(GetPasteboardContent());

	});

	app.AddAfterGUILoadFunction([&app]() { app.SetFrameSize(ax::Size(500, 500)); });

	app.MainLoop();

	return 0;
}
