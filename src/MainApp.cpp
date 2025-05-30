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

#include <Graphics/Renderer.hpp>
#include <Graphics/Shader/ShaderManager.hpp>

#include "MainApp.hpp"

void openglErrorCallback() {
    std::cerr << "Application callback" << std::endl;
}

MainApp::MainApp() {
    useDockSpaceMode = false;
    useLinearRGB = false;

    sgl::Renderer->setErrorCallback(&openglErrorCallback);
    sgl::Renderer->setDebugVerbosity(sgl::DEBUG_OUTPUT_CRITICAL_ONLY);
    resolutionChanged(sgl::EventPtr());

    testShaderProgram = sgl::ShaderManager->getShaderProgram({"TestShader.Compute"});
    testBuffer = sgl::Renderer->createGeometryBuffer(
        4096 * sizeof(uint32_t), sgl::SHADER_STORAGE_BUFFER, sgl::BUFFER_DYNAMIC);
}

MainApp::~MainApp() {
}

void MainApp::render() {
    SciVisApp::preRender();
    SciVisApp::prepareReRender();

    sgl::ShaderManager->bindShaderStorageBuffer(0, testBuffer);
    testShaderProgram->dispatchCompute(1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    SciVisApp::postRender();
}

void MainApp::renderGui() {
}

void MainApp::update(float dt) {
    SciVisApp::update(dt);
}

void MainApp::resolutionChanged(sgl::EventPtr event) {
    SciVisApp::resolutionChanged(event);
}
