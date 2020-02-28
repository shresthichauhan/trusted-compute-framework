/* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <string>

#include "file_io.h"
#include "file_io_wrapper.h"

std::string Read(std::string file_name) {
    FileIoExecutor file_io;
    uint32_t file_handler_id = file_io.GetIoHandlerId("tcf-base-file-io");

    file_io.SetIoHandlerId(file_handler_id);
    file_io.SetFileName(file_name);
    std::string result;
    std::string out_buf;

    size_t result_size = file_io.GetMaxIoResultSize();
    size_t out_buf_size = file_io.GetMaxFileSize();

    result.reserve(result_size);
    out_buf.reserve(out_buf_size);
    uint32_t status = file_io.FileRead((uint8_t *)result.c_str(), result_size,
        (uint8_t *)out_buf.c_str(), out_buf_size);
    if (status == 0) {
        return out_buf.c_str(); 
    }
    return "";    
}

uint32_t Write(std::string file_name, std::string data) {
    FileIoExecutor file_io;
    uint32_t file_handler_id = file_io.GetIoHandlerId("tcf-base-file-io");
    file_io.SetIoHandlerId(file_handler_id);
    file_io.SetFileName(file_name);
    std::string result;

    size_t result_size = file_io.GetMaxIoResultSize();
    result.reserve(result_size);

    uint32_t status = file_io.FileWrite((uint8_t *)result.c_str(), result_size,
        (const uint8_t *)data.c_str(), data.length());
    return status;
}

uint32_t Delete(std::string file_name) {
    FileIoExecutor file_io;
    uint32_t file_handler_id = file_io.GetIoHandlerId("tcf-base-file-io");
    file_io.SetIoHandlerId(file_handler_id);
    file_io.SetFileName(file_name);
    std::string result;
    size_t result_size = file_io.GetMaxIoResultSize();
    result.reserve(result_size);

    uint32_t status = file_io.FileDelete((uint8_t *)result.c_str(), result_size);
    return status;
}
