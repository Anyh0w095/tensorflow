/* Copyright 2022 The OpenXLA Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "xla/python/util.h"

#include <memory>
#include <utility>
#include <vector>

#include "xla/pjrt/pjrt_client.h"
#include "xla/pjrt/pjrt_future.h"
#include "xla/python/ifrt/array.h"
#include "xla/status.h"
#include "xla/util.h"

namespace xla {

Status AwaitBuffersReady(ifrt::Array* ifrt_array) {
  Status s = ifrt_array->GetReadyFuture().Await();
  if (!s.ok()) {
    // Fix up error string because some clients rely on it.
    if (s.message() == "GetReadyFuture() called on deleted or donated buffer") {
      s = InvalidArgument(
          "BlockHostUntilReady() called on deleted or donated buffer");
    }
  }
  return s;
}

}  // namespace xla
