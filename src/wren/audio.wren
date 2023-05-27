// @class: Sound
// @desc: A class that handles audio playback
class Sound {
    // @ctor: open a ogg file
    // @desc: Open a file
    construct load_ogg(file) {
        _id = Sound.internal_load_ogg(file)

        if (_id < 0) {
            Fiber.abort("Failed to load ogg file %(file)")
        }
    }

    // @method: play
    // @desc: Plays the audio, default settings
    play() { Sound.internal_play(_id, 1.0, 1.0, 1.0) }

    // @method: play
    // @desc: Plays the audio, with settings
    // @param: volume - the volume to play the audio at
    // @param: pitch - the pitch to play the audio at
    // @param: pan - the pan to play the audio at
    play(volume, pitch, pan) {
        Sound.internal_play(_id, volume, pitch, pan)
    }

    // Load a ogg file internal, return a id
    foreign static internal_load_ogg(file)
    // Play a sound
    foreign static internal_play(id, volume, pitch, pan)
}
