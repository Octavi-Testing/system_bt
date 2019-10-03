/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <unordered_map>

#include "l2cap/classic_dynamic_channel_service.h"
#include "l2cap/internal/classic_dynamic_channel_service_impl.h"
#include "l2cap/psm.h"
#include "os/handler.h"
#include "os/log.h"

namespace bluetooth {
namespace l2cap {
namespace internal {

class ClassicDynamicChannelServiceManagerImpl {
 public:
  explicit ClassicDynamicChannelServiceManagerImpl(os::Handler* l2cap_layer_handler)
      : l2cap_layer_handler_(l2cap_layer_handler) {}

  virtual ~ClassicDynamicChannelServiceManagerImpl() = default;
  //
  // All APIs must be invoked in L2CAP layer handler
  //
  virtual void Register(Psm psm, ClassicDynamicChannelServiceImpl::PendingRegistration pending_registration);
  virtual void Unregister(Psm psm, ClassicDynamicChannelService::OnUnregisteredCallback callback, os::Handler* handler);
  virtual bool IsServiceRegistered(Psm psm) const;
  virtual ClassicDynamicChannelServiceImpl* GetService(Psm psm);

  virtual std::vector<std::pair<Psm, ClassicDynamicChannelServiceImpl*>> GetRegisteredServices();
  //
 private:
  os::Handler* l2cap_layer_handler_ = nullptr;
  std::unordered_map<Psm, ClassicDynamicChannelServiceImpl> service_map_;
};
}  // namespace internal
}  // namespace l2cap
}  // namespace bluetooth
