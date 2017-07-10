// ComHelper.cpp
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//
#include "Windows/ComHelper.h"

using namespace socketplay::windows;

size_t CoContext::context_count_ = 0;

ComPtr<IMMDeviceEnumerator> socketplay::windows::get_device_enumerator(DWORD cls_context, LPUNKNOWN unknown_outer){
  ComPtr<IMMDeviceEnumerator> enumerator;
  throw_if_failed(CoCreateInstance(__uuidof(MMDeviceEnumerator), unknown_outer, CLSCTX_ALL, IID_PPV_ARGS(&enumerator)));

  return enumerator;
}
ComPtr<IMMDevice> socketplay::windows::get_default_audio_endpoint(const ComPtr<IMMDeviceEnumerator>& enumerator, EDataFlow flow, ERole role) {
  ComPtr<IMMDevice> device;
  throw_if_failed(enumerator->GetDefaultAudioEndpoint(flow, role, device.GetAddressOf()));
  return device;
}
ComPtr<IAudioClient> socketplay::windows::activate_audio_client_from_endpoint(const ComPtr<IMMDevice> &endpoint, DWORD cls_context) {
  ComPtr<IAudioClient> audio_client;
  throw_if_failed(endpoint->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                                   reinterpret_cast<void **>(audio_client.GetAddressOf())));

  return audio_client;
}

