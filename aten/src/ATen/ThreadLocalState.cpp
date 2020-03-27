#include <ATen/ThreadLocalState.h>

#if !defined(CAFFE2_IS_XPLAT_BUILD) && !defined(C10_MOBILE)
#include <ATen/core/grad_mode.h>
#endif

namespace at {

ThreadLocalState::ThreadLocalState()
    : dispatch_key_(c10::impl::tls_local_dispatch_key_set()),
#if !defined(CAFFE2_IS_XPLAT_BUILD) && !defined(C10_MOBILE)
      grad_mode_enabled_(GradMode::is_enabled()),
#endif
      debug_info_(ThreadLocalDebugInfo::_current()) {}

/* static */
void ThreadLocalState::setThreadLocalState(
    const ThreadLocalState& state) {
#if !defined(CAFFE2_IS_XPLAT_BUILD) && !defined(C10_MOBILE)
  GradMode::set_enabled(state.grad_mode_enabled_);
#endif

  c10::impl::_force_tls_local_dispatch_key_set(state.dispatch_key_);

  ThreadLocalDebugInfo::_forceCurrentDebugInfo(state.debug_info_);
}

} // namespace torch