# Automated Stem Exporting

https://github.com/SynthstromAudible/DelugeFirmware/assets/138174805/044efe71-ac49-4c4b-bd5c-92b8eb269582

## Description

Added `STEM EXPORT`, an automated process for exporting `CLIP STEMS` while in `SONG VIEW` and `INSTRUMENT STEMS` while in `ARRANGER VIEW`. Press `SAVE + RECORD` to start exporting stems.

Now with one quick action you can start a stem export job, walk away from your Deluge and come back with a bunch of stems for all your clips and arranger instruments.

## Stems Folder

Stems get exported to a new `SAMPLES/STEMS/` folder. 

Within the `STEMS` folder, when exporting stems, a folder with the `SONG NAME` is created if it does not already exist. Unsaved songs are saved with the song name `UNSAVED`. Thus, you will have a new folder named `SAMPLES/STEMS/SONG NAME/`.

Within the `SONG NAME` folder, a folder for the type of export (e.g. `ARRANGER` or `SONG`) is created for each stem export job which contains all the WAV file recordings.

If the same SONG and EXPORT TYPE is exported more than once, a 2 digit number incremental number is appended to that export type's folder name (e.g. ARRANGER## or SONG##).

## Stem File Names

Stem's are given a meaningful name in the following format:

`ClipType_ExportType_PresetName_FileNumber.WAV`

> For example:
> 
> SYNTH_CLIP_PRESETNAME_000.WAV
> SYNTH_TRACK_PRESETNAME_000.WAV
> ARRANGEMENT.WAV

## Shortcuts to Start/Stop Stem Exporting

### Starting Stem Export

- Hold `SAVE` + Press `RECORD` while Playback and Record are disabled to launch Stem Export process
- When the stem export is finished, a dialog will appear on the display that tells you that the stem export process has finished. Press `SELECT`, `BACK` or any `PAD` on the grid to exit the dialog.
- Note 1: Stems are exported without Master (Song) FX applied
- Note 2: MIDI and CV Instruments and Clips are excluded from the stem export
- Note 3: Instruments and Clips that are `EMPTY` (e.g. they have no Notes or Audio Files) are excluded from the stem export
- Note 4: In Arranger View, any Instruments that are `MUTED` are excluded from the stem export

