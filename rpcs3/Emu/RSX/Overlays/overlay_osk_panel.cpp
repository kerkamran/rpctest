#include "stdafx.h"
#include "overlay_osk_panel.h"

namespace rsx
{
	namespace overlays
	{
		osk_panel::osk_panel(u32 panel_mode)
		{
			osk_panel_mode = panel_mode;

			// TODO: Use proper translations for Space/Backspace/Return etc. and make sure they fit in the grid.
			switch (panel_mode)
			{
			case CELL_OSKDIALOG_PANELMODE_DEFAULT:
			case CELL_OSKDIALOG_PANELMODE_GERMAN:
			case CELL_OSKDIALOG_PANELMODE_ENGLISH:
			case CELL_OSKDIALOG_PANELMODE_SPANISH:
			case CELL_OSKDIALOG_PANELMODE_FRENCH:
			case CELL_OSKDIALOG_PANELMODE_ITALIAN:
			case CELL_OSKDIALOG_PANELMODE_DUTCH:
			case CELL_OSKDIALOG_PANELMODE_PORTUGUESE:
			case CELL_OSKDIALOG_PANELMODE_RUSSIAN:
			case CELL_OSKDIALOG_PANELMODE_JAPANESE:
			case CELL_OSKDIALOG_PANELMODE_DEFAULT_NO_JAPANESE:
			case CELL_OSKDIALOG_PANELMODE_POLISH:
			case CELL_OSKDIALOG_PANELMODE_KOREAN:
			case CELL_OSKDIALOG_PANELMODE_TURKEY:
			case CELL_OSKDIALOG_PANELMODE_TRADITIONAL_CHINESE:
			case CELL_OSKDIALOG_PANELMODE_SIMPLIFIED_CHINESE:
			case CELL_OSKDIALOG_PANELMODE_PORTUGUESE_BRAZIL:
			case CELL_OSKDIALOG_PANELMODE_DANISH:
			case CELL_OSKDIALOG_PANELMODE_SWEDISH:
			case CELL_OSKDIALOG_PANELMODE_NORWEGIAN:
			case CELL_OSKDIALOG_PANELMODE_FINNISH:
			case CELL_OSKDIALOG_PANELMODE_JAPANESE_HIRAGANA:
			case CELL_OSKDIALOG_PANELMODE_JAPANESE_KATAKANA:
			case CELL_OSKDIALOG_PANELMODE_ALPHABET_FULL_WIDTH:
			case CELL_OSKDIALOG_PANELMODE_ALPHABET:
			case CELL_OSKDIALOG_PANELMODE_LATIN:
			case CELL_OSKDIALOG_PANELMODE_NUMERAL_FULL_WIDTH:
			case CELL_OSKDIALOG_PANELMODE_NUMERAL:
			case CELL_OSKDIALOG_PANELMODE_URL:
			case CELL_OSKDIALOG_PANELMODE_PASSWORD:
			default:
			{
				space = U"Space";
				backspace = U"Backspace";
				enter = U"Return";
			}
			}
		}

		// Language specific implementations

		// TODO: Check and adjust special characters for each panel

