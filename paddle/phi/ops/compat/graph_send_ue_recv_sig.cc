/* Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "paddle/phi/core/compat/op_utils.h"

namespace phi {

KernelSignature GraphSendUERecvOpArgumentMapping(
    const ArgumentMappingContext& ctx) {
  if (ctx.HasInput("Out_size")) {
    return KernelSignature("send_ue_recv",
                           {"X", "Y", "Src_index", "Dst_index"},
                           {"message_op", "reduce_op", "Out_size"},
                           {"Out", "Dst_count"});
  } else {
    return KernelSignature("send_ue_recv",
                           {"X", "Y", "Src_index", "Dst_index"},
                           {"message_op", "reduce_op", "out_size"},
                           {"Out", "Dst_count"});
  }
}

KernelSignature GraphSendUERecvGradOpArgumentMapping(
    const ArgumentMappingContext& ctx) {
  return KernelSignature(
      "send_ue_recv_grad",
      {"X", "Y", "Src_index", "Dst_index", "Out", "Dst_count", "Out@GRAD"},
      {"message_op", "reduce_op"},
      {"X@GRAD", "Y@GRAD"});
}

}  // namespace phi

PD_REGISTER_BASE_KERNEL_NAME(graph_send_ue_recv, send_ue_recv);
PD_REGISTER_BASE_KERNEL_NAME(graph_send_ue_recv_grad, send_ue_recv_grad);

PD_REGISTER_ARG_MAPPING_FN(graph_send_ue_recv,
                           phi::GraphSendUERecvOpArgumentMapping);

PD_REGISTER_ARG_MAPPING_FN(graph_send_ue_recv_grad,
                           phi::GraphSendUERecvGradOpArgumentMapping);
