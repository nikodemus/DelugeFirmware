#include "model/scale/musical_key.h"
#include "util/const_functions.h"

#include <cstdint>

MusicalKey::MusicalKey() {
	modeNotes.add(0);
	rootNote = 0;
}

uint8_t MusicalKey::intervalOf(int32_t noteCode) const {
	return mod(noteCode - rootNote, 12);
}

int8_t MusicalKey::degreeOf(int32_t noteCode) const {
	return modeNotes.degreeOf(intervalOf(noteCode));
}

// NOTE SPELLING
//
// - Roots prefer sharps
// - Enumerate the scale degrees from root:
//   - First time an accidental is used, it sets the preference.
//   - If the interval is 1 or 2, pick the next note letter if possible without
//     changing preferred style or using double-sharps or double-flats.
//   - For larger intervals, pick the "normal" name, using preferred accidental type (or sharps if no preference).
// - If the note was out of key, use the preferred accidental type (or sharps if no preference).

// This table specifies the note spelling for the next note 1 or 2
// semitones away, always stepping to the next letter, as long as it is
// possible without a double-sharp or flat.
//
// Row is "letter of the previous note", column is flat/natural/sharp, final
// index is semitones to step - 1.
static const char* nextNoteStrings[7][3][2] = {
    // Ab             A               A#
    {{"A", "Bb"}, {"Bb", "B"}, {"B", "B#"}},
    // Bb             B               B#
    {{"Cb", "C"}, {"C", "C#"}, {"C#", "D"}},
    // Cb             C               C#
    {{"C", "Db"}, {"Db", "D"}, {"D", "D#"}},
    // Db             D               D#
    {{"D", "Eb"}, {"Eb", "E"}, {"E", "E#"}},
    // Eb             E               E#
    {{"Fb", "F"}, {"F", "F#"}, {"F#", "G"}},
    // Fb             F               F#
    {{"F", "Gb"}, {"Gb", "G"}, {"G", "G#"}},
    // Gb             G               G#
    {{"G", "Ab"}, {"Ab", "A"}, {"A", "A#"}},
};

// This table is similar to nextNoteStrings, but previous letter
// is never sharp, and result is never sharp.
static const char* nextNoteStringsFlat[7][3][2] = {
    // Ab             A
    {{"A", "Bb"}, {"Bb", "B"}},
    // Bb             B
    {{"Cb", "C"}, {"C", "Db"}},
    // Cb             C
    {{"C", "Db"}, {"Db", "D"}},
    // Db             D
    {{"D", "Eb"}, {"Eb", "E"}},
    // Eb             E
    {{"Fb", "F"}, {"F", "Gb"}},
    // Fb             F
    {{"F", "Gb"}, {"Gb", "G"}},
    // Gb             G
    {{"G", "Ab"}, {"Ab", "A"}},
};

// This table is similar to nextNoteStrings, but previous letter
// is never flat, and result is never flat.
static const char* nextNoteStringsSharp[7][2][2] = {
    // A               A#
    {{"A#", "B"}, {"B", "B#"}},
    // B               B#
    {{"C", "C#"}, {"C#", "D"}},
    // C               C#
    {{"C#", "D"}, {"D", "D#"}},
    // D               D#
    {{"D#", "E"}, {"E", "E#"}},
    // E               E#
    {{"F", "F#"}, {"F#", "G"}},
    // F               F#
    {{"F#", "G"}, {"G", "G#"}},
    // G               G#
    {{"G#", "A"}, {"A", "A#"}},
};

static const char* sharpNoteStrings[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
static const char* flatNoteStrings[] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

enum class AccidentalStyle { SHARP, FLAT, EITHER };

const char* getNewNoteString(uint8_t note, const char* prevString, uint8_t step, AccidentalStyle style) {
	// Large step: ignore the previous noteString and just pick according to preferred style.
	if (step >= 3) {
		if (style == AccidentalStyle::FLAT) {
			return flatNoteStrings[note];
		}
		else {
			return sharpNoteStrings[note];
		}
	}
	// Pull apart the previous notestring to letter and accidental.
	// Letter determines the row of the lookup table, accidental the
	// column.
	uint8_t row = prevString[0] - 'A';
	char accidental = prevString[1];
	uint8_t col;
	if (accidental == 'b') {
		col = 0;
	}
	else if (accidental == '#') {
		col = 2;
	}
	else {
		col = 1; // natural
	}
	if (style == AccidentalStyle::EITHER) {
		return nextNoteStrings[row][col][step - 1];
	}
	else if (style == AccidentalStyle::FLAT || col == 0) {
		// The col == 0 case should never happen, but let's use use the wrong style if it should happen.
		return nextNoteStringsFlat[row][col][step - 1];
	}
	else {
		return nextNoteStringsSharp[row][col - 1][step - 1];
	}
}

const char* spellNoteName(uint8_t note, const MusicalKey& key) {
	int8_t noteDegree = key.degreeOf(note);
	if (noteDegree == 0) {
		// Root: use sharps.
		return sharpNoteStrings[note];
	}
	bool notInKey = noteDegree < 0;
	if (notInKey) {
		// If we're not in key we first enumerate the key to identify the
		// accidental style: setting noteDegree to the last note of the
		// scale accomplishes that.
		noteDegree = key.modeNotes.count() - 1;
	}
	// Start from the root note, enumerating until noteDegree, trying
	// to pick note names which step letters nicely.
	uint8_t currentNote = mod(key.rootNote, 12);
	const char* currentNoteString = sharpNoteStrings[currentNote];
	AccidentalStyle style = AccidentalStyle::EITHER;
	int8_t degree = 0;
	while (degree < noteDegree) {
		if (style == AccidentalStyle::EITHER) {
			if (currentNoteString[1] == '#') {
				style = AccidentalStyle::SHARP;
			}
			else if (currentNoteString[1] == 'b') {
				style = AccidentalStyle::FLAT;
			}
		}
		uint8_t nextNote = mod(key.rootNote + key.modeNotes[++degree], 12);
		uint8_t step = mod(nextNote - currentNote, 12);
		currentNoteString = getNewNoteString(nextNote, currentNoteString, step, style);
		currentNote = nextNote;
	}
	// Done! If our note was not in-key, pick the style this key uses.
	if (notInKey) {
		if (style == AccidentalStyle::FLAT) {
			return flatNoteStrings[note];
		}
		else {
			return sharpNoteStrings[note];
		}
	}
	// For in-key currentNoteString it is.
	return currentNoteString;
}

const char* MusicalKey::getNoteString(int32_t noteCode) const {
	return spellNoteName(noteCode, *this);
}