		osk_panel_latin::osk_panel_latin(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb, u32 osk_panel_mode)
			: osk_panel(osk_panel_mode)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"??", U"??"}, {U"!", U"??"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"??", U"??"}, {U"?", U"??"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"??", U"??"}, {U"#", U"~"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"??", U"??"}, {U"$", U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"??", U"??"}, {U"%", U"??"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"??", U"??"}, {U"&", U"???"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"??", U"??"}, {U"'", U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"??", U"??"}, {U"(", U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"[", U"<"}, {U")", U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"]", U">"}, {U"*", U"???"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"??", U"??"}, {U"/", U"??"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"??", U"??"}, {U"\\", U"??"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"??", U"??"}, {U"[", U"???"}}, default_bg, 1},
				{{{U"r", U"R"}, {U"??", U"??"}, {U"]", U"??"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"??", U"??"}, {U"^", U"??"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"??", U"??"}, {U"_", U"??"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"??", U"??"}, {U"`", U"??"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"??", U"??"}, {U"{", U"??"}}, default_bg, 1},
				{{{U"o", U"O"}, {U";", U"="}, {U"}", U""}}, default_bg, 1},
				{{{U"p", U"P"}, {U":", U"+"}, {U"|", U""}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"??", U"??"}, {U"@", U""}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"d", U"D"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"f", U"F"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"g", U"G"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"h", U"H"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"j", U"J"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"k", U"K"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"l", U"L"}, {U"`", U"~"}, {U"??", U""}}, default_bg, 1},
				{{{U"'", U"\""}, {U"??", U"\""}, {U"??", U""}}, default_bg, 1},

				// Row 4
				{{{U"z", U"Z"}, {U"??", U"??"}, {U"+", U""}}, default_bg, 1},
				{{{U"x", U"X"}, {U"??", U"??"}, {U",", U""}}, default_bg, 1},
				{{{U"c", U"C"}, {U"??", U"??"}, {U"-", U""}}, default_bg, 1},
				{{{U"v", U"V"}, {U"??", U"??"}, {U".", U""}}, default_bg, 1},
				{{{U"b", U"B"}, {U"??", U"??"}, {U"\"", U""}}, default_bg, 1},
				{{{U"n", U"N"}, {U"??", U"??"}, {U":", U""}}, default_bg, 1},
				{{{U"m", U"M"}, {U"??", U"??"}, {U";", U""}}, default_bg, 1},
				{{{U",", U"-"}, {U",", U"-"}, {U"<", U""}}, default_bg, 1},
				{{{U".", U"_"}, {U".", U"_"}, {U"=", U""}}, default_bg, 1},
				{{{U"?", U"/"}, {U"??", U"/"}, {U">", U""}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U"??/??"}, {U"!/??"}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"??????"}, {U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_english::osk_panel_english(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_ENGLISH)
		{
			// English and latin should be mostly the same.
		}

		osk_panel_spanish::osk_panel_spanish(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_SPANISH)
		{
			// Spanish and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_italian::osk_panel_italian(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_ITALIAN)
		{
			// Italian and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_danish::osk_panel_danish(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_DANISH)
		{
			// Danish and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_norwegian::osk_panel_norwegian(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_NORWEGIAN)
		{
			// Norwegian and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_dutch::osk_panel_dutch(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_DUTCH)
		{
			// Dutch and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_swedish::osk_panel_swedish(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_SWEDISH)
		{
			// Swedish and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_finnish::osk_panel_finnish(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_FINNISH)
		{
			// Finnish and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_portuguese_pt::osk_panel_portuguese_pt(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_PORTUGUESE)
		{
			// Portuguese (Portugal) and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_portuguese_br::osk_panel_portuguese_br(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_latin(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_PORTUGUESE_BRAZIL)
		{
			// Portuguese (Brazil) and latin should be mostly the same. Only the translation for the controls should be different.
		}

		osk_panel_french::osk_panel_french(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_FRENCH)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"??", U"??"}, {U"!", U"??"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"??", U"??"}, {U"?", U"??"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"??", U"??"}, {U"#", U"~"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"??", U"??"}, {U"$", U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"??", U"??"}, {U"%", U"??"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"??", U"??"}, {U"&", U"???"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"??", U"??"}, {U"'", U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"??", U"??"}, {U"(", U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"[", U"<"}, {U")", U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"]", U">"}, {U"*", U"???"}}, default_bg, 1},

				// Row 2
				{{{U"a", U"A"}, {U"??", U"??"}, {U"/", U"??"}}, default_bg, 1},
				{{{U"z", U"Z"}, {U"??", U"??"}, {U"\\", U"??"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"??", U"??"}, {U"[", U"???"}}, default_bg, 1},
				{{{U"r", U"R"}, {U"??", U"??"}, {U"]", U"??"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"??", U"??"}, {U"^", U"??"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"??", U"??"}, {U"_", U"??"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"??", U"??"}, {U"`", U"??"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"??", U"??"}, {U"{", U"??"}}, default_bg, 1},
				{{{U"o", U"O"}, {U";", U"="}, {U"}", U""}}, default_bg, 1},
				{{{U"p", U"P"}, {U":", U"+"}, {U"|", U""}}, default_bg, 1},

				// Row 3
				{{{U"q", U"Q"}, {U"??", U"??"}, {U"@", U""}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"d", U"D"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"f", U"F"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"g", U"G"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"h", U"H"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"j", U"J"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"k", U"K"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"l", U"L"}, {U"`", U"~"}, {U"??", U""}}, default_bg, 1},
				{{{U"'", U"\""}, {U"??", U"\""}, {U"??", U""}}, default_bg, 1},

				// Row 4
				{{{U"w", U"W"}, {U"??", U"??"}, {U"+", U""}}, default_bg, 1},
				{{{U"x", U"X"}, {U"??", U"??"}, {U",", U""}}, default_bg, 1},
				{{{U"c", U"C"}, {U"??", U"??"}, {U"-", U""}}, default_bg, 1},
				{{{U"v", U"V"}, {U"??", U"??"}, {U".", U""}}, default_bg, 1},
				{{{U"b", U"B"}, {U"??", U"??"}, {U"\"", U""}}, default_bg, 1},
				{{{U"n", U"N"}, {U"??", U"??"}, {U":", U""}}, default_bg, 1},
				{{{U"m", U"M"}, {U"??", U"??"}, {U";", U""}}, default_bg, 1},
				{{{U",", U"-"}, {U",", U"-"}, {U"<", U""}}, default_bg, 1},
				{{{U".", U"_"}, {U".", U"_"}, {U"=", U""}}, default_bg, 1},
				{{{U"?", U"/"}, {U"??", U"/"}, {U">", U""}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U"??/??"}, {U"!/??"}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"??????"}, {U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_german::osk_panel_german(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_GERMAN)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"??", U"??"}, {U"!", U"??"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"??", U"??"}, {U"?", U"??"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"??", U"??"}, {U"#", U"~"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"??", U"??"}, {U"$", U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"??", U"??"}, {U"%", U"??"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"??", U"??"}, {U"&", U"???"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"??", U"??"}, {U"'", U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"??", U"??"}, {U"(", U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"[", U"<"}, {U")", U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"]", U">"}, {U"*", U"???"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"??", U"??"}, {U"/", U"??"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"??", U"??"}, {U"\\", U"??"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"??", U"??"}, {U"[", U"???"}}, default_bg, 1},
				{{{U"r", U"R"}, {U"??", U"??"}, {U"]", U"??"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"??", U"??"}, {U"^", U"??"}}, default_bg, 1},
				{{{U"z", U"Z"}, {U"??", U"??"}, {U"_", U"??"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"??", U"??"}, {U"`", U"??"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"??", U"??"}, {U"{", U"??"}}, default_bg, 1},
				{{{U"o", U"O"}, {U";", U"="}, {U"}", U""}}, default_bg, 1},
				{{{U"p", U"P"}, {U":", U"+"}, {U"|", U""}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"??", U"??"}, {U"@", U""}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"d", U"D"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"f", U"F"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"g", U"G"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"h", U"H"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"j", U"J"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"k", U"K"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"l", U"L"}, {U"`", U"~"}, {U"??", U""}}, default_bg, 1},
				{{{U"'", U"\""}, {U"??", U"\""}, {U"??", U""}}, default_bg, 1},

				// Row 4
				{{{U"y", U"Y"}, {U"??", U"??"}, {U"+", U""}}, default_bg, 1},
				{{{U"x", U"X"}, {U"??", U"??"}, {U",", U""}}, default_bg, 1},
				{{{U"c", U"C"}, {U"??", U"??"}, {U"-", U""}}, default_bg, 1},
				{{{U"v", U"V"}, {U"??", U"??"}, {U".", U""}}, default_bg, 1},
				{{{U"b", U"B"}, {U"??", U"??"}, {U"\"", U""}}, default_bg, 1},
				{{{U"n", U"N"}, {U"??", U"??"}, {U":", U""}}, default_bg, 1},
				{{{U"m", U"M"}, {U"??", U"??"}, {U";", U""}}, default_bg, 1},
				{{{U",", U"-"}, {U",", U"-"}, {U"<", U""}}, default_bg, 1},
				{{{U".", U"_"}, {U".", U"_"}, {U"=", U""}}, default_bg, 1},
				{{{U"?", U"/"}, {U"??", U"/"}, {U">", U""}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U"??/??"}, {U"!/??"}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"??????"}, {U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_turkey::osk_panel_turkey(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_TURKEY)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"1", U"!"}, {U"!", U"??"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"2", U"@"}, {U"?", U"??"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"3", U"#"}, {U"#", U"~"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"4", U"$"}, {U"$", U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"5", U"%"}, {U"%", U"??"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"6", U"^"}, {U"&", U"???"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"7", U"&"}, {U"'", U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"8", U"*"}, {U"(", U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"9", U"("}, {U")", U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"0", U")"}, {U"*", U"???"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"q", U"Q"}, {U"/", U"??"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"w", U"W"}, {U"\\", U"??"}}, default_bg, 1},
				{{{U"e", U"???"}, {U"e", U"???"}, {U"[", U"???"}}, default_bg, 1},
				{{{U"r", U"R"}, {U"r", U"R"}, {U"]", U"??"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"t", U"T"}, {U"^", U"??"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"y", U"Y"}, {U"_", U"??"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"??", U"??"}, {U"`", U"??"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"??", U"??"}, {U"{", U"??"}}, default_bg, 1}, // I couldn't find ?? and ?? in the PS3 OSK, but I'll put them here anyway
				{{{U"o", U"O"}, {U"??", U"??"}, {U"}", U""}}, default_bg, 1},
				{{{U"p", U"P"}, {U"p", U"P"}, {U"|", U""}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"a", U"A"}, {U"@", U""}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"d", U"D"}, {U"d", U"D"}, {U"???", U""}}, default_bg, 1},
				{{{U"f", U"F"}, {U"f", U"F"}, {U"???", U""}}, default_bg, 1},
				{{{U"g", U"G"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"h", U"H"}, {U"h", U"H"}, {U"??", U""}}, default_bg, 1},
				{{{U"j", U"J"}, {U"j", U"J"}, {U"??", U""}}, default_bg, 1},
				{{{U"k", U"K"}, {U"k", U"K"}, {U"??", U""}}, default_bg, 1},
				{{{U"l", U"L"}, {U"l", U"L"}, {U"??", U""}}, default_bg, 1},
				{{{U"'", U"\""}, {U"'", U"\""}, {U"??", U""}}, default_bg, 1},

				// Row 4
				{{{U"z", U"Z"}, {U"z", U"Z"}, {U"+", U""}}, default_bg, 1},
				{{{U"x", U"X"}, {U"x", U"X"}, {U",", U""}}, default_bg, 1},
				{{{U"c", U"C"}, {U"??", U"??"}, {U"-", U""}}, default_bg, 1},
				{{{U"v", U"V"}, {U"v", U"V"}, {U".", U""}}, default_bg, 1},
				{{{U"b", U"B"}, {U"b", U"B"}, {U"\"", U""}}, default_bg, 1},
				{{{U"n", U"N"}, {U"n", U"N"}, {U":", U""}}, default_bg, 1},
				{{{U"m", U"M"}, {U"m", U"M"}, {U";", U""}}, default_bg, 1},
				{{{U",", U"-"}, {U",", U"-"}, {U"<", U""}}, default_bg, 1},
				{{{U".", U"_"}, {U".", U"_"}, {U"=", U""}}, default_bg, 1},
				{{{U"?", U"/"}, {U"?", U"/"}, {U">", U""}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U"A/a"}, {U"!/??"}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"AltGr"}, {U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_polish::osk_panel_polish(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_POLISH)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"1", U"!"}, {U"!", U"??"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"2", U"@"}, {U"?", U"??"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"3", U"#"}, {U"#", U"~"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"4", U"$"}, {U"$", U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"5", U"%"}, {U"%", U"??"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"6", U"^"}, {U"&", U"???"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"7", U"&"}, {U"'", U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"8", U"*"}, {U"(", U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"9", U"("}, {U")", U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"0", U")"}, {U"*", U"???"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"q", U"Q"}, {U"/", U"??"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"w", U"W"}, {U"\\", U"??"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"??", U"??"}, {U"[", U"???"}}, default_bg, 1},
				{{{U"r", U"R"}, {U"r", U"R"}, {U"]", U"??"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"t", U"T"}, {U"^", U"??"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"y", U"Y"}, {U"_", U"??"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"???", U"???"}, {U"`", U"??"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"i", U"I"}, {U"{", U"??"}}, default_bg, 1},
				{{{U"o", U"O"}, {U"??", U"??"}, {U"}", U""}}, default_bg, 1},
				{{{U"p", U"P"}, {U"p", U"P"}, {U"|", U""}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"??", U"??"}, {U"@", U""}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"d", U"D"}, {U"d", U"D"}, {U"???", U""}}, default_bg, 1},
				{{{U"f", U"F"}, {U"f", U"F"}, {U"???", U""}}, default_bg, 1},
				{{{U"g", U"G"}, {U"g", U"G"}, {U"??", U""}}, default_bg, 1},
				{{{U"h", U"H"}, {U"h", U"H"}, {U"??", U""}}, default_bg, 1},
				{{{U"j", U"J"}, {U"j", U"J"}, {U"??", U""}}, default_bg, 1},
				{{{U"k", U"K"}, {U"k", U"K"}, {U"??", U""}}, default_bg, 1},
				{{{U"l", U"L"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"'", U"\""}, {U"'", U"\""}, {U"??", U""}}, default_bg, 1},

				// Row 4
				{{{U"z", U"Z"}, {U"??", U"??"}, {U"+", U""}}, default_bg, 1},
				{{{U"x", U"X"}, {U"??", U"??"}, {U",", U""}}, default_bg, 1},
				{{{U"c", U"C"}, {U"??", U"??"}, {U"-", U""}}, default_bg, 1},
				{{{U"v", U"V"}, {U"v", U"V"}, {U".", U""}}, default_bg, 1},
				{{{U"b", U"B"}, {U"b", U"B"}, {U"\"", U""}}, default_bg, 1},
				{{{U"n", U"N"}, {U"??", U"??"}, {U":", U""}}, default_bg, 1},
				{{{U"m", U"M"}, {U"m", U"M"}, {U";", U""}}, default_bg, 1},
				{{{U",", U"-"}, {U",", U"-"}, {U"<", U""}}, default_bg, 1},
				{{{U".", U"_"}, {U".", U"_"}, {U"=", U""}}, default_bg, 1},
				{{{U"?", U"/"}, {U"?", U"/"}, {U">", U""}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U"??/??"}, {U"!/??"}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"AltGr"}, {U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_russian::osk_panel_russian(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_RUSSIAN)
		{
			num_rows = 6;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"1", U"!"}, {U"??", U"??"}, {U"!", U"??"}}, default_bg, 1},
				{{{U"2", U"\""}, {U"2", U"@"}, {U"??", U"??"}, {U"?", U"??"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"3", U"#"}, {U"??", U"??"}, {U"#", U"~"}}, default_bg, 1},
				{{{U"4", U";"}, {U"4", U"$"}, {U"??", U"??"}, {U"$", U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"5", U"%"}, {U"??", U"??"}, {U"%", U"??"}}, default_bg, 1},
				{{{U"6", U":"}, {U"6", U"^"}, {U"??", U"??"}, {U"&", U"???"}}, default_bg, 1},
				{{{U"7", U"?"}, {U"7", U"&"}, {U"??", U"??"}, {U"'", U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"8", U"*"}, {U"??", U"??"}, {U"(", U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"9", U"("}, {U"[", U"<"}, {U")", U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"0", U")"}, {U"]", U">"}, {U"*", U"???"}}, default_bg, 1},

				// Row 2
				{{{U"??", U"??"}, {U"q", U"Q"}, {U"??", U"??"}, {U"/", U"??"}}, default_bg, 1},
				{{{U"'", U"@"}, {U"w", U"W"}, {U"??", U"??"}, {U"\\", U"??"}}, default_bg, 1},
				{{{U",", U"$"}, {U"e", U"E"}, {U"??", U"??"}, {U"[", U"???"}}, default_bg, 1},
				{{{U".", U"^"}, {U"r", U"R"}, {U"??", U"??"}, {U"]", U"??"}}, default_bg, 1},
				{{{U"?", U"&"}, {U"t", U"T"}, {U"??", U"??"}, {U"^", U"??"}}, default_bg, 1},
				{{{U"!", U"/"}, {U"y", U"Y"}, {U"??", U"??"}, {U"_", U"??"}}, default_bg, 1},
				{{{U"-", U"_"}, {U"u", U"U"}, {U"??", U"??"}, {U"`", U"??"}}, default_bg, 1},
				{{{U"=", U"+"}, {U"i", U"I"}, {U"??", U"??"}, {U"{", U"??"}}, default_bg, 1},
				{{{U"??", U"??"}, {U"o", U"O"}, {U";", U"="}, {U"}", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"p", U"P"}, {U":", U"+"}, {U"|", U""}}, default_bg, 1},

				// Row 3
				{{{U"??", U"??"}, {U"a", U"A"}, {U"??", U"??"}, {U"@", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"s", U"S"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"d", U"D"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"f", U"F"}, {U"??", U"??"}, {U"???", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"g", U"G"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"h", U"H"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"j", U"J"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"k", U"K"}, {U"??", U"??"}, {U"??", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"l", U"L"}, {U"`", U"~"}, {U"??", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"'", U"\""}, {U"??", U"\""}, {U"??", U""}}, default_bg, 1},

				// Row 4
				{{{U"??", U"??"}, {U"z", U"Z"}, {U"??", U"??"}, {U"+", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"x", U"X"}, {U"??", U"??"}, {U",", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"c", U"C"}, {U"??", U"??"}, {U"-", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"v", U"V"}, {U"??", U"??"}, {U".", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"b", U"B"}, {U"??", U"??"}, {U"\"", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"n", U"N"}, {U"??", U"??"}, {U":", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"m", U"M"}, {U"??", U"??"}, {U";", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U",", U"-"}, {U",", U"-"}, {U"<", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U".", U"_"}, {U".", U"_"}, {U"=", U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U"?", U"/"}, {U"??", U"/"}, {U">", U""}}, default_bg, 1},

				// Row 5
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},
				{{{U"??", U"??"}, {U""}, {U""}, {U""}}, default_bg, 1},

				// Control
				{{{U"??/??"}, {U"A/a"}, {U"??/??"}, {U"!/??"}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"ABC"}, {U"??????"}, {U"@#:"}, {U"????"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_korean::osk_panel_korean(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_KOREAN)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"???"}, {U"1", U"!"}, {U"!"}}, default_bg, 1},
				{{{U"???"}, {U"2", U"@"}, {U"\""}}, default_bg, 1},
				{{{U"???"}, {U"3", U"#"}, {U"#"}}, default_bg, 1},
				{{{U"???"}, {U"4", U"$"}, {U"$"}}, default_bg, 1},
				{{{U"???"}, {U"5", U"%"}, {U"%"}}, default_bg, 1},
				{{{U"^"}, {U"6", U"^"}, {U"&"}}, default_bg, 1},
				{{{U"*"}, {U"7", U"&"}, {U"'"}}, default_bg, 1},
				{{{U"-"}, {U"8", U"*"}, {U"("}}, default_bg, 1},
				{{{U"???"}, {U"9", U"("}, {U")"}}, default_bg, 1},
				{{{U"???"}, {U"0", U")"}, {U"*"}}, default_bg, 1},

				// Row 2
				{{{U"???"}, {U"q", U"Q"}, {U"+"}}, default_bg, 1},
				{{{U"???"}, {U"w", U"W"}, {U","}}, default_bg, 1},
				{{{U"???"}, {U"e", U"E"}, {U"-"}}, default_bg, 1},
				{{{U"???"}, {U"r", U"R"}, {U"."}}, default_bg, 1},
				{{{U"???"}, {U"t", U"T"}, {U"/"}}, default_bg, 1},
				{{{U"???"}, {U"y", U"Y"}, {U":"}}, default_bg, 1},
				{{{U"???"}, {U"u", U"U"}, {U";"}}, default_bg, 1},
				{{{U"???"}, {U"i", U"I"}, {U"<"}}, default_bg, 1},
				{{{U"???"}, {U"o", U"O"}, {U"="}}, default_bg, 1},
				{{{U"???"}, {U"p", U"P"}, {U">"}}, default_bg, 1},

				// Row 3
				{{{U"???"}, {U"a", U"A"}, {U"?"}}, default_bg, 1},
				{{{U"???"}, {U"s", U"S"}, {U"@"}}, default_bg, 1},
				{{{U"???"}, {U"d", U"D"}, {U"["}}, default_bg, 1},
				{{{U"???"}, {U"f", U"F"}, {U"\\"}}, default_bg, 1},
				{{{U"???"}, {U"g", U"G"}, {U"]"}}, default_bg, 1},
				{{{U"???"}, {U"h", U"H"}, {U"^"}}, default_bg, 1},
				{{{U"???"}, {U"j", U"J"}, {U"_"}}, default_bg, 1},
				{{{U"???"}, {U"k", U"K"}, {U"`"}}, default_bg, 1},
				{{{U"???"}, {U"l", U"L"}, {U"{"}}, default_bg, 1},
				{{{U";"}, {U"'", U"\""}, {U"}"}}, default_bg, 1},

				// Row 4
				{{{U"???"}, {U"z", U"Z"}, {U"|"}}, default_bg, 1},
				{{{U"???"}, {U"x", U"X"}, {U"~"}}, default_bg, 1},
				{{{U"???"}, {U"c", U"C"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"v", U"V"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U"b", U"B"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U"n", U"N"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U"m", U"M"}, {U""}}, default_bg, 1},
				{{{U","}, {U",", U"-"}, {U""}}, default_bg, 1},
				{{{U"."}, {U".", U"_"}, {U""}}, default_bg, 1},
				{{{U"?"}, {U"?", U"/"}, {U""}}, default_bg, 1},

				// Control
				{{{U""}, {U"A/a"}, {U""}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"ABC"}, {U"@#:"}, {U"???"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_chinese::osk_panel_chinese(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb, u32 osk_panel_mode)
			: osk_panel(osk_panel_mode)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			// TODO: add mode for chinese dictionaries

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"9", U"("}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"0", U")"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"r", U"R"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"o", U"O"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"p", U"P"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"s", U"S"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"d", U"D"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"f", U"F"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"g", U"G"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"h", U"H"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"j", U"J"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"k", U"K"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"l", U"L"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"'", U"\""}, {U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 4
				{{{U"z", U"Z"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"x", U"X"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"c", U"C"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"v", U"V"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"b", U"B"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"n", U"N"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"m", U"M"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U",", U"-"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U".", U"_"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"?", U"/"}, {U"???", U"???"}, {U""}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U"???/???"}, {U""}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"??????"}, {U"??????"}, {U"abc"}}, special2_bg, 2, button_flags::_layer, layer_cb},
				{{{space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb},
				{{{backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_simplified_chinese::osk_panel_simplified_chinese(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_chinese(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_SIMPLIFIED_CHINESE)
		{
			// Simplified chinese uses osk_panel_chinese. Only the translation for the controls and the dictionary should be different than for traditional chinese.
		}

		osk_panel_traditional_chinese::osk_panel_traditional_chinese(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_chinese(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_TRADITIONAL_CHINESE)
		{
			// Traditional chinese uses osk_panel_chinese. Only the translation for the controls and the dictionary should be different than for simplified chinese.
		}

		osk_panel_japanese::osk_panel_japanese(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_JAPANESE)
		{
			num_rows = 6;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"???", U"???"}, {U"1", U"!"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"2", U"@"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"3", U"#"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"4", U"$"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"5", U"%"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"6", U"^"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"7", U"&"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"8", U"*"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"9", U"("}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"0", U")"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 2
				{{{U"???", U"???"}, {U"q", U"Q"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"w", U"W"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"e", U"E"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"r", U"R"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"t", U"T"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"y", U"Y"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"u", U"U"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"i", U"I"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"o", U"O"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"p", U"P"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 3
				{{{U"???", U"???"}, {U"a", U"A"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"s", U"S"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"d", U"D"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"f", U"F"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"g", U"G"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"h", U"H"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"j", U"J"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"k", U"K"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"l", U"L"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"'", U"\""}, {U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 4
				{{{U"???", U"???"}, {U"z", U"Z"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"x", U"X"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"c", U"C"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"v", U"V"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"b", U"B"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"n", U"N"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"m", U"M"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U",", U"-"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U".", U"_"}, {U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"?", U"/"}, {U"???", U"???"}, {U""}}, default_bg, 1},

				// Row 5
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"???", U"???"}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},
				{{{U"", U""}, {U"", U""}, {U"", U""}, {U""}}, default_bg, 1},

				// Control
				{{{U"???/???"}, {U"A/a"}, {U"???/???"}, {U""}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"abc"}, {U"??????"}, {U"??????"}, {U"??????"}}, special2_bg, 2, button_flags::_layer, layer_cb},
				{{{space}, {space}, {space}, {space}}, special_bg, 2, button_flags::_space, space_cb},
				{{{backspace}, {backspace}, {backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}, {enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_japanese_hiragana::osk_panel_japanese_hiragana(callback_t /*shift_cb*/, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_JAPANESE_HIRAGANA)
		{
			num_rows = 6;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},

				// Row 2
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},

				// Row 3
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},

				// Row 4
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},

				// Row 5
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U""}, {U""}}, default_bg, 1},

				// Control
				{{{U""}, {U""}}, special2_bg, 2, button_flags::_shift, nullptr },
				{{{U"??????"}, {U"???"}}, special2_bg, 2, button_flags::_layer, layer_cb},
				{{{space}, {space}}, special_bg, 2, button_flags::_space, space_cb},
				{{{backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_japanese_katakana::osk_panel_japanese_katakana(callback_t /*shift_cb*/, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_JAPANESE_KATAKANA)
		{
			num_rows = 6;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},

				// Row 2
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},

				// Row 3
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},

				// Row 4
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},

				// Row 5
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U"???"}, {U""}}, default_bg, 1},
				{{{U""}, {U""}}, default_bg, 1},

				// Control
				{{{U""}, {U""}}, special2_bg, 2, button_flags::_shift, nullptr },
				{{{U"??????"}, {U"???"}}, special2_bg, 2, button_flags::_layer, layer_cb},
				{{{space}, {space}}, special_bg, 2, button_flags::_space, space_cb},
				{{{backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_alphabet_half_width::osk_panel_alphabet_half_width(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb, u32 osk_panel_mode)
			: osk_panel(osk_panel_mode)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"!"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"?"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"#"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"$"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"%"}}, default_bg, 1},
				{{{U"6", U"^"}, {U"&"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"'"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"("}}, default_bg, 1},
				{{{U"9", U"("}, {U")"}}, default_bg, 1},
				{{{U"0", U")"}, {U"*"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"/"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"\\"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"["}}, default_bg, 1},
				{{{U"r", U"R"}, {U"]"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"^"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"_"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"`"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"{"}}, default_bg, 1},
				{{{U"o", U"O"}, {U"}"}}, default_bg, 1},
				{{{U"p", U"P"}, {U"|"}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"@"}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??"}}, default_bg, 1},
				{{{U"d", U"D"}, {U"???"}}, default_bg, 1},
				{{{U"f", U"F"}, {U"???"}}, default_bg, 1},
				{{{U"g", U"G"}, {U"??"}}, default_bg, 1},
				{{{U"h", U"H"}, {U"??"}}, default_bg, 1},
				{{{U"j", U"J"}, {U"??"}}, default_bg, 1},
				{{{U"k", U"K"}, {U"??"}}, default_bg, 1},
				{{{U"l", U"L"}, {U"??"}}, default_bg, 1},
				{{{U"'", U"\""}, {U"??"}}, default_bg, 1},

				// Row 4
				{{{U"z", U"Z"}, {U"+"}}, default_bg, 1},
				{{{U"x", U"X"}, {U","}}, default_bg, 1},
				{{{U"c", U"C"}, {U"-"}}, default_bg, 1},
				{{{U"v", U"V"}, {U"."}}, default_bg, 1},
				{{{U"b", U"B"}, {U"\""}}, default_bg, 1},
				{{{U"n", U"N"}, {U":"}}, default_bg, 1},
				{{{U"m", U"M"}, {U";"}}, default_bg, 1},
				{{{U",", U"-"}, {U"<"}}, default_bg, 1},
				{{{U".", U"_"}, {U"="}}, default_bg, 1},
				{{{U"?", U"/"}, {U">"}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U""}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_alphabet_full_width::osk_panel_alphabet_full_width(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_ALPHABET_FULL_WIDTH)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 2
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 3
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},

				// Row 4
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U"???"}}, default_bg, 1},
				{{{U"???", U"???"}, {U""}}, default_bg, 1},

				// Control
				{{{U"???/???"}, {U""}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_numeral_half_width::osk_panel_numeral_half_width(callback_t /*shift_cb*/, callback_t /*layer_cb*/, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_NUMERAL)
		{
			num_rows = 2;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1"}}, default_bg, 1},
				{{{U"2"}}, default_bg, 1},
				{{{U"3"}}, default_bg, 1},
				{{{U"4"}}, default_bg, 1},
				{{{U"5"}}, default_bg, 1},
				{{{U"6"}}, default_bg, 1},
				{{{U"7"}}, default_bg, 1},
				{{{U"8"}}, default_bg, 1},
				{{{U"9"}}, default_bg, 1},
				{{{U"0"}}, default_bg, 1},

				// Control
				{{{U""}}, special2_bg, 2, button_flags::_shift, nullptr },
				{{{U""}}, special2_bg, 2, button_flags::_layer, nullptr },
				{{{space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_numeral_full_width::osk_panel_numeral_full_width(callback_t /*shift_cb*/, callback_t /*layer_cb*/, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_NUMERAL_FULL_WIDTH)
		{
			num_rows = 2;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},
				{{{U"???"}}, default_bg, 1},

				// Control
				{{{U""}}, special2_bg, 2, button_flags::_shift, nullptr },
				{{{U""}}, special2_bg, 2, button_flags::_layer, nullptr },
				{{{space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_url::osk_panel_url(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel(CELL_OSKDIALOG_PANELMODE_URL)
		{
			num_rows = 5;
			num_columns = 10;
			cell_size_x = 50;
			cell_size_y = 40;

			layout =
			{
				// Row 1
				{{{U"1", U"!"}, {U"!"}}, default_bg, 1},
				{{{U"2", U"@"}, {U"?"}}, default_bg, 1},
				{{{U"3", U"#"}, {U"#"}}, default_bg, 1},
				{{{U"4", U"$"}, {U"$"}}, default_bg, 1},
				{{{U"5", U"%"}, {U"%"}}, default_bg, 1},
				{{{U"6", U"~"}, {U"&"}}, default_bg, 1},
				{{{U"7", U"&"}, {U"'"}}, default_bg, 1},
				{{{U"8", U"*"}, {U"("}}, default_bg, 1},
				{{{U"9", U";"}, {U")"}}, default_bg, 1},
				{{{U"0", U"+"}, {U"*"}}, default_bg, 1},

				// Row 2
				{{{U"q", U"Q"}, {U"/"}}, default_bg, 1},
				{{{U"w", U"W"}, {U"\\"}}, default_bg, 1},
				{{{U"e", U"E"}, {U"["}}, default_bg, 1},
				{{{U"r", U"R"}, {U"]"}}, default_bg, 1},
				{{{U"t", U"T"}, {U"^"}}, default_bg, 1},
				{{{U"y", U"Y"}, {U"_"}}, default_bg, 1},
				{{{U"u", U"U"}, {U"`"}}, default_bg, 1},
				{{{U"i", U"I"}, {U"{"}}, default_bg, 1},
				{{{U"o", U"O"}, {U"}"}}, default_bg, 1},
				{{{U"p", U"P"}, {U"|"}}, default_bg, 1},

				// Row 3
				{{{U"a", U"A"}, {U"@"}}, default_bg, 1},
				{{{U"s", U"S"}, {U"??"}}, default_bg, 1},
				{{{U"d", U"D"}, {U"???"}}, default_bg, 1},
				{{{U"f", U"F"}, {U"???"}}, default_bg, 1},
				{{{U"g", U"G"}, {U"??"}}, default_bg, 1},
				{{{U"h", U"H"}, {U"??"}}, default_bg, 1},
				{{{U"j", U"J"}, {U"??"}}, default_bg, 1},
				{{{U"k", U"K"}, {U"??"}}, default_bg, 1},
				{{{U"l", U"L"}, {U"??"}}, default_bg, 1},
				{{{U"-", U"="}, {U"??"}}, default_bg, 1},

				// Row 4
				{{{U"z", U"Z"}, {U"+"}}, default_bg, 1},
				{{{U"x", U"X"}, {U","}}, default_bg, 1},
				{{{U"c", U"C"}, {U"-"}}, default_bg, 1},
				{{{U"v", U"V"}, {U"."}}, default_bg, 1},
				{{{U"b", U"B"}, {U"\""}}, default_bg, 1},
				{{{U"n", U"N"}, {U":"}}, default_bg, 1},
				{{{U"m", U"M"}, {U";"}}, default_bg, 1},
				{{{U"/", U":"}, {U"<"}}, default_bg, 1},
				{{{U".", U","}, {U"="}}, default_bg, 1},
				{{{U"_", U"?"}, {U">"}}, default_bg, 1},

				// Control
				{{{U"A/a"}, {U""}}, special2_bg, 2, button_flags::_shift, shift_cb },
				{{{U"@#:"}, {U"ABC"}}, special2_bg, 2, button_flags::_layer, layer_cb },
				{{{space}, {space}}, special_bg, 2, button_flags::_space, space_cb },
				{{{backspace}, {backspace}}, special_bg, 2, button_flags::_default, delete_cb },
				{{{enter}, {enter}}, special2_bg, 2, button_flags::_return, enter_cb },
			};
		}

		osk_panel_password::osk_panel_password(callback_t shift_cb, callback_t layer_cb, callback_t space_cb, callback_t delete_cb, callback_t enter_cb)
			: osk_panel_alphabet_half_width(shift_cb, layer_cb, space_cb, delete_cb, enter_cb, CELL_OSKDIALOG_PANELMODE_PASSWORD)
		{
			// Same as the half-width alphanumeric character panel.
		}
	}
}
