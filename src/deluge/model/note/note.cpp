/*
 * Copyright © 2014-2023 Synthstrom Audible Limited
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

#include "model/note/note.h"
#include "storage/storage_manager.h"
#include "util/functions.h"

Note::Note() {
}

/*

void Note::writeToFile(Serializer &writer) {
    writer.writeOpeningTag((char*)"note");

    writer.writeTag((char*)"length", length);
    writer.writeTag((char*)"velocity", velocity);
    writer.writeTag((char*)"pos", pos);

    writer.writeClosingTag((char*)"note");
}
*/