- You can also start the stem export via a new `EXPORT STEMS` menu found in the `SONG` menu accessible in Song and Arranger Views. Start the stem export by entering the `SONG\EXPORT STEMS\` menu and pressing `SELECT` on the menu item titled `START EXPORT`. It will exit out of the menu and display the export progress on the display.

### Cancelling Stem Export

- Press `BACK` to cancel Stem Export process
- When you cancel stem export, a dialog will appear on the screen asking you to confirm if you want to cancel the export. Press on the `SELECT` encoder to confirm that you want to cancel. Press `BACK` to exit out of the dialog and continue with stem export process.
- Note: When you press `BACK`, the stem export still continues in the background until you confirm you want to stop.

## Recording Parameters

### Recording Length
- In terms of the length of each stem recording:
  - In Arranger, a track is played until the end of the arrangement's length is reached.
  - In Song, a clip is played until the end of the longest note row with notes in it is reached.

  - If `Exporting Stems to Silence` is enabled, tails will be allowed to ring out and recording will continue past the track or clip length until silence is reached (see below).

### Silence
- Stems are recorded by default until silence is reached (mutable noise floor, ~70dB from peak) to allow for sound tails (e.g. delay, reverb) to be captured
  - This can be turned off in the stem export configuration menu located at: `SONG\EXPORT STEMS\CONFIGURE EXPORT\EXPORT TO SILENCE`
- If silence is not reached within 60 seconds of playback stopping, then the recording will stop automatically as a safety precaution.

### Normalization
- Normalization is off by default. Normalization sets the peak of the recorded stems to be at 0dB (as loud as possible without distorting).
  - Normalization can be turned on in the stem export configuration menu located at: `SONG\EXPORT STEMS\CONFIGURE EXPORT\NORMALIZATION`  

### Song FX
- Song FX are excluded by default. They can be included in the stem export configuration menu located at: `SONG\EXPORT STEMS\CONFIGURE EXPORT\SONG FX`

### Clip Stem Loop Points

- For clip stems, a loop point marker is saved with the stem file to mark the clip's loop length. This makes it easy to reload your stems and they will play back and loop as if you were playing those clip's on the deluge.

### Offline Rendering
- Offline Rendering is enabled by default. Offline rendering enables you to render and export stems faster than if you recorded playback using live audio (e.g. resampling). There are still improvements to be made to make offline rendering even faster, but it is significantly fast as is!
  - Offline rendering can be turned off in the stem export configuration menu located at: `SONG\EXPORT STEMS\CONFIGURE EXPORT\OFFLINE RENDERING`

### Export Master Arrangement
- Exporting all unmuted tracks as a single arrangement stem is disabled by default. This can be enabled in the stem export configuration menu located at: `SONG\EXPORT STEMS\CONFIGURE EXPORT\EXPORT MASTER ARRANGEMENT`

## Stem Export Menu

A new `EXPORT STEMS` menu has been added to the `SONG` menu accessible in Song and Arranger Views. 

This menu allows you to start a stem export and configure various settings related to the stem export.

- Start the stem export by entering the `SONG\EXPORT STEMS\` menu and pressing `SELECT` on the menu item titled `START EXPORT`. It will exit out of the menu and display the export progress on the display.

- Configure settings for the stem export by entering the `SONG\EXPORT STEMS\CONFIGURE EXPORT\` menu.
    - You can currently configure the following for the Stem Export:
      - `NORMALIZATION`: Normalization sets the peak of the recorded stems to be at 0dB (as loud as possible without distorting).
      - `EXPORT TO SILENCE`: Stems are recorded until silence is reached (mutable noise floor, ~70dB from peak) to allow for sound tails (e.g. delay, reverb) to be captured.
      - `SONG FX`: Stems are recorded with or without Song FX applied.
      - `OFFLINE RENDERING`: Stems are exported with offline rendering. You will not hear any audio playback when stems are being exported which is enables the stems to be rendered and exported at a faster than real-time basis.
      - `EXPORT MASTER ARRANGEMENT`: A single stem is exported for all unmuted tracks in Arranger View.

## Troubleshooting

### I have a track that won't export

#### Scenario: Track(s) get exported with only 5 seconds of audio

Several users reported that their arranger stems were not getting exported properly as they included only 5 seconds of audio.

All of these users were using offline rendering.

All of these users had complex arrangements.

Solution:

For heavy arrangements, if you encounter the above issue, we recommend turning off `Offline Rendering` in the `SONG\EXPORT STEMS\CONFIGURE EXPORT\` menu.

The problem is due to memory filling up faster when using `Offline Rendering` compared to `Online (Live) Rendering`. We hope to find a solution for this problem as soon as possible.

#### Scenario: Special characters in the track name 

One user reported that they were unable to export a track even though the stem export indicated that the track had been exported.

Solution: 

Check that the track name doesn't have any special characters. In this case, the user had a track called << Organ >>. Removing the characters "<< >>" and just naming the track "Organ" allowed the track to be exported.

### I have a track that takes much longer to export than others

#### Scenario: The track has an exceptionally long tail that doesn't not drop to silence

If you are using the `EXPORT TO SILENCE` feature, it may take longer for your track to export because the recorder is waiting for your track to become silent. Thus, you will see that playback has turned off but the record button continues to blink rapidly because it is still waiting for silence before stopping the recording.

As a safety measure, if your track does not become silent within 60 seconds of playback stopping, then the recording will stop automatically.

If you do not want to wait potentially 60 seconds, you will need to press `BACK` to cancel the stem export and save what has been recorded up to that point.

If you want to continue using the `EXPORT TO SILENCE` feature, check what might be contributing to the exceptionally long tails (e.g. delay, reverb, release, compressor). Use the `VU Meter` to check the levels when you start and stop a track. If the `VU Meter` gets stuck with pads that do not turn off, then it is an indication that you have exceptionally long tails.

### The tails of one stem recording "bleed" into another stem recording

If you are not using the `EXPORT TO SILENCE` feature, it is possible that when exporting a stem that the audio from the previous stem recording may bleed into the start of the recording of the next stem to be exported.

Other than using the `EXPORT TO SILENCE` feature, we do not have a solution for this yet. Ideally if we can find a way to cut any sustaining audio from the previous track / clip recorded that would ensure that no bleed occurs, however we have not found a way to do this yet.

## Videos

https://github.com/SynthstromAudible/DelugeFirmware/assets/138174805/77bb8dfc-8b39-408d-8688-fc43eb7be593

https://github.com/SynthstromAudible/DelugeFirmware/assets/138174805/c48d0ab8-656f-427a-99c0-f7c4076b06ca

https://github.com/SynthstromAudible/DelugeFirmware/assets/138174805/c00e69c6-96a6-4b25-94ed-abcf1a0088f4
