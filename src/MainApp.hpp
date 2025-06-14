/*
 * BSD 2-Clause License
 *
 * Copyright (c) 2025, Christoph Neuhauser
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MAINAPP_HPP
#define MAINAPP_HPP

#include <chrono>

#include <Utils/SciVis/SciVisApp.hpp>
#include <Graphics/OpenGL/Shader.hpp>

class MainApp : public sgl::SciVisApp {
public:
    MainApp();
    ~MainApp() override;
    void setUseHangCheckMode(bool _useHangCheckMode);
    void render() override;
    void renderGui() override;
    void update(float dt) override;
    void resolutionChanged(sgl::EventPtr event) override;

private:
    void reloadDataSet() override {}

    using time_point_t = std::invoke_result<decltype(std::chrono::high_resolution_clock::now)>::type;
    bool useHangCheckMode = true;
    bool isFirstFrame = true;
    bool appHasHung = false;
    const uint64_t MAX_NUM_MS_RUN = 20000;
    time_point_t timeLastFrame;
    time_point_t timeAppStart;
    sgl::ShaderProgramPtr testShaderProgram;
    sgl::GeometryBufferPtr testBuffer;
};

#endif //MAINAPP_HPP
