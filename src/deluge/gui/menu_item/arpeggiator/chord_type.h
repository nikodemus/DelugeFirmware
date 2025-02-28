/*
 * Copyright (c) 2014-2023 Synthstrom Audible Limited
 *
 * This file is part of The Synthstrom Audible Deluge Firmware.
 *
 * The Synthstrom Audible Deluge Firmware is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "definitions_cxx.hpp"
#include "gui/l10n/l10n.h"
#include "gui/l10n/strings.h"
#include "gui/menu_item/selection.h"
#include "gui/ui/sound_editor.h"
#include "model/song/song.h"
#include <cstdint>

namespace deluge::gui::menu_item::arpeggiator {
class ChordType : public Selection {
public:
	using Selection::Selection;
	void readCurrentValue() override { this->setValue(soundEditor.currentArpSettings->chordTypeIndex); }
	void writeCurrentValue() override {
		int32_t value = this->getValue();
		if (value >= 0 && value < MAX_CHORD_TYPES) {
			soundEditor.currentArpSettings->chordTypeIndex = value;
			soundEditor.currentArpSettings->flagForceArpRestart = true;
		}
	}
	bool isRelevant(ModControllableAudio* modControllable, int32_t whichThing) override {
		return soundEditor.editingKit();
	}

	deluge::vector<std::string_view> getOptions() override {
		using enum l10n::String;
		return {
		    l10n::getView(STRING_FOR_NONE),      //<
		    l10n::getView(STRING_FOR_FIFTH),     //<
		    l10n::getView(STRING_FOR_SUS2),      //<
		    l10n::getView(STRING_FOR_MINOR),     //<
		    l10n::getView(STRING_FOR_MAJOR),     //<
		    l10n::getView(STRING_FOR_SUS4),      //<
		    l10n::getView(STRING_FOR_MINOR7),    //<
		    l10n::getView(STRING_FOR_DOMINANT7), //<
		    l10n::getView(STRING_FOR_MAJOR7),    //<
		};
	}
};

} // namespace deluge::gui::menu_item::arpeggiator
