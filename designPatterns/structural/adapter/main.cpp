#include <iostream>
#include <string>

// Target Interface
class AudioPlayer {
public:
    virtual void play(const std::string& audioFile) const = 0;
    virtual ~AudioPlayer() = default;
};

// Adaptee
class LegacyAudioPlayer {
public:
    void playWAV(const std::string& wavFile) const {
        std::cout << "Playing WAV file: " << wavFile << std::endl;
    }
};

// Adapter
class AudioPlayerAdapter : public AudioPlayer {
private:
    LegacyAudioPlayer legacyPlayer;

public:
    void play(const std::string& audioFile) const override {
        if (audioFile.substr(audioFile.find_last_of(".") + 1) == "wav") {
            std::cout << "Converting WAV to MP3..." << std::endl;
            legacyPlayer.playWAV(audioFile);
        } else {
            std::cout << "Playing MP3 file: " << audioFile << std::endl;
        }
    }
};

// Example Usage
int main() {
    AudioPlayer* player = new AudioPlayerAdapter();

    player->play("song.mp3");
    player->play("track.wav");

    delete player;
    return 0;
}