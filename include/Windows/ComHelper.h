// ComHelper.h
// Created by Caner Korkmaz on 2/7/2017.
// Copyright 2017 Caner Korkmaz
//

#ifndef SOCKETPLAY_COMHELPER_H
#define SOCKETPLAY_COMHELPER_H

#include <windows.h>

#include <memory>

#include <audioclient.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <comdef.h>
#include <wrl/client.h>
#include "Logger.h"

namespace socketplay::windows{

using Microsoft::WRL::ComPtr;

inline void throw_if_failed_impl(HRESULT hr, const char* filename, int line, const char* func) {
  if (FAILED(hr)) {
    detail::log("ERROR", filename, line, func) << "Com Error!\n";
    throw _com_error(hr);
  }
}
#define throw_if_failed(hr) throw_if_failed_impl( (hr), __FILE__, __LINE__, __func__ )

class CoContext {
 public:
  CoContext() {
    if (context_count_==0) {
      throw_if_failed(CoInitialize(nullptr));
    }
    ++context_count_;
  }

  ~CoContext() noexcept(true) {
    if (context_count_!=0 && --context_count_==0) {
      CoUninitialize();
    }
  }

  CoContext(const CoContext &context) {
    ++context_count_;
  };
  CoContext &operator=(const CoContext &context) {
    ++context_count_;
    return *this;
  };
  CoContext(CoContext &&context) noexcept(true) {

  };
  CoContext &operator=(CoContext &&context) noexcept(true) {
    return *this;
  };

 private:
  static size_t context_count_;
};

template<typename T>
struct CoTaskMemDeleter {
  void operator()(T *element) {
    CoTaskMemFree(element);
  }
};

template<typename T>
using co_taskmem_ptr = std::unique_ptr<T, CoTaskMemDeleter<T>>;

template<typename T>
co_taskmem_ptr<T> co_make_unique(T *t) {
  return co_taskmem_ptr<T>(t);
}

ComPtr<IMMDeviceEnumerator> get_device_enumerator(DWORD cls_context = CLSCTX_ALL, LPUNKNOWN unknown_outer = nullptr);
ComPtr<IMMDevice> get_default_audio_endpoint(const ComPtr<IMMDeviceEnumerator> &enumerator, EDataFlow flow, ERole role);
ComPtr<IAudioClient> activate_audio_client_from_endpoint(const ComPtr<IMMDevice> &endpoint,
                                                         DWORD cls_context = CLSCTX_ALL);

}

#endif //SOCKETPLAY_COMHELPER_H
