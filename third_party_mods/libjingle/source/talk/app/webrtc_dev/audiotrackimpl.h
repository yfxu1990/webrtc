/*
 * libjingle
 * Copyright 2011, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TALK_APP_WEBRTC_AUDIOTRACKIMPL_H_
#define TALK_APP_WEBRTC_AUDIOTRACKIMPL_H_

#include <string>

#include "talk/app/webrtc_dev/notifierimpl.h"
#include "talk/app/webrtc_dev/scoped_refptr.h"
#include "talk/app/webrtc_dev/mediastream.h"
#ifdef WEBRTC_RELATIVE_PATH
#include "modules/audio_device/main/interface/audio_device.h"
#else
#include "third_party/webrtc/files/include/audio_device.h"
#endif

namespace webrtc {

class AudioTrack : public NotifierImpl<LocalAudioTrackInterface> {
 public:
  // Creates an audio track. This can be used in remote media streams.
  // For local audio tracks use CreateLocalAudioTrack.
  static scoped_refptr<AudioTrackInterface> Create(const std::string& label,
                                          uint32 ssrc);

  // Get the AudioDeviceModule associated with this track.
  virtual AudioDeviceModule* GetAudioDevice();

  // Implement MediaStreamTrack
  virtual const char* kind() const; 
  virtual const std::string& label() const { return label_; }
  virtual TrackType type() const { return kAudio; }
  virtual uint32 ssrc() const { return ssrc_; }
  virtual TrackState state() const { return state_; }
  virtual bool enabled() const { return enabled_; }
  virtual bool set_enabled(bool enable);
  virtual bool set_ssrc(uint32 ssrc);
  virtual bool set_state(TrackState new_state);

 protected:
  AudioTrack(const std::string& label, uint32 ssrc);
  AudioTrack(const std::string& label, AudioDeviceModule* audio_device);

 private:
  bool enabled_;
  std::string label_;
  uint32 ssrc_;
  TrackState state_;
  scoped_refptr<AudioDeviceModule> audio_device_;
};

}  // namespace webrtc

#endif  // TALK_APP_WEBRTC_AUDIOTRACKIMPL_H_
