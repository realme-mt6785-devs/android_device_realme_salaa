#include <android/media/IAudioTrack.h>
#include <android/media/IAudioTrackCallback.h>
#include <gui/SurfaceComposerClient.h>
#include <media/AudioTrack.h>
#include <media/stagefright/MediaMuxer.h>

#include "LegacyCallbackWrapper.h"

using namespace android;

extern "C" {

void _ZN7android10AudioTrackC1E19audio_stream_type_tj14audio_format_t20audio_channel_mask_tRKNS_2spINS_7IMemoryEEE20audio_output_flags_tRKNS_2wpINS0_19IAudioTrackCallbackEEEi15audio_session_tNS0_13transfer_typeEPK20audio_offload_info_tRKNS_7content22AttributionSourceStateEPK18audio_attributes_tbf(
    void *thisptr, audio_stream_type_t streamType, uint32_t sampleRate,
    audio_format_t format, audio_channel_mask_t channelMask, size_t frameCount,
    audio_output_flags_t flags,
    const android::wp<android::AudioTrack::IAudioTrackCallback> &cbf,
    int32_t notificationFrames, audio_session_t sessionId,
    android::AudioTrack::transfer_type transferType,
    const audio_offload_info_t *offloadInfo,
    const AttributionSourceState &attributionSource,
    const audio_attributes_t *pAttributes, bool doNotReconnect,
    float maxRequiredSpeed, audio_port_handle_t selectedDeviceId);

void _ZN7android10AudioTrackC1E19audio_stream_type_tj14audio_format_t20audio_channel_mask_tm20audio_output_flags_tPFviPvS5_ES5_i15audio_session_tNS0_13transfer_typeEPK20audio_offload_info_tRKNS_7content22AttributionSourceStateEPK18audio_attributes_tbfi(
    void *thisptr, audio_stream_type_t streamType, uint32_t sampleRate,
    audio_format_t format, audio_channel_mask_t channelMask, size_t frameCount,
    audio_output_flags_t flags, android::AudioTrack::legacy_callback_t cbf,
    void *user, int32_t notificationFrames, audio_session_t sessionId,
    android::AudioTrack::transfer_type transferType,
    const audio_offload_info_t *offloadInfo,
    const AttributionSourceState &attributionSource,
    const audio_attributes_t *pAttributes, bool doNotReconnect,
    float maxRequiredSpeed, audio_port_handle_t selectedDeviceId) {
  android::wp<LegacyCallbackWrapper> cbfWrapper =
      new LegacyCallbackWrapper(cbf, user);
  _ZN7android10AudioTrackC1E19audio_stream_type_tj14audio_format_t20audio_channel_mask_tRKNS_2spINS_7IMemoryEEE20audio_output_flags_tRKNS_2wpINS0_19IAudioTrackCallbackEEEi15audio_session_tNS0_13transfer_typeEPK20audio_offload_info_tRKNS_7content22AttributionSourceStateEPK18audio_attributes_tbf(
      thisptr, streamType, sampleRate, format, channelMask, frameCount, flags,
      cbfWrapper, notificationFrames, sessionId, transferType, offloadInfo,
      attributionSource, pAttributes, doNotReconnect, maxRequiredSpeed,
      selectedDeviceId);
}
}